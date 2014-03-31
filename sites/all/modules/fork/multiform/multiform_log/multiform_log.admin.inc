<?php

// @todo: Add range to the search form.

function multiform_log_list_page() {
  $result = db_select('multiform_log', 'a')
    ->fields('a')
    ->extend('PagerDefault')->limit(10)
    ->execute()
    ->fetchAll();

  $header = array('#', 'time', 'multiform_id', 'timestamp');
  //~ $header = array('#', 'time', 'multiform_id', 'timestamp' => array('data' => 'timestamp', 'field' => 'timestamp'));
  $rows = array();

  foreach ($result as $entry) {
    $rows[] = array(l($entry->id, 'multiform/log/' . $entry->id), date('Y-m-d H:i:s', $entry->timestamp), $entry->multiform_id, $entry->timestamp);
  }

  $table = array(
    'header' => $header,
    'rows' => $rows,
  );

  $output = theme('table', $table);
  $output .= theme('pager', array('tags' => array()));
  return $output;
}


function multiform_log_entry_page($id) {
  $result = db_select('multiform_log', 'a')
    ->fields('a')
    ->condition('id', $id,'=')
    ->execute()
    ->fetchAssoc();

  if (empty($result)) {
    drupal_not_found();
  }


  $id = $result['id'];
  $timestamp = $result['timestamp'];
  $multiform_id = $result['multiform_id'];
  $context_data = unserialize($result['context_data']);
  $post = unserialize($result['post_array']);

  drupal_set_title('#' . $id . ', ' . date('Y-m-d H:i:s', $timestamp));

  $output = '_POST:<br />';
  $output .= kpr($post, TRUE);

  $output .= 'Context data:<br />';
  $output .= kpr($context_data, TRUE);

  return $output;
}


function multiform_log_search() {
  return drupal_get_form('multiform_log_search_form');
}

function multiform_log_search_form($form, $form_state) {
  $form['search_result'] = array(
    '#markup' => !empty($_GET['search']) ? multiform_search_result($_GET['search']) : '',
  );
  $form['search_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Search string'),
    '#default_value' => !empty($_GET['search']) ? $_GET['search'] : '',
    '#required' => TRUE,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
  );

  if (!empty($form_state['search_result'])) {
    $form['search_result'] = array(
      '#markup' => $form_state['search_result'],
    );
  }
  return $form;
}

function multiform_log_search_form_submit($form, &$form_state) {
  $search_string = $form_state['values']['search_string'];
  drupal_goto('multiform/log/search', array('query' => array('search' => $search_string)));
}

function multiform_log_search_array($haystack, $needle, &$matches, $current_path = array()) {
  foreach ($haystack as $k => $v) {
    if (!is_array($v) && strpos($v, $needle) !== FALSE) {
      $new_path = $current_path;
      $new_path[] = $k;
      $new_path[] = "Contents: {$v}";
      $matches[] = $new_path;
    }
    elseif(is_array($v)) {
      $new_path = $current_path;
      $new_path[] = $k;
      multiform_log_search_array($v, $needle, $matches, $new_path);
    }
  }
}

function multiform_search_result($search_string) {
  $output = '';

  $result = db_select('multiform_log', 'a')
    ->fields('a')
    ->execute()
    ->fetchAll();

  foreach ($result as $entry) {
    if (strpos($entry->post_array, $search_string) !== FALSE) {
      $output .= kpr($entry, TRUE);
      $matches = array();
      $haystack = unserialize($entry->post_array);
      multiform_log_search_array($haystack, $search_string, $matches);
      $output .= kpr($matches, TRUE);
    }
  }
  return $output;
}
