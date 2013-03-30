<?php

/**
 * @file
 * Field Collection Item translation handler for the translation module.
 */


/**
 * Field Collection Item translation handler.
 *
 * Overrides default behaviours for Field Collection Item properties.
 */
class EntityTranslationFieldCollectionItemHandler extends EntityTranslationDefaultHandler {

  public function __construct($entity_type, $entity_info, $entity) {
    parent::__construct('field_collection_item', $entity_info, $entity);
  }

  public function getAccess($op) {
    return field_collection_item_access($op, $this->entity);
  }
}
