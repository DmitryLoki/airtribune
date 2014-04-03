<?php

/**
 * @file
 * Provides a generic entity class for remote entities.
 */

/**
 * Generic entity class for remote entities.
 *
 * This is not required, but takes care of setting the 'created' and 'changed'
 * timestamps on entities.
 */
class RemoteEntity extends Entity {

  /**
   * Permanently saves the entity.
   *
   * @see entity_save()
   */
  public function save() {
    if (!empty($this->is_new)) {
      // On a new entity, set the 'created' timestamp.
      $this->created = REQUEST_TIME;
    }

    // Set the changed timestamp in all cases.
    $this->changed = REQUEST_TIME;

    return entity_get_controller($this->entityType)->save($this);
  }

}
