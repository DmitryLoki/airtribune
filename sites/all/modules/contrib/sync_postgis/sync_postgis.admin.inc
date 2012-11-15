<?php

/**
 * Control which content types get their geofields sync'd.
 */
function sync_postgis_admin_settings() {
  $instances = field_info_instances();
  $form = array();
  $form['sync_postgis_transform_indexes'] = array(
    '#type' => 'textfield',
    '#title' => 'Commonly used SRIDs',
    '#description' => t('Comma-separated list of SRIDs for which you wish to have an index in the database'),
    '#default_value' => variable_get('sync_postgis_transform_indexes'),
  );
  foreach ($instances as $entity_type => $bundles) {
    foreach ($bundles as $bundle_name => $fields) {
      $options = array();
      $other_fields = array();
      foreach ($fields as $name => $info) {
        if ($info['widget']['module'] == 'geofield') {
          $options[$name] = $info['label'];
        }
        else {
          $other_fields[$name] = $info['label'];
        }
      }
      if (!empty($options)) {
        $form['sync_pg_' . $entity_type . '_' . $bundle_name] = array(
          '#markup' => '<h2>' . $bundle_name . '</h2>',
        );
        $form['sync_pg_enabled_' . $entity_type . '_' . $bundle_name] = array(
          '#type' => 'checkboxes',
          '#title' => t('Enable PostGIS syncing for these fields'),
          '#options' => $options,
          '#default_value' => variable_get('sync_pg_enabled_' . $entity_type . '_' . $bundle_name, array()),
          '#description' => t('Check which fields you would like sync\'d to PostGIS for this bundle'),
        );
        $form['sync_pg_fields_' . $entity_type . '_' . $bundle_name] = array(
          '#type' => 'checkboxes',
          '#title' => t('Additional data to store'),
          '#options' => $other_fields,
          '#default_value' => variable_get('sync_pg_fields_' . $entity_type . '_' . $bundle_name, array()),
          '#description' => t('Check which additional (non-geo) fields you would like to have in PostGIS for filtering or sorting on'),
        );
      }
    }

  }
  return system_settings_form($form);
}

/**
 * Form for creating PostGIS base tables and any extra bundle tables as per the
 * configuration at admin/config/system/sync-postgis.
 */
function sync_postgis_check_db_form($form, &$form_state) {
  $form = array();
  $form['description'] = array(
    '#type' => 'markup',
    '#markup' => '<div>' . t('Clicking the button below will cause the base tables in PostGIS to be created if they do not exist yet, and any required bundle tables for extra field data to be recreated. You will need to re-sync your data after this.') . '</div>',
  );
  $form['create_table'] = array(
    '#type' => 'submit',
    '#value' => 'Ensure PostGIS tables and indexes exist',
  );
  return $form;
}

/**
 * Submit handler for the DB Set-up form. Ensures the base postgis tables exist
 * plus any additional st_transform indexes on the geometry column.
 */
function sync_postgis_check_db_form_submit($form, &$form_state) {
  sync_postgis_ensure_base_tables();
  sync_postgis_create_bundle_tables();
}

function sync_postgis_ensure_base_tables() {
  $schemas = sync_postgis_get_base_schemas();
  $connection = sync_postgis_get_postgis_connection();
  // Set up the entity and entity_geom tables.
  foreach ($schemas as $table_name => $schema) {
    if (!$connection->schema()->tableExists($table_name)) {
      try {
        sync_postgis_create_table($table_name, $schema);
        drupal_set_message(t('Created table @table', array('@table' => $table_name)));
      }
      catch (Exception $e) {
        drupal_set_message(t('Could not create table @table', array('@table' => $table_name)), 'error');
        watchdog_exception('sync_postgis_tables', $e);
      }
    }
    else {
      drupal_set_message(t('Table @table already exists', array('@table' => $table_name)));
    }
  }
  // Set up whatever st_transform indexes are required.
  $srids = explode(',', variable_get('sync_postgis_transform_indexes', ''));
  if (!empty($srids)) {
    foreach ($srids as $srid) {
      $srid = trim($srid);
      if (!empty($srid)) { // Make sure it's not an empty string.
        try {
          sync_postgis_add_index('entity_geom', 'transform_' . $srid, 'gist', 'ST_Transform(geom, ' . $srid . ')');
        }
        catch (Exception $e) {
          drupal_set_message($e->getMessage(), 'error');
        }
      }
    }
  }
}

/**
 * Creates or recreates the bundle tables, based on the fields that have been
 * selected for syncing at admin/config/settings/sync-postgis
 */
function sync_postgis_create_bundle_tables() {
  $schemas = sync_postgis_get_bundle_schemas();
  // Now create our PostgGIS tables based on the schemas. If a table already
  // exists, it will be dropped and recreated.
  $connection = sync_postgis_get_postgis_connection();
  foreach ($schemas as $entity_type => $bundles) {
    foreach ($bundles as $bundle_name => $schema) {
      $table_name = sync_postgis_table_name($entity_type, $bundle_name);
      sync_postgis_drop_table($table_name);
      try {
        sync_postgis_create_table($table_name, $schema);
        drupal_set_message(t('Created table @table', array('@table' => $table_name)));
      }
      catch (Exception $e) {
        drupal_set_message(t('Could not create table @table', array('@table' => $table_name)), 'error');
        watchdog_exception('sync_postgis_tables', $e);
      }
    }
  }
}

/**
 * Bulk sync form.
 */
function sync_postgis_bulk_sync($form, &$form_state) {
  $form = array();
  $form['bulk_sync'] = array(
    '#type' => 'markup',
    '#markup' => '<div>' . t('Clicking the button below will cause all exiting content with geofields configured for syncing to be syncd to the PostGIS db.') . '</div>',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Sync all PostGis content'),
  );
  return $form;
}

/**
 * Submit function for the bulk sync form.
 */
function sync_postgis_bulk_sync_submit($form, &$form_state) {
  $instances = field_info_instances();
  $queue = DrupalQueue::get('sync_postgis_queue');
  foreach ($instances as $entity_type => $bundles) {
    foreach ($bundles as $bundle_name => $fields) {
      $enabled = array_filter(variable_get('sync_pg_enabled_' . $entity_type . '_' . $bundle_name, array()));
      if (!empty($enabled)) {
        // Add all entities of this type for processing.
        try {
          $query = new EntityFieldQuery();
          $entities = $query
            ->entityCondition('entity_type', $entity_type)
            ->entityCondition('bundle', $bundle_name)
            ->execute();

          $result = $entities[$entity_type];
          foreach ($result as $eid => $obj) {
            $item = array(
              'entity_type' => $entity_type,
              'bundle' => $bundle_name,
              'eid' => $eid,
            );
            $queue->createItem($item);
          }
          // Now schedule the vacuum analayze query to be run on the newly
          // sync'd content
          $item = array(
            'type' => 'vacuum_analyze',
          );
          $queue->createItem($item);
        }
        catch (Exception $e) {
          watchdog_exception('sync_postgis_bulk', $e);
        }
      }
    }
  }
  drupal_set_message(t('All relevant content has been queued for syncing to the PostGIS db.'));
}
