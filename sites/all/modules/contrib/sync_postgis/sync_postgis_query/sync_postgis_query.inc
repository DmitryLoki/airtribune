<?php

class syncPgQuery {

  /**
   * The database connection object to use for the query.
   * 
   * @var DatabaseConnection
   */
  private $connection;

  /**
   * The SRID to use for the query.
   *
   * @var string
   */
  private $srid = '4326';

  /**
   * The name of the entity table to use in the query.
   *
   * @var string
   */
  private $entity_table;

  /**
   * The name of the geometry table to use in the query.
   *
   * @var string
   */
  private $geom_table;

  /**
   * The name of the geometry column to use in the query.
   *
   * @var string
   */
  private $geom_column;

  /**
   * The base table for the query.
   */
  private $base_table;

  /**
   * The method of execution of the query.
   *
   * We set this to 'print' if we don't actually want it to be executed but just
   * returned as sql.
   *
   * @var string
   */
  private $exec_method = 'execute';

  /**
   * The entity type this query is concerned with, necessary for joining on a
   * bundle-specific table.
   *
   * @var string
   */
  private $entity_type = NULL;

  /**
   * The bundle this query is concerned with, necessary for joining on a
   * bundle-specific table.
   *
   * @var string
   */
  private $bundle = NULL;

  /**
   * The select query object.
   *
   * @var SelectQuery
   */
  private $query;

  /**
   * The array of placeholders being used in the query.
   *
   * @var array
   */
  private $placeholders;

  /**
   * Current placeholder index.
   */
  private $placeholder_index = 0;

  /**
   * Array of tables that have been joined to the query.
   *
   * @var array
   */
  private $joins = array();

  /**
   * The fields we want to return in the result set.
   *
   * @var array
   */
  private $return_fields = array();

  /**
   * Set this to a format, e.g. 'AsText' or 'AsGeoJSON' to return the geometry
   * in that format with the results.
   */
  private $return_geometry = NULL;

  /**
   * The filter conditions for the query.
   *
   * @var array
   */
  private $filterConditions = array();

  /**
   * The filter conditions for the query.
   *
   * @var array
   */
  private $geometryConditions = array();

  /**
   * Stores whether the query has already been built, i.e. is ready to execute.
   */
  private $built = FALSE;

  /**
   * Stores whether the query has been executed.
   */
  private $executed = FALSE;

  /**
   * Store the name of a class that is used to return the results in the
   * desired format.
   */
  private $return_strategy = 'syncPgRowReturn';

  /**
   * Stores the actual result of the query.
   */
  private $result;

  /**
   * Constructor for a syngPgQuery.
   *
   * @param $connection
   *   The DatabaseConnection object to use
   *
   * @param $srid
   *   The SRID to use
   *
   * @param $entity_table
   *   The name of the entity table in the database
   *
   * @param $geom_table
   *   The name of the geometry table in the database
   *
   * @param $geom_column
   *   The name of the geometry column in the database
   */
  public function __construct(DatabaseConnection $connection, $srid = NULL, $entity_table = SYNC_PG_ENTITY_TABLE, $geom_table = SYNC_PG_GEOMETRY_TABLE, $geom_column = SYNC_PG_GEOMETRY_COLUMN) {

    $this->connection = $connection;
    $this->entity_table = $entity_table;
    $this->geom_table = $geom_table;
    $this->geom_column = $geom_column;

    if ($srid) {
      $this->setSrid($srid);
    }

  }

  /**
   * Sets the srid to use in this query. Our geometry column uses 4326, so if
   * anything else gets passed in here, we will use st_transform in our query
   * to transform to the desired geometry.
   *
   * @param $srid
   *   A string representing the SRID to use in the query, e.g. '900913'.
   */
  public function setSrid($srid) {
    $this->srid = $srid;
  }

  /**
   * Returns the entity type being used in this query.
   */
  public function getEntityType() {
    return $this->entity_type;
  }

  /**
   * Returns the bundle being used in this query.
   */
  public function getBundle() {
    return $this->bundle;
  }

  /**
   * Sets the $entity_type and $bundle properties on the query object, allowing
   * bundle tables to be used in the query.
   */
  public function filterByBundle($entity_type, $bundle) {
    $this->entity_type = $entity_type;
    $this->bundle = $bundle;
    if (!isset($this->filterConditions['entity'])) {
      $this->filterConditions['entity'] = array();
    }
    $this->filterConditions['entity'] += array(
      array(
        'column' => 'entity_type',
        'value' => $entity_type,
        'operator' => '=',
      ),
      array(
        'column' => 'bundle',
        'value' => $bundle,
        'operator' => '=',
      ),
    );
    return $this;
  }

  /**
   * Add a condition to the query.
   *
   * @param $name
   *   Usually the table name, unless it is a bundle table condition.
   *
   * @param $column
   *   The column name.
   *
   * @param $value
   *   The value to check for.
   *
   * @param $operator
   *   The operator for the filter condition.
   *
   * @return SyncPgQuery
   *   The called object.
   */
  public function filterCondition($name, $column, $value, $operator = '=') {
    $this->filterConditions[$name][] = array(
      'column' => $column,
      'value' => $value,
      'operator' => $operator,
    );
    return $this;
  }

  /**
   * Add a geometry-based condition to the query.
   *
   * @param $type
   *   The type of condition, e.g. 'within', 'intersects'.
   *
   * @param $geom
   *   A string of wkt representing the geometry to check against
   *
   * @return SyncPgQuery
   *   The called object.
   */
  public function geometryCondition($type, $geom) {
    $this->geometryConditions[] = array(
      'type' => $type,
      'value' => $geom,
    );
    return $this;
  }

  /**
   * Add fields to be returned from the query.
   *
   * @param $fields
   *   An array of arrays of field names keyed by type, where type corresponds
   *   to a class that is responsible for the table on which to join, whose
   *   values should be included in the result set.
   *
   * @return SyncPgQuery
   *   The called object.
   */
  public function addReturnFields($fields = array()) {
    if (empty($fields)) {
      return $this;
    }
    $this->return_fields = array_merge_recursive($this->return_fields, $fields);
    return $this;
  }

  /**
   * This is just a convenience method so that client code does not have to specify
   * the name of the geometry table and geometry column.
   */
  public function returnGeometry($format = 'AsText') {
    $this->return_geometry = $format;
    return $this;
  }

  /**
   * Execute the query.
   *
   * @return
   *   The result set as an array of row objects.
   */
  public function execute() {
    // Give a chance to other modules to alter the query.
    drupal_alter('sync_pg_query', $this);
    $this->altered = TRUE;
    if (!($this->built)) {
    // Build the query
      $this->buildQuery();
    }
    return $this->finishQuery();
  }

  /**
   * Builds the query.
   *
   * @return
   *   See syncPgQuery::execute().
   */
  public function buildQuery() {
    if (is_null($this->base_table)) {
      $this->base_table = $this->entity_table;
    }
    if (is_null($this->query)) {
      // Initialise a select query on the base table.
      $this->query = $this->connection->select($this->base_table);
    }

    if (empty($this->return_fields)) {
      // Nothing has been specified to be returned by the query, so just return
      // eid, entity_type and bundle.
      $this->query->fields($this->base_table, array('eid', 'entity_type'));
    }

    foreach ($this->return_fields as $type => $fields) {
      $table_info = $this->ensureTable($type);
      $this->query->fields($table_info['table_name'], $fields);
    }

    if (isset($this->return_geometry)) {
      $this->ensureTable('geometry');
      $expr = "St_Transform({$this->geom_table}.{$this->geom_column}, {$this->srid})";

      $format = $this->return_geometry;
      $alias = 'geom';
      if ($format != 'raw') {
        $expr = "st_$format($expr)";
        $alias .= "_$format";
      }

      // Build a snippet for the geometry expression.
      $this->query->addExpression($expr, $alias);
    }

    foreach ($this->filterConditions as $type => $filters) {
      $table_info = $this->ensureTable($type);
      foreach ($filters as $condition) {
        $field = $condition['column'];
        $sql_field = "{$table_info['table_name']}." . $field;
        $this->query->condition($sql_field, $condition['value'], $condition['operator']);
        if (isset($condition['value'])) {
          $ph_key = ':db_condition_placeholder_' . $this->placeholder_index++;
          // Add information about this field to the placeholders array.
          $this->placeholders[$ph_key] = array(
            'table' => $table_info['table_name'],
            'field' => $field,
          );
        }
      }
    }

    if (!empty($this->geometryConditions)) {
      // TODO: this is currently limited to geometry conditions of the form e.g.
      // "ST_Within(geom1, geom2)" - need to make it more generic.
      $table_info = $this->ensureTable('geometry');
      foreach ($this->geometryConditions as $i => $condition) {
        // A bit of nastiness here: we cannot use a placeholder for the geometry
        // that's passed in because we have to allow for the passing in of an
        // expression to be evaluated, not just a string of wkt. For example,
        // for the geometry you might need to pass in
        // "St_MakeEnvelope([some_wkt], 4326)", and this expression must not
        // have quotes around it. Not sure if there's a better way to get around
        // this, i.e. without throwing all the anti-sql-injection goodness out
        // the window.
        $this->query->where("St_{$condition['type']}(St_Transform({$this->geom_table}.{$this->geom_column}, {$this->srid}), St_SetSrid({$condition['value']}, {$this->srid}))");
      }
    }
    $this->built = TRUE;
    // TODO: add ability to order the query.
  }

  /**
   * Finalises and executes the query.
   */
  function finishQuery() {
    // Only execute the query if $exec_method is set to 'execute'.
    $return = NULL;
    if ($this->exec_method == 'execute' && !$this->executed) {
      $result = $this->query->execute();
      $strategy_class = $this->return_strategy;
      $this->result = call_user_func_array(array($strategy_class, 'returnResult'), array($result, $this));
      $this->executed = TRUE;
    }
    return $this->result;
  }

  /**
   * Returns the string of sql for the query, with all placeholders replaced by
   * the actual values.
   *
   * @return string
   *   A string version of the query.
   */
  public function getSql() {

    // Setting the exec_method property to 'print' will prevent the query from
    // actually executing; the select query object will be stored in the query
    // property, so that we can print it out.
    $this->exec_method = 'print';
    $this->execute();
    // The schemas for the tables involved in the query will let us know whether
    // each field contains numeric data or not.
    $schemas = sync_postgis_get_base_schemas();
    if (isset($this->entity_type) && isset($this->bundle)) {
      $table_name = sync_postgis_table_name($this->entity_type, $this->bundle);
      $schemas = array_merge($schemas, array($table_name => sync_postgis_get_bundle_schemas($this->entity_type, $this->bundle)));
    }

    // Figure out whether each placeholder value should have quotes around it or
    // not.
    $arg_types = array();
    foreach ($this->placeholders as $key => $info) {
      $arg_types[$key] = 's';
      if (isset($schemas[$info['table']]['fields'][$info['field']])) {
        if (in_array($schemas[$info['table']]['fields'][$info['field']]['type'], array('int', 'decimal', 'float'))) {
          $arg_types[$key] = 'd';
        }
      }
    }

    // Running the query string through prepareQuery gets rid of the curly
    // braces around table names.
    $prepared = $this->connection->prepareQuery((string) $this->query);
    $querystring = $prepared->queryString;

    // Now match up our arguments against their placeholder names and replace
    // them into the string - this essentially throws away all the goodness
    // that protects against sql injection but there's no way around that if we
    // want to be able to print out the full sql without placeholders.
    $args = $this->query->getArguments();

    foreach ($args as $placeholder => $value) {
      $replacement = $arg_types[$placeholder] == 'd' ? $value : $this->connection->quote($value);
      $querystring = str_replace($placeholder, $replacement, $querystring);
    }
    return $querystring;
  }

  /**
   * Performs a geometry relationship query on two entities. Each entity can
   * either be passed in as an array with keys 'eid' and 'entity_type' or as an
   * array of values corresponding to ids in the entity_geom table. The latter
   * use case is for running a query on an entity during presave when it does
   * not yet have an entity id but its geometries have been added to PostGIS.
   *
   * @param $type
   *   The type of relationship to check for between the two entities, e.g.
   *   'intersects', 'within'.
   *
   * @param $item1
   *   The first item of the relationship, the syntax being e.g. "item1 intersects
   *   item2". This should be an array that either has 'eid' and 'entity_type'
   *   keys or is an indexed array of ids in the entity_geom table.
   *
   * @param $item2
   *   The second item of the relationship. See $item1 above.
   *
   * @param distance
   *   If this is a buffer query, the buffer distance to check.
   *
   * @return
   *   TRUE if the two entities have the relationship in question, FALSE if not.
   */
  public function booleanRelQuery($type, $item1, $item2, $distance = NULL) {
    // Initialise a select query on the geometry table...
    $select_query = $this->connection->select($this->geom_table, 'a');
    // ... CROSS JOIN'd with itself.
    $select_query->addJoin('CROSS', $this->geom_table, 'b');

    // Build a snippet for the relationship expression.
    $snippet = "st_$type(a." . $this->geom_column . ", b." . $this->geom_column;
    // Certain geometry relationship queries, such as ST_DWithin, have a third
    // parameter, which is the buffer distance to check.
    if (is_numeric($distance)) {
      $snippet .= ", " . $distance;
    }
    $snippet .= ")";
    $select_query->addExpression($snippet, 'booleanValue');

    // Set up the conditions. This will produce a WHERE clause like e.g.
    // "WHERE a.eid = 5 AND a.entity_type = 'node' AND b.id IN (1,2,3)"
    foreach (array('a' => 'item1', 'b' => 'item2') as $alias => $param) {
      if (isset(${$param}['eid'])) {
        $select_query->condition("$alias.eid", ${$param}['eid']);
        $select_query->condition("$alias.entity_type", ${$param}['entity_type']);
      }
      else {
        // We've been passed an array of ids for geoms that don't yet have their
        // eid set.
        $select_query->condition("$alias.id", ${$param}, 'IN');
      }
    }
    $this->built = TRUE; // Prevents the buildQuery() method from being called.
    $this->query = $select_query;
    $this->return_strategy = 'syncPgBooleanReturn';
    return $this;
  }

  /**
   * Builds a query that finds all entities that have a particular geometry
   * relationship with the entity whose type and id are passed in. An example
   * query would look like this:
   * "SELECT a.eid, a.entity_type FROM entity_geom a JOIN entity_geom b ON
   * St_within(a.geom, b.geom) WHERE b.entity_type = 'node' and b.eid = 740"
   *
   * @param $type
   *  The type of geometry function to use, e.g. 'within' for the ST_Within
   *  function
   *
   * @param $entity_type
   *  The type of entity we're checking against
   *
   * @param $eid
   *  The entity id of the entity to check against.
   *
   * @param $reverse
   *  If set to TRUE then the order of the geometries is reversed in the geometry
   *  function being used.
   *
   * @param $distance
   *  Used for example in buffer queries, the distance of the buffer to search,
   *  passed in the units of the SRID being used for the query.
   *
   */
  public function entityRelQuery($function_type, $item, $reverse = FALSE, $distance = NULL) {
    $this->base_table = $this->geom_table;
    // Initialise a select query on the geometry table.
    $select_query = $this->connection->select($this->geom_table, $this->geom_table);

    $geoms = array($this->geom_table, 'geom_b');
    if ($reverse) {
      $geoms = array_reverse($geoms);
    }
    // Build up the geometry condition as a string of sql.
    $func = sync_pg_query_get_function($function_type);
    if (is_null($func)) {
      throw new syncPgQueryException('Unrecognized PostGIS function type passed in');
    }
    $condition = "$func(ST_Transform({$geoms[0]}.{$this->geom_column}, {$this->srid}), ST_Transform({$geoms[1]}.{$this->geom_column}, {$this->srid})";
    if (is_numeric($distance)) {
      $condition .= ", $distance";
    }
    $condition .= ")";
    // Join the table to itself based on the geometry condition.
    $select_query->join($this->geom_table, 'geom_b', $condition);

    // Set up the conditions. This will produce a WHERE clause like e.g.
    // "WHERE geom_b.eid = 5 AND geom_b.entity_type = 'node'"
    // ... if we've been passed an array describing an entity, or
    // "WHERE geom_b.id IN (1,2,3)"
    // ... if we've been passed an array of geometry ids.
    if (isset($item['eid'])) {
      foreach (array('eid' => $item['eid'], 'entity_type' => $item['entity_type']) as $field_name => $value) {
        $sql_field = "geom_b.$field_name";
        $select_query->condition($sql_field, $value);
        $ph_key = ':db_condition_placeholder_' . $this->placeholder_index++;
        // Add information about this field to the placeholders array.
        $this->placeholders[$ph_key] = array(
          'table' => $this->geom_table,
          'field' => $field_name,
        );
      }
    }
    else {
      $select_query->condition("geom_b.id", $item, 'IN');
      // Keep track of the placeholders.
      foreach ($item as $i) {
        $ph_key = ':db_condition_placeholder_' . $this->placeholder_index++;
        // Add information about this field to the placeholders array.
        $this->placeholders[$ph_key] = array(
          'table' => $this->geom_table,
          'field' => 'id',
        );
      }
    }

    // Add return fields
    $this->return_fields = array(
      'geometry' => array('eid', 'entity_type')
    );
    // Store the query and set the return strategy.
    $this->query = $select_query;

    $this->return_strategy = 'syncPgEntityReturn';
    return $this;
  }

  /**
   * Ensure that the table required for fields or filters is joined to the query.
   *
   * @param $name
   *  Usually corresponds to the table name.
   *
   * @see sync_pg_query_get_queryables().
   */
  public function ensureTable($name) {
    if (!isset($this->joins[$name])) {
      // Get the relevant table info so we can do a table join, if needed.
      $table_info = sync_pg_query_get_queryables($name);
      
      if (isset($table_info['callback'])) {
        $table_info = call_user_func($table_info['callback'], $this);
      }
      // Store the table info in our joins array.
      $this->joins[$name] = $table_info;

      // No need to join if it's the base table
      if ($table_info['table_name'] == $this->base_table) {
        return $table_info;
      }

      // Build up the string to pass as the join condition.
      $condition = '';
      $i = 0;
      foreach ($table_info['columns'] as $this_table_col => $base_table_col) {
        if ($i) {
          $condition .= ' AND ';
        }
        $condition .= "{$table_info['table_name']}.$this_table_col = {$this->base_table}.$base_table_col";
        $i++;
      }
      // Add the join to our select query.
      $this->query->join($table_info['table_name'], $table_info['table_name'], $condition);
    }
    return $this->joins[$name];
  }

  /**
   * Resets everything back to defaults so that we can re-use this object for
   * a new query.
   */
  public function destroy() {
    $this->base_table = NULL;
    $this->exec_method = 'execute';
    $this->entity_type = $this->bundle = $this->return_geometry = NULL;
    if (isset($this->query)) {
      unset($this->query);
    }
    $this->placeholders = array();
    $this->placeholder_index = 0;
    $this->joins = $this->return_fields = array();
    $this->filterConditions = $this->geometryConditions = array();
    $this->return_strategy = 'syncPgRowReturn';
    $this->built = $this->executed = FALSE;
  }

}

/**
 * Interface for return strategy classes.
 */
interface SyncPgReturnStrategy {
  /**
   * Returns the result in the desired format.
   *
   * @param $result
   *  The query result as a DatabaseStatementBase object.
   *
   * @return either an array of results or a value, depending on the strategy
   * used.
   */
  public static function returnResult(DatabaseStatementBase $result, syncPgQuery $query);
}

/**
 * Class for returning the result as an array of row objects.
 */
class syncPgRowReturn implements SyncPgReturnStrategy {
  public static function returnResult(DatabaseStatementBase $result, syncPgQuery $query) {
    $return = array();
    foreach ($result as $row) {
      $return[] = $row;
    }
    return $return;
  }
}

/**
 * Class for returning the result as an array of stub entities keyed by entity
 * type.
 */
class syncPgEntityReturn implements syncPgReturnStrategy {
  public static function returnResult(DatabaseStatementBase $result, syncPgQuery $query) {
    $return = array();
    if ($entity_type = $query->getEntityType()) {
      // This means we won't have to call entity_get_info() for each individual
      // row.
      $entity_type_info = entity_get_info($entity_type);
    }
    foreach ($result as $partial_entity) {
      if (!isset($partial_entity->eid) || !isset($partial_entity->entity_type)) {
        throw new syncPgQueryException('Entity type or entity id is missing from results');
      }
      $bundle = isset($partial_entity->bundle) ? $partial_entity->bundle : $query->getBundle();
      // Build up a stub entity.
      $entity = new stdClass();
      $info = isset($entity_type_info) ? $entity_type_info : entity_get_info($partial_entity->entity_type);

      $entity->{$info['entity keys']['id']} = $partial_entity->eid;
      if (!empty($info['entity keys']['bundle']) && $bundle) {
        $entity->{$info['entity keys']['bundle']} = $bundle;
      }
      if (!empty($info['entity keys']['label']) && isset($partial_entity->label)) {
        $entity->{$info['entity keys']['label']} = $partial_entity->label;
      }
      $return[$partial_entity->entity_type][$partial_entity->eid] = $entity;
    }
    return $return;
  }
}

/**
 * Return strategy that simply returns TRUE or FALSE. When used on a
 * booleanRelQuery, this will return TRUE if at least one row has a TRUE value
 * for its booleanvalue field. Used on a query that does not return a boolean-
 * value field, it returns TRUE as long as the result set contains at least one
 * row.
 */
class syncPgBooleanReturn implements syncPgReturnStrategy {
  public static function returnResult(DatabaseStatementBase $result, syncPgQuery $query) {
    // Return TRUE if any of the rows' values is TRUE
    foreach ($result as $row) {
      if (!isset($row->booleanvalue)) {
        // This may seem counter-intuitive, but if this return strategy is being
        // used for a query that is not actually returning a booleanvalue, we
        // just return true if it's returning at least one row.
        return TRUE;
      }
      elseif ($row->booleanvalue) {
        return TRUE;
      }
    }
    return FALSE;
  }
}

/**
 * Exception thrown if invalid fields or filters are added to a query.
 */
class syncPgQueryException extends Exception {}
