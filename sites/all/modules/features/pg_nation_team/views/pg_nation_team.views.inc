<?php

/**
 * @file
 * Provide views data and handlers
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function pg_nation_team_views_data_alter(&$data) {
  $data['views_entity_ent_team']['view_approve_team_leader'] = array(
    'field' => array(
      'title' => t('Approve team leader'),
      'help' => t('Approve team leader'),
      'handler' => 'views_handler_field_approve_team_leader',
    ),
  );
  return $data;
}

