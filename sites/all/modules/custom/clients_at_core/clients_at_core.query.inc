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
    $response = $this->connection->makeRequest($this->connection->url, 'GET');
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
    $data = _query_object_to_array($this->base_entity_type, $this->entity);
    $response = $this->connection->makeRequest($this->connection->url, 'POST', $data);
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
    $data = _query_object_to_array($this->base_entity_type, $this->entity);
    $response = $this->connection->makeRequest($this->connection->url, 'PATCH', $data);
    return $response;
  }
}


class ATCoreDeleteQuery extends RemoteEntitySaveQuery {

  function execute() {
    $entity_info = $this->entity_info;
    $response = $this->connection->makeRequest($this->connection->url, 'DELETE');
    //$this->connection->debug(print_r($response));
    return $response;
  }
}

/**
 * Helper function to get more clean array of entity values, without Drupal stuff,
 * like [field_xxx][und][value] = 123
 */
function _query_object_to_array($entity_type, $entity) {
  $a = array();
  $wrapper = entity_metadata_wrapper($entity_type, $entity);
  foreach ($entity as $key => $attr) {
    // Processing of probleming fields.
    if (in_array($key, array('field_person_phone', 'field_phone', 'field_address', 'field_country'))) {
      $a[$key] = $attr['und']['0'];
    }
    // Other fields.
    elseif ((strpos($key, 'field_') !== FALSE) && is_array($attr)) {
      $a[$key] = $wrapper->{$key}->raw();
    }
    // Plain stuff.
    else {
      $a[$key] = $attr;
    }
  }
  unset($a['original']);
  unset($a['rdf_mapping']);
  $data = _convert_drupal2core($entity_type, $a);
  return $data;
}

function _convert_drupal2core($entity_type, $data) {
  if ($entity_type == 'profile2') {
    $user = user_load($data['uid']);
    $gender = array(0 => 'M', 1 => 'F');
    $core_data = array(
      'first_name' => $data['field_full_name']['given'],
      'last_name' => $data['field_full_name']['family'],
      'birthdate' => date('Y-m-d', $data['field_birthdate']),
      'gender' => $gender[$data['field_gender']],
      'country' => array('code' => $data['field_country']['iso2']),
      'uid' => $data['uid'],
      'id' => $data['remote_id'],
      'mail' => $user->mail,
    );
    return $core_data;
  }
}