<?php
/**
 * @file
 * Implements the field handler class.
 *
 * Created by JetBrains PhpStorm.
 * User: das_ricardo
 * Date: 02.12.12
 * Time: 13:37
 */

class extrafield_views_integration_handler_field_extrafield extends views_handler_field_entity {

  /**
   * Overrides views_handler_field_entity::render().
   *
   * @param mixed $values
   *   The values retrieved from the database.
   */
  public function render($values) {
    $return = '';
    if (($entity = $this->get_value($values)) && entity_access('view', $this->entity_type, $entity)) {
      $return = call_user_func_array($this->definition['callback'], array('entity' => $entity));
    }
    return $return;
  }

}
