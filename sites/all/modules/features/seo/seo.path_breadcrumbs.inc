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
      1 => '%node:title',
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
  $path_breadcrumb->weight = -100;
  $export['breadcrumb_accommodation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_activity_newsblog';
  $path_breadcrumb->name = 'Activity NewsBlog';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Activity',
      1 => '%node:title',
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
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_activity_newsblog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_basic_page';
  $path_breadcrumb->name = 'Basic Page';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => '%node:title',
    ),
    'paths' => array(
      0 => '%node:url',
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
              'page' => 'page',
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
  $export['breadcrumb_basic_page'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list';
  $path_breadcrumb->name = 'Events List default by Current';
  $path_breadcrumb->path = 'events';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
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
  $path_breadcrumb->weight = -92;
  $export['breadcrumb_events_list'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_2';
  $path_breadcrumb->name = 'Events List default by Next';
  $path_breadcrumb->path = 'events';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
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
  $path_breadcrumb->weight = -93;
  $export['breadcrumb_events_list_2'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_current';
  $path_breadcrumb->name = 'Events List Current';
  $path_breadcrumb->path = 'events/current';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
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
  $path_breadcrumb->weight = -90;
  $export['breadcrumb_events_list_current'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_next';
  $path_breadcrumb->name = 'Events List Next';
  $path_breadcrumb->path = 'events/next';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
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
  $path_breadcrumb->weight = -89;
  $export['breadcrumb_events_list_next'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_events_list_past';
  $path_breadcrumb->name = 'Events List Past';
  $path_breadcrumb->path = 'events/past';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
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
  $path_breadcrumb->weight = -91;
  $export['breadcrumb_events_list_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current';
  $path_breadcrumb->name = 'Paragliding Contest Current';
  $path_breadcrumb->path = 'event/%node';
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
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/blog',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -82;
  $export['breadcrumb_pg_contest_current'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_blog';
  $path_breadcrumb->name = 'Paragliding Contest Current Blog';
  $path_breadcrumb->path = 'event/%node/blog';
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -80;
  $export['breadcrumb_pg_contest_current_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_blog_entry';
  $path_breadcrumb->name = 'Paragliding Contest Current Blog Entry';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => '%node:title',
      1 => 'Blog',
      2 => '%node:og-group-ref:0:title',
      3 => 'Current',
      4 => 'Events',
    ),
    'paths' => array(
      0 => 'node/%node:nid',
      1 => 'event/%node:og-group-ref:0:nid/blog',
      2 => 'event/%node:og-group-ref:0:nid',
      3 => 'events/current',
      4 => 'events',
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
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        2 => array(
          'name' => 'og_is_node_group_content',
          'settings' => NULL,
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -97;
  $export['breadcrumb_pg_contest_current_blog_entry'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_details';
  $path_breadcrumb->name = 'Paragliding Contest Current Details';
  $path_breadcrumb->path = 'event/%node/info/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Info',
      4 => 'Details',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
      4 => 'event/%node:nid/info/details',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        'logic' => 'and',
      ),
    ),
  );
  $path_breadcrumb->weight = -79;
  $export['breadcrumb_pg_contest_current_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_info';
  $path_breadcrumb->name = 'Paragliding Contest Current Info';
  $path_breadcrumb->path = 'event/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Info',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -81;
  $export['breadcrumb_pg_contest_current_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_map';
  $path_breadcrumb->name = 'Paragliding Contest Current Map';
  $path_breadcrumb->path = 'event/%node/map';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Event map',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -77;
  $export['breadcrumb_pg_contest_current_map'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_pilots';
  $path_breadcrumb->name = 'Paragliding Contest Current Pilots';
  $path_breadcrumb->path = 'event/%node/pilots';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Pilots',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -78;
  $export['breadcrumb_pg_contest_current_pilots'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_register';
  $path_breadcrumb->name = 'Paragliding Contest Current Register';
  $path_breadcrumb->path = 'event/%node/register';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Registration',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/register',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'current',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -76;
  $export['breadcrumb_pg_contest_current_register'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next';
  $path_breadcrumb->name = 'Paragliding Contest Next';
  $path_breadcrumb->path = 'event/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Info',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -75;
  $export['breadcrumb_pg_contest_next'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_blog';
  $path_breadcrumb->name = 'Paragliding Contest Next Blog';
  $path_breadcrumb->path = 'event/%node/blog';
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
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/blog',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -73;
  $export['breadcrumb_pg_contest_next_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_blog_entry';
  $path_breadcrumb->name = 'Paragliding Contest Next Blog Entry';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:og-group-ref:0:title',
      3 => 'Blog',
      4 => '%node:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:og-group-ref:0:nid',
      3 => 'event/%node:og-group-ref:0:nid/blog',
      4 => 'node/%node:nid',
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
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        2 => array(
          'name' => 'og_is_node_group_content',
          'settings' => NULL,
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -99;
  $export['breadcrumb_pg_contest_next_blog_entry'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_details';
  $path_breadcrumb->name = 'Paragliding Contest Next Details';
  $path_breadcrumb->path = 'event/%node/info/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Info',
      4 => 'Details',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
      4 => 'event/%node:nid/info/details',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -72;
  $export['breadcrumb_pg_contest_next_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_info';
  $path_breadcrumb->name = 'Paragliding Contest Next Info';
  $path_breadcrumb->path = 'event/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Info',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -74;
  $export['breadcrumb_pg_contest_next_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_map';
  $path_breadcrumb->name = 'Paragliding Contest Next Map';
  $path_breadcrumb->path = 'event/%node/map';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Event map',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -70;
  $export['breadcrumb_pg_contest_next_map'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_pilots';
  $path_breadcrumb->name = 'Paragliding Contest Next Pilots';
  $path_breadcrumb->path = 'event/%node/pilots';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Pilots',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -71;
  $export['breadcrumb_pg_contest_next_pilots'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_register';
  $path_breadcrumb->name = 'Paragliding Contest Next Registration';
  $path_breadcrumb->path = 'event/%node/register';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Registration',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/register',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'next',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -69;
  $export['breadcrumb_pg_contest_next_register'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past';
  $path_breadcrumb->name = 'Paragliding Contest Past';
  $path_breadcrumb->path = 'event/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Results',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/results',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -88;
  $export['breadcrumb_pg_contest_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_blog';
  $path_breadcrumb->name = 'Paragliding Contest Past Blog';
  $path_breadcrumb->path = 'event/%node/blog';
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
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/blog',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -86;
  $export['breadcrumb_pg_contest_past_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_blog_entry';
  $path_breadcrumb->name = 'Paragliding Contest Past Blog Entry';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:og-group-ref:0:title',
      3 => 'Blog',
      4 => '%node:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:og-group-ref:0:nid',
      3 => 'event/%node:og-group-ref:0:nid/blog',
      4 => 'node/%node:nid',
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
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        1 => array(
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
        2 => array(
          'name' => 'og_is_node_group_content',
          'settings' => NULL,
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -98;
  $export['breadcrumb_pg_contest_past_blog_entry'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_details';
  $path_breadcrumb->name = 'Paragliding Contest Past Details';
  $path_breadcrumb->path = 'event/%node/info/details';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Info',
      4 => 'Details',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
      4 => 'event/%node:nid/info/details',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -85;
  $export['breadcrumb_pg_contest_past_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_info';
  $path_breadcrumb->name = 'Paragliding Contest Past Info';
  $path_breadcrumb->path = 'event/%node/info';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Info',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/info',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -87;
  $export['breadcrumb_pg_contest_past_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_map';
  $path_breadcrumb->name = 'Paragliding Contest Past Map';
  $path_breadcrumb->path = 'event/%node/map';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Event map',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -83;
  $export['breadcrumb_pg_contest_past_map'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_pilots';
  $path_breadcrumb->name = 'Paragliding Contest Past Pilots';
  $path_breadcrumb->path = 'event/%node/pilots';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Pilots',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
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
          'name' => 'event_dates',
          'settings' => array(
            'status' => 'past',
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -84;
  $export['breadcrumb_pg_contest_past_pilots'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_race';
  $path_breadcrumb->name = 'Race';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => '%node:og-group-ref:0:title',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'event/%node:og-group-ref:0:nid',
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
  $path_breadcrumb->weight = -94;
  $export['breadcrumb_pg_race'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'user_register';
  $path_breadcrumb->name = 'User Register';
  $path_breadcrumb->path = 'user/register';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Register new user',
    ),
    'paths' => array(
      0 => 'user/register',
    ),
    'home' => 1,
    'translatable' => 0,
    'arguments' => NULL,
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 1,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['user_register'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'user_request_new_password';
  $path_breadcrumb->name = 'User Request new password';
  $path_breadcrumb->path = 'user/password';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Request new password',
    ),
    'paths' => array(
      0 => 'user/password',
    ),
    'home' => 1,
    'translatable' => 0,
    'arguments' => NULL,
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 1,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['user_request_new_password'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'user_sign_in';
  $path_breadcrumb->name = 'User Sign in';
  $path_breadcrumb->path = 'user';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Sign in',
    ),
    'paths' => array(
      0 => 'user',
    ),
    'home' => 1,
    'translatable' => 0,
    'arguments' => NULL,
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 1,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = 0;
  $export['user_sign_in'] = $path_breadcrumb;

  return $export;
}
