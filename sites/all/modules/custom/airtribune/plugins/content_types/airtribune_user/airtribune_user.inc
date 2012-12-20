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
 *
 * TODO Move markup to template file.
 */
function airtribune_airtribune_user_content_type_render($subtype, $conf, $panel_args, $context) {
  global $user, $language;
  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/airtribune_user';

  $build['#prefix'] = '<div id="sign-in">';
  $build['#suffix'] = '</div>';
  $build['#attached'] = array(
    'js' => array($plugin_path . '/script.js'),
    'css' => array($plugin_path . '/style.css'),
  );

  $build['airtribune-user'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'airtribune-user'),
  );

  $path = drupal_is_front_page() ? '<front>' : current_path();
  $links = language_negotiation_get_switch_links('language', $path);

  foreach ($links->links as $lang_code => $link) {
    $links->links[$lang_code]['title'] = theme('countryicons_icon_sprite', array('code' => airtribune_airtribune_user_get_lang_code($lang_code), 'iconset' => AIRTRIBUNE_LANGUAGES_ICONSET)) . $lang_code;
    $links->links[$lang_code]['html'] = TRUE;
  }

  if (isset($links->links)) {
    $build['lang-icons'] = array(
      '#prefix' => '<div class="drop-item flags"><div class="pane-inner">',
      '#theme' => 'links',
      '#links' => $links->links,
      '#suffix' => '</div></div>',
    );
    $build['airtribune-user']['lang-icon'] = array(
      '#theme' => 'countryicons_icon',
      '#prefix' => '<div class="lang-icon"><span>',
      '#code' => airtribune_airtribune_user_get_lang_code($language->language),
      '#iconset' => AIRTRIBUNE_LANGUAGES_ICONSET,
      '#suffix' => '</span></div>',
    );
  }
  if ($user->uid) {
    $build['airtribune-user']['user-name'] = array(
      '#prefix' => '<div class="user-button">',
      '#markup' => l('<span>' . airtrubune_format_username($user->name) . '</span>', 'user/' . $user->uid, array('html' => TRUE)),
      '#suffix' => '</div>',
    );
    $build['user-menu'] = menu_tree($conf['menu']);
    $build['user-menu']['#prefix'] = '<div class="drop-item user-menu"><div class="pane-inner">';
    $build['user-menu']['#suffix'] = '</div></div>';
    $build['airtribune-user']['user_picture'] = array(
      '#markup' => theme('user_picture', array('account' => $user)),
    );
  }
  else {
    $build['airtribune-user']['signin'] = array(
     '#prefix' => '<div class="user-button">',
     '#markup' => l('Sign in', 'user'),
     '#suffix' => '</div>',
    );
    $build['login-form'] = drupal_get_form('user_login_block');
    $build['login-form']['#prefix'] = '<div class="drop-item user-login"><div class="pane-inner">';
    $build['login-form']['#suffix'] = '</div></div>';
  }

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
 *
 */
function airtribune_airtribune_user_get_lang_code($lang_code) {
  if ($lang_code == 'en') {
    $lang_code  = 'us';
  }
  return $lang_code ;
}
