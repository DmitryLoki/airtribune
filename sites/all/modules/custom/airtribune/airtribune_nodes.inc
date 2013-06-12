<?php
/**
 * @file
 * airtribune_nodes.inc
 * 
 * Definitions of node types moved from features
 * 
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @see #2860
 */


/**
 * Implements hook_node_info().
 */
function airtribune_node_info() {
  $items = array(
    'accommodation' => array(
      'name' => t('Accommodation'),
      'base' => 'accommodation',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'activity' => array(
      'name' => t('Activity'),
      'base' => 'activity',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'advert' => array(
      'name' => t('Advertisement'),
      'base' => 'advert',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'dayblog' => array(
      'name' => t('Day blog'),
      'base' => 'dayblog',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'newsblog' => array(
      'name' => t('Blog'),
      'base' => 'newsblog',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'pg_scoring_category' => array(
      'name' => t('Scoring category'),
      'base' => 'pg_scoring_category',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'pg_contest' => array(
      'name' => t('Paragliding Contest'),
      'base' => 'pg_contest',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Name'),
      'help' => '',
    ),
  );
  return $items;
}
