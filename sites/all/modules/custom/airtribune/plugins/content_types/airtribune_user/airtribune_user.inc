<?php

/**
 * @file
 * Airtribune user pane plugin.
 *
 * @see #2386.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune user'),
  'single' => TRUE,
  'category' => array('Airtribune'),
);

/**
 * Render airtribune user panel.
 */
function airtribune_airtribune_user_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user, $language;
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_user';

  $content = array(
    '#theme' => 'airtribune_user_pane',
    '#attached' => array(
      'js' => array($plugin_path . '/script.js'),
      'css' => array($plugin_path . '/style.css'),
    ),
  );

  $path = drupal_is_front_page() ? '<front>' : current_path();
  $links = language_negotiation_get_switch_links('language', $path);
  foreach ($links->links as $lang_code => $link) {
    $links->links[$lang_code]['title'] = theme(
      'countryicons_icon_sprite',
      array('code' => airtrubune_get_country_code($lang_code), 'iconset' => AIRTRIBUNE_LANGUAGES_ICONSET)
    )
    // pt-br to pt.
    . substr($lang_code, 0, 2);
    $links->links[$lang_code]['html'] = TRUE;
  }
  $content['lang_links'] = array(
    '#theme' => 'links',
    '#links' => $links->links,
  );
  // Switch language button.
  $content['lang_icon'] = array(
    '#theme' => 'countryicons_icon',
    '#code' => airtrubune_get_country_code($language->language),
    '#iconset' => AIRTRIBUNE_LANGUAGES_ICONSET,
  );

  if ($user->uid) {
    $content['user_menu'] = menu_tree(empty($conf['menu']) ? 'user-menu' : $conf['menu']);
  }
  else {
    $content['login_form'] = drupal_get_form('user_login_block');
  }

  return (object) array(
    'module' => 'airtribune',
    'title' => t('Airtribune user'),
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Returns an edit form for content type settings.
 */
function airtribune_airtribune_user_content_type_edit_form($form, &$form_state) {
  $form['menu'] = array(
    '#type' => 'select',
    '#title' => t('Menu'),
    '#description' => t('Select the source for the dropdown menu in this block.'),
    '#required' => TRUE,
    '#options' => menu_get_menus(),
    '#default_value' => $form_state['conf'],
  );
  return $form;
}

/**
 * Submit handler for content type settings from.
 */
function airtribune_airtribune_user_content_type_edit_form_submit($form, &$form_state) {
  $form_state['conf']['menu'] = $form_state['values']['menu'];
}

/**
 * Callback to provide administrative info.
 */
function airtribune_airtribune_user_content_type_admin_info($subtype, $conf) {
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_user';
  $block = new stdClass();
  $block->title = theme('image', array('path' => $plugin_path . '/images/admin-title.png'));
  $items[] = t('User login form');
  $items[] = t('User picture');
  $items[] = t('User menu');
  $items[] = t('User name');
  $items[] = t('Language selector');
  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * Process variables for airtribune-user-pane.tpl.php.
 *
 * The $vars array contains the following arguments:
 * - $element
 *
 * @see airtribune-user-pane.tpl.php
 */
function template_preprocess_airtribune_user_pane(&$vars) {
  foreach (element_children($vars['elements']) as $key) {
    $vars[$key] = render($vars['elements'][$key]);
  }
  if ($vars['logged_in']) {
    $vars['user_name'] = airtrubune_format_username($vars['user']);
    $vars['user_profile_link'] = url('user/' . $vars['user']->uid);
    $vars['user_picture'] = theme('user_picture', array('account' => $vars['user']));
  }
}
