<?php

/**
 * @file
 * Administrative page callbacks for the Airtribune Core API module.
 */

/**
 * General configuration form for controlling the Airtribune Core API synchronization behaviour.
 */
function at_core_sync_admin_settings() {
  $form['at_core_sync_custom_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Core API settings'),
  );
  $form['at_core_sync_custom_settings']['at_core_sync_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#default_value' => variable_get('at_core_sync_enabled', 0),
    '#description' => t('Enable integration with Core API'),
  );
  /* freezed
  $form['at_core_sync_custom_settings']['at_core_sync_cron_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Queue'),
    '#default_value' => variable_get('at_core_sync_cron_enabled', 0),
    '#description' => t('Queue requests when Core API is unreacheble'),
  );
  */
  $form['at_core_sync_custom_settings']['at_core_sync_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Core API address'),
    '#default_value' => variable_get('at_core_sync_address', 'http://api.airtribune.com'),
    '#size' => 30,
    '#description' => t('For example: http://api.airtribune.com'),
  );

  $form['at_core_sync_custom_settings']['at_core_sync_version'] = array(
    '#type' => 'select',
    '#title' => t('Core API version'),
    '#multiple' => FALSE,
    '#options' => array(
      'v0.1' => 'v0.1',
      'v0.1.2' => 'v0.1.2',
    ),
    '#default_value' => variable_get('at_core_sync_version', 'v0.1'),
    '#description' => t('For example: v0.1, v0.1.2'),
  );

  $entities = entity_get_info();
  $options = array();
  foreach ($entities as $name => $info) {
    foreach ($info['bundles'] as $bname => $bundle) {
      $options[$name][$bname] = $bundle['label'];
    }
    $options[$name]['#title'] = isset($info['plural label']) ? $info['plural label'] : $info['label'];
  }

  $form['at_core_sync_custom_settings']['at_core_bundles'] = array(
    '#type' => 'nested_checkboxes',
    '#options' => $options,
    '#title' => t('Bundles that need sync'),
    '#title_display' => 'after',
    '#default_value' => variable_get('at_core_bundles'),
  );

  $form['#submit'] = array('at_core_sync_field');
  return system_settings_form($form);
}

function at_core_sync_field($form, &$form_state) {
  $values = $form_state['values']['at_core_bundles'];
  $field_info = field_info_field(AIRTRIBUNE_CORE_ID_FIELD);
  $attached = $field_info['bundles'];
  foreach ($values as $entity => $bundles) {
    if (!empty($bundles)) {
      foreach ($bundles as $bundle => $value) {
        if ((string)$value == $bundle) {
          if (!in_array($value, $attached[$entity])) {
            field_create_instance(array('field_name' => AIRTRIBUNE_CORE_ID_FIELD, 'entity_type' => $entity, 'bundle' => $bundle));
          }
        }
      }
    }
  }
}

function _at_core_page_manage() {
  if(arg(4)) 
    return _at_core_page_manage_contest(arg(4));
  $db = db_query("SELECT title, nid, status FROM {node} WHERE type = 'pg_contest' ORDER BY created DESC");
  $table = array(
    'header' => array(
      array('data' => 'CONTEST'),
      array('data' => 'CORE STATUS'),
      array('data' => 'CONFIRMED PILOTS'),
      array('data' => 'RACES'),
      array('data' => 'OPERATIONS'),
    ),
    'rows' => array(),
    'attributes' => array(),
    'colgroups' => array(),
    'sticky' => TRUE,
    'caption' => t('Contests'),
    'empty' => ''
  );
  $contests_from_core = get_contests_from_core();
  
  foreach ($db as $row) {
    $contest = node_load($row->nid);
    $stats = get_core_api_stats($contest->nid);
    $core_id = get_id_from_contest($contest);
    $status = FALSE;
    // Check status in Core
    if($core_id) {
      foreach ($contests_from_core as $id => $tmp) {
        if($tmp->id == $core_id) {
          unset($contests_from_core[$id]);
          $status = l("contest", at_core_sync_get_api_url(). '/contest/' . $core_id);
          $status .= ' ' . l("pilots", at_core_sync_get_api_url(). '/contest/' . $core_id . '/paragliders');
          $status .= ' ' . l("races", at_core_sync_get_api_url(). '/contest/' . $core_id . '/races');
        }
      }
      if (!$status) {
        $status = '<span class="error">Core API ID deprecated!</span>';
      }
    }

    $table['rows'][] = array(
      l($contest->title, 'node/' . $contest->nid . '/edit'),
      $status,
      $stats['pilots'],
      $stats['races'],
      l('Details', 'admin/config/core_api/manage/'
      . $contest->nid, array('attributes'=>array("class"=>"button")))
      . '<a class="button" href="/admin/config/core_api/batch/' . $contest->nid . '">Sync contest</a>'
      . '<a class="button" href="/admin/config/core_api/batch/' . $contest->nid . '/paragliders">Sync pilots</a>'
      . '<a class="button" href="/admin/config/core_api/batch/' . $contest->nid . '/races">Sync races</a>',
    );
  }
  if(count($contests_from_core)>0) {
    drupal_set_message(t('@count contests in Core not exist in Drupal', array('@count' => count($contests_from_core))), 'error'); 
  }
  return '<a class="button" href="#">Synchronize all</a>' . theme_table($table);
}

/**
 * Collects synchronization stats from contest().
 */
function get_core_api_stats($nid = FALSE) {
  $result = array(
    "pilots" => 0,
    "races" => 0,
    "status" => 0,    
  );
  if(!$nid)
    return $result;

  $query = new EntityFieldQuery();
  $result['pilots'] = $query
    ->entityCondition('entity_type', 'og_membership')
    ->propertyCondition('gid', $nid, '=')
    // Get only the active members
    ->propertyCondition('state', OG_STATE_ACTIVE, '=')
    // Get only confirmed pilots
    ->fieldCondition('field_pg_contestant_status', 'value', 4)
    ->count()
    ->execute();
  // Get days for contest
  $days = db_query("SELECT n.nid
  FROM {node} n JOIN {og_membership} o ON o.etid = n.nid
  WHERE n.type = 'day' AND o.gid = :gid AND o.entity_type = 'node'", array(":gid" => $nid));

  foreach ($days as $day) {
    $query = new EntityFieldQuery();
    $result['races'] += $query
      ->entityCondition('entity_type', 'ent_race')
      ->fieldCondition('field_day_ref', 'target_id', $day->nid)
      ->count()
      ->execute();
  }
  return $result;
}

function _at_core_page_manage_contest($nid) {
  $contest = node_load($nid);
  drupal_set_title(t('Synchronizing <em>@contest</em>', array('@contest'=>$contest->title)),PASS_THROUGH);

  $query = new EntityFieldQuery();
  $list['items'] = array(
    'data' => '<label>' . $contest->title . '</label>'
  );

  $pilots = array();
  $result = $query
    ->entityCondition('entity_type', 'og_membership')
    ->propertyCondition('gid', $nid, '=')
    // Get only the active members
    ->propertyCondition('state', OG_STATE_ACTIVE, '=')
    // Get only confirmed pilots
    ->fieldCondition('field_pg_contestant_status', 'value', 4)
    ->execute();

  if (!empty($result['og_membership'])) {
    $pilots = array_keys($result['og_membership']);
  }

  // Get days for contest
  $days = db_query("SELECT n.nid
  FROM {node} n JOIN {og_membership} o ON o.etid = n.nid
  WHERE n.type = 'day' AND o.gid = :gid AND o.entity_type = 'node'", array(":gid" => $nid));
  $races = array();

  // Get all races from contest
  foreach ($days as $day) {
    $query = new EntityFieldQuery();
    $result = $query
      ->entityCondition('entity_type', 'ent_race')
      ->fieldCondition('field_day_ref', 'target_id', $day->nid)
      ->execute();
    if(!empty($result['ent_race'])) {
      $races = array_merge($races, array_keys($result['ent_race']));
    }    
  }

  $core_id = get_id_from_contest($contest);
  $output = '<div class="form-actions"><a class="button" href="/admin/config/core_api/manage/' . $nid . '?">Refresh</a></div>';

  if(!empty($races)) {
    $table = array(
      'header' => array(
        array('data' => '<input type="checkbox" class="form-checkbox">', 'class' => 'select-all'),
        'RACE',
        'CORE STATUS',
        'OPERATIONS',
      ),
      'rows' => array(),
      'attributes' => array(),
      'colgroups' => array(),
      'sticky' => FALSE,
      'caption' => t('Races'),
      'empty' => ''
    );

    foreach ($races as $race) {
      $entity = array_pop(entity_load('ent_race', array($race)));
      $status = get_race_id_from_race($entity);
      $table['rows'][] = array(
        '<input type="checkbox" class="form-checkbox">',
        $entity->title,
        $status,
        '<a class="button" href="#">Check</a><a class="button" href="#">Synchronize</a>',
      );
    }
    $output .= theme_table($table) . '<div class="form-actions"><a class="button" href="#">Synchronize all races</a></div>';
  }

  if(!empty($pilots)) {
    $table = array(
      'header' => array(
        array('data' => '<input type="checkbox" class="form-checkbox">', 'class' => 'select-all'),
        'PILOT NAME',
        'CORE STATUS',
        'OPERATIONS',
      ),
      'rows' => array(),
      'attributes' => array(),
      'colgroups' => array(),
      'sticky' => FALSE,
      'caption' => t('Pilots'),
      'empty' => ''
    );
    foreach ($pilots as $pilot) {
      $entity = array_pop(entity_load('og_membership', array($pilot)));
      $person = user_load($entity->etid);      
      $person_id = get_id_from_user($person);
      $status = FALSE;
      $table['rows'][] = array(
        '<input type="checkbox" class="form-checkbox">',
        $person->name,
        $person_id,
        '<a class="button" href="#">Check</a><a class="button" href="#">Synchronize</a>',
      );
    }
    $output .= theme_table($table) . '<div class="form-actions"><a class="button" href="/admin/config/core_api/batch/' . $nid . '/paragliders">Synchronize all pilots</a></div>';
  }
  return $output;  
}

function _at_core_page_batch() {
  $batch = array(
    'operations' => array(),
    'finished' => 'batch_at_core_sync_finished',
    'title' => t('Processing Example Batch'),
    'init_message' => t('Core synch is starting.'),
    'progress_message' => t('Synchronized @current out of @total.'),
    'error_message' => t('Example Batch has encountered an error.'),
    'file' => drupal_get_path('module', 'at_core_sync') . '/at_core_sync.admin.inc',
  );
  
  $gid = arg(4);
  if($gid) {
    $batch['operations'][] = array('batch_at_core_sync_process', array("node", $gid));
    switch(arg(5)){
      case "paragliders":
        $pilots = array();
        $query = new EntityFieldQuery();
        $result = $query
          ->entityCondition('entity_type', 'og_membership')
          ->propertyCondition('gid', $gid, '=')
          // Get only the active members
          ->propertyCondition('state', OG_STATE_ACTIVE, '=')
          // Get only confirmed pilots
          ->fieldCondition('field_pg_contestant_status', 'value', 4)
          ->execute();

        if (!empty($result['og_membership'])) {
          $pilots = array_keys($result['og_membership']);
        }
        foreach($pilots as $pilot) {
          $batch['operations'][] = array('batch_at_core_sync_process', array("og_membership", $pilot));
        }
        break;
      case "races":
        // Get days for contest
        $days = db_query("SELECT n.nid
        FROM {node} n JOIN {og_membership} o ON o.etid = n.nid
        WHERE n.type = 'day' AND o.gid = :gid AND o.entity_type = 'node'", array(":gid" => $gid));
        $races = array();
      
        // Get all races from contest
        foreach ($days as $day) {
          $query = new EntityFieldQuery();
          $result = $query
            ->entityCondition('entity_type', 'ent_race')
            ->fieldCondition('field_day_ref', 'target_id', $day->nid)
            ->execute();
          if(!empty($result['ent_race'])) {
            $races = array_merge($races, array_keys($result['ent_race']));
          }    
        }
        foreach($races as $race) {
          $batch['operations'][] = array('batch_at_core_sync_process', array("ent_race", $race));
        }
        break;
    }
  } else {
    return 'Sync all';
  }
  
  batch_set($batch);
  batch_process('admin/config/core_api/manage');
}

function batch_at_core_sync_process($entity_type, $entity_id, &$context) {
  $entity = array_pop(entity_load($entity_type, array($entity_id)));
  if ($sync = _get_class_by_entity($entity, $entity_type)) {
    $sync->synchronize();
  }
  //entity_save($entity_type, $entity);
  $context['results'][] = $entity_id;
  $context['message'] = 'Synchronizing ' . (!empty($entity->title)?$entity->title:$entity->name);
}

/**
 * Batch 'finished' callback
 */
function batch_at_core_sync_finished($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = count($results) .' processed.';
    drupal_set_message($message);
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
  
}
