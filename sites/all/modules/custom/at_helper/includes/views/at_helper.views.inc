<?php

/**
 * Implements hook_views_data().
 */
function at_helper_views_data() {
  $data = array();

  $data['views']['nothing_extended'] = array(
    'title' => t('Custom text extended'),
    'help' => t('Provide custom text based on tokens and custom logic.'),
    'field' => array(
      'handler' => 'at_helper_handler_field_custom_extended',
    ),
  );

  return $data;
}
