<?php

/**
 * Remote entity query base class.
 *
 * This is currently very roughly sketched out. This draws inspiration from
 * both EntityFieldQuery and the Views query builder.
 *
 * The idea is that:
 *  - entity_load goes via the controller, and loads from the local tables first
 *    if it can, and then runs a remote query.
 *  - a remote query can also be run. Unlike EntityFieldQuery, this retrieves
 *    full entities, which should then be cached for future entity_load() calls.
 */
abstract class RemoteEntityQuery {

  // TODO: flesh out the common parts of the query that child classes implement.

  /**
   * The query's base entity type.
   */
  public $base_entity_type;

  /**
   * The query's remote base.
   */
  public $remote_base;

  /**
   * The entity info of the base entity.
   */
  public $entity_info;

  /**
   * The connection to connect with.
   */
  public $connection;

  /**
   *  Constructor: sets the connection.
   *
   * @param $connection
   *  A connection of type clients_connection_ms_dynamics_soap.
   */
  function __construct($connection) {
    $this->connection = $connection;
  }

  /**
   * Set the base entity of the query.
   *
   * @param $entity_type
   *  The local entity type.
   */
  function base($entity_type) {
    $this->base_entity_type = $entity_type;
    $this->entity_info = entity_get_info($entity_type);

    // Set the remote base, based on the remote entity definition.
    $this->remote_base = $this->entity_info['remote base table'];
  }

}

/**
 * Abstract class to hold methods common to insert and update queries.
 */
abstract class RemoteEntitySaveQuery extends RemoteEntityQuery {

  /**
   * The entity to insert or update.
   */
  public $entity;

  /**
   * Set the entity to save.
   *
   * This takes care of calling base().
   *
   * @param $entity_type
   *  The entity type.
   * @param $entity
   *  The entity to save.
   */
  function setEntity($entity_type, $entity) {
    $this->base($entity_type);

    $this->entity = $entity;
  }

}

/**
 * Abstract parent class for insert queries.
 */
abstract class RemoteEntityInsertQuery extends RemoteEntitySaveQuery {

}

/**
 * Abstract parent class for update queries.
 */
abstract class RemoteEntityUpdateQuery extends RemoteEntitySaveQuery {

  /**
   * An array of remote properties to send in an update.
   *
   * Implementing classes are not obliged to support this, and may instead opt
   * to always send the entirety of the data.
   */
  protected $update_fields = array();

  /**
   * Add a field to update.
   *
   * @param $field_name
   *  The name of the property that maps to the field on the remote entity.
   */
  function addField($field_name) {
    $property_map = $this->entity_info['property map'];

    $this->update_fields[] = $property_map[$field_name];
  }

  /**
   * Add multiple fields to update.
   *
   * @param $field_names
   *  An array of the names of properties that map to fields on the remote
   *  entity.
   */
  function addFields($field_names) {
    $property_map = $this->entity_info['property map'];

    foreach ($field_names as $field_name) {
      $this->update_fields[] = $property_map[$field_name];
    }
  }

}

/**
 * Abstract parent class for bulk save queries.
 *
 * Bulk save queries are expected to handle both insert and update operations.
 */
abstract class RemoteEntityBulkSaveQuery extends RemoteEntitySaveQuery {

  /**
   * An array of remote properties to send in an update.
   *
   * Implementing classes are not obliged to support this, and may instead opt
   * to always send the entirety of the data.
   */
  protected $update_fields = array();

  /**
   * Set the entities to save.
   *
   * This takes care of calling base().
   *
   * @param $entity_type
   *  The entity type.
   * @param $entities
   *  An array of entities to save, keyed by entity ID.
   */
  function setEntities($entity_type, $entities) {
    $this->base($entity_type);

    $this->entities = $entities;
  }

  /**
   * Add multiple fields to update.
   *
   * @param $field_names
   *  An array of the names of properties that map to fields on the remote
   *  entity.
   */
  function addFields($field_names) {
    $property_map = $this->entity_info['property map'];

    foreach ($field_names as $field_name) {
      $this->update_fields[] = $property_map[$field_name];
    }
  }

}
