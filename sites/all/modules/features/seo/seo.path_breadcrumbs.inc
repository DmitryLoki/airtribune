<?php
/**
 * @file
 * seo.path_breadcrumbs.inc
 */

/**
 * Implements hook_path_breadcrumbs_settings_info().
 */
function seo_path_breadcrumbs_settings_info() {
  $export = array();

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_accommodation';
  $path_breadcrumb->name = 'BreadCrumb Accommodation';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Hotels',
      1 => '%node:title-field',
    ),
    'paths' => array(
      0 => 'hotels',
      1 => '%node:url',
    ),
    'home' => 0,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'accommodation' => 'accommodation',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -95;
  $export['breadcrumb_accommodation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_activity_newsblog';
  $path_breadcrumb->name = 'BreadCrumb Activity NewsBlog';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Activity',
      1 => '%node:title-field',
    ),
    'paths' => array(
      0 => '%site:url',
      1 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -94;
  $export['breadcrumb_activity_newsblog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_current';
  $path_breadcrumb->name = 'Events List Current';
  $path_breadcrumb->path = 'events/current';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current events',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => NULL,
    'access' => array(),
  );
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_events_list_current'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_next';
  $path_breadcrumb->name = 'Events List Next';
  $path_breadcrumb->path = 'events/next';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next events',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => NULL,
    'access' => array(),
  );
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_events_list_next'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_past';
  $path_breadcrumb->name = 'Events List Past';
  $path_breadcrumb->path = 'events/past';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past events',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => NULL,
    'access' => array(),
  );
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_events_list_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => '%node:title-field',
    ),
    'paths' => array(
      0 => 'events',
      1 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_pg_contest'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_2';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest 2';
  $path_breadcrumb->path = 'event/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => '%node:title-field',
    ),
    'paths' => array(
      0 => 'events',
      1 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_pg_contest_2'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_blog';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest Blog';
  $path_breadcrumb->path = 'event/%node/blog';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => '%node:title-field',
      2 => 'Blog',
    ),
    'paths' => array(
      0 => 'events',
      1 => '%node:url',
      2 => 'event/%node:nid/blog',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_pg_contest_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest Current';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current events',
      2 => '%node:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'php',
          'settings' => array(
            'description' => 'Date comparison',
            'php' => '$match = FALSE;
$current_time = time();
if (isset($contexts[\'node\']->data)) {
  $data = $contexts[\'node\']->data;
  if (isset($data->language)) {
    $lang = $data->language;
    if (isset($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value\']) 
        && isset($data->field_dates[$lang][0][\'value2\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value <= $current_time && $value2 >= $current_time) {
        $match = TRUE;
      }
    }
    
  }
}
return $match;',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -99;
  $export['breadcrumb_pg_contest_current'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_details';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest Details';
  $path_breadcrumb->path = 'event/%node/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => '%node:title-field',
      2 => 'Details',
    ),
    'paths' => array(
      0 => 'events',
      1 => '%node:url',
      2 => 'event/%node:nid/details',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_pg_contest_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_info';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest Info';
  $path_breadcrumb->path = 'event/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => '%node:title-field',
      2 => 'Information',
    ),
    'paths' => array(
      0 => 'events',
      1 => '%node:url',
      2 => 'event/%node:nid',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_pg_contest_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest Next';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next events',
      2 => '%node:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'php',
          'settings' => array(
            'description' => 'Date comparison',
            'php' => '$match = FALSE;
$current_time = time();
if (isset($contexts[\'node\']->data)) {
  $data = $contexts[\'node\']->data;
  if (isset($data->language)) {
    $lang = $data->language;
    if (isset($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value\']) 
        && isset($data->field_dates[$lang][0][\'value2\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value > $current_time) {
        $match = TRUE;
      }
    }
    
  }
}
return $match;
return $match;',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -100;
  $export['breadcrumb_pg_contest_next'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past';
  $path_breadcrumb->name = 'BreadCrumb Paragliding Contest Past';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past events',
      2 => '%node:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => '%node:url',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'php',
          'settings' => array(
            'description' => 'Date comparison',
            'php' => '$match = FALSE;
$current_time = time();
if (isset($contexts[\'node\']->data)) {
  $data = $contexts[\'node\']->data;
  if (isset($data->language)) {
    $lang = $data->language;
    if (isset($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value\']) 
        && isset($data->field_dates[$lang][0][\'value2\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value2 < $current_time) {
        $match = TRUE;
      }
    }
    
  }
}
return $match;',
          ),
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -98;
  $export['breadcrumb_pg_contest_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_race';
  $path_breadcrumb->name = 'BreadCrumb Race';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => '%node:og-group-ref:0:title',
      1 => '%node:title-field',
    ),
    'paths' => array(
      0 => '%node:og-group-ref:0:url',
      1 => '%node:url',
    ),
    'home' => 0,
    'translatable' => 1,
    'arguments' => array(
      'node' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Node: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_race' => 'pg_race',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -97;
  $export['breadcrumb_pg_race'] = $path_breadcrumb;

  return $export;
}
