<?php

// @todo
/**
 * Process single node's aliases when it is operated (updated, inserted, deleted).
 */
function _at_alias_process_single_conjugate_node($op, $node) {
  // @todo: add _at_alias_get_conjugate_events() wrapper
  $event_nids = _at_alias_get_conjugate_nodes($node);
  if (!empty($event_nids)) {
    $events = node_load_multiple($event_nids);
    //~ $nodes = array($node->nid => $node);
    switch ($op) {
      case 'insert' :
        _at_alias_insert_single_conjugate_node($node, $events);
        break;
      case 'update' :
        _at_alias_update_single_conjugate_node($node, $events);
        break;
      case 'delete' :
        _at_alias_delete_single_conjugate_node($node);
        break;
    }
  }
}

// @todo

function _at_alias_insert_single_conjugate_node($node, $events) {
  // @todo: This is temporary solution.
  _at_alias_update_single_conjugate_node($node, $events);
}

// @todo

function _at_alias_update_single_conjugate_node($node, $events) {
  switch ($node->type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
      $subalias = 'accommodations';
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $subalias = empty($subalias) ? 'activities' : $subalias;
      $pattern = array(
        'source' => "event/:event_id/map/:nid",
        'alias' => ":alias_base/map/{$subalias}/:clear_title",
      );
      break;
    case AIRTRIBUNE_DAY_TYPE :
      $pattern = array(
        'source' => "event/:event_id/day/:nid",
        'alias' => ":alias_base/day/:day_suffix",
      );
      break;
  }
  
  // Delete node's existing aliases
  _at_alias_delete_single_conjugate_node($node);
  
  // Prepare placeholders.
  $clear_title = _at_alias_clear_string($node->title);
  $placeholders = array(':clear_title' => $clear_title, ':nid' => $node->nid);
  if ($node->type == AIRTRIBUNE_DAY_TYPE) {
    switch($node->field_day_status[LANGUAGE_NONE][0]['value']) {
      case 4:
        $placeholders[':day_suffix'] = 'registration';
        break;
      case 5:
        $placeholders[':day_suffix'] = 'training';
        break;
      default:
        $placeholders[':day_suffix'] = isset($node->field_day_number[LANGUAGE_NONE]['0']['value'])
          ? $node->field_day_number[LANGUAGE_NONE]['0']['value']
          : _at_alias_clear_string($node->title);
        break;
    }

  }

  // Go through events.
  foreach ($events as $event) {
    $alias_base = _at_alias_get_event_alias_base($event);
    if ($alias_base == FALSE) {
      continue;
    }
    
    $placeholders += array(':alias_base' => $alias_base, ':event_id' => $event->nid);
    
    $path = array(
      'source' => strtr($pattern['source'], $placeholders),
      'alias' => strtr($pattern['alias'], $placeholders),
    );
    path_save($path);
  }
}

/**
 * Delete all aliases on conjugate node delete.
 */
function _at_alias_delete_single_conjugate_node($node) {
  switch ($node->type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
      $subalias = 'accommodations';
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $subalias = empty($subalias) ? 'activities' : $subalias;
      $conditions = array(
        'source' => "event/%/map/{$node->nid}",
        'alias' => "%/map/{$subalias}/%",
      );
      break;
    case AIRTRIBUNE_DAY_TYPE :
      $conditions = array(
        'source' => "event/%/day/{$node->nid}",
        'alias' => "%/day/%",
      );
      break;
  }
  _at_alias_delete_node_alias_multiple($conditions);
}


/**
 * Process event's conjugate nodes.
 * 
 * @var $op - event node hook option: insert, update, delete
 * @var $event - event node
 * @var $type - conjugate nodes' type
 * 
 * @return NULL
 */
function _at_alias_process_event_conjugate_nodes($op, $event, $type) {
  //~ if (in_array($type, array(AIRTRIBUNE_ACCOMMODATION_TYPE, AIRTRIBUNE_ACTIVITY_TYPE, AIRTRIBUNE_DAY_TYPE))) {
    //~ return;
  //~ }
  
  $nids = _at_alias_get_conjugate_nodes($event, $type);
  if (!empty($nids)) {
    $nodes = node_load_multiple($nids);
    switch ($op) {
      case 'insert' :
        _at_alias_insert_event_conjugate_nodes_alias($event, $nodes, $type);
        break;
      case 'update' :
        _at_alias_update_event_conjugate_nodes_alias($event, $nodes, $type);
        break;
      case 'delete' :
        _at_alias_delete_event_conjugate_nodes_alias($event, $nodes, $type);
        break;
    }
  }
}


function _at_alias_insert_event_conjugate_nodes_alias($event, $nodes, $type) {
  // @todo: This is temporary solution.
  _at_alias_update_event_conjugate_nodes_alias($event, $nodes, $type);
}

// @todo: When existing event without alias is updated
// aliases_base is obtained whith "-0" suffix
// Also on event update old day aliases not deleted

function _at_alias_update_event_conjugate_nodes_alias($event, $nodes, $type) {
  module_load_include('inc', 'at_alias', 'at_alias.event');
  
  // Get event alias base.
  $alias_base = _at_alias_get_event_alias_base($event);
  // Do nothing if there is no event alias in the db.
  if (empty($alias_base)) {
    return;
  }
  
  // Delete conjugate nodes' old aliases.
  _at_alias_delete_event_conjugate_nodes_alias($event, $nodes, $type);
  
  // @todo: Create new aliases
  
  switch ($type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
      $subalias = 'accommodations';
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $subalias = empty($subalias) ? 'activities' : $subalias;
      $pattern = array(
        'source' => "event/:event_id/map/:nid",
        'alias' => ":alias_base/map/{$subalias}/:clear_title",
      );
      break;
    case AIRTRIBUNE_DAY_TYPE :
      $pattern = array(
        'source' => "event/:event_id/day/:nid",
        'alias' => ":alias_base/day/:day_suffix",
      );
      break;
  }
  
  foreach ($nodes as $node) {
    $placeholders = array(':alias_base' => $alias_base, ':event_id' => $event->nid, ':nid' => $node->nid);
    $placeholders[':clear_title'] = _at_alias_clear_string($node->title);
    if ($node->type == AIRTRIBUNE_DAY_TYPE) {
      $placeholders[':day_suffix'] = isset($node->field_day_number[LANGUAGE_NONE]['0']['value'])
        ? $node->field_day_number[LANGUAGE_NONE]['0']['value']
        : _at_alias_clear_string($node->title);
    }
    
    $path = array(
      'source' => strtr($pattern['source'], $placeholders),
      'alias' => strtr($pattern['alias'], $placeholders),
    );
    path_save($path);
  }
}


// @todo: (?) actually we don't need nodes here. Remove $nodes variable from arguments.
// And don't load $nodes in case of 'delete' in _at_alias_process_event_conjugate_nodes()

/**
 * Delete conjugate nodes' aliases on event delete.
 * 
 * @var $event - event node
 * @var $nodes - conjugate nodes
 * @var $type - conjugate nodes' type
 */
function _at_alias_delete_event_conjugate_nodes_alias($event, $nodes, $type) {
  // Get event alias base.
  $alias_base = _at_alias_get_event_alias_base($event);
  
  // Do nothing if there is no event alias in the db.
  if (empty($alias_base)) {
    return;
  }
  
  
  switch ($type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
      $subalias = 'accommodations';
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $subalias = empty($subalias) ? 'activities' : $subalias;
      $pattern = array(
        'source' => "event/:event_id/map/:nid",
        'alias' => "%/map/{$subalias}/%",
      );
      break;
    case AIRTRIBUNE_DAY_TYPE :
      $pattern = array(
        'source' => "event/:event_id/day/:nid",
        'alias' => "%/day/%",
      );
      break;
  }
  
  //~ dsm($conditions);
  foreach ($nodes as $node) {
    // @todo: Seems, $alias_base isn't required here.
    $placeholders = array(':alias_base' => $alias_base, ':event_id' => $event->nid, ':nid' => $node->nid);
    $conditions = array(
      'source' => strtr($pattern['source'], $placeholders),
      'alias' => strtr($pattern['alias'], $placeholders),
    );
    _at_alias_delete_node_alias_multiple($conditions);
  }
}


// @todo: move this function into at_alias.module file, and rename.
function _at_alias_delete_node_alias_multiple($conditions) {
  if (empty($conditions)) {
    return;
  }
  else {
    $query = db_delete('url_alias');
    if (!empty($conditions['source'])) {
      $query->condition('source', $conditions['source'], 'LIKE');
      //~ $query->condition('source', db_like($conditions['source']), 'LIKE');
    }
    if (!empty($conditions['alias'])) {
      $query->condition('alias', $conditions['alias'], 'LIKE');
      //~ $query->condition('a', db_like($conditions['alias']), 'LIKE');
    }
    $query->execute();
  }
}


// @todo: Maybe return $nodes instead of $nids.

/**
 * Get conjugate nodes for given one.
 * 
 * @var $node - node that provides (geopoint) origin for search.
 * @var $type - type of conjugate nodes: activities or accomodations. Used for event $node only.
 * 
 * @return array $nids.
 * 
 * Possible pairs:
 * AIRTRIBUNE_PG_CONTEST_TYPE | AIRTRIBUNE_HG_CONTEST_TYPE <---> AIRTRIBUNE_ACCOMMODATION_TYPE | AIRTRIBUNE_ACTIVITY_TYPE | AIRTRIBUNE_DAY_TYPE
 */
function _at_alias_get_conjugate_nodes($node, $type = NULL) {
  $nids = array();
  switch ($node->type) {
    case AIRTRIBUNE_PG_CONTEST_TYPE :
    case AIRTRIBUNE_HG_CONTEST_TYPE :
      if (in_array($type, array(AIRTRIBUNE_ACCOMMODATION_TYPE, AIRTRIBUNE_ACTIVITY_TYPE))) {
        $wrapper = entity_metadata_wrapper('node', $node);
        $location = $wrapper->{AIRTRIBUNE_HQ_LOCATION_FIELD}->value();
        // Get nearby activities/accommodations.
        $nids = _at_alias_get_nearby_nodes($location, $type);
      
      }
      elseif ($type == AIRTRIBUNE_DAY_TYPE){
        // Get in-event days.
        $query = db_select('og_membership', 'og');
        $query->join('node', 'n', 'og.etid = n.nid');
        $query->fields('n');
        $query->condition('n.type', AIRTRIBUNE_DAY_TYPE, '=');
        $query->condition('og.gid', $node->nid,'=');
        $result = $query->execute();

        foreach ($result as $row) {
          $nids[] = $row->nid;
        }
      }
      break;

    // Get nearby events.
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $wrapper = entity_metadata_wrapper('node', $node);
      $location = $wrapper->{AIRTRIBUNE_LOCATION_FIELD}->value();
      $nids = _at_alias_get_nearby_nodes($location, AIRTRIBUNE_PG_CONTEST_TYPE);
      $nids += _at_alias_get_nearby_nodes($location, AIRTRIBUNE_HG_CONTEST_TYPE);
      break;

    // Get parent-events (actually, only one will return)
    case AIRTRIBUNE_DAY_TYPE :
      $og_ref_items = field_get_items('node', $node, OG_AUDIENCE_FIELD);
      $nids[] = $og_ref_items[0]['target_id'];
      break;
    default :
      return;
  }
  return $nids;
}




// @todo: Maybe return $nodes instead of $nids.

/**
 * Get nodes of given type around the geopoint.
 * 
 * @var $location - center, around which to look for nodes.
 * @var $type - type of nodes, that are looked for.
 * 
 * @return array $nids.
 */
function _at_alias_get_nearby_nodes($location, $type) {
  switch ($type) {
    case AIRTRIBUNE_PG_CONTEST_TYPE:
    case AIRTRIBUNE_HG_CONTEST_TYPE:
      $location_table = "field_data_" . AIRTRIBUNE_HQ_LOCATION_FIELD;  // table name
      $postgis_lon = AIRTRIBUNE_HQ_LOCATION_FIELD . "_lon";  // columns' names
      $postgis_lat = AIRTRIBUNE_HQ_LOCATION_FIELD . "_lat";
      break;
    case AIRTRIBUNE_ACCOMMODATION_TYPE:
    case AIRTRIBUNE_ACTIVITY_TYPE:
      $location_table = "field_data_" . AIRTRIBUNE_LOCATION_FIELD;  // table name
      $postgis_lon = AIRTRIBUNE_LOCATION_FIELD . "_lon";  // columns' names
      $postgis_lat = AIRTRIBUNE_LOCATION_FIELD . "_lat";
      break;
    default :
      return;
  }
  
  $sql = "SELECT location.* FROM {$location_table} location WHERE bundle = :bundle AND
          ST_Distance(ST_Point(location.{$postgis_lon}, {$postgis_lat})::geography, ST_Point(:lon, :lat)::geography) < :distance";

  // @todo: Add check "if ($location)". E.g. event_statistics.inc

  $nids = array();
  // https://drupal.org/node/355875
  $transaction = db_transaction();
  try {
    $query = db_query($sql, array(
      ':bundle' => $type,
      ':lat' => $location['lat'],
      ':lon' => $location['lon'],
      ':distance' => 30000,
    ));
    $result = $query->fetchAll();
  } catch (Exception $e) {
    $transaction->rollback();
    watchdog('airtribune', 'Fetch location nearby nodes failed: %message', array('%message' => $e->getMessage()), WATCHDOG_ERROR);
    return $nids;
  }
  
  
  
  
  foreach ($result as $row) {
    $nids[] = $row->entity_id;
  }
  return $nids;
}
