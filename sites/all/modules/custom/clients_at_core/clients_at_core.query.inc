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

  /**
   * Add a condition to the query.
   * Based on EntityFieldQuery::entityCondition().
   */
  function entityCondition($name, $value, $operator = NULL) {
    if ($name == 'entity_id') {
      $this->retrieve_multiple = FALSE;
      $field = $this->entity_info['remote entity keys']['remote id'];
      $this->id_condition = $value;
    }
    else {
      $this->conditions[$this->remote_base][] = array(
        'field' => $field,
        'value' => $value,
        'operator' => $operator,
      );
    }
  }

  /**
   * Execute query and get the result.
   */
  function execute() {
    $entity_info = $this->entity_info;

    // $url = 'user/' . $pers-id . '/' . $this->id_condition;
    $url = 'node/' . $this->id_condition;
    $response = $this->connection->makeRequest($url , 'GET');
    // Debug mode output.
    $this->connection->debug(print_r($response));

    return $response;
  }
}


class ATCoreInsertQuery extends RemoteEntityInsertQuery {

  public $table_info;

  function __construct($connection) {
    parent::__construct($connection);
    $this->table_info = remote_entity_get_query_table_info($connection->name);
  }

  function execute() {
    $entity_info = $this->entity_info;
    $data = json_encode(get_object_vars($this->entity));
    $response = $this->connection->makeRequest($this->endpoint, 'POST', $data);
    $this->connection->debug(print_r($response));
    return $response;
  }
}


class ATCoreUpdateQuery extends RemoteEntityUpdateQuery {

  public $table_info;

  function __construct($connection) {
    parent::__construct($connection);
    $this->table_info = remote_entity_get_query_table_info($connection->name);
  }

  function execute() {
    $entity_info = $this->entity_info;
    $data = json_encode(get_object_vars($this->entity));
    $response = $this->connection->makeRequest($this->endpoint, 'PUT', $data);
    $this->connection->debug(print_r($response));
    return $response;
  }
}


class ATCoreDeleteQuery extends RemoteEntitySaveQuery {

  function execute() {
    $entity_info = $this->entity_info;
    $response = $this->connection->makeRequest($this->endpoint, 'DELETE');
    $this->connection->debug(print_r($response));
    return $response;
  }
}

