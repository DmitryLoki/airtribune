<?php

/**
 * @file
 * Common functions for Autocomplete Widgets module.
 */

/**
 * Fetch an array of options for the given widget.
 *
 * @param $instance
 *   A structured array describing the field instance.
 * @param $string
 *   Optional string to filter values on (used by autocomplete).
 * @param $match
 *   Operator to match filtered name against. Can be any of:
 *   'contains', 'equals', 'starts_with'
 * @param $keys
 *   Optional keys to lookup (the $string and $match arguments will be
 *   ignored).
 * @param $limit
 *   If non-zero, limit the size of the result set.
 *
 * @return
 *   An array of valid values in the form:
 *   array(
 *     key => value,
 *     ...
 *   )
 */
function _autocomplete_widgets_get_options($instance, $string = '', $match = 'contains', $keys = NULL, $limit = NULL) {
  static $results = array();

  // Create unique id for static cache.
  if (!isset($keys) || !is_array($keys)) {
    $keys = array();
  }
  $cid = $instance['field_name'] .':'. $match .':'. ($string !== '' ? $string : implode('-', $keys)) . ':' . $limit;

  if (!isset($results[$cid])) {
    switch ($instance['widget']['type']) {
      case 'autocomplete_widgets_allowvals':
        $results[$cid] = _autocomplete_widgets_get_options_allowvals($instance, $string, $match, $keys, $limit);
        break;
      case 'autocomplete_widgets_flddata':
        $results[$cid] = _autocomplete_widgets_get_options_flddata($instance, $string, $match, $keys, $limit);
        break;
      case 'autocomplete_widgets_suggested':
        $results[$cid] = _autocomplete_widgets_get_options_suggested($instance, $string, $match, $keys, $limit);
        break;
      case 'autocomplete_widgets_node_reference':
        $results[$cid] = _autocomplete_widgets_get_options_node_reference($instance, $string, $match, $keys, $limit);
        break;
      default:
        $results[$cid] = array();
    }
  }

  return $results[$cid];
}

/**
 * Fetch an array of options for the given widget (allowed values).
 *
 * Options are retrieved from the allowed values defined for the field.
 */
function _autocomplete_widgets_get_options_allowvals($instance, $string = '', $match = 'contains', $keys = NULL, $limit = NULL) {
  $field_name = $instance['field_name'];
  $allowed_values = list_allowed_values(field_info_field($field_name));
  $limit = (!isset($limit) || !is_numeric($limit)) ? count($allowed_values) : $limit;
  $case_sensitive = $instance['widget']['settings']['autocomplete_case'];
  $filter_xss = !empty($instance['widget']['settings']['autocomplete_xss']);
  $options = array();
  $count = 0; //@todo: cant the count var be replaced with a call to count()?

  foreach ($allowed_values as $key => $value) {
    if ($filter_xss) {
      // Filter all HTML in $value, then trim white spaces.
      $value = trim(filter_xss($value, array()));
    }
    if ($string === '') {
      if (isset($keys) && is_array($keys)) {
        if (in_array($key, $keys)) {
          $options[$key] = $value;
          $count++;
        }
      }
      else {
        $options[$key] = $value;
        $count++;
      }
    }
    else if ($match == 'equals') {
      if ($value == $string) {
        $options[$key] = $value;
        $count++;
      }
    }
    else {
      $pos = $case_sensitive ? strpos($value, $string) : strpos(drupal_strtolower($value), drupal_strtolower($string));
      if (($match == 'starts_with' && $pos === 0) || ($match == 'contains' && $pos !== FALSE)) {
        $options[$key] = $value;
        $count++;
      }
    }
    if ($count >= $limit) {
      break;
    }
  }

  _autocomplete_widgets_sort_options($options, $instance);

  return $options;
}

/**
 * Fetch an array of options for the given widget (field data).
 *
 * Options are retrieved from existing values for the field.
 */
function _autocomplete_widgets_get_options_flddata($instance, $string = '', $match = 'contains', $keys = NULL, $limit = NULL) {
  $table = 'field_data_' . $instance['field_name'];
  $column = $instance['field_name'] . '_value';
  $order = isset($instance['widget']['settings']['order']) ? $instance['widget']['settings']['order'] : '';
  $case_sensitive = !empty($instance['widget']['settings']['autocomplete_case']);

  $select = db_select('node', 'n');

  if (!empty($instance['widget']['settings']['obey_access_controls'])) {
    // Add entity_field_access so that node permission are respected.
    $select->addTag('node_access');

    if (!user_access('bypass node access')) {
      // If the user is able to view their own unpublished nodes, allow them
      // to see these in addition to published nodes. Check that they actually
      // have some unpublished nodes to view before adding the condition.
      if (user_access('view own unpublished content') && $own_unpublished = db_query('SELECT nid FROM {node} WHERE uid = :uid AND status = :status', array(':uid' => $GLOBALS['user']->uid, ':status' => NODE_NOT_PUBLISHED))->fetchCol()) {
        $select->condition(db_or()
          ->condition('n.status', NODE_PUBLISHED)
          ->condition('n.nid', $own_unpublished, 'IN')
        );
      }
      else {
        // If not, restrict the query to published nodes.
        $select->condition('n.status', NODE_PUBLISHED);
      }
    }
  }

  $select->join($table, 'fd', 'revision_id = n.vid');
  $select->addField('fd', $column);

  if ($string !== '') {
    switch ($match) {
      case 'equals':
        $select->condition($column, $string);
        break;
      case 'starts_with':
        $select->condition($column, $string . '%', 'LIKE');
        break;
      case 'contains':
      default:
        $select->condition($column, '%' . $string . '%', 'LIKE');
        break;
    }
  }
  elseif (isset($keys) && is_array($keys)) {
    $select->condition($column, $keys, 'IN');
  }
  if (!empty($limit)) {
    $select->range(0, $limit);
  }
  if (!empty($order)) {
    $select->orderBy($column, $order);
  }

  $rows = $select->execute()->fetchAll(PDO::FETCH_ASSOC);
  $options = array();
  foreach($rows as $row) {
    // MySQL does not do case sensitive text comparisons with Drupal's default
    // colation (utf8_general_ci) so we deal with it here after the fact.
    if (!$case_sensitive || ($case_sensitive && strpos($row[$column], $string) !== FALSE)) {
      $options[$row[$column]] = $row[$column];
    }
  }

  return $options;
}

/**
 * Fetch an array of options for the given widget (suggested).
 *
 * Options are retrieved from the suggested values defined for the field.
 */
function _autocomplete_widgets_get_options_suggested($instance, $string = '', $match = 'contains', $keys = NULL, $limit = NULL) {
  $case_sensitive = !empty($instance['widget']['settings']['autocomplete_case']);
  $options = explode("\n", $instance['widget']['settings']['suggested_values']);
  $options = array_map('trim', $options);
  $options = array_filter($options, 'strlen');

  switch ($match) {
    case 'contains':
    case 'starts_with':
      $matched_options = array();
      $string = !$case_sensitive ? strtolower($string) : $string;

      foreach ($options as $key => $option) {
        $option = !$case_sensitive ? strtolower($option) : $option;
        if ($match == 'contains' && strpos($option, $string) !== FALSE) {
          $matched_options[] = $options[$key];
        }
        elseif ($match == 'starts_with' && strpos($option, $string) === 0) {
          $matched_options[] = $options[$key];
        }
      }

      $options = $matched_options;
      break;
    case 'equals':
      if (in_array($string, $options, TRUE)) {
        $options = array($string);
      }
      break;
  }

  _autocomplete_widgets_sort_options($options, $instance);

  return $options;
}

/**
 * Fetch an array of options for the given widget (node_reference).
 *
 * Options are retrieved from the titles of the allowed node types.
 */
function _autocomplete_widgets_get_options_node_reference($instance, $string = '', $match = 'contains', $keys = NULL, $limit = NULL) {
  $field_name = $instance['field_name'];
  $table = 'field_data_' . $field_name;
  $column = $field_name . '_value';
  $options = array();
  $case_sensitive = !empty($instance['widget']['settings']['autocomplete_case']);
  $order = isset($instance['widget']['settings']['order']) ? $instance['widget']['settings']['order'] : '';

  $field_query = db_select($table, 'fd')
    ->fields('fd', array($column));

  $node_title_query = db_select('node', 'n')
    ->fields('n', array('title'))
    ->condition('n.type', $instance['widget']['settings']['allowed_node_types'], 'IN')
    ->addTag('node_access');

  $field_query = db_select('node', 'n');

  if (!empty($instance['widget']['settings']['obey_access_controls'])) {
    // Add entity_field_access so that node permission are respected.
    $field_query->addTag('node_access');

    if (!user_access('bypass node access')) {
      // If the user is able to view their own unpublished nodes, allow them
      // to see these in addition to published nodes. Check that they actually
      // have some unpublished nodes to view before adding the condition.
      if (user_access('view own unpublished content') && $own_unpublished = db_query('SELECT nid FROM {node} WHERE uid = :uid AND status = :status', array(':uid' => $GLOBALS['user']->uid, ':status' => NODE_NOT_PUBLISHED))->fetchCol()) {
        $field_query->condition(db_or()
          ->condition('n.status', NODE_PUBLISHED)
          ->condition('n.nid', $own_unpublished, 'IN')
        );
        $node_title_query->condition(db_or()
          ->condition('n.status', NODE_PUBLISHED)
          ->condition('n.nid', $own_unpublished, 'IN')
        );
      }
      else {
        // If not, restrict the query to published nodes.
        $field_query->condition('n.status', NODE_PUBLISHED);
        $node_title_query->condition('n.status', NODE_PUBLISHED);
      }
    }
  }

  $field_query->join($table, 'fd', 'revision_id = n.vid');
  $field_query->addField('fd', $column);

  if (!empty($order)) {
    $field_query->orderBy($column, $order);
    $node_title_query->orderBy('title', $order);
  }

  if ($string !== '') {
    switch ($match) {
      case 'starts_with':
        $field_query->condition($column, $string . '%', 'LIKE');
        $node_title_query->condition('n.title', $string . '%', 'LIKE');
        break;
      case 'contains':
      default:
        $field_query->condition($column, '%' . $string . '%', 'LIKE');
        $node_title_query->condition('n.title', '%' . $string . '%', 'LIKE');
        break;
    }

    // @todo: can these fetch all's be replaced with fetchAssoc?
    // MySQL does not do case sensitive text comparisons with Drupal's default
    // colation (utf8_general_ci) so we deal with it here after the fact.
    $rows = $node_title_query->execute()->fetchAll(PDO::FETCH_ASSOC);
    foreach($rows as $row) {
      if (!$case_sensitive || ($case_sensitive && strpos($row['title'], $string) !== FALSE)) {
        $options[$row['title']] = $row['title'];
      }
    }
    $rows = $field_query->execute()->fetchAll(PDO::FETCH_ASSOC);
    foreach($rows as $row) {
      if (!$case_sensitive || ($case_sensitive && strpos($row[$column], $string) !== FALSE)) {
        $options[$row[$column]] = $row[$column];
      }
    }
  }

  // @todo: limit should be accounted for here...
  return $options;
}

/**
 * Validate a list autocomplete element.
 */
function _autocomplete_widgets_validate_allowvals($element, &$form_state) {
  $instance = field_widget_instance($element, $form_state);
  if ($instance['widget']['type'] == 'autocomplete_widgets_allowvals') {
    $label = $element['#value'];
    if ($label !== '') {
      module_load_include('inc', 'autocomplete_widgets', 'autocomplete_widgets.common');
      $options = _autocomplete_widgets_get_options($instance, $label, 'equals', NULL, 1);
      if (empty($options)) {
        form_error($element, t('%name: %label is not a valid option for this field.', array('%name' => $instance['label'], '%label' => $label)));
      }
    }
  }
}

/**
 * Sort an array of options fo the given field instance.
 */
function _autocomplete_widgets_sort_options(&$options, $instance) {
  if (isset($instance['widget']['settings']['order'])) {
    switch ($instance['widget']['settings']['order']) {
      case 'ASC':
        asort($options);
        break;
      case 'DESC':
        arsort($options);
        break;
    }
  }
}

