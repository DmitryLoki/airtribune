<?php
/**
 * @file
 * views_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function views_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'activity';
  $view->description = 'Emulates the default Drupal front page; you may set the default home page path to this view to make it your front page.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Activity';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* Sort criterion: Content: Sticky */
  $handler->display->display_options['sorts']['sticky']['id'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['table'] = 'node';
  $handler->display->display_options['sorts']['sticky']['field'] = 'sticky';
  $handler->display->display_options['sorts']['sticky']['order'] = 'DESC';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Promoted to front page */
  $handler->display->display_options['filters']['promote']['id'] = 'promote';
  $handler->display->display_options['filters']['promote']['table'] = 'node';
  $handler->display->display_options['filters']['promote']['field'] = 'promote';
  $handler->display->display_options['filters']['promote']['value'] = '1';
  $handler->display->display_options['filters']['promote']['group'] = 0;
  $handler->display->display_options['filters']['promote']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'activity';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Front page feed';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'rss.xml';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'page' => 'page',
  );
  $handler->display->display_options['sitename_title'] = '1';
  $translatables['activity'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Page'),
    t('Feed'),
    t('Front page feed'),
  );
  $export['activity'] = $view;

  $view = new view();
  $view->name = 'admin_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'og_membership';
  $view->human_name = 'Admin events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Pilot events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    7 => '7',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_dates' => 'field_dates',
    'field_contestant_number' => 'field_contestant_number',
    'field_pg_contestant_status' => 'field_pg_contestant_status',
    'edit_og_membership' => 'edit_og_membership',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_dates' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contestant_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pg_contestant_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_og_membership' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Empty result.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['required'] = TRUE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_dates']['label'] = 'Start date';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'dmy',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: OG membership: Pilot's number */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  /* Field: OG membership: OG membership edit link */
  $handler->display->display_options['fields']['edit_og_membership']['id'] = 'edit_og_membership';
  $handler->display->display_options['fields']['edit_og_membership']['table'] = 'views_entity_og_membership';
  $handler->display->display_options['fields']['edit_og_membership']['field'] = 'edit_og_membership';
  $handler->display->display_options['fields']['edit_og_membership']['label'] = 'Membership edit';
  /* Sort criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['sorts']['field_dates_value']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'og_membership_related_user';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid']['title'] = 'Pilot events: %1';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: OG membership: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'og_membership';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contestant' => 'pg_contestant',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/people/pilots/events';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Pilot events';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['admin_events'] = array(
    t('Master'),
    t('Pilot events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Empty result.'),
    t('user from OG membership'),
    t('Group node from OG membership'),
    t('Title'),
    t('Start date'),
    t('Pilot\'s number'),
    t('Payment status'),
    t('Membership edit'),
    t('All'),
    t('Pilot events: %1'),
    t('Page'),
  );
  $export['admin_events'] = $view;

  $view = new view();
  $view->name = 'admin_pilots';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Admin pilots';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Pilots';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    7 => '7',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'uid' => 'uid',
    'field_full_name' => 'field_full_name',
    'mail' => 'mail',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'uid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_full_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Empty result.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'main' => 'main',
  );
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['exclude'] = TRUE;
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['path'] = 'user/[uid]';
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'User events';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'events';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'admin/people/pilots/events/[uid]';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['masquerade_as']['id'] = 'masquerade_as';
  $handler->display->display_options['fields']['masquerade_as']['table'] = 'users';
  $handler->display->display_options['fields']['masquerade_as']['field'] = 'masquerade_as';
  $handler->display->display_options['fields']['masquerade_as']['label'] = 'Masquerade';
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    6 => '6',
  );
  $handler->display->display_options['filters']['rid']['group'] = 1;
  /* Filter criterion: Profile: Name */
  $handler->display->display_options['filters']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['filters']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['filters']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['filters']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['filters']['field_full_name']['operator'] = 'allwords';
  $handler->display->display_options['filters']['field_full_name']['group'] = 1;
  $handler->display->display_options['filters']['field_full_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_full_name']['expose']['operator_id'] = 'field_full_name_op';
  $handler->display->display_options['filters']['field_full_name']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['field_full_name']['expose']['operator'] = 'field_full_name_op';
  $handler->display->display_options['filters']['field_full_name']['expose']['identifier'] = 'field_full_name';
  $handler->display->display_options['filters']['field_full_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_full_name']['group_info']['label'] = 'Name';
  $handler->display->display_options['filters']['field_full_name']['group_info']['identifier'] = 'field_full_name';
  $handler->display->display_options['filters']['field_full_name']['group_info']['group_items'] = array(
    1 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
    2 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
    3 => array(
      'title' => '',
      'operator' => 'contains',
      'value' => '',
    ),
  );
  /* Filter criterion: User: E-mail */
  $handler->display->display_options['filters']['mail']['id'] = 'mail';
  $handler->display->display_options['filters']['mail']['table'] = 'users';
  $handler->display->display_options['filters']['mail']['field'] = 'mail';
  $handler->display->display_options['filters']['mail']['operator'] = 'contains';
  $handler->display->display_options['filters']['mail']['group'] = 1;
  $handler->display->display_options['filters']['mail']['exposed'] = TRUE;
  $handler->display->display_options['filters']['mail']['expose']['operator_id'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['label'] = 'E-mail';
  $handler->display->display_options['filters']['mail']['expose']['operator'] = 'mail_op';
  $handler->display->display_options['filters']['mail']['expose']['identifier'] = 'mail';
  $handler->display->display_options['filters']['mail']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    7 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/people/pilots';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Pilots';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['admin_pilots'] = array(
    t('Master'),
    t('Pilots'),
    t('more'),
    t('Search'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Empty result.'),
    t('Profile'),
    t('Uid'),
    t('Name'),
    t('E-mail'),
    t('User events'),
    t('events'),
    t('Masquerade'),
    t('Page'),
  );
  $export['admin_pilots'] = $view;

  $view = new view();
  $view->name = 'advert_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Event Sponsors List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Partners';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_link' => 'field_link',
    'field_image' => 'field_image',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_link' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_image' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Draggableviews: Content */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['link_to_entity'] = 1;
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Field: Field: Link */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'self';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 0;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'advert' => 'advert',
  );

  /* Display: Event Sponsors */
  $handler = $view->new_display('panel_pane', 'Event Sponsors', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php print l(t(\'Add partner\'), \'node/add/advert\', array(\'query\' => array(\'og_group_ref\' => !1)));?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no partners added yet for the current event.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Event Banners */
  $handler = $view->new_display('panel_pane', 'Event Banners', 'panel_pane_2');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Banner blank 200x140 */
  $handler->display->display_options['empty']['area_1']['id'] = 'area_1';
  $handler->display->display_options['empty']['area_1']['table'] = 'views';
  $handler->display->display_options['empty']['area_1']['field'] = 'area';
  $handler->display->display_options['empty']['area_1']['ui_name'] = 'Banner blank 200x140';
  $handler->display->display_options['empty']['area_1']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_1']['content'] = '<div><a href="#"><img src="/sites/default/files/Sponsors200x140blank.png"/></a></div>';
  $handler->display->display_options['empty']['area_1']['format'] = 'full_html';
  /* No results behavior: Banner blank 200x200 */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['ui_name'] = 'Banner blank 200x200';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<div><a href="#"><img src="/sites/default/files/Sponsors200x200blank.png"/></a></div>';
  $handler->display->display_options['empty']['area']['format'] = 'full_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Link (excluded) */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['ui_name'] = 'Link (excluded)';
  $handler->display->display_options['fields']['field_link']['label'] = '';
  $handler->display->display_options['fields']['field_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['path'] = '[field_link]';
  $handler->display->display_options['fields']['field_image']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['field_image']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'advert_list:panel_pane_1';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Site Partners */
  $handler = $view->new_display('page', 'Site Partners', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Partners';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
    3 => '3',
  );
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<?php print l(t(\'Add partner\'), \'node/add/advert\');?>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no sponsors added yet.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'advert' => 'advert',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: OG membership: Og membership ID */
  $handler->display->display_options['filters']['id']['id'] = 'id';
  $handler->display->display_options['filters']['id']['table'] = 'og_membership';
  $handler->display->display_options['filters']['id']['field'] = 'id';
  $handler->display->display_options['filters']['id']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['id']['operator'] = 'empty';
  $handler->display->display_options['filters']['id']['group'] = 1;
  $handler->display->display_options['path'] = 'partners';

  /* Display: Site banners */
  $handler = $view->new_display('panel_pane', 'Site banners', 'panel_pane_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Partners';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Link (excluded) */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['ui_name'] = 'Link (excluded)';
  $handler->display->display_options['fields']['field_link']['label'] = '';
  $handler->display->display_options['fields']['field_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['path'] = '[field_link]';
  $handler->display->display_options['fields']['field_image']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['field_image']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'advert_list:page_1';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 0;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'advert' => 'advert',
  );
  /* Filter criterion: OG membership: Og membership ID */
  $handler->display->display_options['filters']['id']['id'] = 'id';
  $handler->display->display_options['filters']['id']['table'] = 'og_membership';
  $handler->display->display_options['filters']['id']['field'] = 'id';
  $handler->display->display_options['filters']['id']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['id']['operator'] = 'empty';
  $translatables['advert_list'] = array(
    t('Master'),
    t('Partners'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from node'),
    t('Content'),
    t('Title'),
    t('Image'),
    t('Link'),
    t('Edit link'),
    t('Delete link'),
    t('All'),
    t('Event Sponsors'),
    t('<?php print l(t(\'Add partner\'), \'node/add/advert\', array(\'query\' => array(\'og_group_ref\' => !1)));?>'),
    t('There are no partners added yet for the current event.'),
    t('View panes'),
    t('Event Banners'),
    t('<div><a href="#"><img src="/sites/default/files/Sponsors200x140blank.png"/></a></div>'),
    t('<div><a href="#"><img src="/sites/default/files/Sponsors200x200blank.png"/></a></div>'),
    t('Site Partners'),
    t('<?php print l(t(\'Add partner\'), \'node/add/advert\');?>'),
    t('There are no sponsors added yet.'),
    t('Site banners'),
  );
  $export['advert_list'] = $view;

  $view = new view();
  $view->name = 'advert_on_visualization';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_ent_advert';
  $view->human_name = 'Advert on Visualization';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: OG membership: OG membership from Advertisement */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_advert';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Field: Field: Link */
  $handler->display->display_options['fields']['field_link']['id'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['table'] = 'field_data_field_link';
  $handler->display->display_options['fields']['field_link']['field'] = 'field_link';
  $handler->display->display_options['fields']['field_link']['label'] = '';
  $handler->display->display_options['fields']['field_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_link']['click_sort_column'] = 'url';
  /* Field: Field: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_image']['alter']['path'] = '[field_link]';
  $handler->display->display_options['fields']['field_image']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'advert_on_visualization',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Advertisement: ent_advert type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_ent_advert';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'advert_visualisation' => 'advert_visualisation',
  );

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );
  $translatables['advert_on_visualization'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('OG membership from ent_advert'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['advert_on_visualization'] = $view;

  $view = new view();
  $view->name = 'category_results';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'Category results';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['display_comment'] = 'This view is used as subquery in "Category results" view."';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Race */
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['id'] = 'field_competition_results_ent_race';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['field'] = 'field_competition_results_ent_race';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['ui_name'] = 'Race';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['label'] = 'Race';
  /* Relationship: Scoring category */
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['id'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['table'] = 'field_data_field_scoring_category_ref';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['field'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['ui_name'] = 'Scoring category';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['label'] = 'Scoring category';
  /* Field: Scoring category - excluded */
  $handler->display->display_options['fields']['field_pg_scoring_category']['id'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['table'] = 'field_data_field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['field'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['relationship'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['fields']['field_pg_scoring_category']['ui_name'] = 'Scoring category - excluded';
  $handler->display->display_options['fields']['field_pg_scoring_category']['label'] = '';
  $handler->display->display_options['fields']['field_pg_scoring_category']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_label_colon'] = FALSE;
  /* Field: Results file - overriden */
  $handler->display->display_options['fields']['field_results_file']['id'] = 'field_results_file';
  $handler->display->display_options['fields']['field_results_file']['table'] = 'field_data_field_results_file';
  $handler->display->display_options['fields']['field_results_file']['field'] = 'field_results_file';
  $handler->display->display_options['fields']['field_results_file']['ui_name'] = 'Results file - overriden';
  $handler->display->display_options['fields']['field_results_file']['label'] = '';
  $handler->display->display_options['fields']['field_results_file']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_results_file']['alter']['text'] = '[field_pg_scoring_category] results';
  $handler->display->display_options['fields']['field_results_file']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_results_file']['alter']['path'] = '[field_results_file]';
  $handler->display->display_options['fields']['field_results_file']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_results_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_results_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_results_file']['type'] = 'file_url_plain';
  /* Sort criterion: Post day */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'eck_ent_race';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'field_competition_results_ent_race';
  $handler->display->display_options['sorts']['created']['ui_name'] = 'Post day';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Scoring category */
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['id'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['table'] = 'field_data_field_scoring_category_ref';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['field'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['ui_name'] = 'Scoring category';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_scoring_category_ref_target_id']['validate_options']['types'] = array(
    'pg_scoring_category' => 'pg_scoring_category',
  );
  /* Filter criterion: Field collection field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['ui_name'] = 'Field collection field name';
  $handler->display->display_options['filters']['field_name']['value'] = array(
    'field_competition_results' => 'field_competition_results',
  );
  $translatables['category_results'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Race'),
    t('Scoring category'),
    t('[field_pg_scoring_category] results'),
    t('All'),
  );
  $export['category_results'] = $view;

  $view = new view();
  $view->name = 'contest_blog';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Contest blog';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Post date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'strong';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'race_date';
  /* Field: Tile */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Tile';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'p';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: View more link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['ui_name'] = 'View more link';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'View more';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['exception']['title'] = 'Все';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'newsblog' => 'newsblog',
  );

  /* Display: Contest pane */
  $handler = $view->new_display('panel_pane', 'Contest pane', 'contest_pane');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['display_description'] = 'This pane will be shown at the event info page.';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Blog ID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Blog ID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Post date - excluded */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Post date - excluded';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['exclude'] = TRUE;
  $handler->display->display_options['fields']['created']['element_type'] = 'strong';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'race_date';
  /* Field: Title field - excluded */
  $handler->display->display_options['fields']['title_field']['id'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['table'] = 'field_data_title_field';
  $handler->display->display_options['fields']['title_field']['field'] = 'title_field';
  $handler->display->display_options['fields']['title_field']['ui_name'] = 'Title field - excluded';
  $handler->display->display_options['fields']['title_field']['label'] = '';
  $handler->display->display_options['fields']['title_field']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_field']['type'] = 'text_plain';
  $handler->display->display_options['fields']['title_field']['link_to_entity'] = 0;
  /* Field: Tile - rewrited */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Tile - rewrited';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<strong>[created]</strong><span class="blog_title"><span class="blog_title_inner">[title_field]</span><span class="view-more"><span>[nothing]</span></span></span>';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/blog/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'p';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.og-group-ref--og-membership--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Contest full pane */
  $handler = $view->new_display('panel_pane', 'Contest full pane', 'contest_full_pane');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Preparation blog';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'event_blog_teaser';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Next contest blog */
  $handler = $view->new_display('panel_pane', 'Next contest blog', 'next_contest');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['view_mode'] = 'event_blog_teaser';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );
  $translatables['contest_blog'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from node'),
    t('View more'),
    t('Все'),
    t('Contest pane'),
    t('This pane will be shown at the event info page.'),
    t('<strong>[created]</strong><span class="blog_title"><span class="blog_title_inner">[title_field]</span><span class="view-more"><span>[nothing]</span></span></span>'),
    t('View panes'),
    t('Contest full pane'),
    t('Preparation blog'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Next contest blog'),
  );
  $export['contest_blog'] = $view;

  $view = new view();
  $view->name = 'contest_scoring_categories';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Contest scoring categories';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: OG membership from node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'OG membership from node';
  /* Field: Nid - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Nid - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Winners photo */
  $handler->display->display_options['fields']['field_single_image']['id'] = 'field_single_image';
  $handler->display->display_options['fields']['field_single_image']['table'] = 'field_data_field_single_image';
  $handler->display->display_options['fields']['field_single_image']['field'] = 'field_single_image';
  $handler->display->display_options['fields']['field_single_image']['ui_name'] = 'Winners photo';
  $handler->display->display_options['fields']['field_single_image']['label'] = '';
  $handler->display->display_options['fields']['field_single_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_single_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_single_image']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_single_image']['settings'] = array(
    'colorbox_node_style' => 'scoring_winner',
    'colorbox_image_style' => 'large',
    'colorbox_gallery' => 'field_page',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_single_image']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_single_image']['group_columns'] = array(
    'fid' => 'fid',
  );
  /* Field: Scoring photo */
  $handler->display->display_options['fields']['field_pg_scoring_category']['id'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['table'] = 'field_data_field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['field'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['ui_name'] = 'Scoring photo';
  $handler->display->display_options['fields']['field_pg_scoring_category']['label'] = '';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_default_classes'] = FALSE;
  /* Field: Winners */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Winners';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'contest_winners';
  $handler->display->display_options['fields']['view']['arguments'] = '!1/[nid]';
  /* Field: Results story */
  $handler->display->display_options['fields']['field_results_story']['id'] = 'field_results_story';
  $handler->display->display_options['fields']['field_results_story']['table'] = 'field_data_field_results_story';
  $handler->display->display_options['fields']['field_results_story']['field'] = 'field_results_story';
  $handler->display->display_options['fields']['field_results_story']['ui_name'] = 'Results story';
  $handler->display->display_options['fields']['field_results_story']['label'] = '';
  $handler->display->display_options['fields']['field_results_story']['element_label_colon'] = FALSE;
  /* Field: Results files */
  $handler->display->display_options['fields']['view_1']['id'] = 'view_1';
  $handler->display->display_options['fields']['view_1']['table'] = 'views';
  $handler->display->display_options['fields']['view_1']['field'] = 'view';
  $handler->display->display_options['fields']['view_1']['ui_name'] = 'Results files';
  $handler->display->display_options['fields']['view_1']['label'] = '';
  $handler->display->display_options['fields']['view_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_1']['view'] = 'category_results';
  $handler->display->display_options['fields']['view_1']['arguments'] = '[!nid]';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'pg_scoring_categories:page';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 0;
  /* Contextual filter: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['ui_name'] = 'Group ID';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_scoring_category' => 'pg_scoring_category',
  );

  /* Display: Results pane */
  $handler = $view->new_display('panel_pane', 'Results pane', 'results_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership from node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'OG membership from node';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Nid - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Nid - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Winners photo */
  $handler->display->display_options['fields']['field_single_image']['id'] = 'field_single_image';
  $handler->display->display_options['fields']['field_single_image']['table'] = 'field_data_field_single_image';
  $handler->display->display_options['fields']['field_single_image']['field'] = 'field_single_image';
  $handler->display->display_options['fields']['field_single_image']['ui_name'] = 'Winners photo';
  $handler->display->display_options['fields']['field_single_image']['label'] = '';
  $handler->display->display_options['fields']['field_single_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_single_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_single_image']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_single_image']['settings'] = array(
    'colorbox_node_style' => 'scoring_winner',
    'colorbox_image_style' => 'large',
    'colorbox_gallery' => 'field_page',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_single_image']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_single_image']['group_columns'] = array(
    'fid' => 'fid',
  );
  /* Field: Scoring photo */
  $handler->display->display_options['fields']['field_pg_scoring_category']['id'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['table'] = 'field_data_field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['field'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['ui_name'] = 'Scoring photo';
  $handler->display->display_options['fields']['field_pg_scoring_category']['label'] = '';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_default_classes'] = FALSE;
  /* Field: Winners */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Winners';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'contest_winners';
  $handler->display->display_options['fields']['view']['arguments'] = '!1/[nid]';
  /* Field: Results story */
  $handler->display->display_options['fields']['field_results_story']['id'] = 'field_results_story';
  $handler->display->display_options['fields']['field_results_story']['table'] = 'field_data_field_results_story';
  $handler->display->display_options['fields']['field_results_story']['field'] = 'field_results_story';
  $handler->display->display_options['fields']['field_results_story']['ui_name'] = 'Results story';
  $handler->display->display_options['fields']['field_results_story']['label'] = '';
  $handler->display->display_options['fields']['field_results_story']['element_label_colon'] = FALSE;
  /* Field: Results files */
  $handler->display->display_options['fields']['view_1']['id'] = 'view_1';
  $handler->display->display_options['fields']['view_1']['table'] = 'views';
  $handler->display->display_options['fields']['view_1']['field'] = 'view';
  $handler->display->display_options['fields']['view_1']['ui_name'] = 'Results files';
  $handler->display->display_options['fields']['view_1']['label'] = '';
  $handler->display->display_options['fields']['view_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_1']['view'] = 'category_results';
  $handler->display->display_options['fields']['view_1']['arguments'] = '[!nid]';
  /* Field: Content: Sponsors */
  $handler->display->display_options['fields']['field_collection_sponsors']['id'] = 'field_collection_sponsors';
  $handler->display->display_options['fields']['field_collection_sponsors']['table'] = 'field_data_field_collection_sponsors';
  $handler->display->display_options['fields']['field_collection_sponsors']['field'] = 'field_collection_sponsors';
  $handler->display->display_options['fields']['field_collection_sponsors']['label'] = '';
  $handler->display->display_options['fields']['field_collection_sponsors']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_collection_sponsors']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_collection_sponsors']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_collection_sponsors']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_scoring_category' => 'pg_scoring_category',
  );
  /* Filter criterion: Content: Results story (field_results_story) */
  $handler->display->display_options['filters']['field_results_story_value']['id'] = 'field_results_story_value';
  $handler->display->display_options['filters']['field_results_story_value']['table'] = 'field_data_field_results_story';
  $handler->display->display_options['filters']['field_results_story_value']['field'] = 'field_results_story_value';
  $handler->display->display_options['filters']['field_results_story_value']['operator'] = 'not empty';
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Awards pane */
  $handler = $view->new_display('panel_pane', 'Awards pane', 'awards_pane');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Prize fund and scoring categories';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Awards photos */
  $handler->display->display_options['fields']['field_awards_photos']['id'] = 'field_awards_photos';
  $handler->display->display_options['fields']['field_awards_photos']['table'] = 'field_data_field_awards_photos';
  $handler->display->display_options['fields']['field_awards_photos']['field'] = 'field_awards_photos';
  $handler->display->display_options['fields']['field_awards_photos']['ui_name'] = 'Awards photos';
  $handler->display->display_options['fields']['field_awards_photos']['label'] = '';
  $handler->display->display_options['fields']['field_awards_photos']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_awards_photos']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_awards_photos']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_awards_photos']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_awards_photos']['settings'] = array(
    'colorbox_node_style' => 'award',
    'colorbox_image_style' => 'large',
    'colorbox_gallery' => 'field_post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_awards_photos']['delta_offset'] = '0';
  /* Field: Scoring category */
  $handler->display->display_options['fields']['field_pg_scoring_category']['id'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['table'] = 'field_data_field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['field'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['ui_name'] = 'Scoring category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['label'] = '';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Group ID',
    ),
  );

  /* Display: Awards pane with sponsors */
  $handler = $view->new_display('panel_pane', 'Awards pane with sponsors', 'awards_pane_with_sponsors');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Prize fund and scoring categories';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['links'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Scoring category */
  $handler->display->display_options['fields']['field_pg_scoring_category']['id'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['table'] = 'field_data_field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['field'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['ui_name'] = 'Scoring category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['label'] = '';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_label_colon'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Group ID',
    ),
  );
  $translatables['contest_scoring_categories'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from node'),
    t('All'),
    t('Results pane'),
    t('View panes'),
    t('Awards pane'),
    t('Prize fund and scoring categories'),
    t('Awards pane with sponsors'),
  );
  $export['contest_scoring_categories'] = $view;

  $view = new view();
  $view->name = 'contest_trackers';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_ent_tracker';
  $view->human_name = 'Contest trackers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_tracker_og_membership']['id'] = 'reverse_field_tracker_og_membership';
  $handler->display->display_options['relationships']['reverse_field_tracker_og_membership']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['relationships']['reverse_field_tracker_og_membership']['field'] = 'reverse_field_tracker_og_membership';
  /* Field: Tracker: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Sort criterion: Tracker: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'reverse_field_tracker_og_membership';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  /* Contextual filter: OG membership: Og membership ID */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['relationship'] = 'reverse_field_tracker_og_membership';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['id']['not'] = TRUE;

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'trackers_by_contest');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['default_argument_options']['argument'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null_1']['default_argument_options']['argument'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Tracker: Id */
  $handler->display->display_options['arguments']['id_1']['id'] = 'id_1';
  $handler->display->display_options['arguments']['id_1']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['arguments']['id_1']['field'] = 'id';
  $handler->display->display_options['arguments']['id_1']['default_action'] = 'default';
  $handler->display->display_options['arguments']['id_1']['default_argument_type'] = 'php';
  $handler->display->display_options['arguments']['id_1']['default_argument_options']['code'] = 'return _at_get_contest_trackers($view->args[0], $view->args[1]);';
  $handler->display->display_options['arguments']['id_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['id_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['id_1']['validate']['fail'] = 'ignore';
  $handler->display->display_options['arguments']['id_1']['break_phrase'] = TRUE;
  $handler->display->display_options['arguments']['id_1']['not'] = TRUE;
  $translatables['contest_trackers'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership referencing Tracker from field_tracker'),
    t('All'),
    t('Entity Reference'),
  );
  $export['contest_trackers'] = $view;

  $view = new view();
  $view->name = 'contest_winners';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Contest winners';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['display_comment'] = 'This view used in "Contest scoring categories" as view_field.';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['type'] = 'ol';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: User */
  $handler->display->display_options['relationships']['field_results_winners_target_id']['id'] = 'field_results_winners_target_id';
  $handler->display->display_options['relationships']['field_results_winners_target_id']['table'] = 'field_data_field_results_winners';
  $handler->display->display_options['relationships']['field_results_winners_target_id']['field'] = 'field_results_winners_target_id';
  $handler->display->display_options['relationships']['field_results_winners_target_id']['ui_name'] = 'User';
  $handler->display->display_options['relationships']['field_results_winners_target_id']['label'] = 'User';
  /* Relationship: Main profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['relationship'] = 'field_results_winners_target_id';
  $handler->display->display_options['relationships']['profile']['ui_name'] = 'Main profile';
  $handler->display->display_options['relationships']['profile']['label'] = 'Main profile';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'main' => 'main',
  );
  /* Relationship: OG membership */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['relationship'] = 'field_results_winners_target_id';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'OG membership';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'OG membership';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Field: Pilot number */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot number';
  $handler->display->display_options['fields']['field_contestant_number']['label'] = '';
  $handler->display->display_options['fields']['field_contestant_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_contestant_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['ui_name'] = 'Name';
  $handler->display->display_options['fields']['field_full_name']['label'] = '';
  $handler->display->display_options['fields']['field_full_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name] ([field_contestant_number])';
  $handler->display->display_options['fields']['field_full_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['relationship'] = 'field_results_winners_target_id';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  /* Sort criterion: Winners delta */
  $handler->display->display_options['sorts']['delta']['id'] = 'delta';
  $handler->display->display_options['sorts']['delta']['table'] = 'field_data_field_results_winners';
  $handler->display->display_options['sorts']['delta']['field'] = 'delta';
  $handler->display->display_options['sorts']['delta']['ui_name'] = 'Winners delta';
  /* Contextual filter: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['ui_name'] = 'Group ID';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Contextual filter: Node ID */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['ui_name'] = 'Node ID';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'pg_scoring_category' => 'pg_scoring_category',
  );
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_scoring_category' => 'pg_scoring_category',
  );
  $translatables['contest_winners'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('User'),
    t('Main profile'),
    t('OG membership'),
    t('[field_full_name] ([field_contestant_number])'),
    t('All'),
  );
  $export['contest_winners'] = $view;

  $view = new view();
  $view->name = 'day_blog';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Day blog';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_plain_body' => 'field_plain_body',
    'created' => 0,
  );
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '&nbsp;';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_dayblog_ref_node']['id'] = 'reverse_field_dayblog_ref_node';
  $handler->display->display_options['relationships']['reverse_field_dayblog_ref_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_dayblog_ref_node']['field'] = 'reverse_field_dayblog_ref_node';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'div';
  $handler->display->display_options['fields']['created']['element_class'] = 'field-item posted';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'H:i';
  /* Field: Body */
  $handler->display->display_options['fields']['field_plain_body']['id'] = 'field_plain_body';
  $handler->display->display_options['fields']['field_plain_body']['table'] = 'field_data_field_plain_body';
  $handler->display->display_options['fields']['field_plain_body']['field'] = 'field_plain_body';
  $handler->display->display_options['fields']['field_plain_body']['ui_name'] = 'Body';
  $handler->display->display_options['fields']['field_plain_body']['label'] = '';
  $handler->display->display_options['fields']['field_plain_body']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_plain_body']['element_class'] = 'field-item plain-body';
  $handler->display->display_options['fields']['field_plain_body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_plain_body']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_plain_body']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_dayblog_ref_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'dayblog' => 'dayblog',
  );

  /* Display: Day blog */
  $handler = $view->new_display('entityreference', 'Day blog', 'dayblog_formatter');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_plain_body' => 'field_plain_body',
    'created' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['row_options']['separator'] = '';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['day_blog'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('Content referencing Content from field_dayblog_ref'),
    t('All'),
    t('Day blog'),
  );
  $export['day_blog'] = $view;

  $view = new view();
  $view->name = 'day_results';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'Results files for categories';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_name',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Competition results */
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['id'] = 'field_competition_results_ent_race';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['field'] = 'field_competition_results_ent_race';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['ui_name'] = 'Competition results';
  $handler->display->display_options['relationships']['field_competition_results_ent_race']['label'] = 'Competition results';
  /* Relationship: Day results */
  $handler->display->display_options['relationships']['field_day_results_ent_race']['id'] = 'field_day_results_ent_race';
  $handler->display->display_options['relationships']['field_day_results_ent_race']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_day_results_ent_race']['field'] = 'field_day_results_ent_race';
  $handler->display->display_options['relationships']['field_day_results_ent_race']['ui_name'] = 'Day results';
  $handler->display->display_options['relationships']['field_day_results_ent_race']['label'] = 'Day results';
  /* Relationship: Scoring category */
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['id'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['table'] = 'field_data_field_scoring_category_ref';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['field'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['ui_name'] = 'Scoring category';
  $handler->display->display_options['relationships']['field_scoring_category_ref_target_id']['label'] = 'Scoring category';
  /* Field: Field name - excluded */
  $handler->display->display_options['fields']['field_name']['id'] = 'field_name';
  $handler->display->display_options['fields']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['field_name']['field'] = 'field_name';
  $handler->display->display_options['fields']['field_name']['ui_name'] = 'Field name - excluded';
  $handler->display->display_options['fields']['field_name']['label'] = '';
  $handler->display->display_options['fields']['field_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_name']['element_label_colon'] = FALSE;
  /* Field: Results file - excluded */
  $handler->display->display_options['fields']['field_results_file']['id'] = 'field_results_file';
  $handler->display->display_options['fields']['field_results_file']['table'] = 'field_data_field_results_file';
  $handler->display->display_options['fields']['field_results_file']['field'] = 'field_results_file';
  $handler->display->display_options['fields']['field_results_file']['ui_name'] = 'Results file - excluded';
  $handler->display->display_options['fields']['field_results_file']['label'] = '';
  $handler->display->display_options['fields']['field_results_file']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_results_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_results_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_results_file']['type'] = 'file_url_plain';
  /* Field: Scoring category - overriden */
  $handler->display->display_options['fields']['field_pg_scoring_category']['id'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['table'] = 'field_data_field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['field'] = 'field_pg_scoring_category';
  $handler->display->display_options['fields']['field_pg_scoring_category']['relationship'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['fields']['field_pg_scoring_category']['ui_name'] = 'Scoring category - overriden';
  $handler->display->display_options['fields']['field_pg_scoring_category']['label'] = '';
  $handler->display->display_options['fields']['field_pg_scoring_category']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_pg_scoring_category']['alter']['path'] = '[field_results_file]';
  $handler->display->display_options['fields']['field_pg_scoring_category']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_pg_scoring_category']['element_label_colon'] = FALSE;
  /* Sort criterion: Field collection item: Field name */
  $handler->display->display_options['sorts']['field_name']['id'] = 'field_name';
  $handler->display->display_options['sorts']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['sorts']['field_name']['field'] = 'field_name';
  /* Sort criterion: Draggableviews: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'draggableviews_structure';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  $handler->display->display_options['sorts']['weight']['relationship'] = 'field_scoring_category_ref_target_id';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_view'] = 'pg_scoring_categories:page';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_arguments'] = 'php';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_arguments_php'] = '$view = views_get_current_view();
$args = $view->args;
$race_id = $args[0];
$entities = entity_load(\'ent_race\', array($race_id));
$entity = array_shift($entities);
$wrapper = entity_metadata_wrapper(\'ent_race\', $entity);
$value = $wrapper->{OG_AUDIENCE_FIELD}->value();
$items = field_get_items(\'ent_race\', $entity, OG_AUDIENCE_FIELD);
$event_id = $items[0][\'target_id\'];
return array($event_id);';
  $handler->display->display_options['sorts']['weight']['draggableviews_setting_new_items_bottom_list'] = 0;
  /* Contextual filter: Race ID */
  $handler->display->display_options['arguments']['id']['id'] = 'id';
  $handler->display->display_options['arguments']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['arguments']['id']['field'] = 'id';
  $handler->display->display_options['arguments']['id']['relationship'] = 'field_competition_results_ent_race';
  $handler->display->display_options['arguments']['id']['ui_name'] = 'Race ID';
  $handler->display->display_options['arguments']['id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id']['summary_options']['items_per_page'] = '25';
  /* Contextual filter: Race ID */
  $handler->display->display_options['arguments']['id_1']['id'] = 'id_1';
  $handler->display->display_options['arguments']['id_1']['table'] = 'eck_ent_race';
  $handler->display->display_options['arguments']['id_1']['field'] = 'id';
  $handler->display->display_options['arguments']['id_1']['relationship'] = 'field_day_results_ent_race';
  $handler->display->display_options['arguments']['id_1']['ui_name'] = 'Race ID';
  $handler->display->display_options['arguments']['id_1']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['id_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['id_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['id_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['id_1']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['ui_name'] = 'Field name';
  $handler->display->display_options['filters']['field_name']['value'] = array(
    'field_day_results' => 'field_day_results',
    'field_competition_results' => 'field_competition_results',
  );
  $translatables['day_results'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Competition results'),
    t('Day results'),
    t('Scoring category'),
    t('All'),
  );
  $export['day_results'] = $view;

  $view = new view();
  $view->name = 'day_selection';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Day selection';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: OG membership */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'OG membership';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'OG membership';
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Sort criterion: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['ui_name'] = 'Title';
  /* Contextual filter: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['ui_name'] = 'Group ID';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Content type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'day' => 'day',
  );
  /* Filter criterion: Content: Day status (field_day_status) */
  $handler->display->display_options['filters']['field_day_status_value']['id'] = 'field_day_status_value';
  $handler->display->display_options['filters']['field_day_status_value']['table'] = 'field_data_field_day_status';
  $handler->display->display_options['filters']['field_day_status_value']['field'] = 'field_day_status_value';
  $handler->display->display_options['filters']['field_day_status_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_day_status_value']['value'] = array(
    4 => '4',
    5 => '5',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'day_selection');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
    'gid' => 0,
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['day_selection'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('« first'),
    t('‹ previous'),
    t('next ›'),
    t('last »'),
    t('OG membership'),
    t('All'),
    t('Entity Reference'),
  );
  $export['day_selection'] = $view;

  $view = new view();
  $view->name = 'event_accommodations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Event accommodations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Accommodation';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['disable_sql_rewrite'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: HQ contest */
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['id'] = 'reverse_field_headquarter_hotel_node';
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['field'] = 'reverse_field_headquarter_hotel_node';
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['ui_name'] = 'HQ contest';
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['label'] = 'HQ contest';
  /* Field: NID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'NID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: First photo - overriden */
  $handler->display->display_options['fields']['field_photo']['id'] = 'field_photo';
  $handler->display->display_options['fields']['field_photo']['table'] = 'field_data_field_photo';
  $handler->display->display_options['fields']['field_photo']['field'] = 'field_photo';
  $handler->display->display_options['fields']['field_photo']['ui_name'] = 'First photo - overriden';
  $handler->display->display_options['fields']['field_photo']['label'] = '';
  $handler->display->display_options['fields']['field_photo']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_photo']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['field_photo']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['field_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photo']['settings'] = array(
    'image_style' => 'event_map_picture_preview',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photo']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_photo']['delta_offset'] = '0';
  /* Field: Title - overriden */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title - overriden';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['title']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Distance to HQ */
  $handler->display->display_options['fields']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['fields']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['fields']['field_geofield_distance']['ui_name'] = 'Distance to HQ';
  $handler->display->display_options['fields']['field_geofield_distance']['label'] = '';
  $handler->display->display_options['fields']['field_geofield_distance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geofield_distance']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['field_geofield_distance']['precision'] = '1';
  $handler->display->display_options['fields']['field_geofield_distance']['suffix'] = ' km';
  $handler->display->display_options['fields']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_manual'] = array(
    'lat' => '',
    'lon' => '',
  );
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_track';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';
  $handler->display->display_options['fields']['field_geofield_distance']['radius_of_earth'] = '6371';
  /* Field: WiFi */
  $handler->display->display_options['fields']['field_hotel_wifi']['id'] = 'field_hotel_wifi';
  $handler->display->display_options['fields']['field_hotel_wifi']['table'] = 'field_data_field_hotel_wifi';
  $handler->display->display_options['fields']['field_hotel_wifi']['field'] = 'field_hotel_wifi';
  $handler->display->display_options['fields']['field_hotel_wifi']['ui_name'] = 'WiFi';
  $handler->display->display_options['fields']['field_hotel_wifi']['label'] = '';
  $handler->display->display_options['fields']['field_hotel_wifi']['element_label_colon'] = FALSE;
  /* Field: Currency - excluded */
  $handler->display->display_options['fields']['field_price_currency']['id'] = 'field_price_currency';
  $handler->display->display_options['fields']['field_price_currency']['table'] = 'field_data_field_price_currency';
  $handler->display->display_options['fields']['field_price_currency']['field'] = 'field_price_currency';
  $handler->display->display_options['fields']['field_price_currency']['ui_name'] = 'Currency - excluded';
  $handler->display->display_options['fields']['field_price_currency']['label'] = '';
  $handler->display->display_options['fields']['field_price_currency']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_price_currency']['element_label_colon'] = FALSE;
  /* Field: Single price - overridden */
  $handler->display->display_options['fields']['field_price_single']['id'] = 'field_price_single';
  $handler->display->display_options['fields']['field_price_single']['table'] = 'field_data_field_price_single';
  $handler->display->display_options['fields']['field_price_single']['field'] = 'field_price_single';
  $handler->display->display_options['fields']['field_price_single']['ui_name'] = 'Single price - overridden';
  $handler->display->display_options['fields']['field_price_single']['label'] = '';
  $handler->display->display_options['fields']['field_price_single']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_price_single']['alter']['text'] = '<span class="currency-[field_price_currency]">[field_price_single]</span>';
  $handler->display->display_options['fields']['field_price_single']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_price_single']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Double price - overridden */
  $handler->display->display_options['fields']['field_price_double']['id'] = 'field_price_double';
  $handler->display->display_options['fields']['field_price_double']['table'] = 'field_data_field_price_double';
  $handler->display->display_options['fields']['field_price_double']['field'] = 'field_price_double';
  $handler->display->display_options['fields']['field_price_double']['ui_name'] = 'Double price - overridden';
  $handler->display->display_options['fields']['field_price_double']['label'] = '';
  $handler->display->display_options['fields']['field_price_double']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_price_double']['alter']['text'] = '<span class="currency-[field_price_currency]">[field_price_double]</span>';
  $handler->display->display_options['fields']['field_price_double']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_price_double']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['ui_name'] = 'Description';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '300',
  );
  /* Field: Phone */
  $handler->display->display_options['fields']['field_place_phone']['id'] = 'field_place_phone';
  $handler->display->display_options['fields']['field_place_phone']['table'] = 'field_data_field_place_phone';
  $handler->display->display_options['fields']['field_place_phone']['field'] = 'field_place_phone';
  $handler->display->display_options['fields']['field_place_phone']['ui_name'] = 'Phone';
  $handler->display->display_options['fields']['field_place_phone']['label'] = 'Tel';
  $handler->display->display_options['fields']['field_place_phone']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_place_phone']['click_sort_column'] = 'number';
  $handler->display->display_options['fields']['field_place_phone']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_place_phone']['delta_offset'] = '0';
  /* Field: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['ui_name'] = 'Email';
  $handler->display->display_options['fields']['field_email']['label'] = 'Email:';
  $handler->display->display_options['fields']['field_email']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_email']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_email']['type'] = 'email_plain';
  $handler->display->display_options['fields']['field_email']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_email']['delta_offset'] = '0';
  /* Field: Contest ID - hidden in template */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'reverse_field_headquarter_hotel_node';
  $handler->display->display_options['fields']['nid_1']['ui_name'] = 'Contest ID - hidden in template';
  $handler->display->display_options['fields']['nid_1']['label'] = '';
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid_1']['hide_empty'] = TRUE;
  /* Sort criterion: Distance to HQ */
  $handler->display->display_options['sorts']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['sorts']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['sorts']['field_geofield_distance']['ui_name'] = 'Distance to HQ';
  $handler->display->display_options['sorts']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_manual'] = array(
    'lat' => '',
    'lon' => '',
  );
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
  );
  /* Filter criterion: Distance to HQ */
  $handler->display->display_options['filters']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['ui_name'] = 'Distance to HQ';
  $handler->display->display_options['filters']['field_geofield_distance']['operator'] = '<=';
  $handler->display->display_options['filters']['field_geofield_distance']['value'] = array(
    'distance' => '30',
    'distance2' => 200,
    'unit' => '6371',
    'origin' => '',
  );
  $handler->display->display_options['filters']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_event_map_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'null' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Global: Null',
    ),
  );
  $translatables['event_accommodations'] = array(
    t('Master'),
    t('Accommodation'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('HQ contest'),
    t('.'),
    t(','),
    t(' km'),
    t('<span class="currency-[field_price_currency]">[field_price_single]</span>'),
    t('<span class="currency-[field_price_currency]">[field_price_double]</span>'),
    t('Tel'),
    t('Email:'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['event_accommodations'] = $view;

  $view = new view();
  $view->name = 'event_activities';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Event activities';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Activities';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: NID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'NID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: First photo - overriden */
  $handler->display->display_options['fields']['field_photo']['id'] = 'field_photo';
  $handler->display->display_options['fields']['field_photo']['table'] = 'field_data_field_photo';
  $handler->display->display_options['fields']['field_photo']['field'] = 'field_photo';
  $handler->display->display_options['fields']['field_photo']['ui_name'] = 'First photo - overriden';
  $handler->display->display_options['fields']['field_photo']['label'] = '';
  $handler->display->display_options['fields']['field_photo']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_photo']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['field_photo']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['field_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photo']['settings'] = array(
    'image_style' => 'event_map_picture_preview',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_photo']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_photo']['delta_offset'] = '0';
  /* Field: Title - overriden */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title - overriden';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['title']['alter']['rel'] = 'nofollow';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Distance to HQ */
  $handler->display->display_options['fields']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['fields']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['fields']['field_geofield_distance']['ui_name'] = 'Distance to HQ';
  $handler->display->display_options['fields']['field_geofield_distance']['label'] = '';
  $handler->display->display_options['fields']['field_geofield_distance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geofield_distance']['set_precision'] = TRUE;
  $handler->display->display_options['fields']['field_geofield_distance']['precision'] = '1';
  $handler->display->display_options['fields']['field_geofield_distance']['suffix'] = ' km';
  $handler->display->display_options['fields']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_manual'] = array(
    'lat' => '',
    'lon' => '',
  );
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_track';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['fields']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';
  $handler->display->display_options['fields']['field_geofield_distance']['radius_of_earth'] = '6371';
  /* Field: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['ui_name'] = 'Description';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['alter']['max_length'] = '230';
  $handler->display->display_options['fields']['body']['alter']['trim'] = TRUE;
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Phone */
  $handler->display->display_options['fields']['field_place_phone']['id'] = 'field_place_phone';
  $handler->display->display_options['fields']['field_place_phone']['table'] = 'field_data_field_place_phone';
  $handler->display->display_options['fields']['field_place_phone']['field'] = 'field_place_phone';
  $handler->display->display_options['fields']['field_place_phone']['ui_name'] = 'Phone';
  $handler->display->display_options['fields']['field_place_phone']['label'] = 'Tel';
  $handler->display->display_options['fields']['field_place_phone']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_place_phone']['click_sort_column'] = 'number';
  $handler->display->display_options['fields']['field_place_phone']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_place_phone']['delta_offset'] = '0';
  /* Field: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['ui_name'] = 'Email';
  $handler->display->display_options['fields']['field_email']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_email']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_email']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_email']['delta_offset'] = '0';
  /* Sort criterion: Distance to HQ */
  $handler->display->display_options['sorts']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['sorts']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['sorts']['field_geofield_distance']['ui_name'] = 'Distance to HQ';
  $handler->display->display_options['sorts']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_manual'] = array(
    'lat' => '',
    'lon' => '',
  );
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['sorts']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'activity' => 'activity',
  );
  /* Filter criterion: Distance to HQ */
  $handler->display->display_options['filters']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['ui_name'] = 'Distance to HQ';
  $handler->display->display_options['filters']['field_geofield_distance']['operator'] = '<=';
  $handler->display->display_options['filters']['field_geofield_distance']['value'] = array(
    'distance' => '100',
    'distance2' => 200,
    'unit' => '6371',
    'origin' => '',
  );
  $handler->display->display_options['filters']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_event_map_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'null' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Global: Null',
    ),
  );
  $translatables['event_activities'] = array(
    t('Master'),
    t('Activities'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('.'),
    t(','),
    t(' km'),
    t('Tel'),
    t('Email'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['event_activities'] = $view;

  $view = new view();
  $view->name = 'event_days';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Event days';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_accordion';
  $handler->display->display_options['style_options']['row_class'] = 'event-day';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['collapsible'] = 1;
  $handler->display->display_options['style_options']['row-start-open'] = '0';
  $handler->display->display_options['style_options']['autoheight'] = 0;
  $handler->display->display_options['style_options']['navigation'] = 1;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: pg_contest */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'pg_contest';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'pg_contest';
  /* Relationship: pg_race */
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['id'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['field'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['ui_name'] = 'pg_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['label'] = 'pg_race';
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'pg_contest node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['id'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['table'] = 'field_data_field_pg_racetype_ref';
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['field'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['relationship'] = 'reverse_field_day_ref_ent_race';
  /* Field: Contest ID (excluded) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Contest ID (excluded)';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Race ID - excluded */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['id']['ui_name'] = 'Race ID - excluded';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Day number */
  $handler->display->display_options['fields']['field_day_number']['id'] = 'field_day_number';
  $handler->display->display_options['fields']['field_day_number']['table'] = 'field_data_field_day_number';
  $handler->display->display_options['fields']['field_day_number']['field'] = 'field_day_number';
  $handler->display->display_options['fields']['field_day_number']['label'] = 'Day ';
  $handler->display->display_options['fields']['field_day_number']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_number']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_day_number']['element_default_classes'] = FALSE;
  /* Field: Race: Race number */
  $handler->display->display_options['fields']['field_race_number']['id'] = 'field_race_number';
  $handler->display->display_options['fields']['field_race_number']['table'] = 'field_data_field_race_number';
  $handler->display->display_options['fields']['field_race_number']['field'] = 'field_race_number';
  $handler->display->display_options['fields']['field_race_number']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_race_number']['label'] = 'Task ';
  $handler->display->display_options['fields']['field_race_number']['element_type'] = '0';
  $handler->display->display_options['fields']['field_race_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_race_number']['element_wrapper_type'] = '0';
  /* Field: Race: Distance */
  $handler->display->display_options['fields']['field_optdistance']['id'] = 'field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['table'] = 'field_data_field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['field'] = 'field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_optdistance']['label'] = '';
  $handler->display->display_options['fields']['field_optdistance']['element_type'] = '0';
  $handler->display->display_options['fields']['field_optdistance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_optdistance']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_optdistance']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_optdistance']['type'] = 'text_plain';
  /* Field: Day status */
  $handler->display->display_options['fields']['field_day_status']['id'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['table'] = 'field_data_field_day_status';
  $handler->display->display_options['fields']['field_day_status']['field'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['ui_name'] = 'Day status';
  $handler->display->display_options['fields']['field_day_status']['label'] = '';
  $handler->display->display_options['fields']['field_day_status']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_status']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_day_status']['element_default_classes'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  /* Field: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Post date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'posted';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'j M, Y';
  /* Field: Content: Extrafield Set a task link */
  $handler->display->display_options['fields']['day_set_a_task']['id'] = 'day_set_a_task';
  $handler->display->display_options['fields']['day_set_a_task']['table'] = 'node';
  $handler->display->display_options['fields']['day_set_a_task']['field'] = 'day_set_a_task';
  $handler->display->display_options['fields']['day_set_a_task']['label'] = '';
  $handler->display->display_options['fields']['day_set_a_task']['element_label_colon'] = FALSE;
  /* Field: Results view */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Results view';
  $handler->display->display_options['fields']['view']['label'] = 'Results tables';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'day_results';
  $handler->display->display_options['fields']['view']['arguments'] = '[!id]/[!id]';
  /* Field: Tracks */
  $handler->display->display_options['fields']['field_pg_race_tracks']['id'] = 'field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['table'] = 'field_data_field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['field'] = 'field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_pg_race_tracks']['ui_name'] = 'Tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['label'] = 'Tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['text'] = 'IGC';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['path'] = '[field_pg_race_tracks]';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['prefix'] = '<span class="file">';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['suffix'] = '</span>';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pg_race_tracks']['type'] = 'file_url_plain';
  /* Field: Images */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['ui_name'] = 'Images';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'colorbox_node_style' => 'thumbnail',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Field: Competition results */
  $handler->display->display_options['fields']['field_competition_results']['id'] = 'field_competition_results';
  $handler->display->display_options['fields']['field_competition_results']['table'] = 'field_data_field_competition_results';
  $handler->display->display_options['fields']['field_competition_results']['field'] = 'field_competition_results';
  $handler->display->display_options['fields']['field_competition_results']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_competition_results']['ui_name'] = 'Competition results';
  $handler->display->display_options['fields']['field_competition_results']['label'] = '';
  $handler->display->display_options['fields']['field_competition_results']['element_type'] = '0';
  $handler->display->display_options['fields']['field_competition_results']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_competition_results']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_competition_results']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_competition_results']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_competition_results']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_competition_results']['multi_type'] = 'ul';
  /* Field: Day results */
  $handler->display->display_options['fields']['field_day_results']['id'] = 'field_day_results';
  $handler->display->display_options['fields']['field_day_results']['table'] = 'field_data_field_day_results';
  $handler->display->display_options['fields']['field_day_results']['field'] = 'field_day_results';
  $handler->display->display_options['fields']['field_day_results']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_day_results']['ui_name'] = 'Day results';
  $handler->display->display_options['fields']['field_day_results']['label'] = '';
  $handler->display->display_options['fields']['field_day_results']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_results']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_results']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_day_results']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_day_results']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_day_results']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_day_results']['multi_type'] = 'ul';
  /* Field: Day blog */
  $handler->display->display_options['fields']['field_dayblog_ref']['id'] = 'field_dayblog_ref';
  $handler->display->display_options['fields']['field_dayblog_ref']['table'] = 'field_data_field_dayblog_ref';
  $handler->display->display_options['fields']['field_dayblog_ref']['field'] = 'field_dayblog_ref';
  $handler->display->display_options['fields']['field_dayblog_ref']['ui_name'] = 'Day blog';
  $handler->display->display_options['fields']['field_dayblog_ref']['label'] = '';
  $handler->display->display_options['fields']['field_dayblog_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dayblog_ref']['type'] = 'entityreference_views_formatter';
  $handler->display->display_options['fields']['field_dayblog_ref']['settings'] = array(
    'view_name' => 'day_blog',
    'view_display' => 'dayblog_formatter',
  );
  $handler->display->display_options['fields']['field_dayblog_ref']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_dayblog_ref']['multi_type'] = 'ul';
  /* Field: Race Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_core_id']['ui_name'] = 'Race Core ID';
  $handler->display->display_options['fields']['field_core_id']['label'] = '';
  $handler->display->display_options['fields']['field_core_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_core_id']['element_label_colon'] = FALSE;
  /* Field: Contest Core ID */
  $handler->display->display_options['fields']['field_core_id_1']['id'] = 'field_core_id_1';
  $handler->display->display_options['fields']['field_core_id_1']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id_1']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_core_id_1']['ui_name'] = 'Contest Core ID';
  $handler->display->display_options['fields']['field_core_id_1']['label'] = '';
  $handler->display->display_options['fields']['field_core_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_core_id_1']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="data-race" data-race-id="[field_core_id]" data-contest-id="[field_core_id_1]"></div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Race type: Id */
  $handler->display->display_options['fields']['id_1']['id'] = 'id_1';
  $handler->display->display_options['fields']['id_1']['table'] = 'eck_ent_racetype';
  $handler->display->display_options['fields']['id_1']['field'] = 'id';
  $handler->display->display_options['fields']['id_1']['relationship'] = 'field_pg_racetype_ref_target_id';
  /* Field: Race type: Race points */
  $handler->display->display_options['fields']['field_pg_race_points']['id'] = 'field_pg_race_points';
  $handler->display->display_options['fields']['field_pg_race_points']['table'] = 'field_data_field_pg_race_points';
  $handler->display->display_options['fields']['field_pg_race_points']['field'] = 'field_pg_race_points';
  $handler->display->display_options['fields']['field_pg_race_points']['relationship'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['fields']['field_pg_race_points']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_points']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_pg_race_points']['delta_offset'] = '0';
  /* Field: Day task visualization link */
  $handler->display->display_options['fields']['day_pg_race_play_link']['id'] = 'day_pg_race_play_link';
  $handler->display->display_options['fields']['day_pg_race_play_link']['table'] = 'node';
  $handler->display->display_options['fields']['day_pg_race_play_link']['field'] = 'day_pg_race_play_link';
  $handler->display->display_options['fields']['day_pg_race_play_link']['ui_name'] = 'Day task visualization link';
  $handler->display->display_options['fields']['day_pg_race_play_link']['label'] = '';
  $handler->display->display_options['fields']['day_pg_race_play_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['day_pg_race_play_link']['element_default_classes'] = FALSE;
  /* Sort criterion: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['ui_name'] = 'Post date';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Content type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'day' => 'day',
  );

  /* Display: List of day (accordion) */
  $handler = $view->new_display('panel_pane', 'List of day (accordion)', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Contest ID (excluded) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Contest ID (excluded)';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Race ID - excluded */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['id']['ui_name'] = 'Race ID - excluded';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Day number */
  $handler->display->display_options['fields']['field_day_number']['id'] = 'field_day_number';
  $handler->display->display_options['fields']['field_day_number']['table'] = 'field_data_field_day_number';
  $handler->display->display_options['fields']['field_day_number']['field'] = 'field_day_number';
  $handler->display->display_options['fields']['field_day_number']['label'] = 'Day ';
  $handler->display->display_options['fields']['field_day_number']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_number']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_day_number']['element_default_classes'] = FALSE;
  /* Field: Race: Race number */
  $handler->display->display_options['fields']['field_race_number']['id'] = 'field_race_number';
  $handler->display->display_options['fields']['field_race_number']['table'] = 'field_data_field_race_number';
  $handler->display->display_options['fields']['field_race_number']['field'] = 'field_race_number';
  $handler->display->display_options['fields']['field_race_number']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_race_number']['label'] = 'Task ';
  $handler->display->display_options['fields']['field_race_number']['element_type'] = '0';
  $handler->display->display_options['fields']['field_race_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_race_number']['element_wrapper_type'] = '0';
  /* Field: Race: Distance */
  $handler->display->display_options['fields']['field_optdistance']['id'] = 'field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['table'] = 'field_data_field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['field'] = 'field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_optdistance']['label'] = '';
  $handler->display->display_options['fields']['field_optdistance']['element_type'] = '0';
  $handler->display->display_options['fields']['field_optdistance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_optdistance']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_optdistance']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_optdistance']['type'] = 'text_plain';
  /* Field: Day status */
  $handler->display->display_options['fields']['field_day_status']['id'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['table'] = 'field_data_field_day_status';
  $handler->display->display_options['fields']['field_day_status']['field'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['ui_name'] = 'Day status';
  $handler->display->display_options['fields']['field_day_status']['label'] = '';
  $handler->display->display_options['fields']['field_day_status']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_status']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_day_status']['element_default_classes'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  /* Field: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Post date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'posted';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'j M, Y';
  /* Field: Content: Extrafield Set a task link */
  $handler->display->display_options['fields']['day_set_a_task']['id'] = 'day_set_a_task';
  $handler->display->display_options['fields']['day_set_a_task']['table'] = 'node';
  $handler->display->display_options['fields']['day_set_a_task']['field'] = 'day_set_a_task';
  $handler->display->display_options['fields']['day_set_a_task']['label'] = '';
  $handler->display->display_options['fields']['day_set_a_task']['element_label_colon'] = FALSE;
  /* Field: Results view */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Results view';
  $handler->display->display_options['fields']['view']['label'] = 'Results tables';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'day_results';
  $handler->display->display_options['fields']['view']['arguments'] = '[!id]/[!id]';
  /* Field: Tracks */
  $handler->display->display_options['fields']['field_pg_race_tracks']['id'] = 'field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['table'] = 'field_data_field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['field'] = 'field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_pg_race_tracks']['ui_name'] = 'Tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['label'] = 'Tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['text'] = 'IGC';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['path'] = '[field_pg_race_tracks]';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['prefix'] = '<span class="file">';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['suffix'] = '</span>';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pg_race_tracks']['type'] = 'file_url_plain';
  /* Field: Images */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['ui_name'] = 'Images';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'colorbox_node_style' => 'thumbnail',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Field: Competition results */
  $handler->display->display_options['fields']['field_competition_results']['id'] = 'field_competition_results';
  $handler->display->display_options['fields']['field_competition_results']['table'] = 'field_data_field_competition_results';
  $handler->display->display_options['fields']['field_competition_results']['field'] = 'field_competition_results';
  $handler->display->display_options['fields']['field_competition_results']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_competition_results']['ui_name'] = 'Competition results';
  $handler->display->display_options['fields']['field_competition_results']['label'] = '';
  $handler->display->display_options['fields']['field_competition_results']['element_type'] = '0';
  $handler->display->display_options['fields']['field_competition_results']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_competition_results']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_competition_results']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_competition_results']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_competition_results']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_competition_results']['multi_type'] = 'ul';
  /* Field: Day results */
  $handler->display->display_options['fields']['field_day_results']['id'] = 'field_day_results';
  $handler->display->display_options['fields']['field_day_results']['table'] = 'field_data_field_day_results';
  $handler->display->display_options['fields']['field_day_results']['field'] = 'field_day_results';
  $handler->display->display_options['fields']['field_day_results']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_day_results']['ui_name'] = 'Day results';
  $handler->display->display_options['fields']['field_day_results']['label'] = '';
  $handler->display->display_options['fields']['field_day_results']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_results']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_results']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_day_results']['type'] = 'field_collection_fields';
  $handler->display->display_options['fields']['field_day_results']['settings'] = array(
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_day_results']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_day_results']['multi_type'] = 'ul';
  /* Field: Day blog */
  $handler->display->display_options['fields']['field_dayblog_ref']['id'] = 'field_dayblog_ref';
  $handler->display->display_options['fields']['field_dayblog_ref']['table'] = 'field_data_field_dayblog_ref';
  $handler->display->display_options['fields']['field_dayblog_ref']['field'] = 'field_dayblog_ref';
  $handler->display->display_options['fields']['field_dayblog_ref']['ui_name'] = 'Day blog';
  $handler->display->display_options['fields']['field_dayblog_ref']['label'] = '';
  $handler->display->display_options['fields']['field_dayblog_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dayblog_ref']['type'] = 'entityreference_views_formatter';
  $handler->display->display_options['fields']['field_dayblog_ref']['settings'] = array(
    'view_name' => 'day_blog',
    'view_display' => 'dayblog_formatter',
  );
  $handler->display->display_options['fields']['field_dayblog_ref']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_dayblog_ref']['multi_type'] = 'ul';
  /* Field: Race Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_core_id']['ui_name'] = 'Race Core ID';
  $handler->display->display_options['fields']['field_core_id']['label'] = '';
  $handler->display->display_options['fields']['field_core_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_core_id']['element_label_colon'] = FALSE;
  /* Field: Contest Core ID */
  $handler->display->display_options['fields']['field_core_id_1']['id'] = 'field_core_id_1';
  $handler->display->display_options['fields']['field_core_id_1']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id_1']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_core_id_1']['ui_name'] = 'Contest Core ID';
  $handler->display->display_options['fields']['field_core_id_1']['label'] = '';
  $handler->display->display_options['fields']['field_core_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_core_id_1']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="data-race" data-race-id="[field_core_id]" data-contest-id="[field_core_id_1]"></div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Race type: Id */
  $handler->display->display_options['fields']['id_1']['id'] = 'id_1';
  $handler->display->display_options['fields']['id_1']['table'] = 'eck_ent_racetype';
  $handler->display->display_options['fields']['id_1']['field'] = 'id';
  $handler->display->display_options['fields']['id_1']['relationship'] = 'field_pg_racetype_ref_target_id';
  /* Field: Race type: Race points */
  $handler->display->display_options['fields']['field_pg_race_points']['id'] = 'field_pg_race_points';
  $handler->display->display_options['fields']['field_pg_race_points']['table'] = 'field_data_field_pg_race_points';
  $handler->display->display_options['fields']['field_pg_race_points']['field'] = 'field_pg_race_points';
  $handler->display->display_options['fields']['field_pg_race_points']['relationship'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['fields']['field_pg_race_points']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_points']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_pg_race_points']['delta_offset'] = '0';
  /* Field: Day task visualization link */
  $handler->display->display_options['fields']['day_pg_race_play_link']['id'] = 'day_pg_race_play_link';
  $handler->display->display_options['fields']['day_pg_race_play_link']['table'] = 'node';
  $handler->display->display_options['fields']['day_pg_race_play_link']['field'] = 'day_pg_race_play_link';
  $handler->display->display_options['fields']['day_pg_race_play_link']['ui_name'] = 'Day task visualization link';
  $handler->display->display_options['fields']['day_pg_race_play_link']['label'] = '';
  $handler->display->display_options['fields']['day_pg_race_play_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['day_pg_race_play_link']['element_default_classes'] = FALSE;
  /* Field: Link to retrieve */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['ui_name'] = 'Link to retrieve';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<a href="http://retrieve.airtribune.com/table/index.php?contestid=[field_core_id_1]&raceid=[field_core_id]" >Retrieve table</a>';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: List of race (results) */
  $handler = $view->new_display('panel_pane', 'List of race (results)', 'results_race_list');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Tasks and results';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: pg_contest */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['ui_name'] = 'pg_contest';
  $handler->display->display_options['relationships']['og_membership_rel']['label'] = 'pg_contest';
  /* Relationship: pg_race */
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['id'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['field'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['ui_name'] = 'pg_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['label'] = 'pg_race';
  $handler->display->display_options['relationships']['reverse_field_day_ref_ent_race']['required'] = TRUE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['label'] = 'pg_contest node';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['id'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['table'] = 'field_data_field_pg_racetype_ref';
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['field'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['relationships']['field_pg_racetype_ref_target_id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Race ID - excluded */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['id']['ui_name'] = 'Race ID - excluded';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Race preview (coming soon)';
  $handler->display->display_options['fields']['nothing_1']['element_type'] = 'div';
  $handler->display->display_options['fields']['nothing_1']['element_class'] = 'race-preview-wrapper';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Content: Day status */
  $handler->display->display_options['fields']['field_day_status']['id'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['table'] = 'field_data_field_day_status';
  $handler->display->display_options['fields']['field_day_status']['field'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['label'] = 'Day ';
  $handler->display->display_options['fields']['field_day_status']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_status']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_day_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_status']['element_default_classes'] = FALSE;
  /* Field: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['title_1']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  /* Field: Content: Day number */
  $handler->display->display_options['fields']['field_day_number']['id'] = 'field_day_number';
  $handler->display->display_options['fields']['field_day_number']['table'] = 'field_data_field_day_number';
  $handler->display->display_options['fields']['field_day_number']['field'] = 'field_day_number';
  $handler->display->display_options['fields']['field_day_number']['label'] = '';
  $handler->display->display_options['fields']['field_day_number']['element_type'] = '0';
  $handler->display->display_options['fields']['field_day_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_day_number']['element_wrapper_type'] = '0';
  /* Field: Race: Distance */
  $handler->display->display_options['fields']['field_optdistance']['id'] = 'field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['table'] = 'field_data_field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['field'] = 'field_optdistance';
  $handler->display->display_options['fields']['field_optdistance']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_optdistance']['label'] = '';
  $handler->display->display_options['fields']['field_optdistance']['element_type'] = '0';
  $handler->display->display_options['fields']['field_optdistance']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_optdistance']['element_wrapper_type'] = '0';
  /* Field: Race: Race number */
  $handler->display->display_options['fields']['field_race_number']['id'] = 'field_race_number';
  $handler->display->display_options['fields']['field_race_number']['table'] = 'field_data_field_race_number';
  $handler->display->display_options['fields']['field_race_number']['field'] = 'field_race_number';
  $handler->display->display_options['fields']['field_race_number']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_race_number']['label'] = 'Task ';
  $handler->display->display_options['fields']['field_race_number']['element_type'] = '0';
  $handler->display->display_options['fields']['field_race_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_race_number']['element_wrapper_type'] = '0';
  /* Field: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['ui_name'] = 'Post date';
  $handler->display->display_options['fields']['created']['label'] = '';
  $handler->display->display_options['fields']['created']['element_type'] = 'span';
  $handler->display->display_options['fields']['created']['element_class'] = 'posted';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'custom';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'j M, Y';
  /* Field: Race type: ent_racetype type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'eck_ent_racetype';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['relationship'] = 'field_pg_racetype_ref_target_id';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  /* Field: Race: Extrafield Paragliding race link */
  $handler->display->display_options['fields']['pg_race_play_link']['id'] = 'pg_race_play_link';
  $handler->display->display_options['fields']['pg_race_play_link']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['pg_race_play_link']['field'] = 'pg_race_play_link';
  $handler->display->display_options['fields']['pg_race_play_link']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['pg_race_play_link']['label'] = 'Replay';
  $handler->display->display_options['fields']['pg_race_play_link']['element_type'] = 'span';
  $handler->display->display_options['fields']['pg_race_play_link']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['pg_race_play_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['pg_race_play_link']['element_wrapper_type'] = 'span';
  /* Field: Results view */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['ui_name'] = 'Results view';
  $handler->display->display_options['fields']['view']['label'] = '';
  $handler->display->display_options['fields']['view']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view']['view'] = 'day_results';
  $handler->display->display_options['fields']['view']['arguments'] = '[!id]/[!id]';
  /* Field: Tracks */
  $handler->display->display_options['fields']['field_pg_race_tracks']['id'] = 'field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['table'] = 'field_data_field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['field'] = 'field_pg_race_tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_pg_race_tracks']['ui_name'] = 'Tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['label'] = 'Tracks';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['text'] = 'IGC';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['path'] = '[field_pg_race_tracks]';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['prefix'] = '<span class="file">';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['suffix'] = '</span>';
  $handler->display->display_options['fields']['field_pg_race_tracks']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_label_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['field_pg_race_tracks']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['field_pg_race_tracks']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_pg_race_tracks']['type'] = 'file_url_plain';
  /* Field: Race Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['fields']['field_core_id']['ui_name'] = 'Race Core ID';
  $handler->display->display_options['fields']['field_core_id']['label'] = '';
  $handler->display->display_options['fields']['field_core_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_core_id']['element_label_colon'] = FALSE;
  /* Field: Contest Core ID */
  $handler->display->display_options['fields']['field_core_id_1']['id'] = 'field_core_id_1';
  $handler->display->display_options['fields']['field_core_id_1']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id_1']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id_1']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_core_id_1']['ui_name'] = 'Contest Core ID';
  $handler->display->display_options['fields']['field_core_id_1']['label'] = '';
  $handler->display->display_options['fields']['field_core_id_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_core_id_1']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<div class="data-race" data-race-id="[field_core_id]" data-contest-id="[field_core_id_1]"></div>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['ui_name'] = 'Post date';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'AND',
    2 => 'OR',
  );
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Content type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'day' => 'day',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Race: Race Tracks (field_pg_race_tracks:fid) */
  $handler->display->display_options['filters']['field_pg_race_tracks_fid']['id'] = 'field_pg_race_tracks_fid';
  $handler->display->display_options['filters']['field_pg_race_tracks_fid']['table'] = 'field_data_field_pg_race_tracks';
  $handler->display->display_options['filters']['field_pg_race_tracks_fid']['field'] = 'field_pg_race_tracks_fid';
  $handler->display->display_options['filters']['field_pg_race_tracks_fid']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['filters']['field_pg_race_tracks_fid']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_pg_race_tracks_fid']['group'] = 2;
  /* Filter criterion: Race: Day results (field_day_results) */
  $handler->display->display_options['filters']['field_day_results_value']['id'] = 'field_day_results_value';
  $handler->display->display_options['filters']['field_day_results_value']['table'] = 'field_data_field_day_results';
  $handler->display->display_options['filters']['field_day_results_value']['field'] = 'field_day_results_value';
  $handler->display->display_options['filters']['field_day_results_value']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['filters']['field_day_results_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_day_results_value']['group'] = 2;
  /* Filter criterion: Race: Competition results (field_competition_results) */
  $handler->display->display_options['filters']['field_competition_results_value']['id'] = 'field_competition_results_value';
  $handler->display->display_options['filters']['field_competition_results_value']['table'] = 'field_data_field_competition_results';
  $handler->display->display_options['filters']['field_competition_results_value']['field'] = 'field_competition_results_value';
  $handler->display->display_options['filters']['field_competition_results_value']['relationship'] = 'reverse_field_day_ref_ent_race';
  $handler->display->display_options['filters']['field_competition_results_value']['operator'] = 'not empty';
  $handler->display->display_options['filters']['field_competition_results_value']['group'] = 2;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );
  $translatables['event_days'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('pg_contest'),
    t('pg_race'),
    t('pg_contest node'),
    t('Race type entity referenced from field_pg_racetype_ref'),
    t('Nid'),
    t('.'),
    t('Day '),
    t('Task '),
    t('Results tables'),
    t('Tracks'),
    t('IGC'),
    t('<span class="file">'),
    t('</span>'),
    t('<div class="data-race" data-race-id="[field_core_id]" data-contest-id="[field_core_id_1]"></div>'),
    t('Id'),
    t(','),
    t('Race points'),
    t('All'),
    t('List of day (accordion)'),
    t('<a href="http://retrieve.airtribune.com/table/index.php?contestid=[field_core_id_1]&raceid=[field_core_id]" >Retrieve table</a>'),
    t('View panes'),
    t('List of race (results)'),
    t('Tasks and results'),
    t('Race preview (coming soon)'),
    t('Replay'),
  );
  $export['event_days'] = $view;

  $view = new view();
  $view->name = 'event_map';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Event_map';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'title',
    'other_lon' => 'title',
    'wkt' => 'field_location',
    'other_top' => 'title',
    'other_right' => 'title',
    'other_bottom' => 'title',
    'other_left' => 'title',
    'name_field' => 'title',
    'description_field' => '',
    'view_mode' => 'full',
    'style_field' => '',
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['id'] = 'reverse_field_headquarter_hotel_node';
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_headquarter_hotel_node']['field'] = 'reverse_field_headquarter_hotel_node';
  /* Field: Node ID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Node ID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Title - overrided */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title - overrided';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['field_location']['label'] = '';
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_location']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['ui_name'] = 'Description';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'accommodation' => 'accommodation',
    'activity' => 'activity',
  );
  $handler->display->display_options['arguments']['nid']['validate']['fail'] = 'ignore';
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
    'activity' => 'activity',
  );
  /* Filter criterion: Content: Location - proximity */
  $handler->display->display_options['filters']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['operator'] = '<';
  $handler->display->display_options['filters']['field_geofield_distance']['value'] = array(
    'distance' => '2000',
    'distance2' => 200,
    'unit' => '6371',
    'origin' => '',
  );
  $handler->display->display_options['filters']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_geocoder_engine'] = 'json';

  /* Display: Overlay active accommodation */
  $handler = $view->new_display('openlayers', 'Overlay active accommodation', 'accommodation_active');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'accommodation' => 'accommodation',
    'activity' => 'activity',
  );
  $handler->display->display_options['arguments']['nid']['validate']['fail'] = 'ignore';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
  );

  /* Display: Overlay active activity */
  $handler = $view->new_display('openlayers', 'Overlay active activity', 'active_activity');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'activity' => 'activity',
  );

  /* Display: Overlay HQ */
  $handler = $view->new_display('openlayers', 'Overlay HQ', 'overlay_hq');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Node ID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Node ID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Title - overriden */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title - overriden';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['field_location']['label'] = '';
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_location']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['ui_name'] = 'Description';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_headquarter_hotel_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
  );

  /* Display: Overlay HQ location */
  $handler = $view->new_display('openlayers', 'Overlay HQ location', 'openlayers_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'title',
    'other_lon' => 'title',
    'wkt' => 'field_hq_location',
    'other_top' => 'title',
    'other_right' => 'title',
    'other_bottom' => 'title',
    'other_left' => 'title',
    'name_field' => '',
    'description_field' => '',
    'view_mode' => 'full',
    'style_field' => '',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Node ID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Node ID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Title - overriden */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title - overriden';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Description */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['ui_name'] = 'Description';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Field: Content: Headquarter location */
  $handler->display->display_options['fields']['field_hq_location']['id'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_hq_location']['table'] = 'field_data_field_hq_location';
  $handler->display->display_options['fields']['field_hq_location']['field'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_hq_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_hq_location']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_hq_location']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Content: Headquarter info */
  $handler->display->display_options['fields']['field_headquarter_info']['id'] = 'field_headquarter_info';
  $handler->display->display_options['fields']['field_headquarter_info']['table'] = 'field_data_field_headquarter_info';
  $handler->display->display_options['fields']['field_headquarter_info']['field'] = 'field_headquarter_info';
  $handler->display->display_options['fields']['field_headquarter_info']['label'] = '';
  $handler->display->display_options['fields']['field_headquarter_info']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_headquarter_hotel_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );

  /* Display: Accommodations pane */
  $handler = $view->new_display('panel_pane', 'Accommodations pane', 'event_map');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'event_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'null' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '56',
      'label' => 'Global: Null',
    ),
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );

  /* Display: Active activity pane */
  $handler = $view->new_display('panel_pane', 'Active activity pane', 'active_activity_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'activity_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'null' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '56',
      'label' => 'Global: Null',
    ),
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );

  /* Display: Overlay activities */
  $handler = $view->new_display('openlayers', 'Overlay activities', 'overlay_activities');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'activity' => 'activity',
  );
  /* Filter criterion: Content: Location - proximity */
  $handler->display->display_options['filters']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['operator'] = '<=';
  $handler->display->display_options['filters']['field_geofield_distance']['value'] = array(
    'distance' => '100',
    'distance2' => 200,
    'unit' => '6371',
    'origin' => '',
  );
  $handler->display->display_options['filters']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';

  /* Display: Overlay accommodations */
  $handler = $view->new_display('openlayers', 'Overlay accommodations', 'overlay_accommodations');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['null']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['null']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
  );
  /* Filter criterion: Content: Location - proximity */
  $handler->display->display_options['filters']['field_geofield_distance']['id'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_geofield_distance']['field'] = 'field_geofield_distance';
  $handler->display->display_options['filters']['field_geofield_distance']['operator'] = '<=';
  $handler->display->display_options['filters']['field_geofield_distance']['value'] = array(
    'distance' => '30',
    'distance2' => 200,
    'unit' => '6371',
    'origin' => '',
  );
  $handler->display->display_options['filters']['field_geofield_distance']['source'] = 'entity_from_argument';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_entity_url_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_current_user_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_field'] = 'field_hq_location';
  $handler->display->display_options['filters']['field_geofield_distance']['geofield_proximity_argument_number'] = '0';

  /* Display: Active accommodation pane */
  $handler = $view->new_display('panel_pane', 'Active accommodation pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'accommodation_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'null' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '56',
      'label' => 'Global: Null',
    ),
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );

  /* Display: Activities pane */
  $handler = $view->new_display('panel_pane', 'Activities pane', 'activities_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'eventactivities_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'null' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '56',
      'label' => 'Global: Null',
    ),
    'nid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 1,
      'panel' => '0',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );

  /* Display: Overlay all accommodations */
  $handler = $view->new_display('openlayers', 'Overlay all accommodations', 'openlayers_2');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'title',
    'other_lon' => 'title',
    'wkt' => 'field_location',
    'other_top' => 'title',
    'other_right' => 'title',
    'other_bottom' => 'title',
    'other_left' => 'title',
    'name_field' => '',
    'description_field' => '#row',
    'view_mode' => 'full',
    'style_field' => '',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Node ID - excluded */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Node ID - excluded';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Title - overrided */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title - overrided';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/!1/map/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['ui_name'] = 'Location';
  $handler->display->display_options['fields']['field_location']['label'] = '';
  $handler->display->display_options['fields']['field_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_location']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Select as headquarter';
  $handler->display->display_options['fields']['nothing']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_class'] = 'entityreference-select';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Node is published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node is published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
  );
  /* Filter criterion: Content: Location (field_location:lat) */
  $handler->display->display_options['filters']['field_location_lat']['id'] = 'field_location_lat';
  $handler->display->display_options['filters']['field_location_lat']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_location_lat']['field'] = 'field_location_lat';
  $handler->display->display_options['filters']['field_location_lat']['operator'] = 'between';
  $handler->display->display_options['filters']['field_location_lat']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_location_lat']['expose']['operator_id'] = 'field_location_lat_op';
  $handler->display->display_options['filters']['field_location_lat']['expose']['label'] = 'Location (field_location:lat)';
  $handler->display->display_options['filters']['field_location_lat']['expose']['operator'] = 'field_location_lat_op';
  $handler->display->display_options['filters']['field_location_lat']['expose']['identifier'] = 'field_location_lat';
  $handler->display->display_options['filters']['field_location_lat']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    7 => 0,
  );
  /* Filter criterion: Content: Location (field_location:lon) */
  $handler->display->display_options['filters']['field_location_lon']['id'] = 'field_location_lon';
  $handler->display->display_options['filters']['field_location_lon']['table'] = 'field_data_field_location';
  $handler->display->display_options['filters']['field_location_lon']['field'] = 'field_location_lon';
  $handler->display->display_options['filters']['field_location_lon']['operator'] = 'between';
  $handler->display->display_options['filters']['field_location_lon']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_location_lon']['expose']['operator_id'] = 'field_location_lon_op';
  $handler->display->display_options['filters']['field_location_lon']['expose']['label'] = 'Location (field_location:lon)';
  $handler->display->display_options['filters']['field_location_lon']['expose']['operator'] = 'field_location_lon_op';
  $handler->display->display_options['filters']['field_location_lon']['expose']['identifier'] = 'field_location_lon';
  $handler->display->display_options['filters']['field_location_lon']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    5 => 0,
    4 => 0,
    7 => 0,
  );
  $translatables['event_map'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Content referencing Content from field_headquarter_hotel'),
    t('All'),
    t('Overlay active accommodation'),
    t('Overlay active activity'),
    t('Overlay HQ'),
    t('Overlay HQ location'),
    t('Headquarter location'),
    t('Accommodations pane'),
    t('View panes'),
    t('Active activity pane'),
    t('Overlay activities'),
    t('Overlay accommodations'),
    t('Active accommodation pane'),
    t('Activities pane'),
    t('Overlay all accommodations'),
    t('Select as headquarter'),
    t('Location (field_location:lat)'),
    t('Location (field_location:lon)'),
  );
  $export['event_map'] = $view;

  $view = new view();
  $view->name = 'events_list';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'List of past, current and next events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Current events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No events found';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: NID (excluded) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'NID (excluded)';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Path (excluded) */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['ui_name'] = 'Path (excluded)';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['text'] = 'event/[nid]';
  $handler->display->display_options['fields']['path']['element_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['path']['element_default_classes'] = FALSE;
  /* Field: Dates (excluded) */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['ui_name'] = 'Dates (excluded)';
  $handler->display->display_options['fields']['field_dates']['label'] = '';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates']['type'] = 'adapitve_dates';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Title (excluded) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (excluded)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'span';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Country (excluded) */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['ui_name'] = 'Country (excluded)';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  /* Field: City (excluded) */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['ui_name'] = 'City (excluded)';
  $handler->display->display_options['fields']['field_city']['label'] = '';
  $handler->display->display_options['fields']['field_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_city']['element_label_colon'] = FALSE;
  /* Field: All fields */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'All fields';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'next_event';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_dates_1']['id'] = 'field_dates_1';
  $handler->display->display_options['fields']['field_dates_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates_1']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates_1']['label'] = '';
  $handler->display->display_options['fields']['field_dates_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates_1']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Sort criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['filters']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_dates_value']['default_date'] = 'now';
  /* Filter criterion: Content: Dates - end date (field_dates:value2) */
  $handler->display->display_options['filters']['field_dates_value2']['id'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value2']['field'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['operator'] = '<=';
  $handler->display->display_options['filters']['field_dates_value2']['default_date'] = 'now';

  /* Display: Past */
  $handler = $view->new_display('page', 'Past', 'page_events_past');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Past events';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_dates_1',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: NID (excluded) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'NID (excluded)';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Path (excluded) */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['ui_name'] = 'Path (excluded)';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['text'] = 'event/[nid]';
  $handler->display->display_options['fields']['path']['element_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['path']['element_default_classes'] = FALSE;
  /* Field: Dates (excluded) */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['ui_name'] = 'Dates (excluded)';
  $handler->display->display_options['fields']['field_dates']['label'] = '';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates']['type'] = 'adapitve_dates';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Title (excluded) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (excluded)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'span';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Country (excluded) */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['ui_name'] = 'Country (excluded)';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  /* Field: City (excluded) */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['ui_name'] = 'City (excluded)';
  $handler->display->display_options['fields']['field_city']['label'] = '';
  $handler->display->display_options['fields']['field_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_city']['element_label_colon'] = FALSE;
  /* Field: All fields */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'All fields';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'next_event';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_dates_1']['id'] = 'field_dates_1';
  $handler->display->display_options['fields']['field_dates_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates_1']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates_1']['label'] = '';
  $handler->display->display_options['fields']['field_dates_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates_1']['settings'] = array(
    'format_type' => 'year',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Content: Dates - end date (field_dates:value2) */
  $handler->display->display_options['filters']['field_dates_value2']['id'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value2']['field'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['operator'] = '<';
  $handler->display->display_options['filters']['field_dates_value2']['default_date'] = 'now';
  $handler->display->display_options['path'] = 'events/past';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Past';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Next */
  $handler = $view->new_display('page', 'Next', 'page_events_next');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Next events';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_dates_1',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['filters']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_dates_value']['default_date'] = 'now';
  $handler->display->display_options['path'] = 'events/next';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Next';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Next';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Current */
  $handler = $view->new_display('page', 'Current', 'page_events_current');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Current events';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['filters']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['operator'] = '<=';
  $handler->display->display_options['filters']['field_dates_value']['default_date'] = 'now';
  /* Filter criterion: Content: Dates - end date (field_dates:value2) */
  $handler->display->display_options['filters']['field_dates_value2']['id'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value2']['field'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['operator'] = '>=';
  $handler->display->display_options['filters']['field_dates_value2']['default_date'] = 'now';
  $handler->display->display_options['path'] = 'events/current';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Current';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Current';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['events_list'] = array(
    t('Master'),
    t('Current events'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('No events found'),
    t('event/[nid]'),
    t('<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>'),
    t('Past'),
    t('Past events'),
    t('Next'),
    t('Next events'),
    t('Current'),
  );
  $export['events_list'] = $view;

  $view = new view();
  $view->name = 'events_map';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'events_map';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'openlayers_data';
  $handler->display->display_options['style_options']['data_source'] = array(
    'value' => 'wkt',
    'other_lat' => 'field_hq_location',
    'other_lon' => 'field_hq_location',
    'wkt' => 'field_hq_location',
    'other_top' => 'title',
    'other_right' => 'title',
    'other_bottom' => 'title',
    'other_left' => 'title',
    'name_field' => '',
    'description_field' => 'nothing',
    'view_mode' => 'full',
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Title (excluded) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (excluded)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'event/[nid]';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Headquarter location */
  $handler->display->display_options['fields']['field_hq_location']['id'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_hq_location']['table'] = 'field_data_field_hq_location';
  $handler->display->display_options['fields']['field_hq_location']['field'] = 'field_hq_location';
  $handler->display->display_options['fields']['field_hq_location']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_hq_location']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Country (excluded) */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['ui_name'] = 'Country (excluded)';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  /* Field: City (excluded) */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['ui_name'] = 'City (excluded)';
  $handler->display->display_options['fields']['field_city']['label'] = '';
  $handler->display->display_options['fields']['field_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_city']['element_label_colon'] = FALSE;
  /* Field: Dates (excluded) */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['ui_name'] = 'Dates (excluded)';
  $handler->display->display_options['fields']['field_dates']['label'] = '';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates']['type'] = 'adapitve_dates';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: All fields for popup */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'All fields for popup';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'event/[nid]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Next:start */
  $handler->display->display_options['filters']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['ui_name'] = 'Next:start';
  $handler->display->display_options['filters']['field_dates_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_dates_value']['default_date'] = 'now';
  /* Filter criterion: Past:finish */
  $handler->display->display_options['filters']['field_dates_value2']['id'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value2']['field'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2']['ui_name'] = 'Past:finish';
  $handler->display->display_options['filters']['field_dates_value2']['operator'] = '<';
  $handler->display->display_options['filters']['field_dates_value2']['default_date'] = 'now';
  /* Filter criterion: Current:start */
  $handler->display->display_options['filters']['field_dates_value_1']['id'] = 'field_dates_value_1';
  $handler->display->display_options['filters']['field_dates_value_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value_1']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value_1']['ui_name'] = 'Current:start';
  $handler->display->display_options['filters']['field_dates_value_1']['operator'] = '<=';
  $handler->display->display_options['filters']['field_dates_value_1']['default_date'] = 'now';
  /* Filter criterion: Current:finish */
  $handler->display->display_options['filters']['field_dates_value2_1']['id'] = 'field_dates_value2_1';
  $handler->display->display_options['filters']['field_dates_value2_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value2_1']['field'] = 'field_dates_value2';
  $handler->display->display_options['filters']['field_dates_value2_1']['ui_name'] = 'Current:finish';
  $handler->display->display_options['filters']['field_dates_value2_1']['operator'] = '>=';
  $handler->display->display_options['filters']['field_dates_value2_1']['default_date'] = 'now';

  /* Display: Events overlay */
  $handler = $view->new_display('openlayers', 'Events overlay', 'overlay');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';

  /* Display: Events pane */
  $handler = $view->new_display('panel_pane', 'Events pane', 'events_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'openlayers_map';
  $handler->display->display_options['style_options']['map'] = 'events_map';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $translatables['events_map'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Nid'),
    t('Headquarter location'),
    t('<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>'),
    t('Events overlay'),
    t('Events pane'),
    t('View panes'),
  );
  $export['events_map'] = $view;

  $view = new view();
  $view->name = 'header_slideshow';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'eck_ent_featured_header';
  $view->human_name = 'Header slideshow';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'slideshow';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['slideshow_type'] = 'views_slideshow_cycle';
  $handler->display->display_options['style_options']['slideshow_skin'] = 'default';
  $handler->display->display_options['style_options']['skin_info'] = array(
    'class' => 'default',
    'name' => 'Default',
    'module' => 'views_slideshow',
    'path' => '',
    'stylesheets' => array(),
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_header_image' => 0,
    'field_header_author' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['top']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['type'] = 'views_slideshow_pager_fields';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_pager']['views_slideshow_pager_fields_fields'] = array(
    'field_header_image' => 0,
    'field_header_author' => 0,
  );
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['weight'] = '1';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_controls']['type'] = 'views_slideshow_controls_text';
  $handler->display->display_options['style_options']['widgets']['bottom']['views_slideshow_slide_counter']['weight'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['transition_advanced'] = 1;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['timeout'] = '7000';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['speed'] = '1800';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['delay'] = '0';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['start_paused'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['remember_slide_days'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['items_per_slide'] = '1';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['wait_for_image_load_timeout'] = '3000';
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartype'] = 0;
  $handler->display->display_options['style_options']['views_slideshow_cycle']['cleartypenobg'] = 0;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Relationship: OG membership: OG membership from Featured header */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Featured header: Image */
  $handler->display->display_options['fields']['field_header_image']['id'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['table'] = 'field_data_field_header_image';
  $handler->display->display_options['fields']['field_header_image']['field'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['label'] = '';
  $handler->display->display_options['fields']['field_header_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_header_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_header_image']['settings'] = array(
    'image_style' => 'header',
    'image_link' => '',
  );
  /* Field: Featured header: Author link */
  $handler->display->display_options['fields']['field_header_author']['id'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['table'] = 'field_data_field_header_author';
  $handler->display->display_options['fields']['field_header_author']['field'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['label'] = 'Photo by';

  /* Display: Default header */
  $handler = $view->new_display('panel_pane', 'Default header', 'default_header');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: OG membership: Group ID */
  $handler->display->display_options['filters']['gid']['id'] = 'gid';
  $handler->display->display_options['filters']['gid']['table'] = 'og_membership';
  $handler->display->display_options['filters']['gid']['field'] = 'gid';
  $handler->display->display_options['filters']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['gid']['operator'] = 'empty';

  /* Display: Front page header */
  $handler = $view->new_display('panel_pane', 'Front page header', 'front_page_header');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Featured header: Image */
  $handler->display->display_options['fields']['field_header_image']['id'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['table'] = 'field_data_field_header_image';
  $handler->display->display_options['fields']['field_header_image']['field'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['label'] = '';
  $handler->display->display_options['fields']['field_header_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_header_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_header_image']['settings'] = array(
    'image_style' => 'header',
    'image_link' => '',
  );
  /* Field: Featured header: Author link */
  $handler->display->display_options['fields']['field_header_author']['id'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['table'] = 'field_data_field_header_author';
  $handler->display->display_options['fields']['field_header_author']['field'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['label'] = 'Photo by';
  /* Field: Featured header: Slogan */
  $handler->display->display_options['fields']['field_header_slogan']['id'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['table'] = 'field_data_field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['field'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['label'] = '';
  $handler->display->display_options['fields']['field_header_slogan']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Field: Groups audience (og_group_ref) */
  $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['og_group_ref_target_id']['operator'] = 'empty';

  /* Display: Event header */
  $handler = $view->new_display('panel_pane', 'Event header', 'event_header');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Featured header */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Featured header: Type (field_header_page) */
  $handler->display->display_options['filters']['field_header_page_value']['id'] = 'field_header_page_value';
  $handler->display->display_options['filters']['field_header_page_value']['table'] = 'field_data_field_header_page';
  $handler->display->display_options['filters']['field_header_page_value']['field'] = 'field_header_page_value';
  $handler->display->display_options['filters']['field_header_page_value']['operator'] = 'empty';
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Event Results header */
  $handler = $view->new_display('panel_pane', 'Event Results header', 'event_results_header');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: View (Views field view) */
  $handler->display->display_options['empty']['view_field']['id'] = 'view_field';
  $handler->display->display_options['empty']['view_field']['table'] = 'views';
  $handler->display->display_options['empty']['view_field']['field'] = 'view_field';
  $handler->display->display_options['empty']['view_field']['label'] = '';
  $handler->display->display_options['empty']['view_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['empty']['view_field']['view'] = 'header_slideshow';
  $handler->display->display_options['empty']['view_field']['display'] = 'event_header';
  $handler->display->display_options['empty']['view_field']['arguments'] = '!1';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: OG membership: OG membership from Featured header */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Featured header: Type (field_header_page) */
  $handler->display->display_options['filters']['field_header_page_value']['id'] = 'field_header_page_value';
  $handler->display->display_options['filters']['field_header_page_value']['table'] = 'field_data_field_header_page';
  $handler->display->display_options['filters']['field_header_page_value']['field'] = 'field_header_page_value';
  $handler->display->display_options['filters']['field_header_page_value']['value'] = array(
    'results' => 'results',
  );
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );
  $translatables['header_slideshow'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from ent_featured_header'),
    t('Photo by'),
    t('Default header'),
    t('View panes'),
    t('Front page header'),
    t('Event header'),
    t('All'),
    t('Event Results header'),
  );
  $export['header_slideshow'] = $view;

  $view = new view();
  $view->name = 'my_registrations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'og_membership';
  $view->human_name = 'My registrations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My registrations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'You do not take part in any of the upcoming events.';
  $handler->display->display_options['empty']['area']['format'] = 'php_code';
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['required'] = TRUE;
  /* Relationship: OG membership: Group Node from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_node_group']['id'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['field'] = 'og_membership_related_node_group';
  $handler->display->display_options['relationships']['og_membership_related_node_group']['required'] = TRUE;
  /* Field: OG membership: Og membership ID */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'og_membership';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['id'] = 'field_pg_contestant_status_1';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['label'] = '';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['element_label_colon'] = FALSE;
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['label'] = '';
  $handler->display->display_options['fields']['field_pg_contestant_status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_pg_contestant_status']['element_class'] = 'status-[field_pg_contestant_status_1]';
  $handler->display->display_options['fields']['field_pg_contestant_status']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_pg_contestant_status']['type'] = 'i18n_list_default';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_dates']['label'] = '';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates']['type'] = 'adapitve_dates';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['fields']['field_city']['label'] = '';
  $handler->display->display_options['fields']['field_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_city']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<span class="event-header"><span class="title">[title]</span><span class="status-value">[field_pg_contestant_status]</span></span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'event/[nid]';
  $handler->display->display_options['fields']['nothing_1']['alter']['link_class'] = 'next_event';
  $handler->display->display_options['fields']['nothing_1']['element_class'] = 'status-[field_pg_contestant_status_1]';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Cancel';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'group-membership/[id]/delete';
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'cancel-participation';
  $handler->display->display_options['fields']['nothing']['element_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nothing']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['nothing']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['sorts']['field_dates_value']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['relationship'] = 'og_membership_related_user';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['argument'] = '1';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['filters']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['relationship'] = 'og_membership_related_node_group';
  $handler->display->display_options['filters']['field_dates_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_dates_value']['group'] = 1;
  $handler->display->display_options['filters']['field_dates_value']['default_date'] = 'now';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'uid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'User: Uid',
    ),
  );
  $translatables['my_registrations'] = array(
    t('Master'),
    t('My registrations'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('You do not take part in any of the upcoming events.'),
    t('user from OG membership'),
    t('Group node from OG membership'),
    t('.'),
    t('<span class="event-header"><span class="title">[title]</span><span class="status-value">[field_pg_contestant_status]</span></span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>'),
    t('Cancel'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['my_registrations'] = $view;

  $view = new view();
  $view->name = 'next_events';
  $view->description = 'Display three upcoming events';
  $view->tag = 'airtribune';
  $view->base_table = 'node';
  $view->human_name = 'Next events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Next events';
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['use_more_text'] = 'All events';
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '3';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: NID (excluded) */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'NID (excluded)';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Path (excluded) */
  $handler->display->display_options['fields']['path']['id'] = 'path';
  $handler->display->display_options['fields']['path']['table'] = 'node';
  $handler->display->display_options['fields']['path']['field'] = 'path';
  $handler->display->display_options['fields']['path']['ui_name'] = 'Path (excluded)';
  $handler->display->display_options['fields']['path']['label'] = '';
  $handler->display->display_options['fields']['path']['exclude'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['path']['alter']['text'] = 'event/[nid]';
  $handler->display->display_options['fields']['path']['element_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_type'] = '0';
  $handler->display->display_options['fields']['path']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['path']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['path']['element_default_classes'] = FALSE;
  /* Field: Title (excluded) */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title (excluded)';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'span';
  $handler->display->display_options['fields']['title']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Dates (excluded) */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['ui_name'] = 'Dates (excluded)';
  $handler->display->display_options['fields']['field_dates']['label'] = '';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_dates']['type'] = 'adapitve_dates';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Country (excluded) */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['ui_name'] = 'Country (excluded)';
  $handler->display->display_options['fields']['field_country']['label'] = '';
  $handler->display->display_options['fields']['field_country']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_country']['element_label_colon'] = FALSE;
  /* Field: City (excluded) */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['ui_name'] = 'City (excluded)';
  $handler->display->display_options['fields']['field_city']['label'] = '';
  $handler->display->display_options['fields']['field_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_city']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['field_city']['element_label_colon'] = FALSE;
  /* Field: All fields with markup */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'All fields with markup';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[path]';
  $handler->display->display_options['fields']['nothing']['alter']['absolute'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['link_class'] = 'next_event';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: FAI category (field_fai_category) */
  $handler->display->display_options['sorts']['field_fai_category_value']['id'] = 'field_fai_category_value';
  $handler->display->display_options['sorts']['field_fai_category_value']['table'] = 'field_data_field_fai_category';
  $handler->display->display_options['sorts']['field_fai_category_value']['field'] = 'field_fai_category_value';
  /* Sort criterion: Start date */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['ui_name'] = 'Start date';
  /* Filter criterion: Node should be published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['ui_name'] = 'Node should be published';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Start date is greater than */
  $handler->display->display_options['filters']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['filters']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['filters']['field_dates_value']['ui_name'] = 'Start date is greater than';
  $handler->display->display_options['filters']['field_dates_value']['operator'] = '>';
  $handler->display->display_options['filters']['field_dates_value']['default_date'] = 'now';

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'sidebar_pane');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['link_url'] = 'events';
  $translatables['next_events'] = array(
    t('Master'),
    t('Next events'),
    t('All events'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('event/[nid]'),
    t('<span class="title">[title]</span><span class="dates">[field_dates]</span><span class="place">[field_country], [field_city]</span>'),
    t('Content pane'),
    t('more'),
    t('View panes'),
  );
  $export['next_events'] = $view;

  $view = new view();
  $view->name = 'paragliding_contest_pilots_stats';
  $view->description = 'Statistics: count of confirmed pilots on event';
  $view->tag = 'airtribune';
  $view->base_table = 'users';
  $view->human_name = 'Paragliding contest pilots statistics';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['footer']['result']['content'] = '@total';
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  $handler->display->display_options['fields']['name']['format_username'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = '%1 members';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';
  /* Filter criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['value'] = array(
    4 => '4',
  );
  $translatables['paragliding_contest_pilots_stats'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('@total'),
    t('OG membership from user'),
    t('All'),
    t('%1 members'),
  );
  $export['paragliding_contest_pilots_stats'] = $view;

  $view = new view();
  $view->name = 'paragliding_pilots_list';
  $view->description = '';
  $view->tag = 'airtribune';
  $view->base_table = 'users';
  $view->human_name = 'Paragliding contest pilots';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '3600';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '3600';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_gender',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
    1 => array(
      'field' => 'field_pg_contestant_status',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_full_name' => 'field_full_name',
    'field_paraglider_model' => 'field_paraglider_model',
    'field_pg_contestant_status' => 'field_pg_contestant_status',
    'field_gender' => 'field_gender',
    'field_address' => 'field_address',
  );
  $handler->display->display_options['style_options']['default'] = 'field_pg_contestant_status';
  $handler->display->display_options['style_options']['info'] = array(
    'field_full_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_model' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pg_contestant_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gender' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['label'] = 'MainProfile';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'main' => 'main',
  );
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile_1']['id'] = 'profile_1';
  $handler->display->display_options['relationships']['profile_1']['table'] = 'users';
  $handler->display->display_options['relationships']['profile_1']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile_1']['label'] = 'PilotProfile';
  $handler->display->display_options['relationships']['profile_1']['bundle_types'] = array(
    'pilot' => 'pilot',
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  /* Field: Field: Paraglider color */
  $handler->display->display_options['fields']['field_paraglider_color']['id'] = 'field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['table'] = 'field_data_field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['field'] = 'field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['relationship'] = 'og_membership_rel';
  /* Field: Field: Paraglider manufacturer */
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['id'] = 'field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['table'] = 'field_data_field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['field'] = 'field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['relationship'] = 'og_membership_rel';
  /* Field: Field: Paraglider model */
  $handler->display->display_options['fields']['field_paraglider_model']['id'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['table'] = 'field_data_field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['field'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['relationship'] = 'og_membership_rel';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status']['type'] = 'i18n_list_default';
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Profile: Gender */
  $handler->display->display_options['fields']['field_gender']['id'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['table'] = 'field_data_field_gender';
  $handler->display->display_options['fields']['field_gender']['field'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['relationship'] = 'profile';
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['text'] = '[field_address-country]';
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(),
  );
  /* Field: Field: Link to Tracker */
  $handler->display->display_options['fields']['field_tracker']['id'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['table'] = 'field_data_field_tracker';
  $handler->display->display_options['fields']['field_tracker']['field'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_tracker']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Profile: Gender (field_gender) */
  $handler->display->display_options['sorts']['field_gender_value']['id'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['table'] = 'field_data_field_gender';
  $handler->display->display_options['sorts']['field_gender_value']['field'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['relationship'] = 'profile';
  $handler->display->display_options['sorts']['field_gender_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'og_membership';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'og_membership_rel';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = '%1 members';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';
  /* Filter criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['value'] = array(
    4 => '4',
  );

  /* Display: Standard */
  $handler = $view->new_display('panel_pane', 'Standard', 'standard');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_gender',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_contestant_number' => 'field_contestant_number',
    'field_gender' => 'field_gender',
    'counter' => 'counter',
    'field_full_name' => 'field_full_name',
    'field_address' => 'field_address',
    'field_sponsors' => 'field_sponsors',
    'field_paraglider_model' => 'field_paraglider_model',
    'field_pg_contestant_status' => 'field_pg_contestant_status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_contestant_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gender' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_full_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sponsors' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_model' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pg_contestant_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Pilot`s number (excluded) */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot`s number (excluded)';
  $handler->display->display_options['fields']['field_contestant_number']['label'] = '';
  $handler->display->display_options['fields']['field_contestant_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_contestant_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Payment status (excluded) */
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['id'] = 'field_pg_contestant_status_1';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['ui_name'] = 'Payment status (excluded)';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['exclude'] = TRUE;
  /* Field: Gender (excluded) */
  $handler->display->display_options['fields']['field_gender']['id'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['table'] = 'field_data_field_gender';
  $handler->display->display_options['fields']['field_gender']['field'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_gender']['ui_name'] = 'Gender (excluded)';
  $handler->display->display_options['fields']['field_gender']['label'] = '';
  $handler->display->display_options['fields']['field_gender']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gender']['element_label_colon'] = FALSE;
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name] ([field_contestant_number])';
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address']['label'] = 'Country';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['text'] = '[field_address-country]';
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(),
  );
  /* Field: Profile: Sponsors */
  $handler->display->display_options['fields']['field_sponsors']['id'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['table'] = 'field_data_field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['field'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_sponsors']['label'] = 'Sponsor';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status']['alter']['text'] = '<span class="status-value">[field_pg_contestant_status]</span>';
  $handler->display->display_options['fields']['field_pg_contestant_status']['element_class'] = 'status-[field_pg_contestant_status_1]';
  $handler->display->display_options['fields']['field_pg_contestant_status']['settings'] = array(
    'click_to_edit' => 1,
    'empty_text' => '',
    'fallback_format' => 'list_default',
  );
  /* Field: Field: Paraglider model */
  $handler->display->display_options['fields']['field_paraglider_model']['id'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['table'] = 'field_data_field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['field'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_paraglider_model']['label'] = 'Glider';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Profile: Gender (field_gender) */
  $handler->display->display_options['sorts']['field_gender_value']['id'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['table'] = 'field_data_field_gender';
  $handler->display->display_options['sorts']['field_gender_value']['field'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['relationship'] = 'profile';
  $handler->display->display_options['sorts']['field_gender_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'og_membership';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';
  $handler->display->display_options['pane_title'] = 'Standard event pilots';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: FAI */
  $handler = $view->new_display('panel_pane', 'FAI', 'fai');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_address',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_contestant_number' => 'field_contestant_number',
    'field_address' => 'field_address',
    'field_gender' => 'field_gender',
    'counter' => 'counter',
    'field_full_name' => 'field_full_name',
    'field_sponsors' => 'field_sponsors',
    'field_paraglider_model' => 'field_paraglider_model',
    'field_pg_contestant_status' => 'field_pg_contestant_status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_contestant_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gender' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_full_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sponsors' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_model' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pg_contestant_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Pilot`s number (excluded) */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot`s number (excluded)';
  $handler->display->display_options['fields']['field_contestant_number']['label'] = '';
  $handler->display->display_options['fields']['field_contestant_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_contestant_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contestant_number']['type'] = 'number_unformatted';
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Payment status (excluded) */
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['id'] = 'field_pg_contestant_status_1';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['ui_name'] = 'Payment status (excluded)';
  $handler->display->display_options['fields']['field_pg_contestant_status_1']['exclude'] = TRUE;
  /* Field: Country (excluded) */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address']['ui_name'] = 'Country (excluded)';
  $handler->display->display_options['fields']['field_address']['label'] = '';
  $handler->display->display_options['fields']['field_address']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['text'] = '[field_address-country]';
  $handler->display->display_options['fields']['field_address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(),
  );
  /* Field: Gender (excluded) */
  $handler->display->display_options['fields']['field_gender']['id'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['table'] = 'field_data_field_gender';
  $handler->display->display_options['fields']['field_gender']['field'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_gender']['ui_name'] = 'Gender (excluded)';
  $handler->display->display_options['fields']['field_gender']['label'] = '';
  $handler->display->display_options['fields']['field_gender']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gender']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_gender']['alter']['text'] = '<span class="gender-[field_gender-value]"></span>';
  $handler->display->display_options['fields']['field_gender']['element_label_colon'] = FALSE;
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name] ([field_contestant_number])[field_gender]';
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Profile: Sponsors */
  $handler->display->display_options['fields']['field_sponsors']['id'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['table'] = 'field_data_field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['field'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_sponsors']['label'] = 'Sponsor';
  /* Field: Field: Paraglider model */
  $handler->display->display_options['fields']['field_paraglider_model']['id'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['table'] = 'field_data_field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['field'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_paraglider_model']['label'] = 'Glider';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status']['alter']['text'] = '<span class="status-value">[field_pg_contestant_status]</span>';
  $handler->display->display_options['fields']['field_pg_contestant_status']['element_class'] = 'status-[field_pg_contestant_status_1]';
  $handler->display->display_options['fields']['field_pg_contestant_status']['settings'] = array(
    'click_to_edit' => 1,
    'empty_text' => '',
    'fallback_format' => 'list_default',
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Country */
  $handler->display->display_options['sorts']['field_address_country']['id'] = 'field_address_country';
  $handler->display->display_options['sorts']['field_address_country']['table'] = 'field_data_field_address';
  $handler->display->display_options['sorts']['field_address_country']['field'] = 'field_address_country';
  $handler->display->display_options['sorts']['field_address_country']['relationship'] = 'profile_1';
  $handler->display->display_options['sorts']['field_address_country']['ui_name'] = 'Country';
  /* Sort criterion: Payment status */
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['ui_name'] = 'Payment status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['order'] = 'DESC';
  /* Sort criterion: Gender */
  $handler->display->display_options['sorts']['field_gender_value']['id'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['table'] = 'field_data_field_gender';
  $handler->display->display_options['sorts']['field_gender_value']['field'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['relationship'] = 'profile';
  $handler->display->display_options['sorts']['field_gender_value']['ui_name'] = 'Gender';
  $handler->display->display_options['sorts']['field_gender_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';
  $handler->display->display_options['pane_title'] = 'FAI event pilots';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Pilot Export */
  $handler = $view->new_display('panel_pane', 'Pilot Export', 'panel_pane_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_gender',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_full_name' => 'field_full_name',
    'field_gender' => 'field_gender',
    'mail' => 'mail',
    'field_contestant_number' => 'field_contestant_number',
    'field_birthdate' => 'field_birthdate',
    'field_address' => 'field_address',
    'field_address_1' => 'field_address_1',
    'field_phone' => 'field_phone',
    'field_fai_license_number' => 'field_fai_license_number',
    'field_civl_id' => 'field_civl_id',
    'field_t_shirt_size' => 'field_t_shirt_size',
    'field_paraglider_manufacturer' => 'field_paraglider_manufacturer',
    'field_paraglider_model' => 'field_paraglider_model',
    'field_paraglider_color' => 'field_paraglider_color',
    'field_sponsors' => 'field_sponsors',
    'field_insurance_company' => 'field_insurance_company',
    'field_insurance_policy_number' => 'field_insurance_policy_number',
    'field_name_in_national_alphabet' => 'field_name_in_national_alphabet',
    'field_person_phone' => 'field_person_phone',
    'field_blood_type' => 'field_blood_type',
    'field_pg_contestant_status' => 'field_pg_contestant_status',
    'field_person_name' => 'field_person_name',
    'etid' => 'etid',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_full_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gender' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'mail' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_contestant_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_birthdate' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_fai_license_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_civl_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_t_shirt_size' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_manufacturer' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_model' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_color' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sponsors' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_insurance_company' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_insurance_policy_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_name_in_national_alphabet' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_person_phone' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_blood_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pg_contestant_status' => array(
      'sortable' => 0,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_person_name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'etid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: OG membership: Entity id */
  $handler->display->display_options['fields']['etid']['id'] = 'etid';
  $handler->display->display_options['fields']['etid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['etid']['field'] = 'etid';
  $handler->display->display_options['fields']['etid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['etid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['etid']['separator'] = '';
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name] ([field_contestant_number])';
  $handler->display->display_options['fields']['field_full_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Gender */
  $handler->display->display_options['fields']['field_gender']['id'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['table'] = 'field_data_field_gender';
  $handler->display->display_options['fields']['field_gender']['field'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_gender']['ui_name'] = 'Gender';
  $handler->display->display_options['fields']['field_gender']['element_label_colon'] = FALSE;
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Field: Pilot`s number */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot`s number';
  $handler->display->display_options['fields']['field_contestant_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Profile: Date of birth */
  $handler->display->display_options['fields']['field_birthdate']['id'] = 'field_birthdate';
  $handler->display->display_options['fields']['field_birthdate']['table'] = 'field_data_field_birthdate';
  $handler->display->display_options['fields']['field_birthdate']['field'] = 'field_birthdate';
  $handler->display->display_options['fields']['field_birthdate']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_birthdate']['settings'] = array(
    'format_type' => 'dmy_dot',
    'fromto' => '',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address']['label'] = 'Nation';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['text'] = '[field_address-country]';
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(),
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address_1']['id'] = 'field_address_1';
  $handler->display->display_options['fields']['field_address_1']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address_1']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address_1']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address_1']['label'] = 'City';
  $handler->display->display_options['fields']['field_address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address_1']['alter']['text'] = '[field_address_1-locality]';
  $handler->display->display_options['fields']['field_address_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address_2']['id'] = 'field_address_2';
  $handler->display->display_options['fields']['field_address_2']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address_2']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address_2']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address_2']['alter']['text'] = '[field_address_2-thoroughfare]';
  $handler->display->display_options['fields']['field_address_2']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address_2']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Field: Mobile phone number */
  $handler->display->display_options['fields']['field_phone']['id'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['field_phone']['field'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_phone']['click_sort_column'] = 'number';
  /* Field: Profile: FAI license number */
  $handler->display->display_options['fields']['field_fai_license_number']['id'] = 'field_fai_license_number';
  $handler->display->display_options['fields']['field_fai_license_number']['table'] = 'field_data_field_fai_license_number';
  $handler->display->display_options['fields']['field_fai_license_number']['field'] = 'field_fai_license_number';
  $handler->display->display_options['fields']['field_fai_license_number']['relationship'] = 'profile_1';
  /* Field: Profile: CIVL ID */
  $handler->display->display_options['fields']['field_civl_id']['id'] = 'field_civl_id';
  $handler->display->display_options['fields']['field_civl_id']['table'] = 'field_data_field_civl_id';
  $handler->display->display_options['fields']['field_civl_id']['field'] = 'field_civl_id';
  $handler->display->display_options['fields']['field_civl_id']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_civl_id']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Profile: T-shirt size */
  $handler->display->display_options['fields']['field_t_shirt_size']['id'] = 'field_t_shirt_size';
  $handler->display->display_options['fields']['field_t_shirt_size']['table'] = 'field_data_field_t_shirt_size';
  $handler->display->display_options['fields']['field_t_shirt_size']['field'] = 'field_t_shirt_size';
  $handler->display->display_options['fields']['field_t_shirt_size']['relationship'] = 'profile_1';
  /* Field: Field: Paraglider manufacturer */
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['id'] = 'field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['table'] = 'field_data_field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['field'] = 'field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['relationship'] = 'og_membership_rel';
  /* Field: Field: Paraglider model */
  $handler->display->display_options['fields']['field_paraglider_model']['id'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['table'] = 'field_data_field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['field'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_paraglider_model']['label'] = 'Glider';
  /* Field: Field: Paraglider color */
  $handler->display->display_options['fields']['field_paraglider_color']['id'] = 'field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['table'] = 'field_data_field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['field'] = 'field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['relationship'] = 'og_membership_rel';
  /* Field: Profile: Sponsors */
  $handler->display->display_options['fields']['field_sponsors']['id'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['table'] = 'field_data_field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['field'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_sponsors']['label'] = 'Sponsor';
  /* Field: Profile: Insurance company */
  $handler->display->display_options['fields']['field_insurance_company']['id'] = 'field_insurance_company';
  $handler->display->display_options['fields']['field_insurance_company']['table'] = 'field_data_field_insurance_company';
  $handler->display->display_options['fields']['field_insurance_company']['field'] = 'field_insurance_company';
  $handler->display->display_options['fields']['field_insurance_company']['relationship'] = 'profile_1';
  /* Field: Profile: Insurance policy number */
  $handler->display->display_options['fields']['field_insurance_policy_number']['id'] = 'field_insurance_policy_number';
  $handler->display->display_options['fields']['field_insurance_policy_number']['table'] = 'field_data_field_insurance_policy_number';
  $handler->display->display_options['fields']['field_insurance_policy_number']['field'] = 'field_insurance_policy_number';
  $handler->display->display_options['fields']['field_insurance_policy_number']['relationship'] = 'profile_1';
  /* Field: Profile: Your full name in national alphabet */
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['id'] = 'field_name_in_national_alphabet';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['table'] = 'field_data_field_name_in_national_alphabet';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['field'] = 'field_name_in_national_alphabet';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['label'] = 'Name in national alphabet';
  /* Field: Profile: Person to contact in case of emergency */
  $handler->display->display_options['fields']['field_person_name']['id'] = 'field_person_name';
  $handler->display->display_options['fields']['field_person_name']['table'] = 'field_data_field_person_name';
  $handler->display->display_options['fields']['field_person_name']['field'] = 'field_person_name';
  $handler->display->display_options['fields']['field_person_name']['relationship'] = 'profile_1';
  /* Field: Profile: Contact phone number in case of emergency */
  $handler->display->display_options['fields']['field_person_phone']['id'] = 'field_person_phone';
  $handler->display->display_options['fields']['field_person_phone']['table'] = 'field_data_field_person_phone';
  $handler->display->display_options['fields']['field_person_phone']['field'] = 'field_person_phone';
  $handler->display->display_options['fields']['field_person_phone']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_person_phone']['click_sort_column'] = 'number';
  /* Field: Profile: Blood type */
  $handler->display->display_options['fields']['field_blood_type']['id'] = 'field_blood_type';
  $handler->display->display_options['fields']['field_blood_type']['table'] = 'field_data_field_blood_type';
  $handler->display->display_options['fields']['field_blood_type']['field'] = 'field_blood_type';
  $handler->display->display_options['fields']['field_blood_type']['relationship'] = 'profile_1';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status']['type'] = 'i18n_list_default';
  /* Field: Field: Link to Tracker */
  $handler->display->display_options['fields']['field_tracker']['id'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['table'] = 'field_data_field_tracker';
  $handler->display->display_options['fields']['field_tracker']['field'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_tracker']['label'] = 'Tracker';
  $handler->display->display_options['fields']['field_tracker']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tracker']['alter']['text'] = '[field_tracker-target_id]';
  $handler->display->display_options['fields']['field_tracker']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Profile: Gender (field_gender) */
  $handler->display->display_options['sorts']['field_gender_value']['id'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['table'] = 'field_data_field_gender';
  $handler->display->display_options['sorts']['field_gender_value']['field'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['relationship'] = 'profile';
  $handler->display->display_options['sorts']['field_gender_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'og_membership';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';
  $handler->display->display_options['pane_title'] = 'Standard event pilots';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );

  /* Display: Manage */
  $handler = $view->new_display('panel_pane', 'Manage', 'manage');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_gender',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_contestant_number' => 'field_contestant_number',
    'field_gender' => 'field_gender',
    'counter' => 'counter',
    'field_full_name' => 'field_full_name',
    'field_address' => 'field_address',
    'field_sponsors' => 'field_sponsors',
    'field_paraglider_model' => 'field_paraglider_model',
    'field_pg_contestant_status' => 'field_pg_contestant_status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_contestant_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gender' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_full_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_address' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sponsors' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_paraglider_model' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_pg_contestant_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Gender (excluded) */
  $handler->display->display_options['fields']['field_gender']['id'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['table'] = 'field_data_field_gender';
  $handler->display->display_options['fields']['field_gender']['field'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_gender']['ui_name'] = 'Gender (excluded)';
  $handler->display->display_options['fields']['field_gender']['label'] = '';
  $handler->display->display_options['fields']['field_gender']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gender']['element_label_colon'] = FALSE;
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name]';
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Pilot`s number */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot`s number';
  $handler->display->display_options['fields']['field_contestant_number']['label'] = '';
  $handler->display->display_options['fields']['field_contestant_number']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_contestant_number']['type'] = 'editable';
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'click_to_edit' => 0,
    'empty_text' => '',
    'fallback_format' => 'number_integer',
    'fallback_settings' => array(
      'thousand_separator' => ' ',
      'prefix_suffix' => 1,
    ),
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address']['label'] = 'Country';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['text'] = '[field_address-country]';
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(),
  );
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status']['alter']['text'] = '<span class="status-value">[field_pg_contestant_status]</span>';
  $handler->display->display_options['fields']['field_pg_contestant_status']['element_class'] = 'status-[field_pg_contestant_status_1]';
  $handler->display->display_options['fields']['field_pg_contestant_status']['type'] = 'editable';
  $handler->display->display_options['fields']['field_pg_contestant_status']['settings'] = array(
    'click_to_edit' => 0,
    'empty_text' => '',
    'fallback_format' => 'list_default',
  );
  /* Field: Field: Link to Tracker */
  $handler->display->display_options['fields']['field_tracker']['id'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['table'] = 'field_data_field_tracker';
  $handler->display->display_options['fields']['field_tracker']['field'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_tracker']['label'] = 'Tracker';
  $handler->display->display_options['fields']['field_tracker']['type'] = 'editable';
  $handler->display->display_options['fields']['field_tracker']['settings'] = array(
    'click_to_edit' => 1,
    'empty_text' => '',
    'fallback_format' => 'entityreference_label',
    'fallback_settings' => array(
      'link' => 0,
    ),
  );
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Profile: Gender (field_gender) */
  $handler->display->display_options['sorts']['field_gender_value']['id'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['table'] = 'field_data_field_gender';
  $handler->display->display_options['sorts']['field_gender_value']['field'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['relationship'] = 'profile';
  $handler->display->display_options['sorts']['field_gender_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'og_membership';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';
  $handler->display->display_options['pane_title'] = 'Manage event pilots';
  $handler->display->display_options['allow']['use_pager'] = 0;
  $handler->display->display_options['allow']['items_per_page'] = 0;
  $handler->display->display_options['allow']['offset'] = 0;
  $handler->display->display_options['allow']['link_to_view'] = 0;
  $handler->display->display_options['allow']['more_link'] = 0;
  $handler->display->display_options['allow']['path_override'] = 0;
  $handler->display->display_options['allow']['title_override'] = 'title_override';
  $handler->display->display_options['allow']['exposed_form'] = 0;
  $handler->display->display_options['allow']['fields_override'] = 0;
  $handler->display->display_options['argument_input'] = array(
    'gid' => array(
      'type' => 'context',
      'context' => 'entity:node.nid',
      'context_optional' => 0,
      'panel' => '0',
      'fixed' => '',
      'label' => 'OG membership: Group ID',
    ),
  );
  $translatables['paragliding_pilots_list'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from user'),
    t('MainProfile'),
    t('PilotProfile'),
    t('Paraglider color'),
    t('Paraglider manufacturer'),
    t('Paraglider model'),
    t('Payment status'),
    t('Name'),
    t('Gender'),
    t('Address'),
    t('[field_address-country]'),
    t('Link to Tracker'),
    t('All'),
    t('%1 members'),
    t('Standard'),
    t('[field_full_name] ([field_contestant_number])'),
    t('Country'),
    t('Sponsor'),
    t('<span class="status-value">[field_pg_contestant_status]</span>'),
    t('Glider'),
    t('Standard event pilots'),
    t('View panes'),
    t('FAI'),
    t('<span class="gender-[field_gender-value]"></span>'),
    t('[field_full_name] ([field_contestant_number])[field_gender]'),
    t('FAI event pilots'),
    t('Pilot Export'),
    t('Entity id'),
    t('.'),
    t('E-mail'),
    t('Pilot\'s number'),
    t('Date of birth'),
    t('Nation'),
    t('City'),
    t('[field_address_1-locality]'),
    t('[field_address_2-thoroughfare]'),
    t('Mobile phone number'),
    t('FAI license number'),
    t('CIVL ID'),
    t('T-shirt size'),
    t('Insurance company'),
    t('Insurance policy number'),
    t('Name in national alphabet'),
    t('Person to contact in case of emergency'),
    t('Contact phone number in case of emergency'),
    t('Blood type'),
    t('Tracker'),
    t('[field_tracker-target_id]'),
    t('Manage'),
    t('[field_full_name]'),
    t('Manage event pilots'),
  );
  $export['paragliding_pilots_list'] = $view;

  $view = new view();
  $view->name = 'paragliding_pilots_list_export';
  $view->description = '';
  $view->tag = 'airtribune';
  $view->base_table = 'users';
  $view->human_name = 'Paragliding contest pilots export';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    7 => '7',
    5 => '5',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['label'] = 'MainProfile';
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'main' => 'main',
  );
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile_1']['id'] = 'profile_1';
  $handler->display->display_options['relationships']['profile_1']['table'] = 'users';
  $handler->display->display_options['relationships']['profile_1']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile_1']['label'] = 'PilotProfile';
  $handler->display->display_options['relationships']['profile_1']['bundle_types'] = array(
    'pilot' => 'pilot',
  );
  /* Field: OG membership: Entity id */
  $handler->display->display_options['fields']['etid']['id'] = 'etid';
  $handler->display->display_options['fields']['etid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['etid']['field'] = 'etid';
  $handler->display->display_options['fields']['etid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['etid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['etid']['separator'] = '';
  /* Field: Profile: Name */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name] ([field_contestant_number])';
  $handler->display->display_options['fields']['field_full_name']['click_sort_column'] = 'title';
  $handler->display->display_options['fields']['field_full_name']['settings'] = array(
    'format' => 'default',
    'markup' => 0,
    'output' => 'default',
    'multiple' => 'default',
    'multiple_delimiter' => ', ',
    'multiple_and' => 'text',
    'multiple_delimiter_precedes_last' => 'never',
    'multiple_el_al_min' => '3',
    'multiple_el_al_first' => '1',
  );
  /* Field: Gender */
  $handler->display->display_options['fields']['field_gender']['id'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['table'] = 'field_data_field_gender';
  $handler->display->display_options['fields']['field_gender']['field'] = 'field_gender';
  $handler->display->display_options['fields']['field_gender']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_gender']['ui_name'] = 'Gender';
  /* Field: User: E-mail */
  $handler->display->display_options['fields']['mail']['id'] = 'mail';
  $handler->display->display_options['fields']['mail']['table'] = 'users';
  $handler->display->display_options['fields']['mail']['field'] = 'mail';
  $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
  /* Field: Pilot`s number */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot`s number';
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Profile: Date of birth */
  $handler->display->display_options['fields']['field_birthdate']['id'] = 'field_birthdate';
  $handler->display->display_options['fields']['field_birthdate']['table'] = 'field_data_field_birthdate';
  $handler->display->display_options['fields']['field_birthdate']['field'] = 'field_birthdate';
  $handler->display->display_options['fields']['field_birthdate']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_birthdate']['settings'] = array(
    'format_type' => 'dmy_dot',
    'fromto' => '',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address']['id'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address']['label'] = 'Nation';
  $handler->display->display_options['fields']['field_address']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address']['alter']['text'] = '[field_address-country]';
  $handler->display->display_options['fields']['field_address']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(),
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address_1']['id'] = 'field_address_1';
  $handler->display->display_options['fields']['field_address_1']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address_1']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address_1']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address_1']['label'] = 'City';
  $handler->display->display_options['fields']['field_address_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address_1']['alter']['text'] = '[field_address_1-locality]';
  $handler->display->display_options['fields']['field_address_1']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address_1']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Field: Address */
  $handler->display->display_options['fields']['field_address_2']['id'] = 'field_address_2';
  $handler->display->display_options['fields']['field_address_2']['table'] = 'field_data_field_address';
  $handler->display->display_options['fields']['field_address_2']['field'] = 'field_address';
  $handler->display->display_options['fields']['field_address_2']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_address_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_address_2']['alter']['text'] = '[field_address_2-thoroughfare]';
  $handler->display->display_options['fields']['field_address_2']['click_sort_column'] = 'country';
  $handler->display->display_options['fields']['field_address_2']['settings'] = array(
    'use_widget_handlers' => 1,
    'format_handlers' => array(
      'address' => 'address',
    ),
  );
  /* Field: Field: Mobile phone number */
  $handler->display->display_options['fields']['field_phone']['id'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['field_phone']['field'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_phone']['click_sort_column'] = 'number';
  /* Field: Profile: FAI license number */
  $handler->display->display_options['fields']['field_fai_license_number']['id'] = 'field_fai_license_number';
  $handler->display->display_options['fields']['field_fai_license_number']['table'] = 'field_data_field_fai_license_number';
  $handler->display->display_options['fields']['field_fai_license_number']['field'] = 'field_fai_license_number';
  $handler->display->display_options['fields']['field_fai_license_number']['relationship'] = 'profile_1';
  /* Field: Profile: CIVL ID */
  $handler->display->display_options['fields']['field_civl_id']['id'] = 'field_civl_id';
  $handler->display->display_options['fields']['field_civl_id']['table'] = 'field_data_field_civl_id';
  $handler->display->display_options['fields']['field_civl_id']['field'] = 'field_civl_id';
  $handler->display->display_options['fields']['field_civl_id']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_civl_id']['settings'] = array(
    'thousand_separator' => '',
    'prefix_suffix' => 1,
  );
  /* Field: Profile: T-shirt size */
  $handler->display->display_options['fields']['field_t_shirt_size']['id'] = 'field_t_shirt_size';
  $handler->display->display_options['fields']['field_t_shirt_size']['table'] = 'field_data_field_t_shirt_size';
  $handler->display->display_options['fields']['field_t_shirt_size']['field'] = 'field_t_shirt_size';
  $handler->display->display_options['fields']['field_t_shirt_size']['relationship'] = 'profile_1';
  /* Field: Field: Paraglider manufacturer */
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['id'] = 'field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['table'] = 'field_data_field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['field'] = 'field_paraglider_manufacturer';
  $handler->display->display_options['fields']['field_paraglider_manufacturer']['relationship'] = 'og_membership_rel';
  /* Field: Field: Paraglider model */
  $handler->display->display_options['fields']['field_paraglider_model']['id'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['table'] = 'field_data_field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['field'] = 'field_paraglider_model';
  $handler->display->display_options['fields']['field_paraglider_model']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_paraglider_model']['label'] = 'Glider';
  /* Field: Field: Paraglider color */
  $handler->display->display_options['fields']['field_paraglider_color']['id'] = 'field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['table'] = 'field_data_field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['field'] = 'field_paraglider_color';
  $handler->display->display_options['fields']['field_paraglider_color']['relationship'] = 'og_membership_rel';
  /* Field: Profile: Sponsors */
  $handler->display->display_options['fields']['field_sponsors']['id'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['table'] = 'field_data_field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['field'] = 'field_sponsors';
  $handler->display->display_options['fields']['field_sponsors']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_sponsors']['label'] = 'Sponsor';
  /* Field: Profile: Insurance company */
  $handler->display->display_options['fields']['field_insurance_company']['id'] = 'field_insurance_company';
  $handler->display->display_options['fields']['field_insurance_company']['table'] = 'field_data_field_insurance_company';
  $handler->display->display_options['fields']['field_insurance_company']['field'] = 'field_insurance_company';
  $handler->display->display_options['fields']['field_insurance_company']['relationship'] = 'profile_1';
  /* Field: Profile: Insurance policy number */
  $handler->display->display_options['fields']['field_insurance_policy_number']['id'] = 'field_insurance_policy_number';
  $handler->display->display_options['fields']['field_insurance_policy_number']['table'] = 'field_data_field_insurance_policy_number';
  $handler->display->display_options['fields']['field_insurance_policy_number']['field'] = 'field_insurance_policy_number';
  $handler->display->display_options['fields']['field_insurance_policy_number']['relationship'] = 'profile_1';
  /* Field: Profile: Your full name in national alphabet */
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['id'] = 'field_name_in_national_alphabet';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['table'] = 'field_data_field_name_in_national_alphabet';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['field'] = 'field_name_in_national_alphabet';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_name_in_national_alphabet']['label'] = 'Name in national alphabet';
  /* Field: Profile: Person to contact in case of emergency */
  $handler->display->display_options['fields']['field_person_name']['id'] = 'field_person_name';
  $handler->display->display_options['fields']['field_person_name']['table'] = 'field_data_field_person_name';
  $handler->display->display_options['fields']['field_person_name']['field'] = 'field_person_name';
  $handler->display->display_options['fields']['field_person_name']['relationship'] = 'profile_1';
  /* Field: Profile: Contact phone number in case of emergency */
  $handler->display->display_options['fields']['field_person_phone']['id'] = 'field_person_phone';
  $handler->display->display_options['fields']['field_person_phone']['table'] = 'field_data_field_person_phone';
  $handler->display->display_options['fields']['field_person_phone']['field'] = 'field_person_phone';
  $handler->display->display_options['fields']['field_person_phone']['relationship'] = 'profile_1';
  $handler->display->display_options['fields']['field_person_phone']['click_sort_column'] = 'number';
  /* Field: Profile: Blood type */
  $handler->display->display_options['fields']['field_blood_type']['id'] = 'field_blood_type';
  $handler->display->display_options['fields']['field_blood_type']['table'] = 'field_data_field_blood_type';
  $handler->display->display_options['fields']['field_blood_type']['field'] = 'field_blood_type';
  $handler->display->display_options['fields']['field_blood_type']['relationship'] = 'profile_1';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_pg_contestant_status']['type'] = 'i18n_list_default';
  /* Field: Field: Link to Tracker */
  $handler->display->display_options['fields']['field_tracker']['id'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['table'] = 'field_data_field_tracker';
  $handler->display->display_options['fields']['field_tracker']['field'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_tracker']['label'] = 'Tracker';
  $handler->display->display_options['fields']['field_tracker']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_tracker']['alter']['text'] = '[field_tracker-target_id]';
  $handler->display->display_options['fields']['field_tracker']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Profile: Gender (field_gender) */
  $handler->display->display_options['sorts']['field_gender_value']['id'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['table'] = 'field_data_field_gender';
  $handler->display->display_options['sorts']['field_gender_value']['field'] = 'field_gender_value';
  $handler->display->display_options['sorts']['field_gender_value']['relationship'] = 'profile';
  $handler->display->display_options['sorts']['field_gender_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['order'] = 'DESC';
  /* Sort criterion: OG membership: Created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'og_membership';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['relationship'] = 'og_membership_rel';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = '%1 members';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  /* Filter criterion: OG membership: State */
  $handler->display->display_options['filters']['state']['id'] = 'state';
  $handler->display->display_options['filters']['state']['table'] = 'og_membership';
  $handler->display->display_options['filters']['state']['field'] = 'state';
  $handler->display->display_options['filters']['state']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['state']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Pilots number */
  $handler->display->display_options['filters']['field_contestant_number_value']['id'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['filters']['field_contestant_number_value']['field'] = 'field_contestant_number_value';
  $handler->display->display_options['filters']['field_contestant_number_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_contestant_number_value']['ui_name'] = 'Pilots number';
  $handler->display->display_options['filters']['field_contestant_number_value']['operator'] = 'not empty';

  /* Display: All pilots export (csv) */
  $handler = $view->new_display('views_data_export', 'All pilots export (csv)', 'export_pilots_all_csv');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '9999';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'export_pilots/%';

  /* Display: Pilot export */
  $handler = $view->new_display('page', 'Pilot export', 'export_pilots_one_page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = '%1 members';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['path'] = 'export_pilot/%/%';
  $translatables['paragliding_pilots_list_export'] = array(
    t('Defaults'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from user'),
    t('MainProfile'),
    t('PilotProfile'),
    t('Entity id'),
    t('.'),
    t('Name'),
    t('[field_full_name] ([field_contestant_number])'),
    t('Gender'),
    t('E-mail'),
    t('Pilot\'s number'),
    t('Date of birth'),
    t('Nation'),
    t('[field_address-country]'),
    t('City'),
    t('[field_address_1-locality]'),
    t('Address'),
    t('[field_address_2-thoroughfare]'),
    t('Mobile phone number'),
    t('FAI license number'),
    t('CIVL ID'),
    t('T-shirt size'),
    t('Paraglider manufacturer'),
    t('Glider'),
    t('Paraglider color'),
    t('Sponsor'),
    t('Insurance company'),
    t('Insurance policy number'),
    t('Name in national alphabet'),
    t('Person to contact in case of emergency'),
    t('Contact phone number in case of emergency'),
    t('Blood type'),
    t('Payment status'),
    t('Tracker'),
    t('[field_tracker-target_id]'),
    t('All'),
    t('%1 members'),
    t('All pilots export (csv)'),
    t('Pilot export'),
  );
  $export['paragliding_pilots_list_export'] = $view;

  $view = new view();
  $view->name = 'photos_carousel';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Photos carousel';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'jcarousel';
  $handler->display->display_options['style_options']['wrap'] = 'circular';
  $handler->display->display_options['style_options']['visible'] = '1';
  $handler->display->display_options['style_options']['auto'] = '0';
  $handler->display->display_options['style_options']['autoPause'] = 1;
  $handler->display->display_options['style_options']['start'] = '2';
  $handler->display->display_options['style_options']['easing'] = '';
  $handler->display->display_options['style_options']['vertical'] = 0;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Photo */
  $handler->display->display_options['fields']['field_photo']['id'] = 'field_photo';
  $handler->display->display_options['fields']['field_photo']['table'] = 'field_data_field_photo';
  $handler->display->display_options['fields']['field_photo']['field'] = 'field_photo';
  $handler->display->display_options['fields']['field_photo']['label'] = '';
  $handler->display->display_options['fields']['field_photo']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_photo']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_photo']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_photo']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_photo']['settings'] = array(
    'colorbox_node_style' => 'hotel_preview',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_photo']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_photo']['delta_offset'] = '0';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Content pane */
  $handler = $view->new_display('panel_pane', 'Content pane', 'accommodation');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['argument_input'] = array(
    'nid' => array(
      'type' => 'panel',
      'context' => 'entity:node.members--1',
      'context_optional' => 0,
      'panel' => '1',
      'fixed' => '',
      'label' => 'Content: Nid',
    ),
  );
  $translatables['photos_carousel'] = array(
    t('Master'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('All'),
    t('Content pane'),
    t('View panes'),
  );
  $export['photos_carousel'] = $view;

  return $export;
}
