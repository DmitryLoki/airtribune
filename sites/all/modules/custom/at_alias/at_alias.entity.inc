<?php

function _at_alias_process_user($op, $entity) {
  switch ($op) {
    case 'insert' :
    case 'update' :
      _at_alias_update_user($entity);
      break;
    case 'delete' :
      _at_alias_delete_user($entity);
      break;
  }
}

function _at_alias_update_user($user) {
  module_load_include('inc', 'pathauto');
  if (function_exists('pathauto_cleanstring') && isset($user->uid)) {
    // Save tiny aliases.
    $tiny_path_items = field_get_items('user', $user, 'field_tiny_path');
    // Check that $tiny_path_items is not empty
    if (!empty($tiny_path_items) && is_array($tiny_path_items)) {
      foreach ($tiny_path_items as $tiny_path) {
        $path = array('source' => 'user/' . $user->uid, 'alias' => $tiny_path['value']);
        path_save($path);
      }
    }
  }
}

function _at_alias_delete_user($entity) {
  // @todo delete user-alias/edit, user-alias/contestant and other
}

// Note: It is supposed that there can be no two bundles
// of different entities with same names.
function _at_alias_process_single_conjugate_ent_race($op, $entity) {
  // @todo
  // Get event nids (actually, only one)
  $event_nids = _at_alias_get_conjugate_entities($entity);
  if (!empty($event_nids)) {
    $events = node_load_multiple($event_nids);
    switch ($op) {
      case 'insert' :
        _at_alias_insert_single_conjugate_ent_race($entity, $events);
        break;
      case 'update' :
        _at_alias_update_single_conjugate_ent_race($entity, $events);
        break;
      case 'delete' :
        _at_alias_delete_single_conjugate_ent_race($entity);
        break;
    }
  }
  
}

function _at_alias_insert_single_conjugate_ent_race($entity, $events) {
  // @todo: This is temporary solution. we don't need to delete aliases on 'insert'
  // as is done on update. Everything else seems to be the same.
  _at_alias_update_single_conjugate_ent_race($entity, $events);
}

// @todo
function _at_alias_update_single_conjugate_ent_race($entity, $events) {
  module_load_include('inc', 'pathauto');
  module_load_include('inc', 'at_alias', 'at_alias.event');
  switch ($entity->type) {
    case AIRTRIBUNE_PG_RACE_TYPE :
      if (isset($entity->{AIRTRIBUNE_RACE_NUMBER}[LANGUAGE_NONE]['0']['value'])) {  // consider (possible?) case pg_race_number == 0
        $pg_race_number = $entity->{AIRTRIBUNE_RACE_NUMBER}[LANGUAGE_NONE]['0']['value'];
        if (!$pg_race_number) {
          break;
        }
        $wrapper = entity_metadata_wrapper(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity);
        $results_fields = array('day' => AIRTRIBUNE_DAY_RESULTS_FIELD, 'competition' => AIRTRIBUNE_DAY_RESULTS_FIELD);
        
        $pattern = array(
          'source' => "event/:event_nid/race/:entity_id/results/:category_item_nid/:results_type",
          'alias' => ":alias_base/results/task_:race_number/:results_type/:category",
        );
        
        $placeholders_pre = array();
        
        
        foreach ($results_fields as $results_type => $field_name) {
          foreach($wrapper->{$field_name}->value() as $results_item) {
            $wrapper_category = entity_metadata_wrapper($results_item->entityType(), $results_item);
            $category_item = $wrapper_category->{AIRTRIBUNE_SCORING_CATEGORY_REF_FIELD}->value();
            if (isset($category_item->{AIRTRIBUNE_PG_SCORING_CATEGORY_FIELD}[LANGUAGE_NONE][0]['value'])) {
              $category = _at_alias_clear_string($category_item->{AIRTRIBUNE_PG_SCORING_CATEGORY_FIELD}[LANGUAGE_NONE][0]['value']);
            }
            $placeholders = array(
              ':entity_id' => $entity->id,
              ':category_item_nid' => $category_item->nid,
              ':results_type' => $results_type,
              ':race_number' => $pg_race_number,
              ':category' => $category,
              // ':event_nid' => _ _ _ _ _
              // ':alias_base' => _ _ _ _ _
            );
            $placeholders_pre[] = $placeholders;
          }
        }
      }
      
      // delete existing aliases
      _at_alias_delete_single_conjugate_ent_race($entity);
      
      foreach ($events as $event) {
        $alias_base = _at_alias_get_event_alias_base($event);
        // Do nothing if there is no event alias in the db.
        if (empty($alias_base)) {
          continue;
        }
        
        foreach ($placeholders_pre as $placeholders) {
          $placeholders[':alias_base'] = $alias_base;
          $placeholders[':event_nid'] = $event->nid;
          $path = array(
            'source' => strtr($pattern['source'], $placeholders),
            'alias' => strtr($pattern['alias'], $placeholders),
          );
          path_save($path);
        }
      }
      break;
    case AIRTRIBUNE_PG_NATION_TEAM_TYPE :
      module_load_include('module', 'countries');

      $pattern = array(
        'source' => "event/:event_nid/pilots/manage/teams/:entity_id",
        'alias' => ":alias_base/pilots/manage/teams/:country",
      );
      if (!empty($events)) {
        $event = array_shift($events);

        // delete existing aliases
        _at_alias_delete_single_conjugate_ent_race($entity);

        $alias_base = _at_alias_get_event_alias_base($event);
        // Do nothing if there is no event alias in the db.
        if (empty($alias_base)) {
          return;
        }

        // Get team country
        $countries = countries_get_countries('name');
        $country_items = field_get_items(AIRTRIBUNE_TEAM_TYPE, $entity, AIRTRIBUNE_COUNTRY_FIELD);
        if (!empty($country_items)) {
          $country_code = $country_items[0]['iso2'];
        }
        else {
          return;
        }
        $country = str_replace(' ', '-', strtolower($countries[$country_code]));

        $placeholders = array(
          ':event_nid' => $event->nid,
          ':entity_id' => $entity->id,
          ':alias_base' => $alias_base,
          ':country' => $country,
        );

        $path = array(
          'source' => strtr($pattern['source'], $placeholders),
          'alias' => strtr($pattern['alias'], $placeholders),
        );
        path_save($path);
      }
      break;
  }
}

// @todo
function _at_alias_delete_single_conjugate_ent_race($entity) {
  module_load_include('inc', 'at_alias', 'at_alias.node');
  switch ($entity->type) {
    case AIRTRIBUNE_PG_RACE_TYPE :
      $pattern = array(
        'source' => "event/%/race/:entity_id/results/%",
      );
      $placeholders = array(':entity_id' => $entity->id);
      $conditions = array(
        'source' => strtr($pattern['source'], $placeholders),
      );
      _at_alias_delete_node_alias_multiple($conditions);
      break;
    case AIRTRIBUNE_PG_NATION_TEAM_TYPE :
      $pattern = array(
        'source' => "event/%/pilots/manage/teams/:entity_id",
      );
      $placeholders = array(':entity_id' => $entity->id);
      $conditions = array(
        'source' => strtr($pattern['source'], $placeholders),
      );
      _at_alias_delete_node_alias_multiple($conditions);
      break;
  }
}

// @todo
function _at_alias_process_event_conjugate_entities($op, $event, $type) {
  //~ $ids = _at_alias_get_conjugate_entities($event, $type);
  //~ if (!empty($nids)) {
    //~ $nodes = node_load_multiple($nids);
    //~ switch ($op) {
      //~ case 'insert' :
        //~ _at_alias_insert_event_conjugate_nodes_alias($event, $nodes, $type);
        //~ break;
      //~ case 'update' :
        //~ _at_alias_update_event_conjugate_nodes_alias($event, $nodes, $type);
        //~ break;
      //~ case 'delete' :
        //~ _at_alias_delete_event_conjugate_nodes_alias($event, $nodes, $type);
        //~ break;
    //~ }
  //~ }
}

// @todo
// $entity - ent_race or node
function _at_alias_get_conjugate_entities($entity, $type = NULL) {
  $ids = array();
  switch ($entity->type) {
    case AIRTRIBUNE_PG_RACE_TYPE :
      $og_ref_items = field_get_items(AIRTRIBUNE_RACE_ENTITY_TYPE, $entity, OG_AUDIENCE_FIELD);
      if (!empty($og_ref_items)) {
        $ids[] = $og_ref_items[0]['target_id'];
      }
      break;
    case AIRTRIBUNE_PG_NATION_TEAM_TYPE :
      $og_ref_items = field_get_items(AIRTRIBUNE_TEAM_TYPE, $entity, OG_AUDIENCE_FIELD);
      if (!empty($og_ref_items)) {
        $ids[] = $og_ref_items[0]['target_id'];
      }
      break;
  }
  return $ids;
}
