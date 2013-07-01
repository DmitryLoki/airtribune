<?php
/**
 * @file
 * advert_visualisation.features.inc
 */

/**
 * Implements hook_eck_bundle_info().
 */
function advert_visualisation_eck_bundle_info() {
  $items = array(
  'ent_advert_advert_visualisation' => array(
  'machine_name' => 'ent_advert_advert_visualisation',
  'entity_type' => 'ent_advert',
  'name' => 'advert_visualisation',
  'label' => 'Advertisement on visualisation page',
),
  );
  return $items;
}
