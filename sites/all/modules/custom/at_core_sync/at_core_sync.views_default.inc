<?php
/**
 * @file
 * at_core_sync.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function at_core_sync_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'accommodations';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'node';
  $view->human_name = 'Manage accommodations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Accommodations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'title' => 'title',
    'status' => 'status',
    'field_price_single' => 'field_price_single',
    'field_price_double' => 'field_price_double',
    'field_price_currency' => 'field_price_currency',
    'field_hotel_wifi' => 'field_hotel_wifi',
    'field_email' => 'field_email',
    'changed' => 'changed',
    'edit_node' => 'edit_node',
    'delete_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_price_single' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_price_double' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_price_currency' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_hotel_wifi' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_email' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 1,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/node/add/accommodation?destination=admin/config/administration/at_manage/accommodation">Add accommodation</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Footer: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['footer']['result']['ui_name'] = 'Result summary';
  /* No results behavior: No accommodations */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['ui_name'] = 'No accommodations';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Sorry, no accommodations were found to display.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Field: Node ID */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['ui_name'] = 'Node ID';
  $handler->display->display_options['fields']['nid']['label'] = 'ID';
  /* Field: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['ui_name'] = 'Title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['ui_name'] = 'Published';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Single price */
  $handler->display->display_options['fields']['field_price_single']['id'] = 'field_price_single';
  $handler->display->display_options['fields']['field_price_single']['table'] = 'field_data_field_price_single';
  $handler->display->display_options['fields']['field_price_single']['field'] = 'field_price_single';
  $handler->display->display_options['fields']['field_price_single']['ui_name'] = 'Single price';
  $handler->display->display_options['fields']['field_price_single']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Double price */
  $handler->display->display_options['fields']['field_price_double']['id'] = 'field_price_double';
  $handler->display->display_options['fields']['field_price_double']['table'] = 'field_data_field_price_double';
  $handler->display->display_options['fields']['field_price_double']['field'] = 'field_price_double';
  $handler->display->display_options['fields']['field_price_double']['ui_name'] = 'Double price';
  $handler->display->display_options['fields']['field_price_double']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Currency */
  $handler->display->display_options['fields']['field_price_currency']['id'] = 'field_price_currency';
  $handler->display->display_options['fields']['field_price_currency']['table'] = 'field_data_field_price_currency';
  $handler->display->display_options['fields']['field_price_currency']['field'] = 'field_price_currency';
  $handler->display->display_options['fields']['field_price_currency']['ui_name'] = 'Currency';
  /* Field: Wi-Fi */
  $handler->display->display_options['fields']['field_hotel_wifi']['id'] = 'field_hotel_wifi';
  $handler->display->display_options['fields']['field_hotel_wifi']['table'] = 'field_data_field_hotel_wifi';
  $handler->display->display_options['fields']['field_hotel_wifi']['field'] = 'field_hotel_wifi';
  $handler->display->display_options['fields']['field_hotel_wifi']['ui_name'] = 'Wi-Fi';
  /* Field: Email */
  $handler->display->display_options['fields']['field_email']['id'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['table'] = 'field_data_field_email';
  $handler->display->display_options['fields']['field_email']['field'] = 'field_email';
  $handler->display->display_options['fields']['field_email']['ui_name'] = 'Email';
  /* Field: Updated */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['ui_name'] = 'Updated';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'dmy';
  /* Field: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['ui_name'] = 'Edit link';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  /* Field: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['ui_name'] = 'Delete link';
  $handler->display->display_options['fields']['delete_node']['label'] = '';
  $handler->display->display_options['fields']['delete_node']['element_label_colon'] = FALSE;
  /* Filter criterion: Node type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['ui_name'] = 'Node type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'accommodation' => 'accommodation',
  );
  /* Filter criterion: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['ui_name'] = 'Title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Search by title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/accommodation';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Accommodations';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['accommodations'] = array(
    t('Master'),
    t('Accommodations'),
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
    t('<ul class="action-links"><li><a href="/node/add/accommodation?destination=admin/config/administration/at_manage/accommodation">Add accommodation</a></li></ul>'),
    t('Displaying @start - @end of @total'),
    t('Sorry, no accommodations were found to display.'),
    t('ID'),
    t('Title'),
    t('Published'),
    t('Single'),
    t('Double'),
    t('Currency'),
    t('Wi-Fi'),
    t('Email'),
    t('Updated'),
    t('Operations'),
    t('Search by title'),
    t('Page'),
  );
  $export['accommodations'] = $view;

  $view = new view();
  $view->name = 'core_api_manage';
  $view->description = 'Main page';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'node';
  $view->human_name = 'Airtribune manage';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Airtribune manage';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Start date (exclude) */
  $handler->display->display_options['fields']['field_dates_1']['id'] = 'field_dates_1';
  $handler->display->display_options['fields']['field_dates_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates_1']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates_1']['ui_name'] = 'Start date (exclude)';
  $handler->display->display_options['fields']['field_dates_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates_1']['settings'] = array(
    'format_type' => 'dm',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: End date (exclude) */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['ui_name'] = 'End date (exclude)';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['click_sort_column'] = 'value2';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'dmy',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Published */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'node';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  $handler->display->display_options['fields']['status']['exclude'] = TRUE;
  $handler->display->display_options['fields']['status']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['status']['type'] = 'custom';
  $handler->display->display_options['fields']['status']['type_custom_false'] = ' [NOT PUBLISHED]';
  $handler->display->display_options['fields']['status']['not'] = 0;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_contests_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Contest';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title][status]';
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Contest';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '[title] ([field_dates_1] - [field_dates])';
  /* Field: Global: View */
  $handler->display->display_options['fields']['view_1']['id'] = 'view_1';
  $handler->display->display_options['fields']['view_1']['table'] = 'views';
  $handler->display->display_options['fields']['view_1']['field'] = 'view';
  $handler->display->display_options['fields']['view_1']['label'] = 'Contestants';
  $handler->display->display_options['fields']['view_1']['empty'] = '0 contestants';
  $handler->display->display_options['fields']['view_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['view_1']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['view_1']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['view_1']['view'] = 'core_api_manage_contestants';
  $handler->display->display_options['fields']['view_1']['display'] = 'manage_count_contestants_pane';
  $handler->display->display_options['fields']['view_1']['arguments'] = '[!nid]';
  /* Field: Global: View */
  $handler->display->display_options['fields']['view']['id'] = 'view';
  $handler->display->display_options['fields']['view']['table'] = 'views';
  $handler->display->display_options['fields']['view']['field'] = 'view';
  $handler->display->display_options['fields']['view']['label'] = 'Races';
  $handler->display->display_options['fields']['view']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['view']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['view']['view'] = 'core_api_manage_races';
  $handler->display->display_options['fields']['view']['display'] = 'manage_count_race_pane';
  $handler->display->display_options['fields']['view']['arguments'] = '[!nid]';
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['label'] = 'Core status';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<ul>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/day">Manage days</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/ad_vis">Manage ad for vis</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/scoring_category">Manage scoring categories</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/featured-headers">Manage headers</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/points">Manage points</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/custom_object">Manage tracked objects</a></li>
</ul>';
  /* Sort criterion: Content: Published */
  $handler->display->display_options['sorts']['status']['id'] = 'status';
  $handler->display->display_options['sorts']['status']['table'] = 'node';
  $handler->display->display_options['sorts']['status']['field'] = 'status';
  $handler->display->display_options['sorts']['status']['order'] = 'DESC';
  /* Sort criterion: Content: Dates -  start date (field_dates) */
  $handler->display->display_options['sorts']['field_dates_value']['id'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['table'] = 'field_data_field_dates';
  $handler->display->display_options['sorts']['field_dates_value']['field'] = 'field_dates_value';
  $handler->display->display_options['sorts']['field_dates_value']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'pg_contest' => 'pg_contest',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Contests';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Airtribune manage';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  /* Display: Manage contest */
  $handler = $view->new_display('page', 'Manage contest', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Manage contest';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Start date (exclude) */
  $handler->display->display_options['fields']['field_dates_1']['id'] = 'field_dates_1';
  $handler->display->display_options['fields']['field_dates_1']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates_1']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates_1']['ui_name'] = 'Start date (exclude)';
  $handler->display->display_options['fields']['field_dates_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates_1']['settings'] = array(
    'format_type' => 'dm',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: End date (exclude) */
  $handler->display->display_options['fields']['field_dates']['id'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['table'] = 'field_data_field_dates';
  $handler->display->display_options['fields']['field_dates']['field'] = 'field_dates';
  $handler->display->display_options['fields']['field_dates']['ui_name'] = 'End date (exclude)';
  $handler->display->display_options['fields']['field_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_dates']['click_sort_column'] = 'value2';
  $handler->display->display_options['fields']['field_dates']['settings'] = array(
    'format_type' => 'dmy',
    'fromto' => 'value2',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_contests_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Contest';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/edit';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Contest';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '[title] ([field_dates_1] - [field_dates])';
  /* Field: Content: Points file */
  $handler->display->display_options['fields']['field_points_file']['id'] = 'field_points_file';
  $handler->display->display_options['fields']['field_points_file']['table'] = 'field_data_field_points_file';
  $handler->display->display_options['fields']['field_points_file']['field'] = 'field_points_file';
  $handler->display->display_options['fields']['field_points_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_points_file']['type'] = 'editable';
  $handler->display->display_options['fields']['field_points_file']['settings'] = array(
    'click_to_edit' => 0,
    'empty_text' => '',
    'fallback_format' => 'file_default',
  );
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['type'] = 'editable';
  $handler->display->display_options['fields']['field_core_id']['settings'] = array(
    'click_to_edit' => 0,
    'empty_text' => '',
    'fallback_format' => 'text_default',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['title'] = 'Manage %1';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/manage';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage contest';
  $handler->display->display_options['menu']['weight'] = '-100';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['core_api_manage'] = array(
    t('Master'),
    t('Airtribune manage'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Dates'),
    t('Published'),
    t(' [NOT PUBLISHED]'),
    t('Contest'),
    t('[title][status]'),
    t('[title] ([field_dates_1] - [field_dates])'),
    t('Contestants'),
    t('0 contestants'),
    t('Races'),
    t('Core status'),
    t('Operations'),
    t('<ul>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/day">Manage days</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/ad_vis">Manage ad for vis</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/scoring_category">Manage scoring categories</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/featured-headers">Manage headers</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/points">Manage points</a></li>
<li><a href="/admin/config/administration/at_manage/contest/[nid]/custom_object">Manage tracked objects</a></li>
</ul>'),
    t('Page'),
    t('Manage contest'),
    t('Points file'),
    t('Core ID'),
    t('All'),
    t('Manage %1'),
  );
  $export['core_api_manage'] = $view;

  $view = new view();
  $view->name = 'core_api_manage_ad_for_visualisations';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'eck_ent_advert';
  $view->human_name = 'Manage ad for visualisations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage ad for visualisations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'edit_link' => 'edit_link',
    'field_image' => 'field_image',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
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
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_advert/advert_visualisation/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/ad_vis">Add advert</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Relationship: OG membership: OG membership from Advertisement */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_advert';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Advertisement: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_advert';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Field: Advertisement: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_advert';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['alter']['text'] = '[title]';
  /* Field: Field: Banner */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_image']['delta_offset'] = '0';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Ad for visualisations of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
  /* Filter criterion: Advertisement: ent_advert type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_ent_advert';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'advert_visualisation' => 'advert_visualisation',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/ad_vis';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage ad for visualizations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['core_api_manage_ad_for_visualisations'] = array(
    t('Master'),
    t('Manage ad for visualisations'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_advert/advert_visualisation/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/ad_vis">Add advert</a></li></ul>'),
    t('OG membership from ent_advert'),
    t('Title'),
    t('Edit link'),
    t('[title]'),
    t('Banner'),
    t('All'),
    t('Ad for visualisations of %1'),
    t('Page'),
  );
  $export['core_api_manage_ad_for_visualisations'] = $view;

  $view = new view();
  $view->name = 'core_api_manage_contestants';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'users';
  $view->human_name = 'Manage contestants';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage contestants';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Relationship: OG membership: OG membership from User */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'users';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Relationship: User: Profile */
  $handler->display->display_options['relationships']['profile']['id'] = 'profile';
  $handler->display->display_options['relationships']['profile']['table'] = 'users';
  $handler->display->display_options['relationships']['profile']['field'] = 'profile';
  $handler->display->display_options['relationships']['profile']['required'] = TRUE;
  $handler->display->display_options['relationships']['profile']['bundle_types'] = array(
    'main' => 'main',
  );
  /* Field: Contest ID (excluded) */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['ui_name'] = 'Contest ID (excluded)';
  $handler->display->display_options['fields']['gid']['exclude'] = TRUE;
  /* Field: Pilot&#039;s number (Excluded) */
  $handler->display->display_options['fields']['field_contestant_number']['id'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['table'] = 'field_data_field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['field'] = 'field_contestant_number';
  $handler->display->display_options['fields']['field_contestant_number']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_contestant_number']['ui_name'] = 'Pilot\'s number (Excluded)';
  $handler->display->display_options['fields']['field_contestant_number']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_contestant_number']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Name (excluded) */
  $handler->display->display_options['fields']['field_full_name']['id'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['table'] = 'field_data_field_full_name';
  $handler->display->display_options['fields']['field_full_name']['field'] = 'field_full_name';
  $handler->display->display_options['fields']['field_full_name']['relationship'] = 'profile';
  $handler->display->display_options['fields']['field_full_name']['ui_name'] = 'Name (excluded)';
  $handler->display->display_options['fields']['field_full_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_full_name']['alter']['text'] = '[field_full_name] ([field_contestant_number])';
  $handler->display->display_options['fields']['field_full_name']['alter']['path'] = '[edit_og_membership] ';
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
  /* Field: Bulk operations: OG membership */
  $handler->display->display_options['fields']['views_bulk_operations_1']['id'] = 'views_bulk_operations_1';
  $handler->display->display_options['fields']['views_bulk_operations_1']['table'] = 'og_membership';
  $handler->display->display_options['fields']['views_bulk_operations_1']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations_1']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['views_bulk_operations_1']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations_1']['vbo_operations'] = array(
    'action::at_core_sync_contestants_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::og_set_state_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::og_user_roles_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::og_membership_delete_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Contestant edit link (excluded) */
  $handler->display->display_options['fields']['edit_og_membership']['id'] = 'edit_og_membership';
  $handler->display->display_options['fields']['edit_og_membership']['table'] = 'views_entity_og_membership';
  $handler->display->display_options['fields']['edit_og_membership']['field'] = 'edit_og_membership';
  $handler->display->display_options['fields']['edit_og_membership']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['edit_og_membership']['ui_name'] = 'Contestant edit link (excluded)';
  $handler->display->display_options['fields']['edit_og_membership']['label'] = 'Contestant name';
  $handler->display->display_options['fields']['edit_og_membership']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_og_membership']['alter']['text'] = '[field_full_name] ';
  /* Field: OG membership: Payment status */
  $handler->display->display_options['fields']['field_pg_contestant_status']['id'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['field'] = 'field_pg_contestant_status';
  $handler->display->display_options['fields']['field_pg_contestant_status']['relationship'] = 'og_membership_rel';
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['label'] = 'Core status';
  /* Field: Field: Mobile phone number */
  $handler->display->display_options['fields']['field_phone']['id'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['table'] = 'field_data_field_phone';
  $handler->display->display_options['fields']['field_phone']['field'] = 'field_phone';
  $handler->display->display_options['fields']['field_phone']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_phone']['label'] = 'Phone number';
  $handler->display->display_options['fields']['field_phone']['click_sort_column'] = 'number';
  $handler->display->display_options['fields']['field_phone']['type'] = 'editable';
  $handler->display->display_options['fields']['field_phone']['settings'] = array(
    'click_to_edit' => 0,
    'empty_text' => '',
    'fallback_format' => 'global_phone_number',
  );
  /* Sort criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['sorts']['field_pg_contestant_status_value']['order'] = 'DESC';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Contestants of %1';
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
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['value'] = array(
    1 => '1',
    2 => '2',
    3 => '3',
    4 => '4',
  );
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['operator_id'] = 'field_pg_contestant_status_value_op';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['label'] = 'Payment status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['operator'] = 'field_pg_contestant_status_value_op';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['identifier'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['label'] = 'Payment status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['identifier'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Confirmed',
      'operator' => 'or',
      'value' => array(
        4 => '4',
      ),
    ),
    2 => array(
      'title' => 'Not confirmed',
      'operator' => 'or',
      'value' => array(
        1 => '1',
        2 => '2',
        3 => '3',
      ),
    ),
  );

  /* Display: List of contestants (manage) */
  $handler = $view->new_display('page', 'List of contestants (manage)', 'manage_list_contestants_page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/contestants';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage contestants';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Contestants count (manage) */
  $handler = $view->new_display('panel_pane', 'Contestants count (manage)', 'manage_count_contestants_pane');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['footer']['result']['content'] = '@total';
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['content'] = '&nbsp;<a id="view-list-contestants-!1" class="action view contestants-list" data-nid="!1" href="/admin/config/administration/at_manage/contest/!1/contestants">contestants</a>';
  $handler->display->display_options['footer']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Uid */
  $handler->display->display_options['fields']['uid']['id'] = 'uid';
  $handler->display->display_options['fields']['uid']['table'] = 'users';
  $handler->display->display_options['fields']['uid']['field'] = 'uid';
  $handler->display->display_options['fields']['uid']['label'] = '';
  $handler->display->display_options['fields']['uid']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['uid']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['uid']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['uid']['link_to_user'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: OG membership: Payment status (field_pg_contestant_status) */
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['id'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['table'] = 'field_data_field_pg_contestant_status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['field'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['value'] = array(
    4 => '4',
  );
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['operator_id'] = 'field_pg_contestant_status_value_op';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['label'] = 'Payment status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['operator'] = 'field_pg_contestant_status_value_op';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['identifier'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    6 => 0,
    5 => 0,
    7 => 0,
  );
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['label'] = 'Payment status';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['identifier'] = 'field_pg_contestant_status_value';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['default_group'] = '1';
  $handler->display->display_options['filters']['field_pg_contestant_status_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Confirmed',
      'operator' => 'or',
      'value' => array(
        4 => '4',
      ),
    ),
    2 => array(
      'title' => 'Not confirmed',
      'operator' => 'or',
      'value' => array(
        1 => '1',
        2 => '2',
        3 => '3',
      ),
    ),
  );
  $translatables['core_api_manage_contestants'] = array(
    t('Master'),
    t('Manage contestants'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Displaying @start - @end of @total'),
    t('OG membership from user'),
    t('Profile'),
    t('Group ID'),
    t('.'),
    t(','),
    t('Pilot\'s number'),
    t('Name'),
    t('[field_full_name] ([field_contestant_number])'),
    t('Contestant name'),
    t('[field_full_name] '),
    t('Payment status'),
    t('Core status'),
    t('Phone number'),
    t('All'),
    t('Contestants of %1'),
    t('List of contestants (manage)'),
    t('Contestants count (manage)'),
    t('@total'),
    t('&nbsp;<a id="view-list-contestants-!1" class="action view contestants-list" data-nid="!1" href="/admin/config/administration/at_manage/contest/!1/contestants">contestants</a>'),
    t(' '),
    t('View panes'),
  );
  $export['core_api_manage_contestants'] = $view;

  $view = new view();
  $view->name = 'core_api_manage_races';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'eck_ent_race';
  $view->human_name = 'Manage races';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage races';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'field_core_id' => 'field_core_id',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_core_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: OG membership: OG membership from Race */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_race';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Race ID (excluded) */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['ui_name'] = 'Race ID (excluded)';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Bulk operations: Race */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_races_tracks_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::at_core_sync_races_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Race: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Race';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'admin/structure/entity-type/ent_race/pg_race/[id]/edit';
  /* Field: Race: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Race title';
  $handler->display->display_options['fields']['edit_link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['alter']['text'] = '[title]';
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['label'] = 'Core status';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Races of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'og';

  /* Display: List of races (manage) */
  $handler = $view->new_display('page', 'List of races (manage)', 'manage_list_race_page');
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_race/pg_race/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/races">Add Race</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Race ID (excluded) */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['ui_name'] = 'Race ID (excluded)';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Bulk operations: Race */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_races_tracks_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::at_core_sync_races_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Race: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Race';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'admin/structure/entity-type/ent_race/pg_race/[id]/edit';
  /* Field: Race: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Race title';
  $handler->display->display_options['fields']['edit_link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['alter']['text'] = '[title]';
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['label'] = 'Core status';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Race: Race time period -  start date (field_race_start_end) */
  $handler->display->display_options['sorts']['field_race_start_end_value']['id'] = 'field_race_start_end_value';
  $handler->display->display_options['sorts']['field_race_start_end_value']['table'] = 'field_data_field_race_start_end';
  $handler->display->display_options['sorts']['field_race_start_end_value']['field'] = 'field_race_start_end_value';
  $handler->display->display_options['sorts']['field_race_start_end_value']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/races';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage races';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Races count (manage) */
  $handler = $view->new_display('panel_pane', 'Races count (manage)', 'manage_count_race_pane');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['footer']['result']['empty'] = TRUE;
  $handler->display->display_options['footer']['result']['content'] = '@total';
  /* Footer: Global: Unfiltered text */
  $handler->display->display_options['footer']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['footer']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['footer']['area_text_custom']['content'] = '&nbsp;<a id="view-list-race-!1" class="action view race-list" data-nid="!1" href="/admin/config/administration/at_manage/contest/!1/races">races</a>';
  $handler->display->display_options['footer']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = '<a href="/admin/structure/entity-type/ent_race/pg_race/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/races">Add Race</a>';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['empty']['area']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Race ID (excluded) */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_race';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['ui_name'] = 'Race ID (excluded)';
  $handler->display->display_options['fields']['id']['label'] = '';
  $handler->display->display_options['fields']['id']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['id']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['id']['element_label_colon'] = FALSE;
  $translatables['core_api_manage_races'] = array(
    t('Master'),
    t('Manage races'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from ent_race'),
    t('Id'),
    t('.'),
    t(','),
    t('Race'),
    t('Race title'),
    t('[title]'),
    t('Core status'),
    t('All'),
    t('Races of %1'),
    t('List of races (manage)'),
    t('<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_race/pg_race/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/races">Add Race</a></li></ul>'),
    t('Races count (manage)'),
    t('@total'),
    t('&nbsp;<a id="view-list-race-!1" class="action view race-list" data-nid="!1" href="/admin/config/administration/at_manage/contest/!1/races">races</a>'),
    t('<a href="/admin/structure/entity-type/ent_race/pg_race/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/races">Add Race</a>'),
    t(' '),
    t('View panes'),
  );
  $export['core_api_manage_races'] = $view;

  $view = new view();
  $view->name = 'core_api_manage_trackers';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'eck_ent_tracker';
  $view->human_name = 'Manage trackers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage trackers';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'identifier' => 'identifier',
    'views_bulk_operations' => 'views_bulk_operations',
    'edit_link' => 'edit_link',
    'field_core_id' => 'field_core_id',
    'title' => 'title',
    'field_tracker_model' => 'field_tracker_model',
    'field_tracker_type' => 'field_tracker_type',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'identifier' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_core_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_tracker_model' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_tracker_type' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<script type="text/javascript" src="/sites/all/modules/custom/airtribune/js/trackers.js"></script>
<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_tracker/device/add?destination=admin/config/administration/at_manage/tracker">Add tracker</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'php_code';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Field: Tracker: Identifier */
  $handler->display->display_options['fields']['identifier']['id'] = 'identifier';
  $handler->display->display_options['fields']['identifier']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['fields']['identifier']['field'] = 'identifier';
  $handler->display->display_options['fields']['identifier']['exclude'] = TRUE;
  /* Field: Bulk operations: Tracker */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_trackers_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '#';
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* Field: Tracker: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Tracker';
  $handler->display->display_options['fields']['edit_link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['alter']['text'] = '[identifier]';
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['label'] = 'Core Status';
  /* Field: Tracker: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  /* Field: Field: Model */
  $handler->display->display_options['fields']['field_tracker_model']['id'] = 'field_tracker_model';
  $handler->display->display_options['fields']['field_tracker_model']['table'] = 'field_data_field_tracker_model';
  $handler->display->display_options['fields']['field_tracker_model']['field'] = 'field_tracker_model';
  $handler->display->display_options['fields']['field_tracker_model']['settings'] = array(
    'link' => 0,
  );
  /* Field: Tracker: Type */
  $handler->display->display_options['fields']['field_tracker_type']['id'] = 'field_tracker_type';
  $handler->display->display_options['fields']['field_tracker_type']['table'] = 'field_data_field_tracker_type';
  $handler->display->display_options['fields']['field_tracker_type']['field'] = 'field_tracker_type';
  $handler->display->display_options['fields']['field_tracker_type']['settings'] = array(
    'link' => 0,
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Status';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<span class="tracker-status" id="[field_core_id]">No data</span>';
  /* Sort criterion: Tracker: Identifier */
  $handler->display->display_options['sorts']['identifier']['id'] = 'identifier';
  $handler->display->display_options['sorts']['identifier']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['sorts']['identifier']['field'] = 'identifier';
  /* Filter criterion: Tracker: ent_tracker type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'eck_ent_tracker';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'device' => 'device',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/tracker';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Trackers';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';
  $translatables['core_api_manage_trackers'] = array(
    t('Master'),
    t('Manage trackers'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<script type="text/javascript" src="/sites/all/modules/custom/airtribune/js/trackers.js"></script>
<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_tracker/device/add?destination=admin/config/administration/at_manage/tracker">Add tracker</a></li></ul>'),
    t('Displaying @start - @end of @total'),
    t('Identifier'),
    t('#'),
    t('Tracker'),
    t('[identifier]'),
    t('Core Status'),
    t('Name'),
    t('Model'),
    t('Type'),
    t('Status'),
    t('<span class="tracker-status" id="[field_core_id]">No data</span>'),
    t('Page'),
  );
  $export['core_api_manage_trackers'] = $view;

  $view = new view();
  $view->name = 'day_admin';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'node';
  $view->human_name = 'Manage days';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'List of Days';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'group_group' => 'group_group',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'group_group' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/node/add/day?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/day">Add Day</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Days was not created.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Field: Group ID (excluded) */
  $handler->display->display_options['fields']['gid']['id'] = 'gid';
  $handler->display->display_options['fields']['gid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['gid']['field'] = 'gid';
  $handler->display->display_options['fields']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['gid']['ui_name'] = 'Group ID (excluded)';
  $handler->display->display_options['fields']['gid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['gid']['separator'] = '';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_contests_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
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
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Link to edit';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '[title]';
  /* Field: Content: Day status */
  $handler->display->display_options['fields']['field_day_status']['id'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['table'] = 'field_data_field_day_status';
  $handler->display->display_options['fields']['field_day_status']['field'] = 'field_day_status';
  $handler->display->display_options['fields']['field_day_status']['settings'] = array(
    'click_to_edit' => 0,
    'empty_text' => '',
    'fallback_format' => 'list_default',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<ul>
<li><a href="/admin/config/administration/at_manage/contest/[gid]/day/[nid]/blog">Manage blogs</a></li>
</ul>';
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
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Days of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
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
    'day' => 'day',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'manage_list_days_page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/day';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage days';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['day_admin'] = array(
    t('Master'),
    t('List of Days'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<ul class="action-links"><li><a href="/node/add/day?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/day">Add Day</a></li></ul>'),
    t('Days was not created.'),
    t('OG membership from node'),
    t('Group ID'),
    t('.'),
    t('Nid'),
    t('Content'),
    t('Link to edit'),
    t('[title]'),
    t('Day status'),
    t('Operations'),
    t('<ul>
<li><a href="/admin/config/administration/at_manage/contest/[gid]/day/[nid]/blog">Manage blogs</a></li>
</ul>'),
    t('All'),
    t('Days of %1'),
    t('Page'),
  );
  $export['day_admin'] = $view;

  $view = new view();
  $view->name = 'featured_headers';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'eck_ent_featured_header';
  $view->human_name = 'Featured headers';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'eck administer ent_featured_header ent_featured_header entities';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '25';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['columns'] = array(
    'id' => 'id',
    'title' => 'title',
    'field_header_slogan' => 'field_header_slogan',
    'field_header_image' => 'field_header_image',
    'field_header_author' => 'field_header_author',
    'edit_link' => 'edit_link',
    'delete_link' => 'edit_link',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_header_slogan' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_header_image' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_header_author' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'delete_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Add header link */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['ui_name'] = 'Add header link';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_featured_header/ent_featured_header/add?destination=admin/config/administration/at_manage/featured-headers">Add featured header</a></li>
<li><a href="/admin/structure/entity-type/ent_featured_header/service_header/add?destination=admin/config/administration/at_manage/featured-headers">Add service header</a></li></ul>

';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* No results behavior: Sorry, no any entries were found. */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['ui_name'] = 'Sorry, no any entries were found.';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'Sorry, no any entries were found.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: OG membership: OG membership from Featured header */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Featured header: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: Featured header: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Slogan */
  $handler->display->display_options['fields']['field_header_slogan']['id'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['table'] = 'field_data_field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['field'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['ui_name'] = 'Slogan';
  $handler->display->display_options['fields']['field_header_slogan']['element_label_colon'] = FALSE;
  /* Field: Image */
  $handler->display->display_options['fields']['field_header_image']['id'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['table'] = 'field_data_field_header_image';
  $handler->display->display_options['fields']['field_header_image']['field'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['ui_name'] = 'Image';
  $handler->display->display_options['fields']['field_header_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_header_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_header_image']['settings'] = array(
    'image_style' => 'header_thumbnail',
    'image_link' => 'file',
  );
  /* Field: Author link */
  $handler->display->display_options['fields']['field_header_author']['id'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['table'] = 'field_data_field_header_author';
  $handler->display->display_options['fields']['field_header_author']['field'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['ui_name'] = 'Author link';
  $handler->display->display_options['fields']['field_header_author']['label'] = 'Author';
  $handler->display->display_options['fields']['field_header_author']['element_label_colon'] = FALSE;
  /* Field: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['ui_name'] = 'Edit link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Operations';
  /* Field: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['ui_name'] = 'Delete link';
  $handler->display->display_options['fields']['delete_link']['label'] = '';
  $handler->display->display_options['fields']['delete_link']['element_label_colon'] = FALSE;
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Headers of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );

  /* Display: Contest headers (manage) */
  $handler = $view->new_display('page', 'Contest headers (manage)', 'admin_page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Add header link */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['ui_name'] = 'Add header link';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_featured_header/ent_featured_header/add?og_group_ref=!1&destination=admin/content/featured-headers">Add featured header</a></li></ul>';
  $handler->display->display_options['header']['area_text_custom']['tokenize'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Featured header: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: Featured header: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Slogan */
  $handler->display->display_options['fields']['field_header_slogan']['id'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['table'] = 'field_data_field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['field'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['ui_name'] = 'Slogan';
  $handler->display->display_options['fields']['field_header_slogan']['element_label_colon'] = FALSE;
  /* Field: Image */
  $handler->display->display_options['fields']['field_header_image']['id'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['table'] = 'field_data_field_header_image';
  $handler->display->display_options['fields']['field_header_image']['field'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['ui_name'] = 'Image';
  $handler->display->display_options['fields']['field_header_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_header_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_header_image']['settings'] = array(
    'image_style' => 'header_thumbnail',
    'image_link' => 'file',
  );
  /* Field: Featured header: Type */
  $handler->display->display_options['fields']['field_header_page']['id'] = 'field_header_page';
  $handler->display->display_options['fields']['field_header_page']['table'] = 'field_data_field_header_page';
  $handler->display->display_options['fields']['field_header_page']['field'] = 'field_header_page';
  /* Field: Author link */
  $handler->display->display_options['fields']['field_header_author']['id'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['table'] = 'field_data_field_header_author';
  $handler->display->display_options['fields']['field_header_author']['field'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['ui_name'] = 'Author link';
  $handler->display->display_options['fields']['field_header_author']['label'] = 'Author';
  $handler->display->display_options['fields']['field_header_author']['element_label_colon'] = FALSE;
  /* Field: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['ui_name'] = 'Edit link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Operations';
  /* Field: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['ui_name'] = 'Delete link';
  $handler->display->display_options['fields']['delete_link']['label'] = '';
  $handler->display->display_options['fields']['delete_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/featured-headers';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Headers';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Service headers (manage) */
  $handler = $view->new_display('page', 'Service headers (manage)', 'manage_service_headers');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Featured header: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  /* Field: Featured header: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Slogan */
  $handler->display->display_options['fields']['field_header_slogan']['id'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['table'] = 'field_data_field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['field'] = 'field_header_slogan';
  $handler->display->display_options['fields']['field_header_slogan']['ui_name'] = 'Slogan';
  $handler->display->display_options['fields']['field_header_slogan']['element_label_colon'] = FALSE;
  /* Field: Image */
  $handler->display->display_options['fields']['field_header_image']['id'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['table'] = 'field_data_field_header_image';
  $handler->display->display_options['fields']['field_header_image']['field'] = 'field_header_image';
  $handler->display->display_options['fields']['field_header_image']['ui_name'] = 'Image';
  $handler->display->display_options['fields']['field_header_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_header_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_header_image']['settings'] = array(
    'image_style' => 'header_thumbnail',
    'image_link' => 'file',
  );
  /* Field: Author link */
  $handler->display->display_options['fields']['field_header_author']['id'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['table'] = 'field_data_field_header_author';
  $handler->display->display_options['fields']['field_header_author']['field'] = 'field_header_author';
  $handler->display->display_options['fields']['field_header_author']['ui_name'] = 'Author link';
  $handler->display->display_options['fields']['field_header_author']['label'] = 'Author';
  $handler->display->display_options['fields']['field_header_author']['element_label_colon'] = FALSE;
  /* Field: Featured header: Target */
  $handler->display->display_options['fields']['field_target']['id'] = 'field_target';
  $handler->display->display_options['fields']['field_target']['table'] = 'field_data_field_target';
  $handler->display->display_options['fields']['field_target']['field'] = 'field_target';
  $handler->display->display_options['fields']['field_target']['label'] = 'For page';
  $handler->display->display_options['fields']['field_target']['empty'] = 'Frontpage';
  /* Field: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['ui_name'] = 'Edit link';
  $handler->display->display_options['fields']['edit_link']['label'] = 'Operations';
  /* Field: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ent_featured_header';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['ui_name'] = 'Delete link';
  $handler->display->display_options['fields']['delete_link']['label'] = '';
  $handler->display->display_options['fields']['delete_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: OG membership: Group ID */
  $handler->display->display_options['filters']['gid']['id'] = 'gid';
  $handler->display->display_options['filters']['gid']['table'] = 'og_membership';
  $handler->display->display_options['filters']['gid']['field'] = 'gid';
  $handler->display->display_options['filters']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['filters']['gid']['operator'] = 'empty';
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/featured-headers';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Headers';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $translatables['featured_headers'] = array(
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
    t('<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_featured_header/ent_featured_header/add?destination=admin/config/administration/at_manage/featured-headers">Add featured header</a></li>
<li><a href="/admin/structure/entity-type/ent_featured_header/service_header/add?destination=admin/config/administration/at_manage/featured-headers">Add service header</a></li></ul>

'),
    t('Displaying @start - @end of @total'),
    t('Sorry, no any entries were found.'),
    t('OG membership from ent_featured_header'),
    t('Id'),
    t('.'),
    t(','),
    t('Title'),
    t('Slogan'),
    t('Image'),
    t('Author'),
    t('Operations'),
    t('All'),
    t('Headers of %1'),
    t('Contest headers (manage)'),
    t('<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_featured_header/ent_featured_header/add?og_group_ref=!1&destination=admin/content/featured-headers">Add featured header</a></li></ul>'),
    t('Type'),
    t('Service headers (manage)'),
    t('For page'),
    t('Frontpage'),
  );
  $export['featured_headers'] = $view;

  $view = new view();
  $view->name = 'flying_sites';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'node';
  $view->human_name = 'Manage Flying sites';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage Flying sites';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/node/add/pg-flyingsite?destination=admin/config/administration/at_manage/flyingsites">Add flying site</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_contests_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_city']['id'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['table'] = 'field_data_field_city';
  $handler->display->display_options['fields']['field_city']['field'] = 'field_city';
  $handler->display->display_options['fields']['field_city']['label'] = 'Place';
  $handler->display->display_options['fields']['field_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_city']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_city']['alter']['text'] = ', [field_city]';
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_country']['id'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['table'] = 'field_data_field_country';
  $handler->display->display_options['fields']['field_country']['field'] = 'field_country';
  $handler->display->display_options['fields']['field_country']['label'] = 'Place';
  $handler->display->display_options['fields']['field_country']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_country']['alter']['text'] = '[field_country][field_city]';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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
    'pg_flyingsite' => 'pg_flyingsite',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/flying_site';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Flying sites';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['flying_sites'] = array(
    t('Master'),
    t('Manage Flying sites'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<ul class="action-links"><li><a href="/node/add/pg-flyingsite?destination=admin/config/administration/at_manage/flyingsites">Add flying site</a></li></ul>'),
    t('Displaying @start - @end of @total'),
    t('Content'),
    t('Title'),
    t('Place'),
    t(', [field_city]'),
    t('[field_country][field_city]'),
    t('Edit link'),
    t('Page'),
  );
  $export['flying_sites'] = $view;

  $view = new view();
  $view->name = 'manage_contest_points';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'eck_ent_contest_point';
  $view->human_name = 'Manage contest points';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage contest points';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Relationship: OG membership: OG membership from Contest point */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_contest_point';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: Contest point: Id */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_contest_point';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  /* Field: Contest point: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_contest_point';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  /* Field: Bulk operations: Contest point */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'eck_ent_contest_point';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Contest point: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_contest_point';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['alter']['text'] = '[title]';
  /* Field: Contest point: Location */
  $handler->display->display_options['fields']['field_point_location']['id'] = 'field_point_location';
  $handler->display->display_options['fields']['field_point_location']['table'] = 'field_data_field_point_location';
  $handler->display->display_options['fields']['field_point_location']['field'] = 'field_point_location';
  $handler->display->display_options['fields']['field_point_location']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_point_location']['type'] = 'geofield_latlon';
  $handler->display->display_options['fields']['field_point_location']['settings'] = array(
    'data' => 'full',
    'format' => 'decimal_degrees',
    'labels' => 1,
  );
  /* Field: Contest point: Description */
  $handler->display->display_options['fields']['field_point_description']['id'] = 'field_point_description';
  $handler->display->display_options['fields']['field_point_description']['table'] = 'field_data_field_point_description';
  $handler->display->display_options['fields']['field_point_description']['field'] = 'field_point_description';
  /* Field: Contest point: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ent_contest_point';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Points of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/points';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage points';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['manage_contest_points'] = array(
    t('Master'),
    t('Manage contest points'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Displaying @start - @end of @total'),
    t('OG membership from ent_contest_point'),
    t('Id'),
    t('.'),
    t(','),
    t('Title'),
    t('Edit link'),
    t('[title]'),
    t('Location'),
    t('Description'),
    t('Delete link'),
    t('All'),
    t('Points of %1'),
    t('Page'),
  );
  $export['manage_contest_points'] = $view;

  $view = new view();
  $view->name = 'manage_custom_object';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'eck_ent_customobject';
  $view->human_name = 'Manage custom object';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage tracked objects';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_customobject/customobject/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/custom_object">Add object</a></li></ul>';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* Relationship: OG membership: OG membership from Custom object */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'eck_ent_customobject';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  /* Field: ID (exclude) */
  $handler->display->display_options['fields']['id']['id'] = 'id';
  $handler->display->display_options['fields']['id']['table'] = 'eck_ent_customobject';
  $handler->display->display_options['fields']['id']['field'] = 'id';
  $handler->display->display_options['fields']['id']['ui_name'] = 'ID (exclude)';
  $handler->display->display_options['fields']['id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['id']['separator'] = '';
  /* Field: Delete link (exclude) */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'eck_ent_customobject';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['ui_name'] = 'Delete link (exclude)';
  $handler->display->display_options['fields']['delete_link']['exclude'] = TRUE;
  /* Field: Edit link (exclude) */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'eck_ent_customobject';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['ui_name'] = 'Edit link (exclude)';
  $handler->display->display_options['fields']['edit_link']['exclude'] = TRUE;
  /* Field: Bulk operations: OG membership */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'og_membership';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_contestants_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::at_core_sync_tracked_objects_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::og_set_state_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::og_user_roles_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::og_membership_delete_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Global: View result counter */
  $handler->display->display_options['fields']['counter']['id'] = 'counter';
  $handler->display->display_options['fields']['counter']['table'] = 'views';
  $handler->display->display_options['fields']['counter']['field'] = 'counter';
  $handler->display->display_options['fields']['counter']['label'] = '#';
  $handler->display->display_options['fields']['counter']['counter_start'] = '1';
  /* Field: Custom object: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'eck_ent_customobject';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Description */
  $handler->display->display_options['fields']['field_plain_body']['id'] = 'field_plain_body';
  $handler->display->display_options['fields']['field_plain_body']['table'] = 'field_data_field_plain_body';
  $handler->display->display_options['fields']['field_plain_body']['field'] = 'field_plain_body';
  $handler->display->display_options['fields']['field_plain_body']['ui_name'] = 'Description';
  $handler->display->display_options['fields']['field_plain_body']['type'] = 'editable';
  $handler->display->display_options['fields']['field_plain_body']['settings'] = array(
    'click_to_edit' => 1,
    'empty_text' => '',
    'fallback_format' => 'text_default',
  );
  /* Field: Field: Core ID */
  $handler->display->display_options['fields']['field_core_id']['id'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['table'] = 'field_data_field_core_id';
  $handler->display->display_options['fields']['field_core_id']['field'] = 'field_core_id';
  $handler->display->display_options['fields']['field_core_id']['label'] = 'Core status';
  /* Field: OG membership: Tracker */
  $handler->display->display_options['fields']['field_tracker']['id'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['table'] = 'field_data_field_tracker';
  $handler->display->display_options['fields']['field_tracker']['field'] = 'field_tracker';
  $handler->display->display_options['fields']['field_tracker']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['fields']['field_tracker']['type'] = 'editable';
  $handler->display->display_options['fields']['field_tracker']['settings'] = array(
    'click_to_edit' => 1,
    'empty_text' => '',
    'fallback_format' => 'entityreference_label',
    'fallback_settings' => array(
      'link' => 0,
    ),
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Operations';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<ul>
<li>[edit_link]</li>
<li>[delete_link]</li>
</ul>';
  /* Contextual filter: OG membership: Group ID */
  $handler->display->display_options['arguments']['gid']['id'] = 'gid';
  $handler->display->display_options['arguments']['gid']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['gid']['field'] = 'gid';
  $handler->display->display_options['arguments']['gid']['relationship'] = 'og_membership_rel';
  $handler->display->display_options['arguments']['gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Tracked objects of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'manage_list_tracked_objects');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/custom_object';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage custom objects';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['manage_custom_object'] = array(
    t('Master'),
    t('Manage tracked objects'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('<ul class="action-links"><li><a href="/admin/structure/entity-type/ent_customobject/customobject/add?og_group_ref=!1&destination=admin/config/administration/at_manage/contest/!1/custom_object">Add object</a></li></ul>'),
    t('OG membership from ent_customobject'),
    t('Id'),
    t('.'),
    t('Delete link'),
    t('Edit link'),
    t('#'),
    t('Title'),
    t('Awards description'),
    t('Core status'),
    t('Tracker'),
    t('Operations'),
    t('<ul>
<li>[edit_link]</li>
<li>[delete_link]</li>
</ul>'),
    t('All'),
    t('Tracked objects of %1'),
    t('Page'),
  );
  $export['manage_custom_object'] = $view;

  $view = new view();
  $view->name = 'manage_day_blog';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'node';
  $view->human_name = 'Manage day blog';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage day blog';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'bypass node access';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_dayblog_ref_node']['id'] = 'reverse_field_dayblog_ref_node';
  $handler->display->display_options['relationships']['reverse_field_dayblog_ref_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_dayblog_ref_node']['field'] = 'reverse_field_dayblog_ref_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Date';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Title';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '[title]';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
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
  $handler->display->display_options['arguments']['nid']['relationship'] = 'reverse_field_dayblog_ref_node';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['title'] = '%1: Dayblog of %2';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'day' => 'day',
  );
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/day/%/blog';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage day blog';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['manage_day_blog'] = array(
    t('Master'),
    t('Manage day blog'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Content referencing Content from field_dayblog_ref'),
    t('Title'),
    t('Date'),
    t('[title]'),
    t('All'),
    t('%1: Dayblog of %2'),
    t('Page'),
  );
  $export['manage_day_blog'] = $view;

  $view = new view();
  $view->name = 'pg_scoring_categories';
  $view->description = '';
  $view->tag = 'Airtribune manage';
  $view->base_table = 'node';
  $view->human_name = 'Manage scoring categories';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Scoring categories';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
    3 => '3',
    5 => '5',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: OG membership: OG membership from Node */
  $handler->display->display_options['relationships']['og_membership_rel']['id'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel']['field'] = 'og_membership_rel';
  $handler->display->display_options['relationships']['og_membership_rel']['required'] = TRUE;
  /* Field: Draggableviews: Content */
  $handler->display->display_options['fields']['draggableviews']['id'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['table'] = 'node';
  $handler->display->display_options['fields']['draggableviews']['field'] = 'draggableviews';
  $handler->display->display_options['fields']['draggableviews']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['hide_alter_empty'] = FALSE;
  $handler->display->display_options['fields']['draggableviews']['draggableviews']['ajax'] = 0;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::at_core_sync_contests_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Scoring category';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Scoring category';
  $handler->display->display_options['fields']['edit_node']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['edit_node']['alter']['text'] = '[title]';
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
  $handler->display->display_options['arguments']['gid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['gid']['title'] = 'Scoring categories of %1';
  $handler->display->display_options['arguments']['gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['gid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['gid']['validate_options']['types'] = array(
    'pg_contest' => 'pg_contest',
  );
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
    'pg_scoring_category' => 'pg_scoring_category',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'admin/config/administration/at_manage/contest/%/scoring_category';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage scoring categories';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $translatables['pg_scoring_categories'] = array(
    t('Master'),
    t('Scoring categories'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('OG membership from node'),
    t('Content'),
    t('Scoring category'),
    t('[title]'),
    t('All'),
    t('Scoring categories of %1'),
    t('Page'),
  );
  $export['pg_scoring_categories'] = $view;

  return $export;
}
