<?php

/**
 * @file
 * Provide views data and handlers for node.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function airtribune_views_data_alter(&$data) {
  $data['views_entity_node']['view_confirmed_pilots'] = array(
    'field' => array(
      'title' => t('Count pilots'),
      'help' => t('Count pilots'),
      'handler' => 'views_handler_field_airtribune_count_pilots',
    ),
  );
  return $data;
}

