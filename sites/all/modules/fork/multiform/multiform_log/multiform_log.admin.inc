<?php

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
    $rows[] = array(l($entry->id, 'multiform/log/' . $entry->id), date('Y-m-d H:m:i', $entry->timestamp), $entry->multiform_id, $entry->timestamp);
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
  
  drupal_set_title('#' . $id . ', ' . date('Y-d-m H:m:i', $timestamp));
  
  $output = '_POST:<br />';
  $output .= kpr($post, TRUE);
  
  $output .= 'Context data:<br />';
  $output .= kpr($context_data, TRUE);
    
  return $output;
}
