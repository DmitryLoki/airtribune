<?php

/**
 * @file
 * Hooks provided by the Sync PostGIS Query module.
 */

/**
 * @addtogroup hooks
 * @{
 */
 
/**
 * Define table joins so that Sync PostGIS Query can include your module's data
 * in a query. This is not necessary if your module's table just has a foreign
 * key to the entity table with the 'eid' and 'entity_type' columns. However, if
 * your columns are named differently you will need to specify them here. Also,
 * if your module provides tables that are dynamically named somehow, like the
 * bundle tables are (named using the template [entity_type]__[bundle_name]), you
 * need to provide a callback function which is responsible for returning the
 * table name and columns to join on and it can do this based on the actual
 * current query object which gets passed in to the function.
 *
 * Return an array keyed by the name that will be used to specify this join,
 * usually the table name. The array must include EITHER
 *  - 'table_name' the name of the table to join on.
 *  - 'columns' the specification of this table's foreign key to the entity table.
 * OR
 *  - 'callback' the name of a callback function which will be passed the query
 *  object and will return an array with the 'table_name' and 'column'.
 */
function hook_sync_pg_queryable() {
  $queryable = array(
    'entity' => array(
      'table_name' => SYNC_PG_ENTITY_TABLE,
      'columns' => array('eid' => 'eid', 'entity_type' => 'entity_type')
    ),
    'bundle_field' => array(
      'callback' => 'sync_pg_query_bundle_callback',
    ),
  );
  return $queryable;
}

/**
 * @} End of "addtogroup hooks".
 */
