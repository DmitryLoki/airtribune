<?php
/**
 * @file
 * ent_traker_model.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_traker_model_eck_entity_type_info() {
$items = array(
       'ent_traker_model' => array(
  'name' => 'ent_traker_model',
  'label' => 'Traker model',
  'properties' => array(
    'title' => array(
      'label' => 'Title',
      'type' => 'text',
      'behavior' => 'title',
    ),
  ),
),
  );
  return $items;
}
