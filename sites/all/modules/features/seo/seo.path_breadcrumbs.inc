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
  $path_breadcrumb->machine_name = 'breadcrumb_activities';
  $path_breadcrumb->name = 'Activities';
  $path_breadcrumb->path = 'node/%node';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Activities',
      1 => '%node:title',
    ),
    'paths' => array(
      0 => 'activities',
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
              'activity' => 'activity',
            ),
          ),
          'context' => 'node',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -99;
  $export['breadcrumb_activities'] = $path_breadcrumb;

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
  $path_breadcrumb->weight = -95;
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
  $path_breadcrumb->weight = -94;
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
  $path_breadcrumb->weight = -91;
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
  $path_breadcrumb->weight = -92;
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
  $path_breadcrumb->weight = -89;
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
  $path_breadcrumb->weight = -88;
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
  $path_breadcrumb->weight = -90;
  $export['breadcrumb_events_list_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current';
  $path_breadcrumb->name = 'Paragliding contest Current';
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
  $path_breadcrumb->weight = -87;
  $export['breadcrumb_pg_contest_current'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_accommodation';
  $path_breadcrumb->name = 'Paragliding contest Current Accommodation Entry';
  $path_breadcrumb->path = 'event/%node/map/%accommodnode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Accommodation',
      4 => '%accommodnode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map',
      4 => 'event/%node:nid/map/%accommodnode:nid',
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
      'accommodnode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content accommodation: ID',
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
        2 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'accommodation' => 'accommodation',
            ),
          ),
          'context' => 'accommodnode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -62;
  $export['breadcrumb_pg_contest_current_accommodation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_activity';
  $path_breadcrumb->name = 'Paragliding contest Current Activities Entry';
  $path_breadcrumb->path = 'event/%node/map/%activitynode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Activities',
      4 => '%activitynode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map/activities',
      4 => 'event/%node:nid/map/%activitynode:nid',
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
      'activitynode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content activity: ID',
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
        2 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'activity' => 'activity',
            ),
          ),
          'context' => 'activitynode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -56;
  $export['breadcrumb_pg_contest_current_activity'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_activity_list';
  $path_breadcrumb->name = 'Paragliding contest Current Activities';
  $path_breadcrumb->path = 'event/%node/map/activities';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Activities',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map/activities',
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
  $path_breadcrumb->weight = -59;
  $export['breadcrumb_pg_contest_current_activity_list'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_blog';
  $path_breadcrumb->name = 'Paragliding contest Current Blog';
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
  $path_breadcrumb->weight = -83;
  $export['breadcrumb_pg_contest_current_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_blog_entry';
  $path_breadcrumb->name = 'Paragliding contest Current Blog entry';
  $path_breadcrumb->path = 'event/%eventnode/blog/%blognode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%blognode:og-group-ref:0:title',
      3 => 'Blog',
      4 => '%blognode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%blognode:og-group-ref:0:nid',
      3 => 'event/%blognode:og-group-ref:0:nid/blog',
      4 => 'event/%blognode:og-group-ref:0:nid/blog/%blognode:nid',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'eventnode' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID event',
        ),
      ),
      'blognode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID blog',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
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
          'context' => 'blognode',
          'not' => FALSE,
        ),
        3 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'blognode',
          'not' => FALSE,
        ),
        4 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'eventnode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -96;
  $export['breadcrumb_pg_contest_current_blog_entry'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_details';
  $path_breadcrumb->name = 'Paragliding contest Current Details';
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
  $path_breadcrumb->weight = -77;
  $export['breadcrumb_pg_contest_current_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_info';
  $path_breadcrumb->name = 'Paragliding contest Current Info';
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
  $path_breadcrumb->weight = -80;
  $export['breadcrumb_pg_contest_current_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_map';
  $path_breadcrumb->name = 'Paragliding contest Current Accommodation';
  $path_breadcrumb->path = 'event/%node/map';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Accommodation',
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
  $path_breadcrumb->weight = -65;
  $export['breadcrumb_pg_contest_current_map'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_pilots';
  $path_breadcrumb->name = 'Paragliding contest Current Pilots';
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
  $path_breadcrumb->weight = -74;
  $export['breadcrumb_pg_contest_current_pilots'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_pilots_by_nation';
  $path_breadcrumb->name = 'Paragliding contest Current Pilots by nation';
  $path_breadcrumb->path = 'event/%node/pilots/nation';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Pilots',
      4 => 'By nation',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
      4 => 'event/%node:nid/pilots/nation',
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
  $path_breadcrumb->weight = -71;
  $export['breadcrumb_pg_contest_current_pilots_by_nation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_pilots_by_payment_status';
  $path_breadcrumb->name = 'Paragliding contest Current Pilots by Status';
  $path_breadcrumb->path = 'event/%node/pilots/status';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Current',
      2 => '%node:title',
      3 => 'Pilots',
      4 => 'By status',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/current',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
      4 => 'event/%node:nid/pilots/status',
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
  $path_breadcrumb->weight = -68;
  $export['breadcrumb_pg_contest_current_pilots_by_payment_status'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_current_register';
  $path_breadcrumb->name = 'Paragliding contest Current Register';
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
  $path_breadcrumb->weight = -54;
  $export['breadcrumb_pg_contest_current_register'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next';
  $path_breadcrumb->name = 'Paragliding contest Next';
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
  $path_breadcrumb->weight = -85;
  $export['breadcrumb_pg_contest_next'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_accommodation';
  $path_breadcrumb->name = 'Paragliding contest Next Accommodation Entry';
  $path_breadcrumb->path = 'event/%node/map/%accommodnode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Accommodation',
      4 => '%accommodnode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map',
      4 => 'event/%node:nid/map/%accommodnode:nid',
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
      'accommodnode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content accommodation: ID',
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
        2 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'accommodation' => 'accommodation',
            ),
          ),
          'context' => 'accommodnode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -61;
  $export['breadcrumb_pg_contest_next_accommodation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_activity';
  $path_breadcrumb->name = 'Paragliding contest Next Activities Entry';
  $path_breadcrumb->path = 'event/%node/map/%activitynode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Activities',
      4 => '%activitynode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map/activities',
      4 => 'event/%node:nid/map/%activitynode:nid',
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
      'activitynode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content activity: ID',
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
        2 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'activity' => 'activity',
            ),
          ),
          'context' => 'activitynode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -55;
  $export['breadcrumb_pg_contest_next_activity'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_activity_list';
  $path_breadcrumb->name = 'Paragliding contest Next Activities';
  $path_breadcrumb->path = 'event/%node/map/activities';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Activities',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map/activities',
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
  $path_breadcrumb->weight = -58;
  $export['breadcrumb_pg_contest_next_activity_list'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_blog';
  $path_breadcrumb->name = 'Paragliding contest Next Blog';
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
  $path_breadcrumb->weight = -82;
  $export['breadcrumb_pg_contest_next_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_blog_entry';
  $path_breadcrumb->name = 'Paragliding contest Next Blog entry';
  $path_breadcrumb->path = 'event/%eventnode/blog/%blognode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%blognode:og-group-ref:0:title',
      3 => 'Blog',
      4 => '%blognode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%blognode:og-group-ref:0:nid',
      3 => 'event/%blognode:og-group-ref:0:nid/blog',
      4 => 'event/%blognode:og-group-ref:0:nid/blog/%blognode:nid',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'eventnode' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID event',
        ),
      ),
      'blognode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID blog',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
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
          'context' => 'blognode',
          'not' => FALSE,
        ),
        3 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'blognode',
          'not' => FALSE,
        ),
        4 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'eventnode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -98;
  $export['breadcrumb_pg_contest_next_blog_entry'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_details';
  $path_breadcrumb->name = 'Paragliding contest Next Details';
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
  $path_breadcrumb->weight = -76;
  $export['breadcrumb_pg_contest_next_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_info';
  $path_breadcrumb->name = 'Paragliding contest Next Info';
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
  $path_breadcrumb->weight = -79;
  $export['breadcrumb_pg_contest_next_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_map';
  $path_breadcrumb->name = 'Paragliding contest Next Accommodation';
  $path_breadcrumb->path = 'event/%node/map';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Accommodation',
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
  $path_breadcrumb->weight = -64;
  $export['breadcrumb_pg_contest_next_map'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_pilots';
  $path_breadcrumb->name = 'Paragliding contest Next Pilots';
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
  $path_breadcrumb->weight = -73;
  $export['breadcrumb_pg_contest_next_pilots'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_pilots_by_nation';
  $path_breadcrumb->name = 'Paragliding contest Next Pilots by nation';
  $path_breadcrumb->path = 'event/%node/pilots/nation';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Pilots',
      4 => 'By nation',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
      4 => 'event/%node:nid/pilots/nation',
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
  $export['breadcrumb_pg_contest_next_pilots_by_nation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_pilots_by_payment_status';
  $path_breadcrumb->name = 'Paragliding contest Next Pilots by Status';
  $path_breadcrumb->path = 'event/%node/pilots/status';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%node:title',
      3 => 'Pilots',
      4 => 'By status',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
      4 => 'event/%node:nid/pilots/status',
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
  $path_breadcrumb->weight = -67;
  $export['breadcrumb_pg_contest_next_pilots_by_payment_status'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_next_register';
  $path_breadcrumb->name = 'Paragliding contest Next Registration';
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
  $path_breadcrumb->weight = -53;
  $export['breadcrumb_pg_contest_next_register'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past';
  $path_breadcrumb->name = 'Paragliding contest Past';
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
  $path_breadcrumb->weight = -86;
  $export['breadcrumb_pg_contest_past'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_accommodation';
  $path_breadcrumb->name = 'Paragliding contest Past Accommodation Entry';
  $path_breadcrumb->path = 'event/%node/map/%accommodnode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Accommodation',
      4 => '%accommodnode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map',
      4 => 'event/%node:nid/map/%accommodnode:nid',
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
      'accommodnode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content accommodation: ID',
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
        2 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'accommodation' => 'accommodation',
            ),
          ),
          'context' => 'accommodnode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -63;
  $export['breadcrumb_pg_contest_past_accommodation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_activity';
  $path_breadcrumb->name = 'Paragliding contest Past Activities Entry';
  $path_breadcrumb->path = 'event/%node/map/%activitynode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Activities',
      4 => '%activitynode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map/activities',
      4 => 'event/%node:nid/map/%activitynode:nid',
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
      'activitynode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content activity: ID',
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
        2 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'activity' => 'activity',
            ),
          ),
          'context' => 'activitynode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -57;
  $export['breadcrumb_pg_contest_past_activity'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_activity_list';
  $path_breadcrumb->name = 'Paragliding contest Past Activities';
  $path_breadcrumb->path = 'event/%node/map/activities';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Activities',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/map/activities',
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
  $path_breadcrumb->weight = -60;
  $export['breadcrumb_pg_contest_past_activity_list'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_blog';
  $path_breadcrumb->name = 'Paragliding contest Past Blog';
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
  $path_breadcrumb->weight = -84;
  $export['breadcrumb_pg_contest_past_blog'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_blog_entry';
  $path_breadcrumb->name = 'Paragliding contest Past Blog entry';
  $path_breadcrumb->path = 'event/%eventnode/blog/%blognode';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Next',
      2 => '%blognode:og-group-ref:0:title',
      3 => 'Blog',
      4 => '%blognode:title',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/next',
      2 => 'event/%blognode:og-group-ref:0:nid',
      3 => 'event/%blognode:og-group-ref:0:nid/blog',
      4 => 'event/%blognode:og-group-ref:0:nid/blog/%blognode:nid',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'eventnode' => array(
        'position' => 1,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID event',
        ),
      ),
      'blognode' => array(
        'position' => 3,
        'argument' => 'entity_id:node',
        'settings' => array(
          'identifier' => 'Content: ID blog',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
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
          'context' => 'blognode',
          'not' => FALSE,
        ),
        3 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'newsblog' => 'newsblog',
            ),
          ),
          'context' => 'blognode',
          'not' => FALSE,
        ),
        4 => array(
          'name' => 'node_type',
          'settings' => array(
            'type' => array(
              'pg_contest' => 'pg_contest',
            ),
          ),
          'context' => 'eventnode',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -97;
  $export['breadcrumb_pg_contest_past_blog_entry'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_details';
  $path_breadcrumb->name = 'Paragliding contest Past Details';
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
  $path_breadcrumb->weight = -78;
  $export['breadcrumb_pg_contest_past_details'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_info';
  $path_breadcrumb->name = 'Paragliding contest Past Info';
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
  $path_breadcrumb->weight = -81;
  $export['breadcrumb_pg_contest_past_info'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_map';
  $path_breadcrumb->name = 'Paragliding contest Past Accommodation';
  $path_breadcrumb->path = 'event/%node/map';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Accommodation',
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
  $path_breadcrumb->weight = -66;
  $export['breadcrumb_pg_contest_past_map'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_pilots';
  $path_breadcrumb->name = 'Paragliding contest Past Pilots';
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
  $path_breadcrumb->weight = -75;
  $export['breadcrumb_pg_contest_past_pilots'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_pilots_by_nation';
  $path_breadcrumb->name = 'Paragliding contest Past Pilots by nation';
  $path_breadcrumb->path = 'event/%node/pilots/nation';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Pilots',
      4 => 'By nation',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
      4 => 'event/%node:nid/pilots/nation',
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
  $path_breadcrumb->weight = -72;
  $export['breadcrumb_pg_contest_past_pilots_by_nation'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'breadcrumb_pg_contest_past_pilots_by_payment_status';
  $path_breadcrumb->name = 'Paragliding contest Past Pilots by Status';
  $path_breadcrumb->path = 'event/%node/pilots/status';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'Events',
      1 => 'Past',
      2 => '%node:title',
      3 => 'Pilots',
      4 => 'By status',
    ),
    'paths' => array(
      0 => 'events',
      1 => 'events/past',
      2 => 'event/%node:nid',
      3 => 'event/%node:nid/pilots',
      4 => 'event/%node:nid/pilots/status',
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
  $path_breadcrumb->weight = -69;
  $export['breadcrumb_pg_contest_past_pilots_by_payment_status'] = $path_breadcrumb;

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
  $path_breadcrumb->weight = -93;
  $export['breadcrumb_pg_race'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'user_edit';
  $path_breadcrumb->name = 'User Edit';
  $path_breadcrumb->path = 'user/%uid/edit';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'My profile',
      1 => 'Edit user',
    ),
    'paths' => array(
      0 => 'user',
      1 => 'user/%uid:uid/edit',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'uid' => array(
        'position' => 1,
        'argument' => 'entity_id:user',
        'settings' => array(
          'identifier' => 'User: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 2,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -49;
  $export['user_edit'] = $path_breadcrumb;

  $path_breadcrumb = new stdClass();
  $path_breadcrumb->api_version = 1;
  $path_breadcrumb->machine_name = 'user_pilot_edit';
  $path_breadcrumb->name = 'User Pilot Edit';
  $path_breadcrumb->path = 'profile-pilot/%uid/edit';
  $path_breadcrumb->data = array(
    'titles' => array(
      0 => 'My profile',
      1 => 'Edit pilot profile',
    ),
    'paths' => array(
      0 => 'user',
      1 => 'profile-pilot/%uid:uid/edit',
    ),
    'home' => 1,
    'translatable' => 1,
    'arguments' => array(
      'uid' => array(
        'position' => 1,
        'argument' => 'entity_id:user',
        'settings' => array(
          'identifier' => 'User: ID',
        ),
      ),
    ),
    'access' => array(
      'plugins' => array(
        0 => array(
          'name' => 'role',
          'settings' => array(
            'rids' => array(
              0 => 2,
            ),
          ),
          'context' => 'logged-in-user',
          'not' => FALSE,
        ),
      ),
      'logic' => 'and',
    ),
  );
  $path_breadcrumb->weight = -48;
  $export['user_pilot_edit'] = $path_breadcrumb;

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
  $path_breadcrumb->weight = -51;
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
  $path_breadcrumb->weight = -50;
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
  $path_breadcrumb->weight = -52;
  $export['user_sign_in'] = $path_breadcrumb;

  return $export;
}
