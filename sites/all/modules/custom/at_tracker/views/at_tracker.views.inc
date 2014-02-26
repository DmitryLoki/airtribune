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
function at_tracker_views_data_alter(&$data) {
  $fields = field_info_fields();
  foreach ($fields as $field_name => $field) {
    if ($field['type'] == 'at_tracker') {
      foreach ($field['bundles'] as $entity_type => $bundle_array) {
        $data['views_entity_' . $entity_type]['view_at_tracker'] = array(
          'title' => t('Tracker (Core API)'),
          'help' => t('Tracker (Core API)'),
          'field' => array(
            'handler' => 'views_handler_at_tracker_widget',
          ),
        );
      }
    }
  }
  return $data;
}

