<?php

class ATCoreSelectQuery extends RemoteEntityQuery {
  /**
   * An array of conditions on the query. These are grouped by the table they are on.
   */
  public $conditions = array();

  public $fields = array();
  public $relationships = array();

  /**
   * Add a field to retrieve.
   *
   * @param $field_name
   *  The name of the field on the remote entity.
   */
  function addField($field_name) {
    $this->fields[] = $field_name;
  }

  /**
   * Add multiple fields to retrieve.
   *
   * @param $field_names
   *  An array of the names of the field on the remote entity.
   */
  function addFields($field_names) {
    foreach ($field_names as $field_name) {
      $this->fields[] = $field_name;
    }
  }
}