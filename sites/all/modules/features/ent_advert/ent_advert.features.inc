<?php
/**
 * @file
 * ent_advert.features.inc
 */

/**
 * Implements hook_eck_entity_type_info().
 */
function ent_advert_eck_entity_type_info() {
  $items = array(
    'ent_advert' => array(
      'name' => 'ent_advert',
      'label' => 'Advertisement',
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
