<?php


function _at_alias_process_event_pages($op, $node) {
  switch ($op) {
    case 'insert' :
      _at_alias_insert_event_pages_alias($node);
      break;
    case 'update' :
      _at_alias_update_event_pages_alias($node);
      break;
    case 'delete' :
      _at_alias_delete_event_pages_alias($node);
      break;
  }
}

function _at_alias_insert_event_pages_alias($node) {
  $alias_base = _at_alias_prepare_event_alias_base($node);
  if (!empty($alias_base)) {
    _at_alias_create_event_pages_alias($node, $alias_base);
  }
}

function _at_alias_update_event_pages_alias($node) {
  $alias_base = _at_alias_prepare_event_alias_base($node);
  if (!empty($alias_base)) {
    _at_alias_create_event_pages_alias($node, $alias_base);
  }
}

function _at_alias_delete_event_pages_alias($node) {
  if (isset($node->nid)) {
    $nid = $node->nid;
    $pages_urls = _at_alias_event_pages_urls($nid);
    $pages_urls = $pages_urls['complete_urls'];
    foreach ($pages_urls as $page_url) {
      _at_alias_event_page_aliases_delete($page_url);
    }
  }
}

/**
 * Remove existing alises for path.
 */
function _at_alias_event_page_aliases_delete($url) {
  $criteria = path_load($url);
  if (!empty($criteria)) {
    $criteria = array('source' => $criteria['source']);
    path_delete($criteria);
  }
}






/**
 * Initialize urls of pages
 * @param $nid - node nid
 * @return array
 */
function _at_alias_event_pages_urls($nid) {
  $result = array();
  $result['url_base'] = "event/{$nid}";
  $result['url_pages'] = array(
    '/info',
    '/info/details',
    '/blog',
    '/pilots',
    '/pilots/status',
    '/pilots/manage',
    '/pilots/nation',
    '/map',
    '/map/accommodations',
    '/map/activities',
    '/map/basic',
    '/register',
    '/results',
    '/settings',
  );
  $result['complete_urls'][] = $result['url_base'];
  foreach ($result['url_pages'] as $url_page) {
    $result['complete_urls'][] = $result['url_base'] . $url_page;
  }
  return $result;
}





/**
 * This relates to event node form submission (alias settings)
 */
function _at_alias_substitute_event_node_path($node) {
  // Pathauto and path modules should never execute for events by themselves
  if ($node->type == AIRTRIBUNE_PG_CONTEST_TYPE) {
    // Note that $node->path is empty if node is loaded/saved programmatically
    // since it is added in form_alter (see path.module)

    // In case node is processed programmatically
    if (!empty($node->nid) && !isset($node->path)) {
      $conditions = array('source' => 'event/' . $node->nid);
      $path = _at_alias_event_path_load($conditions);
      if (!empty($path)) {
        $node->event_path = $path;
      }
    }
    // In case node is edited through node form
    elseif (isset($node->path)) {
      // Store path alias settings for further processing.
      $node->event_path = $node->path;
    }

    // We don't want path and pathauto module take any action for event nodes, i.e. to create node alias.

    // Set pathauto to FALSE to avoid pathauto_node_update_alias() processing.
    // Clear $node->path['alias'] to avoid path_node_insert() processing.
    // Remove all other path data since we don't need it any more.
    $node->path = array('pathauto' => FALSE, 'alias' => '',);
  }
}









function _at_alias_prepare_event_alias_base($node) {
  module_load_include('inc', 'pathauto');
  if (function_exists('pathauto_cleanstring') && isset($node->nid) && !empty($node->title)) {
    $nid = $node->nid;

    // Check if alias is set manually.
    if (!empty($node->event_path['alias'])) {
      $alias_base = $node->event_path['alias'];
    }
    // Else try to get pathauto pattern.
    else {
      // See pathauto_node_update_alias().
      $options = array('language' => pathauto_entity_language('node', $node));

      // Skip processing if the node has no pattern.
      if (!pathauto_pattern_load_by_entity('node', $node->type, $options['language'])) {
        return;
      }

      //~ module_load_include('inc', 'pathauto');
      $uri = entity_uri('node', $node);
      // Ask pathauto to return alias.
      $alias_base = pathauto_create_alias('node', 'return', $uri['path'], array('node' => $node), $node->type, $options['language']);
    }

    //~ // Do nothing if there is no alias set (otherwise we may blow away existing aliases...)
    //~ if (empty($alias_base)) {
      //~ return;
    //~ }
    return $alias_base;
  }
}



/**
 * Helper function.
 * Get event alias by nid.
 */
function _at_alias_get_event_alias_base($node) {
  $nid = $node->nid;
  // Check if (event) base alias exists.
  $source_base = "event/{$nid}";
  $conditions = array('source' => $source_base);
  $event_path = path_load($conditions);

  // Return FALSE if alias doesn't exist or is empty string.
  return !empty($event_path['alias']) ? $event_path['alias'] : FALSE;
}

/**
 * Create contest alias.
 */
function _at_alias_create_event_pages_alias($node, $alias_base) {
  module_load_include('inc', 'pathauto');
  if (function_exists('pathauto_cleanstring') && isset($node->nid) && !empty($node->title)) {

    $urls_init = _at_alias_event_pages_urls($node->nid);
    $url_base = $urls_init['url_base'];
    $url_pages = $urls_init['url_pages'];
    $aliases = array($alias_base => $url_base);

    // @todo: Remove aliases only on 'update', not 'insert'.
    // Remove existing alises.
    _at_alias_event_page_aliases_delete($url_base);
    foreach ($url_pages as $source) {
      $url_curr = $url_base . $source;
      _at_alias_event_page_aliases_delete($url_curr);

      //Create aliases array
      $aliases[$alias_base . $source] = $url_curr;
    }

    // Save tiny aliases.
    $tiny_path_items = field_get_items('node', $node, AIRTRIBUNE_TINY_PATH_FIELD);
    // Check that $tiny_path_items is not empty
    if (!empty($tiny_path_items) && is_array($tiny_path_items)) {
      foreach ($tiny_path_items as $tiny_path) {
        $path = array('source' => $url_base, 'alias' => $tiny_path['value']);
        path_save($path);
      }
    }

    // Save aliases.
    foreach ($aliases as $alias => $source) {
      $path = array('source' => $source, 'alias' => $alias);
      path_save($path);
    }


  }
}

/**
 * Fetch a specific URL alias from the database.
 *
 * @see path_load()
 * @see http://drupal.org/node/1160764
 */
function _at_alias_event_path_load($conditions) {
  if (is_numeric($conditions)) {
    $conditions = array('pid' => $conditions);
  }
  elseif (is_string($conditions)) {
    $conditions = array('source' => $conditions);
  }
  elseif (!is_array($conditions)) {
    return FALSE;
  }
  $select = db_select('url_alias');
  foreach ($conditions as $field => $value) {
    $select->condition($field, $value);
  }
  return $select
    ->fields('url_alias')
    ->orderBy('pid', 'DESC')
    ->execute()
    ->fetchAssoc();
}
