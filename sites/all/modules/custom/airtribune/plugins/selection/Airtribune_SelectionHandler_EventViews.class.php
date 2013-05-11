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
      $og_items = field_get_items($entity_type, $entity, AIRTRIBUNE_OG_GROUP_REF_FIELD);
      $this->group_id = isset($og_items[0]['target_id']) ? $og_items[0]['target_id'] : FALSE;
    }
    else {
      $this->group_id = FALSE;
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

}
