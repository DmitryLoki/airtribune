<?php
/**
 * @file
 * Imlements views.inc with hook_views_data. Needed to register the extra fields
 * for the entity types with the special field handler.
 *
 * Created by JetBrains PhpStorm.
 * User: das_ricardo
 * Date: 02.12.12
 * Time: 13:33
 */

/**
 * Implements hook_views_data().
 */
function extrafield_views_integration_views_data() {
  $data = array();

  // Get all extrafields in the system that have a existing callback function
  // and are from type display.
  $extra_fields = _extrafield_views_integration_get_extra_fields();
  foreach ($extra_fields as $key => $extra_field) {
    // Get the entityInfo from the extrafield entitytype to get the base
    // table for views.
    $entity_info = entity_get_info($extra_field['entity_type']);
    if (!empty($entity_info)) {
      $data[$entity_info['base table']][$key] = array(
        'title' => t('Extrafield @label', array('@label' => $extra_field['label'])),
        'help' => t('Integrate Extrafield: @label for entity type: @entity_type', array(
          '@label' => $extra_field['label'],
          '@entity_type' => $extra_field['entity_type'],
        )),
        'field' => array(
          'handler' => 'extrafield_views_integration_handler_field_extrafield',
          'click sortable' => FALSE,
          'callback' => $extra_field['callback'],
        ),
      );
    }
  }
  return $data;
}
