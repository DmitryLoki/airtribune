<?php
// $Id$

/**
 * A field that displays fields.
 */
class geofield_handler_field_wkt extends views_handler_field_field {
  function render($values) {
    if (isset($values->_field_data[$this->field_alias])) {
      // Prepare arguments for rendering based on the objects cached in the
      // pre-render phase and the display options for this field.
      $field_name = $this->definition['field_info']['field_name'];
      if (isset($values->_field_data[$this->field_alias]['entity']->{$field_name})) {
        $coord = $values->_field_data[$this->field_alias]['entity']->{$field_name}['und'][0];
        return check_plain($coord['wkt']);
      }
    }
    return '';
  }
}
