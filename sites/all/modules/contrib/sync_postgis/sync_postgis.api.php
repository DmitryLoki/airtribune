<?php

/**
 * @file
 * Hooks provided by the Sync PostGIS module.
 */

/**
 * @addtogroup hooks
 * @{
 */
 
/**
 * Return the schemas for the tables your module adds to Sync PostGIS.
 *
 * Any tables you define with this hook will automatically get created when the
 * "Ensure PostGIS tables and indexes exist" button is clicked at
 * admin/config/settings/sync-postgis/db.
 */
function hook_sync_postgis_schemas() {
  // Grab the array of field type structures to use in our schema definition.
  $db_field_types = sync_postgis_db_field_types();
  $schemas['my_table'] = array(
    'description' => 'Holds some extra information for the entities in Sync PostGIS',
    'fields' => array(
      'entity_type' => array(
        'description' => 'The entity type, e.g. node, taxonomy_term'
      )
      + $db_field_types['text'],
      'eid' => array(
        'description' => 'The entity id'
      )
      + $db_field_types['integer'],
      'my_field' => array(
        'description' => 'Description of my field'
      )
      + $db_field_types['text'],
      'my_other_field' => array(
        'description' => 'Description of my other field'
      )
      + $db_field_types['integer'],
    ),
    // // This table has a one-to-one relationship with the entity table.
    'primary key' => array('eid', 'entity_type'),
    'foreign keys' => array(
      'entity_id' => array(
        'table' => SYNC_PG_ENTITY_TABLE,
        'columns' => array('entity_type' => 'entity_type', 'eid' => 'eid'),
      ),
    ),
    // This table also has a geometry column.
    'geometry columns' => array(
      'my_geom' => array(
        'srid' => 4326,
        'type' => 'GEOMETRY',
        'dimensions' => 2
      )
    )
  );
  return $schemas;
}

/**
 * @} End of "addtogroup hooks".
 */
