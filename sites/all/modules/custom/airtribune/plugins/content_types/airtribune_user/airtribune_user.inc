<?php

/**
 * Airtribune user plugin.
 *
 * See issue #2386.
 */
$plugin = array(
  'title' => t('Airtrubune user'),
  'single' => TRUE,
  'category' => array('Airtribune'),
);

/**
 * Render the custom content type.
 */
function airtribune_airtribune_user_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user, $language;
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_user';

  $build['airtribune-user'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'airtribune-user'),
  );

  $path = drupal_is_front_page() ? '<front>' : current_path();
  $links = language_negotiation_get_switch_links('language', $path);
  if (isset($links->links)) {
    $build['lang-icons'] = array(
      '#prefix' => '<div class="drop_item flags"><div class="pane-inner">',
      '#theme' => 'links',
      '#links' => $links->links,
      '#suffix' => '</div></div>',
    );
    $build['airtribune-user']['lang-icon'] = array(
      '#prefix' => '<div class="lang-icon"><span>',
      '#theme' => 'image',
      '#path' => file_create_url($plugin_path . '/flags/' . $language->language . '.png'),
      '#alt' => $language->language,
      '#suffix' => '</span></div>',
    );
  }

  if ($user->uid) {
    $build['airtribune-user']['user-name'] = array(
      '#prefix' => '<div class="user_button">',
      '#markup' => l(airtrubune_format_username($user->name), 'user/' . $user->uid),
      '#suffix' => '</div>',
    );
    $build['user-menu'] = menu_tree($conf['menu']);
    $build['user-menu']['#prefix'] = '<div class="drop_item user-menu"><div class="pane-inner">';
    $build['user-menu']['#suffix'] = '</div></div>';
    $build['airtribune-user']['user_picture'] = array(
      '#markup' => theme('user_picture', array('account' => $user)),
    );
  }
  else {
    $build['airtribune-user']['signin'] = array(
     '#prefix' => '<div class="user_button">',
     '#markup' => l('Sign in', 'user'),
     '#suffix' => '</div>',
    );
    $build['login-form'] = drupal_get_form('user_login_block');
    $build['login-form']['#prefix'] = '<div class="drop_item user-login"><div class="pane-inner">';
    $build['login-form']['#suffix'] = '</div></div>';
  }

  $build['#attached'] = array(
    'js' => array($plugin_path . '/script.js'),
    'css' => array($plugin_path . '/style.css'),
  );

  return (object) array(
    'module' => 'airtribune',
    'title' => t('Airtribune user'),
    'content' => $build,
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
  $block->title = theme('image', array('path' => $plugin_path . '/admin-title.png'));
  $items[] = t('User login form');
  $items[] = t('User picture');
  $items[] = t('User menu');
  $items[] = t('User name');
  $items[] = t('Language selector');
  $block->content = theme('item_list', array('items' => $items));
  return $block;
}

/**
 * @param $name
 * @return string
 *
 * See issue #2370.
 */
function airtrubune_format_username($name) {
  return $name;
}
