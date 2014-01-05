<?php

/**
 * See issue2686.
 *
 * Accommodation aliases are updated in case:
 * - Accommodation added
 * - Accommodation deleted
 * - Accommodation name changed
 * - Event alias changed
 *
 * Same for Activity
 */


// TODO: Move constants to airtribune.module
// Rewrite using Rules.

/**
 * Generic function for creating custom aliases.
 */
function _at_alias_create_alias($node, $event_nids = NULL) {
  //module_load_include('inc', 'pathauto');
  switch ($node->type) {
    // day alias
    case AIRTRIBUNE_DAY_TYPE:
    // accommodation and activity alias
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
    case AIRTRIBUNE_ACTIVITY_TYPE :
      _al_alias_create_object_aliases($node, $event_nids);
      break;

    // pg_contest alias
    case AIRTRIBUNE_PG_CONTEST_TYPE :
      // TODO: Move contents of the following function into the current one.
      _at_alias_create_event_objects_aliases($node);
      // TODO: Move alias generation from pg_contest feature
      break;
  }

  // TODO:
}

function _at_alias_create_entity_alias($entity, $type, $event_nids = NULL) {
  switch ($type) {
    // race related pages alias
    case AIRTRIBUNE_RACE_ENTITY_TYPE:
      // Create object aliases if needed.
      _al_alias_create_entity_object_aliases($entity, $type, $event_nids = NULL);
      break;
  }
}


/**
 * Generic function for deleting custom aliases.
 */
function _at_alias_delete_alias($node) {

  switch ($node->type) {
    // Delete day alias
    case AIRTRIBUNE_DAY_TYPE:
      $source = "event/%/day/{$node->nid}";
      $alias = "%/day/%";

      // Delete accomodation aliases.
      db_delete('url_alias')
        ->condition('source', $source, 'LIKE')
        ->condition('alias', $alias, 'LIKE')
        ->execute();
      break;
    // accommodation and activity alias
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
      $subalias = 'accommodations';
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $subalias = empty($subalias) ? 'activities' : $subalias;
      //$pattern = "event/%/map/{$subalias}/{$node->nid}";
      $source = "event/%/map/{$node->nid}";
      $alias = "%/map/{$subalias}/%";

      // Delete accomodation aliases.
      db_delete('url_alias')
        ->condition('source', $source, 'LIKE')
        ->condition('alias', $alias, 'LIKE')
        ->execute();
      // TODO:
      break;


    // pg_contest alias
    case AIRTRIBUNE_PG_CONTEST_TYPE :
      // type => subalias
      /*
      $object_types = array('accommodations' => 'accommodations', 'activities' => 'activities');
      foreach ($object_types as $object_type => $subalias) {
        $source = "event/{$node->nid}/map/{$subalias}/%";
        db_delete('url_alias')
          ->condition('source', $source, 'LIKE')
          ->execute();
      }
      */
      $subaliases = array('accommodations', 'activities');
      foreach ($subaliases as $subalias) {
        $source = "event/{$node->nid}/map/{$subalias}/%";
        db_delete('url_alias')
          ->condition('source', $source, 'LIKE')
          ->execute();
      }

      // TODO: Move alias generation from pg_contest feature
      break;
  }

  // TODO: Add case check.
  // Remove case check from hook. Or change this one.

}

function _at_alias_delete_entity_alias($entity, $type) {
  switch ($type) {
    case AIRTRIBUNE_RACE_ENTITY_TYPE:
      $race_number = '';
      if (isset($entity->field_race_number[LANGUAGE_NONE]['0']['value'])) {
        $race_number = $entity->field_race_number[LANGUAGE_NONE]['0']['value'];
      }
      $source = "event/%/race/{$entity->id}/results/%";
      $alias = "%/results/task_{$race_number}/%";

      // Delete aliases.
      db_delete('url_alias')
        ->condition('source', $source, 'LIKE')
        ->condition('alias', $alias, 'LIKE')
        ->execute();
      break;
  }
}

/**
 * Check if alias already exist
 * This is required for existing content in order not to regenerate them.
 */
function _at_alias_exists($pattern) {
  // TODO: Add case

  $query = db_select('url_alias', 'a')
    ->fields('a')
    ->condition('source', $pattern, 'LIKE')
    ->execute()
    ->fetchAll();
  return !empty($query);

}

/**
 * Helper function.
 * Prepare path for alias using pathauto functionality.
 */
function _at_alias_clear_string($string) {
  module_load_include('inc', 'pathauto');
  if (function_exists('pathauto_cleanstring') && !empty($string)) {
    $path = pathauto_cleanstring($string);
  }

  return !empty($path) ? $path : FALSE;
}

/**
 * Get related to accommodation events
 * based on their coordinates.
 */
// TODO: Move into a single function with related objects.
function _at_alias_related_events($node) {
  $nids = array();
  switch ($node->type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE:
    case AIRTRIBUNE_ACTIVITY_TYPE:
      $wrapper = entity_metadata_wrapper('node', $node);
      $location = $wrapper->{AIRTRIBUNE_LOCATION_FIELD}->value();

      // @todo: move this sql into separate function
      $location_table = 'field_data_' . AIRTRIBUNE_HQ_LOCATION_FIELD;
      $sql = "SELECT location.* FROM $location_table location WHERE bundle = :bundle AND
      ST_Distance(ST_Point(location.field_hq_location_lon, field_hq_location_lat)::geography, ST_Point(:lon, :lat)::geography) < :distance";
      //ST_Distance(ST_Point(location.field_location_lon, field_location_lat)::geography, ST_Point(:lon, :lat)::geography) < :distance";


      // Get contest accomodation.
      $query = db_query($sql, array(
        ':bundle' => AIRTRIBUNE_PG_CONTEST_TYPE,
        ':lat' => $location['lat'],
        ':lon' => $location['lon'],
        ':distance' => 30000,
      ));

      $result = $query->fetchAll();

      foreach ($result as $row) {
        $nids[] = $row->entity_id;
      }
      break;
    case AIRTRIBUNE_DAY_TYPE:
      $og_ref_items = field_get_items('node', $node, OG_AUDIENCE_FIELD);
      $nids[] = $og_ref_items[0]['target_id'];
      break;
  }
  return $nids;
}

function _at_alias_related_entity_events($entity, $type) {
  $nids = array();

  switch ($type) {
    // get related events for race
    case AIRTRIBUNE_RACE_ENTITY_TYPE:
      $og_ref_items = field_get_items($type, $entity, OG_AUDIENCE_FIELD);
      $nids[] = $og_ref_items[0]['target_id'];
      break;
  }
  return $nids;
}

/**
 * Get accommodation and activities related to a given event
 * based on their coordinates.
 */
function _at_alias_related_objects($node, $object_types) {
  // @todo: add condition for OG group
  if ($node->type != AIRTRIBUNE_PG_CONTEST_TYPE) {
    return;
  }
  $object_types = (array)$object_types;
  $nids = array();
  foreach ($object_types as $type)
  switch ($type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
    case AIRTRIBUNE_ACTIVITY_TYPE :
      $wrapper = entity_metadata_wrapper('node', $node);
      $location = $wrapper->{AIRTRIBUNE_HQ_LOCATION_FIELD}->value();

      $location_table = 'field_data_' . AIRTRIBUNE_LOCATION_FIELD;
      $sql = "SELECT location.* FROM $location_table location WHERE bundle = :bundle AND
      ST_Distance(ST_Point(location.field_location_lon, field_location_lat)::geography, ST_Point(:lon, :lat)::geography) < :distance";

      // Get contest object.
      $query = db_query($sql, array(
        ':bundle' => $type,
        ':lat' => $location['lat'],
        ':lon' => $location['lon'],
        ':distance' => 30000,
      ));

      $result = $query->fetchAll();

      foreach ($result as $row) {
        $nids[] = $row->entity_id;
      }
      break;
    case AIRTRIBUNE_DAY_TYPE :
      $query = db_select('og_membership', 'og');
      $query->join('node', 'n', 'og.etid = n.nid');
      $query->fields('n');
      $query->condition('n.type', AIRTRIBUNE_DAY_TYPE,'=');
      $query->condition('og.gid', $node->nid,'=');
      $result = $query->execute();

      foreach ($result as $row) {
        $nids[] = $row->nid;
      }
      break;
  }
  return $nids;
}

/**
 * Create aliases for accommodations and activities
 * according to event coordinates.
 */
function _at_alias_create_event_objects_aliases($node) {

  module_load_include('inc', 'pathauto');

  // Get alias base.
  $alias_base = _at_alias_get_event_alias($node->nid);
  // Do nothing.
  if ($alias_base == FALSE) {
    return;
  }

  // Delete objects' aliases if any.
  // Actually we don't need to delete aliases if event is new.
  _at_alias_delete_alias($node);

  // type => subalias
  $object_types = array(AIRTRIBUNE_ACCOMMODATION_TYPE, AIRTRIBUNE_ACTIVITY_TYPE, AIRTRIBUNE_DAY_TYPE);

  foreach ($object_types as $object_type => $subalias) {
    $object_nids = _at_alias_related_objects($node, $object_types);
    foreach ($object_nids as $nid) {
      // TODO: Create alias for object-event pair.
      $object_node = node_load($nid);
      if ($object_node->nid) {
        _at_alias_delete_alias($object_node);
        _at_alias_create_alias($object_node);
      }
    }
  }
  // TODO:
}

/**
 * Create aliases for single object (accommodation or activity).
 */
function _al_alias_create_object_aliases($node, $event_nids = NULL) {

  module_load_include('inc', 'pathauto');

  $real_path_pattern = '';
  $alias_pattern = '';

  switch ($node->type) {
    case AIRTRIBUNE_ACCOMMODATION_TYPE:
      $subalias = 'accommodations';
    case AIRTRIBUNE_ACTIVITY_TYPE:
      $subalias = empty($subalias) ? 'activities' : $subalias;

      // Do nothing.
      if (empty($subalias)) {
        return;
      }

      // Clear title string to use as alias element.
      $clear_title = _at_alias_clear_string($node->title);
      if (!$clear_title) {
        return;
      }

      $real_path_pattern = "event/%/map/{$node->nid}";
      $alias_pattern = "/map/{$subalias}/{$clear_title}";
      // If it is a newly created object, process further.
      if (!isset($node->is_new)) {
        // Check if there exist already any aliases ("event/%/map/{$node->nid}") for object.
        $alias_exist = _at_alias_exists($real_path_pattern);
        $title_updated = FALSE;
        if (isset($node->original)) {
          $title_updated = ($node->title != $node->original->title);
        }
        // If title wasn't updated and some aliases found, do nothing.
        // For example, for old object that existed before, we should create aliases.
        // @TODO: Maybe add regeneration functionality.
        if ($alias_exist && !$title_updated) {
          return;
        }
        elseif ($alias_exist && $title_updated) {
          // @TODO: If object (title) is UPDATED, remove existing aliases. Use $node->original
          _at_alias_delete_alias($node);
        }
      }
      break;
    case AIRTRIBUNE_DAY_TYPE:
      $day_number = NULL;
      if (isset($node->field_day_number[LANGUAGE_NONE]['0']['value'])) {
        $day_number = $node->field_day_number[LANGUAGE_NONE]['0']['value'];
      }
      if (!$day_number) {
        $day_number = _at_alias_clear_string($node->title);
      }
      $real_path_pattern = "event/%/day/{$node->nid}";
      $alias_pattern = "/day/{$day_number}";
      break;
    default:
      return;
      break;
  }

  if (empty($event_nids)) {
    // Get related events based on hq coordinates.
    $event_nids = _at_alias_related_events($node);
  }
  foreach ($event_nids as $event_nid) {
    // Check if (event) base alias exists.
    $alias_base = _at_alias_get_event_alias($event_nid);
    if ($alias_base == FALSE) {
      return;
    }

    $alias = "{$alias_base}{$alias_pattern}";

    // Save object alias for given event.
    $source = str_replace('%', $event_nid, $real_path_pattern);
    $path = array('source' => $source, 'alias' => $alias);
    path_save($path);
  }
}

function _al_alias_create_entity_object_aliases($entity, $type, $event_nids = NULL) {

  module_load_include('inc', 'pathauto');

  $real_path_pattern = '';
  $alias_pattern = '';

  switch ($type) {
    case AIRTRIBUNE_RACE_ENTITY_TYPE:

      $race_number = NULL;
      $category = NULL;
      if (isset($entity->field_race_number[LANGUAGE_NONE]['0']['value'])) {
        $race_number = $entity->field_race_number[LANGUAGE_NONE]['0']['value'];
      }
      if (!$race_number) {
        break;
      }
      $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity);
      $results_fields = array('day' => 'field_day_results', 'competition' => 'field_day_results');
      foreach ($results_fields as $results_type => $field_name) {
        foreach($wrapper->{$field_name}->value() as $results_item) {
          $wrapper_category = entity_metadata_wrapper($results_item->entityType(), $results_item);
          $category_item = $wrapper_category->field_scoring_category_ref->value();
          if (isset($category_item->field_pg_scoring_category[LANGUAGE_NONE][0]['value'])) {
            $category = _at_alias_clear_string($category_item->field_pg_scoring_category[LANGUAGE_NONE][0]['value']);
          }
          $real_path_patterns[] = "event/%/race/{$entity->id}/results/{$category_item->nid}/{$results_type}";
          $alias_patterns[] = "/results/task_{$race_number}/{$results_type}/{$category}";
        }
      }
      break;
    default:
      return;
      break;
  }

  if (empty($event_nids)) {
    // Get related events based on hq coordinates.
    $event_nids = _at_alias_related_entity_events($entity, $type);
  }

  foreach ($event_nids as $event_nid) {
    // Check if (event) base alias exists.
    $alias_base = _at_alias_get_event_alias($event_nid);
    if ($alias_base == FALSE) {
      return;
    }

    $real_path_patterns = (array)$real_path_patterns;
    $alias_patterns = (array)$alias_patterns;

    foreach ($real_path_patterns as $key => $real_path_pattern) {
      $alias = "{$alias_base}{$alias_patterns[$key]}";

      // Save object alias for given event.
      $source = str_replace('%', $event_nid, $real_path_pattern);
      $path = array('source' => $source, 'alias' => $alias);
      path_save($path);
    }
  }
}

/**
 * Implements hook_node_insert.
 */
function at_alias_node_insert($node) {
  switch ($node->type) {
    // day alias
    case AIRTRIBUNE_DAY_TYPE:
    // accommodation and activity alias
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
    case AIRTRIBUNE_ACTIVITY_TYPE :
      // Create object aliases if needed.
      _at_alias_create_alias($node);
      break;

    // pg_contest alias
    case AIRTRIBUNE_PG_CONTEST_TYPE :
      // TODO: This should perform after alias is already created.
      // By the moment it's ok, scince hook_insert() (see pg_contest_insert)
      // is executed before hook_node_insert().

      _at_alias_create_alias($node);
      // TODO: Move alias generation from pg_contest feature
      break;
  }
}

/**
 * Implements hook_entity_insert.
 */
function at_alias_entity_insert($entity, $type) {
  switch ($type) {
    // race related pages alias
    case AIRTRIBUNE_RACE_ENTITY_TYPE:
      // Create object aliases if needed.
      _at_alias_create_entity_alias($entity, $type);
      break;
  }
}

/**
 * Implements hook_node_update.
 */
function at_alias_node_update($node) {
  switch ($node->type) {
    // day alias
    case AIRTRIBUNE_DAY_TYPE:
    // accommodation and activity alias
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
    case AIRTRIBUNE_ACTIVITY_TYPE :
      // Update accommodation aliases if needed.
      _at_alias_delete_alias($node);
      _at_alias_create_alias($node);
      break;

    // pg_contest alias
    case AIRTRIBUNE_PG_CONTEST_TYPE :
      // Create/Updated aliases for related objects.
      // TODO: See comment for hook_node_insert().
      _at_alias_create_alias($node);
      // TODO: Move alias generation from pg_contest feature
      break;
  }
}

/**
 * Implements hook_entity_update.
 */
function at_alias_entity_update($entity, $type) {
  switch ($type) {
    // race related pages alias
    case AIRTRIBUNE_RACE_ENTITY_TYPE:
      // Update object aliases if needed.
      _at_alias_delete_entity_alias($entity, $type);
      _at_alias_create_entity_alias($entity, $type);
      break;
  }
}

/**
 * Implements hook_node_delete.
 */
function at_alias_node_delete($node) {
  switch ($node->type) {
    // day alias
    case AIRTRIBUNE_DAY_TYPE:
    // accommodation and activity alias
    case AIRTRIBUNE_ACCOMMODATION_TYPE :
    case AIRTRIBUNE_ACTIVITY_TYPE :
      // Delete object alias.
      _at_alias_delete_alias($node);
      break;

    // pg_contest alias
    case AIRTRIBUNE_PG_CONTEST_TYPE :
      _at_alias_delete_alias($node);
      // TODO: Move alias generation from pg_contest feature
      break;
  }
}

/**
 * Implements hook_entity_delete.
 */
function _at_alias_entity_delete($entity, $type) {
  switch ($type) {
    // race related pages alias
    case AIRTRIBUNE_RACE_ENTITY_TYPE:
      // Delete object aliases.
      _at_alias_delete_entity_alias($entity, $type);
      break;
  }
}

/**
 * Implements hook_node_presave.
 */
function at_alias_node_presave($node) {
  // TODO:
}

/*
// TODO: This hook is for testing purposes only. Delete.
function at_alias_node_view($node) {
  return;
  // Output related objects
  if ($node->type == AIRTRIBUNE_ACCOMMODATION_TYPE && isset($_GET['test'])) {
    
    $wrapper = entity_metadata_wrapper('node', $node);
    $location = $wrapper->{AIRTRIBUNE_LOCATION_FIELD}->value();
    
    $location = array('lat' => '45.127683000000', 'lon' =>  '21.334920000000');
    
    
    $location_table = 'field_data_' . AIRTRIBUNE_HQ_LOCATION_FIELD;
    // TODO: Use constants for location.field_hq_location
    $sql = "SELECT location.* FROM $location_table location WHERE bundle = :bundle AND
    ST_Distance(ST_Point(location.field_hq_location_lon, field_hq_location_lat)::geography, ST_Point(:lon, :lat)::geography) < :distance";
    //ST_Distance(ST_Point(location.field_location_lon, field_location_lat)::geography, ST_Point(:lon, :lat)::geography) < :distance";
    
    
    // Get contest accomodation.
    $query = db_query($sql, array(
      ':bundle' => 'pg_contest',
      ':lat' => $location['lat'],
      ':lon' => $location['lon'],
      ':distance' => 30000,
    ));
    
    $result = $query->fetchAll();
    
    $nids = array();
    foreach ($result as $row) {
      $nids[] = $row->entity_id;
    }
  }
}
*/

/**
 * Helper function.
 * Get event alias by nid.
 */
function _at_alias_get_event_alias($nid) {
  // Check if (event) base alias exists.
  $source_base = "event/{$nid}";
  $conditions = array('source' => $source_base);
  $event_path = path_load($conditions);

  // Return FALSE if alias doesn't exist or is empty string.
  return !empty($event_path['alias']) ? $event_path['alias'] : FALSE;
}


// NOTES:
// If event's coordinates are signifintly changes, there could remain
// trash aliases for related accommodations (they won't be deleted).
