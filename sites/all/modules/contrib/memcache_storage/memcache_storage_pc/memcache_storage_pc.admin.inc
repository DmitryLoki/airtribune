<?php

/**
 * @file
 * Settings form for MEMCACHE STORAGE PAGE CACHE module.
 */

/**
 * Settings form for actions with cached pages.
 */
function memcache_storage_pc_settings_form() {

  $form['cache_actions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cache expiration actions'),
    '#collapsible' => TRUE,
  );

  $form['cache_actions']['node'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node actions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cache_actions']['node']['memcache_storage_pc_node_actions'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Page cache for node will be expired after selected actions.'),
    '#options' => array(
      MEMCACHE_STORAGE_PC_NODE_INSERT => t('Node insert'),
      MEMCACHE_STORAGE_PC_NODE_UPDATE => t('Node update'),
      MEMCACHE_STORAGE_PC_NODE_DELETE => t('Node delete'),
    ),
    '#default_value' => variable_get('memcache_storage_pc_node_actions', array()),
  );

  $form['cache_actions']['comment'] = array(
    '#type' => 'fieldset',
    '#title' => t('Comment actions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cache_actions']['comment']['memcache_storage_pc_comment_actions'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Page cache for comment will be expired after selected actions.'),
    '#options' => array(
      MEMCACHE_STORAGE_PC_COMMENT_INSERT => t('Comment insert'),
      MEMCACHE_STORAGE_PC_COMMENT_UPDATE => t('Comment update'),
      MEMCACHE_STORAGE_PC_COMMENT_DELETE => t('Comment delete'),
      MEMCACHE_STORAGE_PC_COMMENT_PUBLISH => t('Comment publish'),
      MEMCACHE_STORAGE_PC_COMMENT_UNPUBLISH => t('Comment unpublish'),
    ),
    '#default_value' => variable_get('memcache_storage_pc_comment_actions', array()),
  );

  $form['cache_actions']['user'] = array(
    '#type' => 'fieldset',
    '#title' => t('User actions'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cache_actions']['user']['memcache_storage_pc_user_actions'] = array(
    '#type' => 'checkboxes',
    '#description' => t('Page cache for user will be expired after selected actions.'),
    '#options' => array(
      MEMCACHE_STORAGE_PC_USER_INSERT => t('User insert'),
      MEMCACHE_STORAGE_PC_USER_UPDATE => t('User update'),
      MEMCACHE_STORAGE_PC_USER_DELETE => t('User delete'),
      MEMCACHE_STORAGE_PC_USER_CANCEL => t('User cancel'),
    ),
    '#default_value' => variable_get('memcache_storage_pc_user_actions', array()),
  );

  $form['cache_expire'] = array(
    '#type' => 'fieldset',
    '#title' => t('What pages should be expired?'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  // NODE ACTION.
  $form['cache_expire']['node'] = array(
    '#type' => 'fieldset',
    '#title' => t('After node action'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cache_expire']['node']['memcache_storage_pc_node_expire_front_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Front page'),
    '#default_value' => variable_get('memcache_storage_pc_node_expire_front_page', MEMCACHE_STORAGE_PC_NODE_EXPIRE_FRONT_PAGE),
  );

  $form['cache_expire']['node']['memcache_storage_pc_node_expire_node_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Node page'),
    '#default_value' => variable_get('memcache_storage_pc_node_expire_node_page', MEMCACHE_STORAGE_PC_NODE_EXPIRE_NODE_PAGE),
  );

  if (module_exists('taxonomy')) {
    $form['cache_expire']['node']['memcache_storage_pc_node_expire_term_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Node term pages'),
      '#default_value' => variable_get('memcache_storage_pc_node_expire_term_pages', MEMCACHE_STORAGE_PC_NODE_EXPIRE_TERM_PAGES),
    );
  }

  if (module_exists('node_reference')) {
    $form['cache_expire']['node']['memcache_storage_pc_node_expire_reference_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Node reference pages'),
      '#default_value' => variable_get('memcache_storage_pc_node_expire_reference_pages', MEMCACHE_STORAGE_PC_NODE_EXPIRE_REFERENCE_PAGES),
    );
  }

  $form['cache_expire']['node']['memcache_storage_pc_node_expire_custom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom pages'),
    '#default_value' => variable_get('memcache_storage_pc_node_expire_custom', MEMCACHE_STORAGE_PC_NODE_EXPIRE_CUSTOM),
  );

  $form['cache_expire']['node']['memcache_storage_pc_node_expire_custom_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter custom urls'),
    '#description' => t('Enter every new url on a single line. Example: !example.', array('!example' => '<strong>node/[node:nid]</strong>')) . '<br/>'
      . t('If you want to use wildcard flush, add |wildcard to the end of the line. Example: !example', array('!example' => '<strong>node/[node:nid]|wildcard</strong>')) . '<br/>'
      . t('You may use tokens here.'),
    '#states' => array(
      'visible' => array(
        ':input[name="memcache_storage_pc_node_expire_custom"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('memcache_storage_pc_node_expire_custom_pages'),
  );

  // COMMENT ACTION.
  $form['cache_expire']['comment'] = array(
    '#type' => 'fieldset',
    '#title' => t('After comment action'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_front_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Front page'),
    '#default_value' => variable_get('memcache_storage_pc_comment_expire_front_page', MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_FRONT_PAGE),
  );

  $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_comment_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Comment page'),
    '#default_value' => variable_get('memcache_storage_pc_comment_expire_comment_page', MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_COMMENT_PAGE),
  );

  $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_node_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Comment\'s node page'),
    '#default_value' => variable_get('memcache_storage_pc_comment_expire_node_page', MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_PAGE),
  );

  if (module_exists('taxonomy')) {
    $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_node_term_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Comment\'s node term pages'),
      '#default_value' => variable_get('memcache_storage_pc_comment_expire_node_term_pages', MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_TERM_PAGES),
    );
  }

  if (module_exists('node_reference')) {
    $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_node_reference_pages'] = array(
      '#type' => 'checkbox',
      '#title' => t('Comment\'s node reference pages'),
      '#default_value' => variable_get('memcache_storage_pc_comment_expire_node_reference_pages', MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_REFERENCE_PAGES),
    );
  }

  $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_custom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom pages'),
    '#default_value' => variable_get('memcache_storage_pc_comment_expire_custom', MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_CUSTOM),
  );

  $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_custom_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter custom urls'),
    '#description' => t('Enter every new url on a single line. Example: !example.', array('!example' => '<strong>comment/[comment:cid]</strong>')) . '<br/>'
      . t('If you want to use wildcard flush, add |wildcard to the end of the line. Example: !example', array('!example' => '<strong>comment/[comment:cid]|wildcard</strong>')) . '<br/>'
      . t('You may use tokens here.'),
    '#states' => array(
      'visible' => array(
        ':input[name="memcache_storage_pc_comment_expire_custom"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('memcache_storage_pc_comment_expire_custom_pages'),
  );

  // USER ACTION.
  $form['cache_expire']['user'] = array(
    '#type' => 'fieldset',
    '#title' => t('After user action'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['cache_expire']['user']['memcache_storage_pc_user_expire_front_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('Front page'),
    '#default_value' => variable_get('memcache_storage_pc_user_expire_front_page', MEMCACHE_STORAGE_PC_USER_EXPIRE_FRONT_PAGE),
  );

  $form['cache_expire']['user']['memcache_storage_pc_user_expire_user_page'] = array(
    '#type' => 'checkbox',
    '#title' => t('User page'),
    '#default_value' => variable_get('memcache_storage_pc_user_expire_user_page', MEMCACHE_STORAGE_PC_USER_EXPIRE_USER_PAGE),
  );

  $form['cache_expire']['user']['memcache_storage_pc_user_expire_custom'] = array(
    '#type' => 'checkbox',
    '#title' => t('Custom pages'),
    '#default_value' => variable_get('memcache_storage_pc_user_expire_custom', MEMCACHE_STORAGE_PC_USER_EXPIRE_CUSTOM),
  );

  $form['cache_expire']['user']['memcache_storage_pc_user_expire_custom_pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter custom urls'),
    '#description' => t('Enter every new url on a single line. Example: !example.', array('!example' => '<strong>user/[user:uid]</strong>')) . '<br/>'
      . t('If you want to use wildcard flush, add |wildcard to the end of the line. Example: !example', array('!example' => '<strong>user/[user:uid]|wildcard</strong>')) . '<br/>'
      . t('You may use tokens here.'),
    '#states' => array(
      'visible' => array(
        ':input[name="memcache_storage_pc_user_expire_custom"]' => array('checked' => TRUE),
      ),
    ),
    '#default_value' => variable_get('memcache_storage_pc_user_expire_custom_pages'),
  );

  // Add the token tree UI.
  if (module_exists('token')) {

    $form['cache_expire']['node']['memcache_storage_pc_node_expire_custom_pages']['#description'] .= ' ' .
      theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('node')));

    $form['cache_expire']['comment']['memcache_storage_pc_comment_expire_custom_pages']['#description'] .= ' ' .
      theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('comment')));

    $form['cache_expire']['user']['memcache_storage_pc_user_expire_custom_pages']['#description'] .= ' ' .
      theme('token_tree_link', array('text' => t('View available tokens.'), 'token_types' => array('user')));
  }

  return system_settings_form($form);
}

/**
 * Settings form for node type.
 */
function memcache_storage_pc_node_settings_form(&$form, &$form_state) {

  if (empty($form['#node_type']->type)) {
    return;
  }

  $node_type = $form['#node_type']->type;

  $form['memcache_storage_pc'] = array(
    '#type' => 'fieldset',
    '#title' => t('Memcache Storage Page Cache'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#group' => 'additional_settings',
  );

  // NODE SETTINGS.
  $form['memcache_storage_pc']['memcache_storage_pc_node_override_defaults'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override default settings for this node type'),
    '#default_value' => variable_get('memcache_storage_pc_node_override_defaults_' . $node_type),
  );

  // Copy here settings from default settings form.
  $settings_form = memcache_storage_pc_settings_form();
  $form['memcache_storage_pc']['node_actions'] = $settings_form['cache_actions']['node'];
  $form['memcache_storage_pc']['node_expires'] = $settings_form['cache_expire']['node'];

  $form['memcache_storage_pc']['node_actions']['#collapsed'] = FALSE;
  $form['memcache_storage_pc']['node_expires']['#collapsed'] = FALSE;

  // Display fieldsets with settings only if they should be overriden.
  $form['memcache_storage_pc']['node_actions']['#states'] = array(
    'visible' => array(':input[name="memcache_storage_pc_node_override_defaults"]' => array('checked' => TRUE)),
  );
  $form['memcache_storage_pc']['node_expires']['#states'] = array(
    'visible' => array(':input[name="memcache_storage_pc_node_override_defaults"]' => array('checked' => TRUE)),
  );

  // Change tab title to more suitable.
  $form['memcache_storage_pc']['node_expires']['#title'] = t('What pages should be expired when node action is triggered?');


  // COMMENT SETTINGS.
  $form['memcache_storage_pc']['memcache_storage_pc_comment_override_defaults'] = array(
    '#type' => 'checkbox',
    '#title' => t('Override default settings for comments to this node type'),
    '#default_value' => variable_get('memcache_storage_pc_comment_override_defaults_' . $node_type),
  );

  $form['memcache_storage_pc']['comment_actions'] = $settings_form['cache_actions']['comment'];
  $form['memcache_storage_pc']['comment_expires'] = $settings_form['cache_expire']['comment'];

  $form['memcache_storage_pc']['comment_actions']['#collapsed'] = FALSE;
  $form['memcache_storage_pc']['comment_expires']['#collapsed'] = FALSE;

  // Display fieldsets with settings only if they should be overriden.
  $form['memcache_storage_pc']['comment_actions']['#states'] = array(
    'visible' => array(':input[name="memcache_storage_pc_comment_override_defaults"]' => array('checked' => TRUE)),
  );
  $form['memcache_storage_pc']['comment_expires']['#states'] = array(
    'visible' => array(':input[name="memcache_storage_pc_comment_override_defaults"]' => array('checked' => TRUE)),
  );

  // Set default settings for this node type.
  $form['memcache_storage_pc']['node_actions']['memcache_storage_pc_node_actions']['#default_value'] =
    variable_get('memcache_storage_pc_node_actions_' . $node_type, array());

  $form['memcache_storage_pc']['node_expires']['memcache_storage_pc_node_expire_front_page']['#default_value'] =
    variable_get('memcache_storage_pc_node_expire_front_page_' . $node_type, MEMCACHE_STORAGE_PC_NODE_EXPIRE_FRONT_PAGE);

  $form['memcache_storage_pc']['node_expires']['memcache_storage_pc_node_expire_node_page']['#default_value'] =
    variable_get('memcache_storage_pc_node_expire_node_page_' . $node_type, MEMCACHE_STORAGE_PC_NODE_EXPIRE_NODE_PAGE);

  if (module_exists('taxonomy')) {
    $form['memcache_storage_pc']['node_expires']['memcache_storage_pc_node_expire_term_pages']['#default_value'] =
      variable_get('memcache_storage_pc_node_expire_term_pages_' . $node_type, MEMCACHE_STORAGE_PC_NODE_EXPIRE_TERM_PAGES);
  }

  if (module_exists('node_reference')) {
    $form['memcache_storage_pc']['node_expires']['memcache_storage_pc_node_expire_reference_pages']['#default_value'] =
      variable_get('memcache_storage_pc_node_expire_reference_pages_' . $node_type, MEMCACHE_STORAGE_PC_NODE_EXPIRE_REFERENCE_PAGES);
  }

  $form['memcache_storage_pc']['node_expires']['memcache_storage_pc_node_expire_custom']['#default_value'] =
    variable_get('memcache_storage_pc_node_expire_custom_' . $node_type, MEMCACHE_STORAGE_PC_NODE_EXPIRE_CUSTOM);

  $form['memcache_storage_pc']['node_expires']['memcache_storage_pc_node_expire_custom_pages']['#default_value'] =
    variable_get('memcache_storage_pc_node_expire_custom_pages_' . $node_type);

  // Set default values for comments to this node type.
  $form['memcache_storage_pc']['comment_actions']['memcache_storage_pc_comment_actions']['#default_value'] =
    variable_get('memcache_storage_pc_comment_actions_' . $node_type, array());

  $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_front_page']['#default_value'] =
    variable_get('memcache_storage_pc_comment_expire_front_page_' . $node_type, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_FRONT_PAGE);

  $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_comment_page']['#default_value'] =
    variable_get('memcache_storage_pc_comment_expire_comment_page_' . $node_type, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_COMMENT_PAGE);


  $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_node_page']['#default_value'] =
    variable_get('memcache_storage_pc_comment_expire_node_page_' . $node_type, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_PAGE);

  if (module_exists('taxonomy')) {
    $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_node_term_pages']['#default_value'] =
      variable_get('memcache_storage_pc_comment_expire_node_term_pages_' . $node_type, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_TERM_PAGES);
  }

  if (module_exists('node_reference')) {
    $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_node_reference_pages']['#default_value'] =
      variable_get('memcache_storage_pc_comment_expire_node_reference_pages_' . $node_type, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_NODE_REFERENCE_PAGES);
  }

  $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_custom']['#default_value'] =
    variable_get('memcache_storage_pc_comment_expire_custom_' . $node_type, MEMCACHE_STORAGE_PC_COMMENT_EXPIRE_CUSTOM);

  $form['memcache_storage_pc']['comment_expires']['memcache_storage_pc_comment_expire_custom_pages']['#default_value'] =
    variable_get('memcache_storage_pc_comment_expire_custom_pages_' . $node_type);

  // Attach js.
  $form['#attached']['js'][] = drupal_get_path('module', 'memcache_storage_pc') . '/js/memcache_storage_pc.js';
}
