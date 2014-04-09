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
function at_inline_views_data_alter(&$data) {
  $entity_types = entity_get_info();

  foreach ($entity_types as $type => $info) {
    $data['views_entity_' . $type]['views_handler_field_editable'] = array(
      'field' => array(
        'title' => t('Custom editable field'),
        'help' => t('Show editable field'),
        'handler' => 'views_handler_field_editable',
      ),
    );
  }
  return $data;
}

