<?php

/**
 * Entity handler for Views.
 *
 * @see http://drupal.org/node/1699378
 */
class Airtribune_SelectionHandler_EventViews extends EntityReference_SelectionHandler_Views {

  /**
   * Implements EntityReferenceHandler::getInstance().
   */
  public static function getInstance($field, $instance = NULL, $entity_type = NULL, $entity = NULL) {
    return new Airtribune_SelectionHandler_EventViews($field, $instance, $entity_type, $entity);
  }

  protected function __construct($field, $instance, $entity_type, $entity) {
    if (isset($entity_type, $entity)) {
      // Get group id from field value
      $og_items = field_get_items($entity_type, $entity, OG_AUDIENCE_FIELD);
      // If og reference is not set, then check entity prepopulate value
      if (!isset($og_items[0]['target_id']) && module_exists('og')) {
        $instance_og = field_info_instance($entity_type, OG_AUDIENCE_FIELD, $instance['bundle']);
        $field_og = field_info_field(OG_AUDIENCE_FIELD);
        $og_items = entityreference_prepopulate_get_values($field_og, $instance_og);
      }
      if (isset($og_items[0]['target_id'])) {
        $this->group_id = $og_items[0]['target_id'];
      }
      else {
        if (isset($entity->gid)) {
          $this->group_id = $entity->gid;
        }
        else {
          $this->group_id = FALSE;
        }
      }

      // Get entity id
      $id = entity_extract_ids($entity_type, $entity);
      if (isset($id[0])) {
        $this->eid = $id[0];
      }
    }
    $this->field = $field;
    $this->instance = $instance;
  }

  /**
   * Implements EntityReferenceHandler::getReferencableEntities().
   */
  public function getReferencableEntities($match = NULL, $match_operator = 'CONTAINS', $limit = 0) {
    foreach ($this->field['settings']['handler_settings']['view']['args'] as $key => $arg) {
      if ($arg == 'gid') {
        $this->field['settings']['handler_settings']['view']['args'][$key] = $this->group_id;
      }
      else {
        if ($arg == '[og_membership:id]') {
          $this->field['settings']['handler_settings']['view']['args'][$key] = $this->eid;
        }
      }
    }
    return parent::getReferencableEntities($match, $match_operator, $limit);
  }

  /**
   * Implements EntityReferenceHandler::settingsForm().
   */
  public static function settingsForm($field, $instance) {
    $form = parent::settingsForm($field, $instance);
    if (isset($form['view']['args'])) {
      $form['view']['args']['#description'] .= '<br/>' . t('Avaible tokens: gid - Organic group ID');
    }
    return $form;
  }

  /**
   * Implements EntityReferenceHandler::validateReferencableEntities().
   */
  function validateReferencableEntities(array $ids) {
    $display_name = $this->field['settings']['handler_settings']['view']['display_name'];
    $args = $this->field['settings']['handler_settings']['view']['args'];
    foreach ($args as $key => $arg) {
      if ($arg == 'gid') {
        $args[$key] = $this->group_id;
      }
    }
    $result = array();
    if ($this->initializeView(NULL, 'CONTAINS', 0, $ids)) {
      // Get the results.
      $entities = $this->view->execute_display($display_name, $args);
      $result = array_keys($entities);
    }
    return $result;
  }

}
