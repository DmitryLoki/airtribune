<?php
/**
 * @file
 * ent_contest_point.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_contest_point_eck_entity_type_info() {
  $items = array(
    'ent_contest_point' => array(
      'name' => 'ent_contest_point',
      'label' => 'Contest point',
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
