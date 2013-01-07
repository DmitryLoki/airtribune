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
  $path_breadcrumb->name = 'Accommodation';
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_accommodation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_activity_newsblog';
  $path_breadcrumb->name = 'Activity NewsBlog';
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
  $path_breadcrumb->weight = 0;
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
    'access' => array(),
  );
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_events_list_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_race';
  $path_breadcrumb->name = 'Race';
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_race'] = $path_breadcrumb;


  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next';
  $path_breadcrumb->name = 'Paragliding Contest Next';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value > $current_time) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_next'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_info';
  $path_breadcrumb->name = 'Paragliding Contest Next Info';
  $path_breadcrumb->path = 'node/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Information',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => '%node:url',
      3 => '%node:url/info',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value > $current_time) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_next_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_details';
  $path_breadcrumb->name = 'Paragliding Contest Next details';
  $path_breadcrumb->path = 'node/%node/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'details',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => '%node:url',
      3 => '%node:url/details',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value > $current_time) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_next_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_blog';
  $path_breadcrumb->name = 'Paragliding Contest Next Blog';
  $path_breadcrumb->path = 'node/%node/blog';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Blog',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => '%node:url',
      3 => '%node:url/blog',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
      $value = strtotime($data->field_dates[$lang][0][\'value\']);
      $value2 = strtotime($data->field_dates[$lang][0][\'value2\']);
      if ($value > $current_time) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_next_blog'] = $path_breadcrumb;


  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past';
  $path_breadcrumb->name = 'Paragliding Contest Past';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_info';
  $path_breadcrumb->name = 'Paragliding Contest Past Info';
  $path_breadcrumb->path = 'node/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Information',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => '%node:url',
      3 => '%node:url/info',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_past_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_details';
  $path_breadcrumb->name = 'Paragliding Contest Past details';
  $path_breadcrumb->path = 'node/%node/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'details',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => '%node:url',
      3 => '%node:url/details',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_past_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_blog';
  $path_breadcrumb->name = 'Paragliding Contest Past Blog';
  $path_breadcrumb->path = 'node/%node/blog';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Blog',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => '%node:url',
      3 => '%node:url/blog',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_past_blog'] = $path_breadcrumb;  


  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current';
  $path_breadcrumb->name = 'Paragliding Contest Current';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_current'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_info';
  $path_breadcrumb->name = 'Paragliding Contest Current Info';
  $path_breadcrumb->path = 'node/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Information',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => '%node:url',
      3 => '%node:url/info',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_current_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_details';
  $path_breadcrumb->name = 'Paragliding Contest Current details';
  $path_breadcrumb->path = 'node/%node/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'details',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => '%node:url',
      3 => '%node:url/details',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_current_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_blog';
  $path_breadcrumb->name = 'Paragliding Contest Current Blog';
  $path_breadcrumb->path = 'node/%node/blog';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Blog',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => '%node:url',
      3 => '%node:url/blog',
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
    if (!empty($data->field_dates[$lang][0][\'value\']) && !empty($data->field_dates[$lang][0][\'value2\'])) {
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
  $path_breadcrumb->weight = 0;
  $export['breadcrumb_pg_contest_current_blog'] = $path_breadcrumb;
  
  return $export;
}
