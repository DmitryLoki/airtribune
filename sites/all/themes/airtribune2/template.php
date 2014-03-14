<?php

/**
 * Preprocess html.tpl.php
 */
function airtribune2_preprocess_html(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;
  //print_r($vars);


  // Add class for the active theme name
  $vars['classes_array'][] = drupal_html_class($theme_name);

  // Browser/platform sniff - adds body classes such as ipad, webkit, chrome etc.
  /* -- Delete this line to add a classes for the browser and platform.
  $vars['classes_array'][] = css_browser_selector();
  // */


  // Remove body classes added by Drupal core
  $classes_to_remove = array('two-sidebars', 'one-sidebar sidebar-first', 'one-sidebar sidebar-second', 'no-sidebars');
  foreach ($vars['classes_array'] as $key => $css_class) {
    if (in_array($css_class, $classes_to_remove)) {
      unset($vars['classes_array'][$key]);
    }
  }
  $vars['classes_array'][] = 'body_bgr';
  if (!in_array('page-event-results-facebook', $vars['classes_array'])) {
    $vars['classes_array'][] = 'featured-header-collapsible';
  }
  if ($vars['is_front']) {
    drupal_set_title('');
  }
  if (!empty($vars['page']['content']['system_main']['nodes'])) {

    $nodes = $vars['page']['content']['system_main']['nodes'];
    $nodes_k = array_keys($vars['page']['content']['system_main']['nodes']);

    if (count($nodes) == 2 && !empty($nodes[$nodes_k[0]]['#node']) && $nodes[$nodes_k[0]]['#node']->promote == 1) {
      $vars['classes_array'][] = 'logo_in_title';
    }
  }
  /* Adding specific class for activity and accommodation pages */

  $pemaa = array('node-type-activity', 'node-type-accommodation');
  $result_ar = array_intersect($pemaa, $vars['classes_array']);
  if (!empty($result_ar)) {
    $vars['classes_array'][] = 'page-event-map-activity-accommodation';
  }

  /* If profile pilot page */

  if (!empty($vars['page']['content']['system_main']['profile_pilot'])) {
    $vars['classes_array'][] = 'page-user';
    if (!in_array('page-event-register', $vars['classes_array'])) {
      $vars['classes_array'][] = 'page-user-header-logo';
    }
  }

  /* If user page */

  if (arg(0) =='user' && in_array('page-user', $vars['classes_array'])) {
    $vars['classes_array'][] = 'page-user-header-logo';
  }

  /* If event register page */

  if (arg(0) == 'event' && arg(2) && arg(2) == 'register' && !in_array('page-user', $vars['classes_array'])) {
    $vars['classes_array'][] = 'page-user';
  }

  /* If event settings page */

  if (in_array('page-event-settings', $vars['classes_array'])) {
    array_unshift($vars['classes_array'], 'page-user');
  }

  /* If pilot status list */

  if (in_array('page-event-pilots', $vars['classes_array']) && !arg(3)) {
    $vars['classes_array'][] = 'page-event-pilots-status';
  }

  /* if node event blog */

  if (in_array('page-event-blog', $vars['classes_array'])) {
    $vars['classes_array'][] = 'page-node';
  }

  if (in_array('page-event-results-facebook', $vars['classes_array'])) {
    $vars['html_attributes_array']['class'] = array('fb_view');
  }

  // @see #3796: add class for body on solutions pages
  $part = is_solutions();
  if ($part) {
    $vars['classes_array'][] = $part;
  }

  /* if event pilots manage */

  if (in_array('page-event-pilots-manage', $vars['classes_array'])) {
    drupal_add_js(path_to_theme() . '/js/jquery.mousewheel.min.js');
    drupal_add_js(path_to_theme() . '/js/jquery.jscrollpane.min.js');
    drupal_add_js(path_to_theme() . '/js/jquery.forms.js');
    drupal_add_js(path_to_theme() . '/js/forms_action.js');
  }

  // Temporary exclude css from aggregate
  // @see https://drupal.org/node/1271984
  drupal_add_css(path_to_theme() . '/css/na.css', array('preprocess' => FALSE));
}

/**
 * Preprocess Pane Header
 */
function airtribune2_preprocess_pane_header(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Set up logo element
  if (at_get_setting('toggle_logo', $theme_name) === 1) {
    $vars['site_logo'] = drupal_static('adaptivetheme_preprocess_page_site_logo');
    if (empty($vars['site_logo'])) {
      $logo_path = check_url($vars['logo']);
      $logo_alt = check_plain(variable_get('site_name', t('Site logo')));
      $logo_vars = array('path' => $logo_path, 'alt' => $logo_alt, 'attributes' => array('class' => 'site-logo'));
      $logo_img = theme('image', $logo_vars);
      $vars['site_logo'] = $logo_img ? l($logo_img, '<front>', array('attributes' => array('title' => t('Home page')), 'html' => TRUE)) : '';
    }
    // Maintain backwards compatibility with 7.x-2.x sub-themes
    $vars['logo_img'] = isset($logo_img) ? $logo_img : '';
    $vars['linked_site_logo'] = $vars['site_logo'];
  }
  else {
    $vars['site_logo'] = '';
    $vars['logo_img'] = '';
    $vars['linked_site_logo'] = '';
  }

  // Site name
  $vars['site_name'] = &drupal_static('adaptivetheme_preprocess_page_site_name');
  if (empty($vars['site_name'])) {
    $sitename = variable_get('site_name', 'Drupal');
    $vars['site_name'] = l($sitename, '<front>', array('attributes' => array('title' => t('Home page'))));
    $vars['site_name_unlinked'] = $sitename;
  }

  // Site name visibility and other classes
  $vars['site_name_attributes_array'] = array();

  $vars['visibility'] = '';
  $vars['hide_site_name'] = FALSE;
  if (at_get_setting('toggle_name', $theme_name) === 0) {
    // Keep the visibility variable to maintain backwards compatibility
    $vars['visibility'] = 'element-invisible';
    $vars['site_name_attributes_array']['class'][] = $vars['visibility'];
    $vars['hide_site_name'] = TRUE;
  }

  // hgroup attributes
  $vars['hgroup_attributes_array'] = array();
  if (!$vars['site_slogan'] && $vars['hide_site_name']) {
    $vars['hgroup_attributes_array']['class'][] = $vars['visibility'];
  }
}

/**
 * Process pane header
 */
function airtribune2_process_pane_header(&$vars) {

  global $theme_key;
  $theme_name = $theme_key;

  // Site name, Slogan and hgroup attributes
  $vars['site_name_attributes'] = empty($vars['site_name_attributes_array']) ? '' : drupal_attributes($vars['site_name_attributes_array']);
  $vars['site_slogan_attributes'] = empty($vars['site_slogan_attributes_array']) ? '' : drupal_attributes($vars['site_slogan_attributes_array']);
  $vars['hgroup_attributes'] = empty($vars['hgroup_attributes_array']) ? '' : drupal_attributes($vars['hgroup_attributes_array']);
}

/**
 * Preprocess pane navigation vars
 */
function airtribune2_preprocess_pane_navigation(&$vars) {
  // Build a variable for the main menu
  if (isset($vars['main_menu'])) {
    $vars['primary_navigation'] = theme('links', array(
        'links' => $vars['main_menu'],
        'attributes' => array(
          'class' => array('menu', 'primary-menu', 'clearfix'),
        ),
        'heading' => array(
          'text' => t('Main menu'),
          'level' => 'h2',
          'class' => array('element-invisible'),
        ),
      ));
  }
  // Build a variable for the secondary menu
  if (isset($vars['secondary_menu'])) {
    $vars['secondary_navigation'] = theme('links', array(
        'links' => $vars['secondary_menu'],
        'attributes' => array(
          'class' => array('menu', 'secondary-menu', 'clearfix'),
        ),
        'heading' => array(
          'text' => t('Secondary navigation'),
          'level' => 'h2',
          'class' => array('element-invisible'),
        ),
      ));
  }
}

/**
 * Preprocess pane twocolfourrow
 */
function airtribune2_process_twocolfourrow(&$vars) {}

/**
 * Preprocess pane navigation vars
 */
function airtribune2_process_pane_navigation(&$vars) {
  // theme the menu bars
  if (!empty($vars['primary_navigation'])) {
    $vars['primary_navigation'] = theme('menubar', array('menu' => $vars['primary_navigation'], 'type' => 'primary'));
  }
  if (!empty($vars['secondary_navigation'])) {
    $vars['secondary_navigation'] = theme('menubar', array('menu' => $vars['secondary_navigation'], 'type' => 'secondary'));
  }
}

// Preprocess pane messages vars
function airtribune2_preprocess_pane_messages(&$vars) {

  $vars['primary_local_tasks'] = menu_primary_local_tasks();
  $vars['secondary_local_tasks'] = menu_secondary_local_tasks();
  if (!empty($vars['primary_local_tasks'])) {
    foreach ($vars['primary_local_tasks'] as $k => $v) {
      if ($v['#link']['path'] == 'event/%/register') {
        $event_nid = arg(1);
        $days = airtribune_how_time_after_event_start($event_nid, 'day');
        if ($days && $days < 2) {
          $vars['primary_local_tasks'][$k]['#link']['title'] = t('Late Registration');
          $vars['primary_local_tasks'][$k]['#link']['localized_options']['attributes']['html'] = TRUE;
          $vars['primary_local_tasks'][$k]['#link']['localized_options']['attributes']['class'][0] = 'late-registration';
          $vars['suffix'] = array(
            $vars['primary_local_tasks'][$k],
          );
          unset($vars['primary_local_tasks'][$k]);
        }
        else {
          $vars['primary_local_tasks'][$k]['#link']['localized_options']['attributes']['class'][] = 'registration';
        }
      }
      if ($v['#link']['path'] == 'events/add') {
        $vars['primary_local_tasks'][$k] = array(
          '#theme' => 'links',
          '#links' => array(
            'event_add' => array(
              'title' => $vars['primary_local_tasks'][$k]['#link']['title'],
              'href' => $vars['primary_local_tasks'][$k]['#link']['href'],
              'attributes' => array(
                'class' => array('registration'),
              ),
            ),
          ),
        );
        // $vars['primary_local_tasks'][$k]['#link']['localized_options']['attributes']['class'][] = 'registration';
        // $vars['primary_local_tasks'][$k]['#attributes']['class'] = array('event_add');
      }
    }
  }
}

/**
 * Add templates for panes
 *
 * @param array $variables
 * @autor Vyacheslav "ValiDoll" Malchik <info@vkey.biz>
 */
function airtribune2_preprocess_panels_pane(&$variables) {
  //
  $base = 'panels_pane';
  $delimiter = '__';
  $variables['theme_hook_suggestions'][] = $base . $delimiter . $variables['pane']->type;
  global $user;
  if ($variables['pane']->type == 'node' && $variables['content']['#node']->nid == '5363') {
    //$variables['title'] = '';
  }
  if ($variables['pane']->type == 'page_title' && arg(0) == 'user' && $user->uid == 0) {

    if (arg(1)) {
      if (arg(1) == 'register') {
        drupal_set_title(t('Register new user'));
      }
      if (arg(1) == 'password') {
        drupal_set_title(t('Request new password'));
      }
    }
    else {
      drupal_set_title(t('Sign in'));
    }
  }
  if ($variables['pane']->subtype == 'paragliding_pilots_list-fai') {
    $variables['title'] = '';
  }
  if ($variables['pane']->type == 'node_title') {
    if (arg(2) && arg(2) == 'map' && arg(3)) {
      $n = node_load(arg(3));
      $variables['content'] = $n->title;
    }
  }
  if (isset($variables['pane']->configuration['more'], $variables['display']->args[0])) {
    $variables['classes_array'][] = 'wrapper-with-link';
  }

  $transport = array(
    'node:field_gt_plane',
    'node:field_gt_train',
    'node:field_gt_car',
    'node:field_gt_bus',
    'node:field_gt_taxi',
  );

  if (in_array($variables['pane']->subtype, $transport)) {
    $variables['classes_array'][] = 'transport-icon';
  }
  if ($variables['pane']->type == 'pane_messages') {
    //print_r($variables);
  }
  //print_r($variables['pane']);
  switch ($variables['pane']->subtype) {
    case 'frontpage_events-live_events_pane':
    case 'frontpage_events-soon_worldwide_pane':
    case 'soon_country':
      $variables['classes_array'][] = 'front_live_events';
      $variables['title_attributes_array']['class'][] = 'clearfix';
      break;
    case 'node_content':
      if (is_solutions() || $variables['content']['#node']->type == 'newsblog') {
        $variables['title'] = '';
      }
      break;
    case 'paragliding_pilots_list-manage_confirmed':
    case 'paragliding_pilots_list-manage':
      $variables['classes_array'][] = 'pane_pilots_list_manage';
      break;

    default:
      # code...
      break;
  }
  /* If pilot status list */

  // if (in_array('page-event-pilots', $vars['classes_array']) && !arg(3)) {
  //   $vars['classes_array'][] = 'page-event-pilots-status';
  // }

  // Add disclaimer to activity / accommodation pages
  // See #2802
  if (
    !empty($variables['content']['#bundle']) &&
    in_array($variables['content']['#bundle'], array(AIRTRIBUNE_ACTIVITY_TYPE, AIRTRIBUNE_ACCOMMODATION_TYPE))
  ) {
    $variables['content']['#node']->content['disclaimer'] = _get_disclaimer_for_accom_activity($variables['content']['#node']);
  }
}

/**
 * Implements preprocess_node().
 */
function airtribune2_preprocess_node(&$vars) {

  // Override "read more" link.
  // See issue #2362.
  if (isset($vars['content']['links']['node']['#links']['node-readmore'])) {
    $vars['content']['links']['node']['#links']['node-readmore']['title'] = t('View more');
  }
  $autor = user_load($vars['uid']);
  if (!empty($autor->picture->uri)) {
    $userpic = $autor->picture->uri;
  }
  else {
    $userpic = file_build_uri(DEFAULT_USER_PICTURE_PATH);
  }
  $vars['user_picture'] = '<span class="user-picture">' . theme('image_style', array('path' => $userpic, 'style_name' => 'node_userpic')) . '</span>';
  $vars['notitle'] = FALSE;
  if ($vars['node']->nid == '5363' || $vars['node']->nid == '5362') {
    $vars['notitle'] = TRUE;
    $vars['title'] = '';
    $vars['user_picture'] = '';
  }
  
  // @see #3796: add template for solutions pages
  
  if (is_solutions()) {
    $base = 'node';
    $delimiter = '__';
    $vars['theme_hook_suggestions'][] = $base . $delimiter . 'solutions';
  }

}

function airtribune2_process_node(&$vars) {

  $vars['event_blog'] = FALSE;
  $account = profile2_load_by_user($vars['node']->uid, 'main');

  //print drupal_get_path_alias();

  $vars['full_name'] = get_full_name($account);

  if (is_solutions()) {
    $vars['notitle'] = TRUE;
    $vars['title'] = '';
    $vars['user_picture'] = '';
    $vars['display_submitted'] = '';
    $vars['no_posted_text'] = TRUE;
  }

  /* If view mode is event_blog_teaser */

  if ($vars['view_mode'] == 'event_blog_teaser') {
    $vars['event_blog'] = TRUE;
    $og_items = field_get_items('node', $vars['node'], 'og_group_ref');
    $node_path = 'event/' . $og_items[0]['target_id'] . '/blog/' . $vars['node']->nid;
    $vars['title'] = l($vars['title'], $node_path, array('html' => TRUE));

    /* Changing the style of the output image */

    if (!empty($vars['content']['field_image'])) {
      $vars['content']['field_image'] = _airtribune2_img_dinamic_scaling_event_blog_teaser($vars['content']['field_image']);
    }

    /* Read more link */

    $vars['content']['links']['node-readmore'] = array(
      '#theme' => 'links__node__node',
      '#links' => array(
        'node-readmore' => array(
          'title' => l(t('View more'), $node_path),
          'html' => TRUE,
        ),
      ),
    );

    /* Disqus comment counter */

    if (drupal_get_path('module', 'disqus')) {
      $vars['content']['links']['disqus'] = array(
        '#theme' => 'links',
        '#links' => array(
          'disqus_comments_num' => array(
            'title' => 'Comments',
            'href' => 'node/' . $vars['node']->nid,
            'fragment' => 'disqus_thread',
            'attributes' => array(
              'data-disqus-identifier' => 'node/' . $vars['node']->nid,
            ),
          ),
        ),
        '#attributes' => array(
          'class' => array('links', 'inline'),
        ),
      );
      $vars['content']['links']['#attached']['js'][] = drupal_get_path('module', 'disqus') . '/disqus.js';
      $vars['content']['links']['#attached']['js'][] = array(
        'data' => array('disqusComments' => $vars['node']->disqus['domain']),
        'type' => 'setting',
      );
    }
    $vars['classes'] .= ' node-teaser';
  }

  /* activity & accommodation */
  elseif ($vars['node']->type == 'activity' || $vars['node']->type == 'accommodation') {
    // Display submitted only node page
    if (!$vars['page']) {
      $vars['notitle'] = TRUE;
      $vars['title'] = '';
      $vars['user_picture'] = '';
      $vars['display_submitted'] = '';
    }
    else {
      _airtribune2_add_created($vars);
    }
    if (!empty($vars['content']['body'])) {
      $vars['content']['body']['#prefix'] = '<h2 class="field_title">' . $vars['content']['body']['#title'] . '</h2>';
    }
    if (!empty($vars['content']['field_address'])) {
      $vars['content']['field_address']['#prefix'] = '<h2 class="field_title">' . t('Contacts') . '</h2>';
    }
  }


  /**
   *  paragliding scoring category
   *
   * @see #3265
   * @author Vyacheslav Malchik <info@vkey.biz>
   */
  elseif ($vars['node']->type == 'pg_scoring_category') {
    $view_mode = 'event_details_page';
    // @TODO: remove use arg()
    if (arg(0) == 'event' && arg(2) == 'info' && arg(3) != 'details') {
      // Change view mode on info page
      $view_mode = 'event_info_page';
    }

    if (isset($vars['content']['field_collection_sponsors'])) {
      // Return to the node tpl array of field collection items
      $field_collection_items = _airtribune2_field_collection_as_array($vars['content']['field_collection_sponsors'], $view_mode);
      $vars['content']['sponsors'] = $field_collection_items;
    }
  }

  /* If teaser */
  elseif ($vars['teaser']) {
    $vars['user_picture'] = FALSE;
    $vars['display_submitted'] = FALSE;
    $vars['content']['links']['created'] = array(
      '#theme' => 'links__node__node',
      '#links' => array(
        'node-create' => array(
          'title' => format_date($vars['created'], 'custom', 'd M, Y'),
        ),
      ),
    );

    if (!empty($vars['content']['field_single_image']['#items'])) {
      // If single image is set, then hide image field.
      unset($vars['content']['field_image']);
    }
    elseif (!empty($vars['content']['field_image']['#items'])) {
      $vars['content']['field_image']['#items'] = array($vars['content']['field_image']['#items'][0]);
    }
  }

  /* Change of specific nodes */
  elseif ($vars['node']->nid != '5363' && $vars['node']->nid != '5362') {
    if (empty($vars['no_posted_text'])){
      _airtribune2_add_created($vars);
    }
    if (!empty($vars['content']['field_image'])) {
      $vars['content']['field_image'] = _airtribune2_img_dinamic_scaling($vars['content']['field_image']);
    }

    if ($vars['type'] == 'newsblog') {
      $vars['page'] = TRUE;
    }
  }
  if (!$vars['notitle'] && empty($vars['title'])) {
    if (!empty($vars['title_original'])) {
      $vars['title'] = $vars['title_original'];
    }
    else {
      $vars['title'] = 'Верните заголовки емае';
    }
  }
  $vars['classes'] .= ' node_view_mode_' . $vars['view_mode'];
}

/**
 *  Get field collection field value as array of fc items
 *
 * @see #3265
 * @author Vyacheslav Malchik <info@vkey.biz>
 */
function _airtribune2_field_collection_as_array($fc, $view_mode = 'full') {
  $field_collection_items = array();
  if (isset($fc[0])) {
    foreach ($fc['#items'] as $delta => $data) {
      // Render item with custom view mode
      $item = entity_view('field_collection_item', array(field_collection_field_get_entity($fc['#items'][$delta])), $view_mode);
      $field_collection_items[] = $item['field_collection_item'][$data['value']];
    }
    return $field_collection_items;
  }
}

/**
 * Add author and date to 'created' node links array
 */
function _airtribune2_add_created(&$vars) {
  $vars['content']['links']['created'] = array(
    '#theme' => 'links__node__node',
    '#links' => array(
      'node-create' => array(
        'title' => t('Posted by !user on !date', array('!user' => $vars['full_name'], '!date' => format_date($vars['created'], 'custom', 'd M, Y'))),
        'html' => TRUE,
      ),
    ),
  );
}

/**
 * Implements theme_menu_link().
 */
function airtribune2_menu_link__footer_menu(&$vars) {
  $element = $vars['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  if (!empty($element['#localized_options']['attributes']['title'])) {
    $output .= '<div>' . $element['#localized_options']['attributes']['title'] . '</div>';
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function airtribune2_menu_link__account(&$vars) {
  $element = $vars['element'];
  $sub_menu = '';
  if ($element['#below']) {
    $sub_menu = drupal_render($element['#below']);
  }
  if (!empty($element['#localized_options']['attributes']['class'])) {
    $element['#attributes']['class'] = array_merge($element['#attributes']['class'], $element['#localized_options']['attributes']['class']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  if (!empty($element['#localized_options']['attributes']['title'])) {
    $output .= '<div>' . $element['#localized_options']['attributes']['title'] . '</div>';
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

function airtribune2_menu_tree__menu_solutions_organizers(&$vars) {
  return '<ul class="tabs primary menu">' . $vars['tree'] . '</ul>';
}

function airtribune2_menu_tree__menu_service_rules(&$vars) {
  return '<ul class="tabs primary menu">' . $vars['tree'] . '</ul>';
}

/**
 * Implements hook_form_alter().
 */
function airtribune2_form_alter(&$form, $form_state, $form_id) {
  $form_id_ar = array('og_ui_confirm_subscribe', 'user_register_form', 'user_login', 'user_pass', 'user_profile_form', 'profile2_edit_pilot_form', 'airtribune_event_settings_form', 'at_reg_team_form', /*'views_form_paragliding_pilots_list_manage'*/);
  if (in_array($form_id, $form_id_ar)) {
    $form['#attached']['js'][] = 'sites/all/themes/airtribune2/js/jquery.mousewheel.min.js';
    $form['#attached']['js'][] = 'sites/all/themes/airtribune2/js/jquery.jscrollpane.min.js';
    $form['#attached']['js'][] = 'sites/all/themes/airtribune2/js/jquery.forms.js';
    $form['#attached']['js'][] = 'sites/all/themes/airtribune2/js/forms_action.js';
  }
  switch ($form_id) {
    case 'user_login_block':

      $form['name']['#attributes']['rel'] = t('Enter your e-mail');
      unset($form['name']['#title']);
      $form['pass']['#attributes']['rel'] = t('Enter your password');
      unset($form['pass']['#title']);
      $form['actions']['submit']['#value'] = t('Go');
      $form['actions']['#weight'] = 89;
      $form['hybridauth']['#weight'] = 79;

      $items = array();
      $items[] = l(t('Request new password'), 'user/password', array('attributes' => array('title' => t('Request new password via e-mail.'))));
      if (variable_get('user_register', USER_REGISTER_VISITORS_ADMINISTRATIVE_APPROVAL)) {
        $reg_attrs = array('attributes' => array(
            'class' => array('user_register_button'),
            'title' => t('Create a new user account.'),
          ),
        );
        $items[] = l(t('Register new user'), 'user/register', $reg_attrs);
      }
      $form['links'] = array(
        '#markup' => theme('item_list', array('items' => $items)),
        '#weight' => 100,
      );
      break;

    case 'user_register_form':
      if (isset($form_state['multiform'])) {
        $form['#theme'] = array('user_register_form_multiform');
        // Address field
        $lang = $form['profile_pilot']['field_address']['#language'];
        $form['profile_pilot']['field_address'][$lang][0]['country']['#title'] = t('Nation');
        $form['profile_pilot']['field_address'][$lang][0]['street_block']['premise']['#printed'] = TRUE;
        $form['profile_pilot']['field_address'][$lang][0]['street_block']['thoroughfare']['#title'] = t('Address');
      }
      // Email
      $form['account']['mail']['#title'] = t('Email');
      $form['account']['mail']['#description'] = t('This will be your login.');
      $form['account']['mail']['#attributes']['rel'] = t('Enter your email');
      $form['account']['pass']['pass1']['#attributes']['rel'] = t('Enter your password');
      $form['account']['pass']['pass1']['#description'] = t('Minimum 6 characters.');
      $form['account']['pass']['pass2']['#attributes']['rel'] = t('Repeat your password');
      break;

    case 'user_login':
      unset($form['name']['#description']);
      $form['name']['#attributes']['rel'] = t('Enter your e-mail');
      unset($form['pass']['#description']);
      $form['pass']['#attributes']['rel'] = t('Enter your password');
      $form['hybridauth']['#prefix'] = '<div class="hybridauth_prefix">' . t('or') . '</div>';
      $form['hybridauth']['#weight'] = 89;
      $form['actions']['#weight'] = 79;
      break;

    case 'airtribune_event_settings_form':
      $lang = $form['field_take_offs']['#language'];
      $form['field_take_offs'][$lang]['#prefix'] .= '<div class="field-take-offs-title">' . $form['field_take_offs'][$lang]['#description'] . '</div>';
      unset($form['field_take_offs'][$lang]['#description']);

      $lang = $form['field_dates']['#language'];
      //$form['field_dates'][$lang][0]['#required'] = 1;
      //unset($form['field_dates'][$lang]['#title']);
      
      // unset($form['field_dates'][$lang][0]['#title']);
      //unset($form['field_dates'][$lang][0]['#entity']);
      // unset($form['field_dates'][$lang][1]['#entity']);
      //print_r($form['field_dates']);
      //print_r($form);
      break;
    case 'eck__entity__form_edit_ent_team_pg_nation_team':
      $form['submit']['#prefix'] = '<div class="form-actions">';
      $form['submit']['#suffix'] = '</div>';
      break;
  }
}

function airtribune2_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';

    $output .= '<div class="breadcrumb">' . implode(' &rarr; ', $breadcrumb) . '</div>';
    return $output;
  }
}

function _airtribune2_img_dinamic_scaling($vars) {

  $count = count($vars['#items']);
  $excess = $count - 3 * floor($count / 3);
  $image_style_other = 'node_image_third';
  if ($count % 3 == 0) {
    $image_styles = array('node_image_first', 'node_image_second', 'node_image_second');
  }
  elseif ($excess == 2) {
    $image_styles = array('node_image_second', 'node_image_second');
  }
  else {
    $image_styles = array('node_image_first');
  }
  $is_count = 0;
  foreach ($vars['#items'] as $k => $v) {
    if (!empty($image_styles[$is_count])) {
      $image_style = $image_styles[$is_count];
    }
    else {
      $image_style = $image_style_other;
    }
    if ($vars[$k]['#theme'] != 'colorbox_image_formatter') {
      $vars[$k]['#image_style'] = $image_style;
    }
    else {
      $vars[$k]['#display_settings']['colorbox_node_style'] = $image_style;
    }
    $is_count++;
  }
  return $vars;
}

function _airtribune2_img_dinamic_scaling_event_blog_teaser($vars) {
  $count = count($vars['#items']);
  //$excess = $count-3*floor($count/3);
  //$image_style_other = 'node_image_third';
  switch ($count) {
    case 1:
      $image_styles = array('event_blog_teaser_first');
      break;

    case 2:
      $image_styles = array('event_blog_teaser_second');
      break;

    case 3:
      $image_styles = array('event_blog_teaser_third', 'event_blog_teaser_fourth');
      break;

    case 4:
      $image_styles = array('event_blog_teaser_fifth', 'event_blog_teaser_sixth');
      break;

    case 5:
      $image_styles = array('event_blog_teaser_first', 'event_blog_teaser_sixth_extra', 'event_blog_teaser_sixth_extra', 'event_blog_teaser_sixth');
      break;

    case 6:
      $image_styles = array('event_blog_teaser_second', 'event_blog_teaser_second', 'event_blog_teaser_sixth_extra', 'event_blog_teaser_sixth', 'event_blog_teaser_sixth_extra', 'event_blog_teaser_sixth');
      break;

    case 7:
      $image_styles = array('event_blog_teaser_first', 'event_blog_teaser_seventh');
      break;

    case 8:
      $image_styles = array('event_blog_teaser_second', 'event_blog_teaser_second', 'event_blog_teaser_seventh');
      break;

    case 9:
      $image_styles = array('event_blog_teaser_third', 'event_blog_teaser_fourth', 'event_blog_teaser_fourth', 'event_blog_teaser_seventh');
      break;

    default:
      $image_styles = array('event_blog_teaser_first', 'event_blog_teaser_eighth');
      break;
  }
  $is_count = 0;
  foreach ($vars['#items'] as $k => $v) {
    if (!empty($image_styles[$is_count])) {
      $image_style = $image_style_other = $image_styles[$is_count];
    }
    else {
      $image_style = $image_style_other;
    }
    if ($vars[$k]['#theme'] != 'colorbox_image_formatter') {
      $vars[$k]['#image_style'] = $image_style;
    }
    else {
      $vars[$k]['#display_settings']['colorbox_node_style'] = $image_style;
    }
    $is_count++;
  }
  //print_r($vars[0]);
  return $vars;
}

/**
 * Implements theme_pager().
 */
function airtribune2_pager($variables) {
  $tags = $variables['tags'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $quantity = $variables['quantity'];
  global $pager_page_array, $pager_total;

  // Calculate various markers within this pager piece:
  // Middle is used to "center" pages around the current page.
  $pager_middle = ceil($quantity / 2);
  // current is the page we are currently paged to
  $pager_current = $pager_page_array[$element] + 1;
  // first is the first page listed by this pager piece (re quantity)
  $pager_first = $pager_current - $pager_middle + 1;
  // last is the last page listed by this pager piece (re quantity)
  $pager_last = $pager_current + $quantity - $pager_middle;
  // max is the maximum page number
  $pager_max = $pager_total[$element];
  // End of marker calculations.

  // Prepare for generation loop.
  $i = $pager_first;
  if ($pager_last > $pager_max) {
    // Adjust "center" if at end of query.
    $i = $i + ($pager_max - $pager_last);
    $pager_last = $pager_max;
  }
  if ($i <= 0) {
    // Adjust "center" if at start of query.
    $pager_last = $pager_last + (1 - $i);
    $i = 1;
  }
  // End of generation loop preparation.

  $li_first = theme('pager_first', array('text' => (isset($tags[0]) ? $tags[0] : t('« first')), 'element' => $element, 'parameters' => $parameters));
  $li_previous = theme('pager_previous', array('text' => ('<'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => ('>'), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_last = theme('pager_last', array('text' => $pager_max, 'element' => $element, 'parameters' => $parameters));

  if ($pager_total[$element] > 1) {
    if ($li_previous) {
      $items[] = array(
        'class' => array('pager-previous'),
        'data' => $li_previous,
      );
    }

    // When there is more than one page, create the pager list.
    if ($i != $pager_max) {
      if ($i > 1) {
        if ($li_first) {
          $items[] = array(
            'class' => array('pager-first'),
            'data' => $li_first,
          );
        }
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
      }
      // Now generate the actual pager piece.
      for (; $i <= $pager_last && $i <= $pager_max; $i++) {
        if ($i < $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_previous', array('text' => $i, 'element' => $element, 'interval' => ($pager_current - $i), 'parameters' => $parameters)),
          );
        }
        if ($i == $pager_current) {
          $items[] = array(
            'class' => array('pager-current'),
            'data' => '<span><span>' . $i . '</span></span>',
          );
        }
        if ($i > $pager_current) {
          $items[] = array(
            'class' => array('pager-item'),
            'data' => theme('pager_next', array('text' => $i, 'element' => $element, 'interval' => ($i - $pager_current), 'parameters' => $parameters)),
          );
        }
      }
      if ($i < $pager_max) {
        $items[] = array(
          'class' => array('pager-ellipsis'),
          'data' => '…',
        );
        if ($li_last) {
          $items[] = array(
            'class' => array('pager-last'),
            'data' => $li_last,
          );
        }
      }
    }
    // End generation.

    if ($li_next) {
      $items[] = array(
        'class' => array('pager-next'),
        'data' => $li_next,
      );
    }
    return '<h2 class="element-invisible">' . t('Pages') . '</h2>' . theme('item_list', array(
        'items' => $items,
        'attributes' => array('class' => array('pager')),
      ));
  }
}

/**
 * Implements theme_pager().
 */
function airtribune2_pager_link($variables) {
  $text = $variables['text'];
  $page_new = $variables['page_new'];
  $element = $variables['element'];
  $parameters = $variables['parameters'];
  $attributes = $variables['attributes'];

  $page = isset($_GET['page']) ? $_GET['page'] : '';
  if ($new_page = implode(',', pager_load_array($page_new[$element], $element, explode(',', $page)))) {
    $parameters['page'] = $new_page;
  }

  $query = array();
  if (count($parameters)) {
    $query = drupal_get_query_parameters($parameters, array());
  }
  if ($query_pager = pager_get_query_parameters()) {
    $query = array_merge($query, $query_pager);
  }

  // Set each pager link title
  if (!isset($attributes['title'])) {
    static $titles = NULL;
    if (!isset($titles)) {
      $titles = array(
        t('<') => t('Go to first page'),
        t('‹ previous') => t('Go to previous page'),
        t('>') => t('Go to next page'),
        t('last »') => t('Go to last page'),
      );
    }
    if (isset($titles[$text])) {
      $attributes['title'] = $titles[$text];
    }
    elseif (is_numeric($text)) {
      $attributes['title'] = t('Go to page @number', array('@number' => $text));
    }
  }

  // @todo l() cannot be used here, since it adds an 'active' class based on the
  //   path only (which is always the current path for pager links). Apparently,
  //   none of the pager links is active at any time - but it should still be
  //   possible to use l() here.
  // @see http://drupal.org/node/1410574
  $attributes['href'] = url($_GET['q'], array('query' => $query));
  return '<a' . drupal_attributes($attributes) . '><span>' . check_plain($text) . '</span></a>';
}

/**
 * Implements_preprocess_entity().
 */
function airtribune2_preprocess_entity(&$variables) {

  if (isset($variables['field_collection_item']) && $variables['field_collection_item']->field_name == 'field_collection_organizers' && $variables['view_mode'] == 'event_info_page') {
    if (arg(0) == 'event' && !empty($variables['content']['field_organizer_logo'])) {
      //print_r($variables['field_collection_item']);
      $variables['content']['field_organizer_logo'][0] = array(
        //'#markup' => l(render($variables['content']['field_organizer_logo'][0]), $variables['field_collection_item']->field_url['und'][0]['url'], array('html' => true, 'attributes' => array('target'=>'_blank'))),
        '#markup' => l(render($variables['content']['field_organizer_logo'][0]), 'event/' . arg(1) . '/info/details', array('html' => TRUE, 'fragment' => 'organizer_' . $variables['field_collection_item']->item_id)),
      );
    }
  }

  // See http://drupal.org/node/1462772
  /*
  foreach($variables['theme_hook_suggestions'] as &$suggestion) {
    $suggestion = 'entity__' . $suggestion;
  }
  */
}

/**
 * Implements theme_field__field_collection_organizers.
 */
function airtribune2_field__field_collection_organizers($variables) {
  //print_r($variables);
  $output = '';
  $colon = ':&nbsp;';
  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<span class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . $colon . '</span';
  }

  // Render the items.
  $output .= '<span class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    //print_r(array_keys($item['entity']['field_collection_item']));
    if (!empty($item['entity']['field_collection_item'])) {
      $org = array_keys($item['entity']['field_collection_item']);
      $output .= '<a id="organizer_' . $org[0] . '"></a>';
    }
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<span class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>';
    //$render_item = drupal_render($item);
    $output .= drupal_render($item) . '</span>';
  }
  $output .= '</span>';

  // Render the top-level DIV.
  $output = '<span class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</span>';

  return $output;
}

/**
 * Implements theme_field__field_full_name.
 */
function airtribune2_field__field_full_name($variables) {
  if ($variables['field_view_mode'] == '_custom_display') {
    return drupal_render($item);
  }
  $output = '';
  $colon = ':&nbsp;';
  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . $colon . '</div>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

  return $output;
}

/**
 * Render a container for a set of address fields.
 */
function airtribune2_addressfield_container($variables) {
  $element = $variables['element'];

  $element['#children'] = trim($element['#children']);
  if (strlen($element['#children']) > 0) {
    $element['#tag'] = 'span';
    $output = '<' . $element['#tag'] . drupal_attributes($element['#attributes']) . '> ';
    $output .= $element['#children'];
    $output .= '</' . $element['#tag'] . ">";
    return $output;
  }
  else {
    return '';
  }
}

/**
 * Implements theme_link_formatter_link_default.
 */
function airtribune2_link_formatter_link_default($vars) {
  $link_options = $vars['element'];
  unset($link_options['element']['title']);
  unset($link_options['element']['url']);

  /**
   * Add prefix for sponsor's link
   * @see #3265, #3269
   */
  $prefix = '';
  if ($vars['field']['bundle'] == 'field_collection_sponsors' && $vars['field']['field_name'] == 'field_url') {
    $prefix = '<span>' . t('Prizes by') . '</span>';
  }

  // Issue #1199806 by ss81: Fixes fatal error when the link URl is equal to page URL
  if (isset($link_options['attributes']['class'])) {
    $link_options['attributes']['class'] = array($link_options['attributes']['class']);
  }

  // Display a normal link if both title and URL are available.
  if (!empty($vars['element']['title']) && !empty($vars['element']['url'])) {
    return $prefix . l($vars['element']['title'], $vars['element']['url'], $link_options);
  }
  // If only a title, display the title.
  elseif (!empty($vars['element']['title'])) {
    return $prefix . check_plain($vars['element']['title']);
  }
  elseif (!empty($vars['element']['url'])) {
    return $prefix . l($vars['element']['title'], $vars['element']['url'], $link_options);
  }
}

/**
 * Implements theme_field__field_full_name.
 */
function airtribune2_field($variables) {
  $element = $variables['element'];
  //print $variables['element']['#field_name'];
  $variables['suffix'] = $variables['prefix'] = '';
  $colon = ':&nbsp;';
  switch ($variables['element']['#field_name']) {
    case 'field_price_single':
    case 'field_price_double':

      $colon = '&nbsp;';
      $variables['classes'] .= ' field_buttons';
      $currency = field_view_field('node', $element['#object'], 'field_price_currency');
      //print_r($currency);
      if (isset($variables['items'][0], $currency)) {
        $variables['items'][0]['#suffix'] = ' ' . $currency[0]['#markup'];
      }
      break;

    case 'field_hotel_wifi':
      $colon = ':&nbsp;';
      $variables['field_view_mode'] = '';
      $variables['label_hidden'] = '';
      $variables['classes'] .= ' field_buttons';

      if ($variables['element']['#field_name'] == 'field_hotel_wifi' && empty($variables['element']['#items'][0]['value'])) {
        $variables['classes'] .= ' field_wifi_no';
      }
      break;

    case 'field_address':
      $variables['label'] = t('Address');
      $variables['items'][0]['locality_block']['locality']['#prefix'] = '';
    case 'field_email':
    case 'field_phone':
    case 'field_url':
      $variables['field_view_mode'] = '';
      $variables['classes'] .= ' fields_contacts';
      break;

    case 'field_gt_plane':
    case 'field_gt_train':
    case 'field_gt_car':
    case 'field_gt_bus':
    case 'field_gt_taxi':
      if (!arg(3)) {
        list(, , $key) = explode('_', $variables['element']['#field_name']);
        $contest_id = (int) arg(1);
        $variables['items'][0]['#markup'] = l(
          t(ucfirst($key)),
          'event/' . $contest_id . '/info/details',
          array(
            'fragment' => 'gt_' . $key,
            'attributes' => array('class' => array($key)),
          )
        );
      }
      elseif (arg(3)) {
        $variables['prefix'] = '<a id="' . str_replace('field_', '', $variables['element']['#field_name']) . '"></a>';
        $colon = '';
        $variables['classes'] .= ' transport-icon';
      }
      break;

    default:
      //print $variables['element']['#field_name'];
      # code...
      break;
  }

  $output = '';
  // Render the label, if it's not hidden.
  if (!$variables['label_hidden']) {
    $output .= '<div class="field-label"' . $variables['title_attributes'] . '>' . $variables['label'] . $colon . '</div>';
  }

  // Render the items.
  $output .= '<div class="field-items"' . $variables['content_attributes'] . '>';
  foreach ($variables['items'] as $delta => $item) {
    $classes = 'field-item ' . ($delta % 2 ? 'odd' : 'even');
    $output .= '<div class="' . $classes . '"' . $variables['item_attributes'][$delta] . '>' . drupal_render($item) . '</div>';
  }
  $output .= '</div>';

  // Render the top-level DIV.
  $output = $variables['prefix'] . '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>' . $variables['suffix'];

  return $output;
}

/**
 * Implements hook_theme().
 */
function airtribune2_theme() {
  return array(
    'user_register_form' => array(
      'render element' => 'form',
      'template' => 'templates/user-register-form',
    ),
    'contest_registration_multiform' => array(
      'render element' => 'form',
      'template' => 'templates/contest-registration-multiform',
    ),
    'og_ui_confirm_subscribe' => array(
      'render element' => 'form',
      'template' => 'templates/contest-registration',
    ),
    'user_profile_form' => array(
      'render element' => 'form',
      'template' => 'templates/user-profile-form',
    ),
    'profile2_edit_pilot_form' => array(
      'render element' => 'form',
      'template' => 'templates/profile2-edit-pilot-form',
    ),
    
    'contest_registration_anonymous' => array(
      'render element' => 'form',
      'template' => 'templates/contest-registration-anonymous',
    ),
    'contest_registration_authorized' => array(
      'render element' => 'form',
      'template' => 'templates/contest-registration-authorized',
    ),
  );
}

/**
 * Implements theme_file_icon.
 */
function airtribune2_file_icon($variables) {
  $icons = array(
    'dem' => 'dem.png',
    'doc' => 'doc.png',
    'docx' => 'docx.png',
    'jpg' => 'jpg.png',
    'lkm' => 'lkm.png',
    'odc' => 'odc.png',
    'odt' => 'odt.png',
    'pdf' => 'pdf.png',
    'png' => 'png.png',
    'tpl' => 'tpl.png',
    'txt' => 'txt.png',
    'wpt' => 'wpt.png',
    'xcm' => 'xcm.png',
    'xls' => 'xls.png',
    'xlsx' => 'xlsx.png',
    'CompeGPS' => 'compegps.png',
    'KML' => 'kml.png',
    'kml' => 'kml.png',
    'SeeYou' => 'seeyou.png',
    'cup' => 'seeyou.png',
    'UTM' => 'utm.png',
    'GEO' => 'geo.png',
    'OZI' => 'ozi.png',
  );
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $mime = check_plain($file->filemime);
  $path_info = pathinfo($file->filename);
  $extension_desc = '';
  if (isset($file->description)) {
    $extension_desc = str_replace(array('Waypoints', ' ', '(', ')'), '', $file->description);
  }
  if ($path_info['extension'] == 'wpt' && isset($icons[$extension_desc])) {
    $icon_url = '/' . path_to_theme() . '/images/icons/' . $icons[$extension_desc];
  }
  elseif (!empty($icons[$path_info['extension']])) {
    $icon_url = '/' . path_to_theme() . '/images/icons/' . $icons[$path_info['extension']];
  }
  else {
    $icon_url = file_icon_url($file, $icon_directory);
  }
  return '<img class="file-icon" alt="" title="' . $mime . '" src="' . $icon_url . '" />';
}

/**
 * Preprocess field.tpl.php
 */
function airtribune2_preprocess_field(&$vars) {

  $element = $vars['element'];
  if ($element['#field_name'] == AIRTRIBUNE_AWARDS_PHOTOS_FIELD) {
    $categories = airtribune_prize_categories();
    foreach ($vars['items'] as $delta => $item) {
      if (isset($categories[$item['#item']['title']])) {
        $vars['items'][$delta]['#item']['title'] = $categories[$item['#item']['title']];
        $vars['items'][$delta]['#suffix'] = $categories[$item['#item']['title']];
      }
    }
  }
}

/**
 * Implements theme_preprocess_openlayers_map.
 */
function airtribune2_preprocess_openlayers_map(&$variables, $hook) {
  drupal_add_js('sites/all/themes/airtribune2/js/FramedCloud.js');
  // Enable zoom wheel only after click on the map.
  drupal_add_js('sites/all/themes/airtribune2/js/ol.js');
}

/**
 * Implements hook_js_alter().
 */
function airtribune2_js_alter(&$javascript) {
  // Fix script weight.
  $nav_path = drupal_get_path('module', 'openlayers') . '/plugins/behaviors/openlayers_behavior_navigation.js';
  $oj_path = drupal_get_path('theme', 'airtribune2') . '/js/ol.js';
  if (isset($javascript[$nav_path]) && isset($javascript[$oj_path])) {
    $javascript[$oj_path]['weight'] = $javascript[$nav_path]['weight'] + 0.001;
  }
}

/**
 * Implements hook_tablesort_indicator().
 */
function airtribune2_tablesort_indicator($variables) {
  if ($variables['style'] == "asc") {
    //theme('image', array('path' => 'misc/arrow-asc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort ascending'), 'title' => t('sort ascending')));
    return '<span class="arrow_sort arrow-asc" title="' . t('sort ascending') . '"></span>';
  }
  else {
    //theme('image', array('path' => 'misc/arrow-desc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort descending'), 'title' => t('sort descending')));
    return '<span class="arrow_sort arrow-desc" title="' . t('sort descending') . '"></span>';
  }
}

/**
 * Implements theme_colorbox_image_formatter().
 */
function airtribune2_colorbox_image_formatter($variables) {

  $item = $variables['item'];
  $entity_type = $variables['entity_type'];
  $entity = $variables['entity'];
  $field = $variables['field'];
  $settings = $variables['display_settings'];
  $items_obj = $entity->$field['field_name'];

  $image = array(
    'path' => $item['uri'],
    'alt' => $item['alt'],
    'title' => $item['title'],
    'style_name' => $settings['colorbox_node_style'],
  );

  if (isset($item['width']) && isset($item['height'])) {
    $image['width'] = $item['width'];
    $image['height'] = $item['height'];
  }

  $entity_title = entity_label($entity_type, $entity);

  switch ($settings['colorbox_caption']) {
    case 'auto':
      // If the title is empty use alt or the entity title in that order.
      if (!empty($image['title'])) {
        $caption = $image['title'];
      }
      elseif (!empty($image['alt'])) {
        $caption = $image['alt'];
      }
      elseif (!empty($entity_title)) {
        $caption = $entity_title;
      }
      else {
        $caption = '';
      }
      break;

    case 'title':
      $caption = $image['title'];
      break;

    case 'alt':
      $caption = $image['alt'];
      break;

    case 'node_title':
      $caption = $entity_title;
      break;

    case 'custom':
      $caption = token_replace($settings['colorbox_caption_custom'], array($entity_type => $entity, 'file' => (object) $item), array('clear' => TRUE));
      break;

    default:
      $caption = '';
  }

  // Shorten the caption for the example styles or when caption shortening is active.
  $colorbox_style = variable_get('colorbox_style', 'default');
  $trim_length = variable_get('colorbox_caption_trim_length', 75);
  if (((strpos($colorbox_style, 'colorbox/example') !== FALSE) || variable_get('colorbox_caption_trim', 0)) && (drupal_strlen($caption) > $trim_length)) {
    $caption = drupal_substr($caption, 0, $trim_length - 5) . '...';
  }

  // Build the gallery id.
  list($id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
  $entity_id = !empty($id) ? $entity_type . '-' . $id : 'entity-id';
  switch ($settings['colorbox_gallery']) {
    case 'post':
      $gallery_id = 'gallery-' . $entity_id;
      break;

    case 'page':
      $gallery_id = 'gallery-all';
      break;

    case 'field_post':
      $gallery_id = 'gallery-' . $entity_id . '-' . $field['field_name'];
      break;

    case 'field_page':
      $gallery_id = 'gallery-' . $field['field_name'];
      break;

    case 'custom':
      $gallery_id = $settings['colorbox_gallery_custom'];
      break;

    default:
      $gallery_id = '';
  }

  if ($style_name = $settings['colorbox_image_style']) {
    $path = image_style_url($style_name, $image['path']);
  }
  else {
    $path = file_create_url($image['path']);
  }

  $count = count($items_obj['und']);

  return theme('colorbox_imagefield', array('image' => $image, 'path' => $path, 'title' => $caption, 'gid' => $gallery_id, 'count' => $count));
}

/**
 * Implements theme_colorbox_image_field().
 */
function airtribune2_colorbox_imagefield($variables) {

  $count = $variables['count'];
  static $counter;
  $gid = $variables['gid'];

  if ($counter == NULL) {
    $counter['contest_photos'] = $counter['flying_site_photos'] = 0;
    $counter['contest_photos_details'] = $counter['flying_site_photos_details'] = 0;
  }

  if (isset($counter[$gid])) {
    $counter[$gid]++;
    // if ($gid == 'contest_photos_details') {
    //   $hidden = $counter[$gid] > 4;
    // }
    // elseif ($gid == 'flying_site_photos_details') {
    //   $hidden = $counter[$gid] > 8;
    // }
    if (
      $count < 4 ||
      ($count < 8 && $counter[$gid] > 4) ||
      $counter[$gid] > 8
    ) {
      $hidden = TRUE;
    }
    else {
      $hidden = FALSE;
    }
    $gid = 'contest-gallery';
  }
  else {
    $hidden = FALSE;
  }

  $class = array('colorbox');
  if ($hidden) {
    $image = '';
    $class[] = 'js-hide';
  }
  elseif (!empty($variables['image']['style_name'])) {
    $image = theme('image_style', $variables['image']);
  }
  else {
    $image = theme('image', $variables['image']);
  }

  $options = array(
    'html' => TRUE,
    'attributes' => array(
      'title' => $variables['title'],
      'class' => implode(' ', $class),
      'rel' => $gid,
    ),
  );


  return l($image, $variables['path'], $options);
}

/**
 * Implements theme_form_element_label().
 */
function airtribune2_form_element_label($variables) {
  $element = $variables['element'];
  // This is also used in the installer, pre-database setup.
  $t = get_t();

  // If title and required marker are both empty, output no label.
  if ((!isset($element['#title']) || $element['#title'] === '') && empty($element['#required'])) {
    return '';
  }

  // If the element is required, a required marker is appended to the label.
  $required = !empty($element['#required']) ? theme('form_required_marker', array('element' => $element)) : '';

  $title = filter_xss_admin($element['#title']);

  $attributes = array();
  // Style the label as class option to display inline with the element.
  if ($element['#title_display'] == 'after') {
    $attributes['class'] = 'option';
  }
  // Show label only to screen readers to avoid disruption in visual flows.
  elseif ($element['#title_display'] == 'invisible') {
    $attributes['class'] = 'element-invisible';
  }

  if (!empty($element['#id'])) {
    $attributes['for'] = $element['#id'];
  }

  // Style checkbox labels for take-offs, see #3848
//  if (strpos($element['#id'], 'edit-field-take-offs') !== FALSE) {
//    $title = l($title, '/ent_basicmark/pg_takeoff/' . $element['#return_value']);
//  }
  // The leading whitespace helps visually separate fields from inline labels.
  return ' <div class="inline-label"><label' . drupal_attributes($attributes) . '>' . $t('!title!required', array('!title' => str_replace(' <', '<', $title), '!required' => $required)) . "</label><span class=\"valign\"></span></div>\n";
}

/**
 * Implements theme_form_element().
 */
function airtribune2_form_element($variables) {
  $element = &$variables['element'];

  // This function is invoked as theme wrapper, but the rendered form element
  // may not necessarily have been processed by form_builder().
  $element += array(
    '#title_display' => 'before',
  );

  // Add element #id for #type 'item'.
  if (isset($element['#markup']) && !empty($element['#id'])) {
    $attributes['id'] = $element['#id'];
  }
  // Add element's #type and #name as class to aid with JS/CSS selectors.
  $attributes['class'] = array('form-item');
  if (!empty($element['#type'])) {
    $attributes['class'][] = 'form-type-' . strtr($element['#type'], '_', '-');
  }
  if (!empty($element['#name'])) {
    $attributes['class'][] = 'form-item-' . strtr($element['#name'], array(' ' => '-', '_' => '-', '[' => '-', ']' => ''));
  }
  // Add a class for disabled elements to facilitate cross-browser styling.
  if (!empty($element['#attributes']['disabled'])) {
    $attributes['class'][] = 'form-disabled';
  }
  $output = '<div' . drupal_attributes($attributes) . '>' . "\n";

  // If #title is not set, we don't display any label or required marker.
  if (!isset($element['#title'])) {
    $element['#title_display'] = 'none';
  }
  $prefix = isset($element['#field_prefix']) ? '<span class="field-prefix">' . $element['#field_prefix'] . '</span> ' : '';
  $suffix = isset($element['#field_suffix']) ? ' <span class="field-suffix">' . $element['#field_suffix'] . '</span>' : '';

  $date_prefix = $date_suffix = '';
  if (!empty($element['#extra_wrap'])){
    $date_prefix = '<div class="date_prefix">';
    $date_suffix = '</div>';
  }

  switch ($element['#title_display']) {
    case 'before':
    case 'invisible':
      $output .= ' ' . theme('form_element_label', $variables);
      $output .= ' ' . $date_prefix . $prefix . $element['#children'] . $suffix;
      break;

    case 'after':
      $output .= ' ' . $date_prefix . $prefix . $element['#children'] . $suffix . $date_suffix;
      $output .= ' ' . theme('form_element_label', $variables);
      $date_suffix = '';
      break;

    case 'none':
    case 'attribute':
      // Output no label and no required marker, only the children.
      $output .= ' ' . $date_prefix . $prefix . $element['#children'] . $suffix;
      break;
  }

  if (!empty($element['#description'])) {
    $output .= '<div class="description">' . $element['#description'] . "</div>" . $date_suffix;
  }
  //print_r($variables);
  $output .= "</div>\n";

  return $output;
}

/**
 * Implements hook_css_alter().
 */
function airtribune2_css_alter(&$css) {
  // Remove defaults.css file.
  //unset($css[drupal_get_path('module', 'system') . '/defaults.css']);
  unset($css[drupal_get_path('module', 'date') . '/date_api/date.css']);
}

/**
 * Implements theme_status_messages().
 */
function airtribune2_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
  );
  foreach (drupal_get_messages($display) as $type => $messages) {
    $output .= "<div class=\"messages $type\">\n";
    if (!empty($status_heading[$type])) {
      $output .= '<h2 class="element-invisible">' . $status_heading[$type] . "</h2>\n";
    }
    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= '<span>' . $messages[0] . '</span><span class="valign"></span>';
    }
    $output .= "</div>\n";
  }
  return $output;
}

/**
 * Implemetns hook_jcarousel_formatter_element_alter().
 */
function airtribune2_jcarousel_formatter_element_alter(&$element) {
  $element['#attached']['js'][] = drupal_get_path('theme', 'airtribune2') . '/js/jcarousel-circular.js';
  $element[0]['#options']['wrap'] = 'circular';
  $element[0]['#options']['start'] = 2;
}

/**
 * Implements hook_menu_local_tasks_alter().
 *
 * @see #2851
 */
function airtribune2_menu_local_tasks_alter(&$data, $router_item, $root_path) {
  if (isset($data['tabs'][0]['output'])) {
    foreach ($data['tabs'][0]['output'] as $index => $tab) {
      $path = $data['tabs'][0]['output'][$index]['#link']['path'];
      $path = str_replace('%/', '', $path);
      $path_array = explode("/", $path);
      $class = 'tab-'.implode("-", $path_array);
      $attributes = array('attributes' => array( 'class' => array($class)));
      $data['tabs'][0]['output'][$index]['#link']['localized_options'] = $attributes;
    }
  }
  if (isset($data['tabs'][1]['output'])) {
    // Hide tabs on map nodes.
    if ($root_path == 'event/%/map/%') {
      unset($data['tabs'][1]);
    }
    // Add unique CSS ID to each tab.
    else {
      $tabs = array('accommodations', 'activities', 'basic');
      foreach ($data['tabs'][1]['output'] as $index => $tab) {
        $id = arg(3, $tab['#link']['path']);
        if (in_array($id, $tabs)) {
          $data['tabs'][1]['output'][$index]['#link']['localized_options']['attributes']['id'] = $id . '-tab';
        }
      }
    }
  }
}

/**
 * Change canonical url for accommodation, activities, blog, from /event/123/map/456 to /node/456
 * Remove shortlink tag
 *
 * This allow:
 * 1. avoid duplicate content in search engines
 * 2. disqus module attach comment form, basics on canonical-url
 *
 * @autor Vasily Kraev
 * @see #2986
 */
function airtribune2_html_head_alter(&$head_elements) {
  global $base_url;
  if (arg(0) != 'event') {
    return;
  }
  $event_nid = arg(1);
  $node_nid = arg(3);
  if ((arg(2) == 'map' || arg(2) == 'blog') && $node_nid) {
    foreach ($head_elements as $key => $element) {
      // Metatag module canonical & shortlink links
      if (empty($element['#name'])) {
        return;
      }
      if ($element['#name'] == 'canonical') {
        $head_elements[$key]['#value'] = $base_url . '/' . drupal_get_path_alias('node/' . $node_nid);
      }
      if ($element['#name'] == 'shortlink') {
        unset($head_elements[$key]);
      }
      // core canonical & shortlink links, uncomment if
      // if (isset($element['#attributes']['rel'])) {
      //   if ($element['#attributes']['rel'] == 'canonical') {
      //     $head_elements[$key]['#attributes']['href'] = $base_url . '/' . drupal_get_path_alias('node/' . $node_nid);
      //   }
      //   if ($element['#attributes']['rel'] == 'shortlink') {
      //     unset($head_elements[$key]);
      //   }
      // }
    }
  }
}

/**
 * Preprocess theme_image_style().
 *
 * Add corresponding classes for scoring winner images.
 */
function airtribune2_preprocess_image_style(&$variables) {
  // Add extra classes for scoring_winner image_style images
  if ($variables['style_name'] == 'scoring_winner') {
    $variables['width'] >= $variables['height'];
    $variables['attributes']['class'][] = $variables['width'] >= $variables['height'] ? 'scoring-winner-horizontal' : 'scoring-winner-vertical';
  }
}

/**
 * Prerender hook_views_pre_render().
 *
 */
function airtribune2_views_pre_render(&$view) {
  static $live_events_day_nids = array();

  if ($view->name == 'frontpage_events') {
    drupal_add_js(drupal_get_path('theme', 'airtribune2') . '/js/frontpage.js');
    $standart = floor(count($view->result)/3) * 3;
    $deviant = count($view->result) - $standart;
    if ($deviant == 1) {
      $img_styles = array('frontpage_event_padding_once', 'event_logo_once');
      //$view->name .= '_once';
    }
    if ($deviant == 2) {
      $img_styles = array('frontpage_event_padding_twice', 'event_logo_twice');
      //$view->name .= '_twice';
    }
    // Output "show more events" button after view, if we have more, than 3 items.
    if (count($view->result) > 3) {
      $view->attachment_after = '<div class="frontpage-show-more-events">...</div>';
    }
    if (!empty($img_styles)) {
      $index = 1;
      foreach ($view->result as $key => $value) {
        if ($index > $standart) {
          $view->result[$key]->field_field_contest_photos[0]['rendered']['#image_style'] = $img_styles['0'];
          //$view->result[$key]->field_field_logo[0]['rendered']['#image_style'] = $img_styles['1'];
        }
        $index ++;
      }
    }
  }

  if ($view->name == 'frontpage_live_events' && (in_array($view->current_display, array('page', 'panel_pane_2')))) {

    drupal_add_js(drupal_get_path('theme', 'airtribune2') . '/js/frontpage.js');
    $standart = floor(count($view->result)/3) * 3;
    $deviant = count($view->result) - $standart;
    if ($deviant == 1) {
      $img_styles = array('frontpage_event_padding_once', 'event_logo_once');
      //$view->name .= '_once';
    }
    if ($deviant == 2) {
      $img_styles = array('frontpage_event_padding_twice', 'event_logo_twice');
      //$view->name .= '_twice';
    }
    // Output "show more events" button after view, if we have more, than 3 items.
    if (count($view->result) > 3) {
      // @todo: Add attachment for new Live Events block
      //~ $view->attachment_after = '<div class="frontpage-show-more-events">...</div>';
    }
    if (!empty($img_styles)) {
      $index = 1;
      foreach ($view->result as $key => $value) {
        if ($index > $standart) {
          $view->result[$key]->field_field_contest_photos[0]['rendered']['#image_style'] = $img_styles['0'];
          $view->result[$key]->field_field_image[0]['rendered']['#image_style'] = $img_styles['0'];
          //$view->result[$key]->field_field_logo[0]['rendered']['#image_style'] = $img_styles['1'];
        }
        $index ++;
      }
    }


    // store nids for last dayblog entry text trim (see below)
    foreach ($view->result as $key => $value) {
      $live_events_day_nids[] = $value->nid;
    }
  }

  // Last dayblog entry trim text
  if ($view->name == 'frontpage_live_events' && $view->current_display == 'panel_pane_1') {

    $current_nid = $view->args[0];
    $current_position = array_search($current_nid, $live_events_day_nids) + 1;
    $live_events_count = count($live_events_day_nids);

    $remainder = $current_position % 3;

    $max_lengths = array(
      'single' => 250,
      'double' => 125,
      'tripple' => 75,
    );

    if ($remainder == 0) {
      $max_length = $max_lengths['tripple'];
    }
    else {
      $current_row_elements_count = $live_events_count - $current_position + $remainder;
      if ($current_row_elements_count >= 3) {
        $max_length = $max_lengths['tripple'];
      }
      elseif ($current_row_elements_count == 2) {
        $max_length = $max_lengths['double'];
      }
      else {
        $max_length = $max_lengths['single'];
      }
    }
    $view->field['field_plain_body']->options['alter']['max_length'] = $max_length;
  }
}


function airtribune2_preprocess_views_view_fields(&$vars) {
  $view = $vars['view'];
  // Replace link to event with link to dayblog
  // @author Vyacheslav Malchik <info@vkey.biz>
  // @see #4261
  if ($view->name == 'frontpage_events' && $view->current_display == 'live_events_pane') {
    $href = $vars['fields']['view_1']->content;
    unset($vars['fields']['view_1']);
    // Remove tags
    $href = preg_replace("/<[^>]*>/", " ", $href);
    $href = trim(str_replace("  ", " ", $href));
    if (!empty($href)) {
      // Get raw path
      $href = explode('#', $href);
      // Get alias
      $href[0] = url($href[0]);
      $href = implode('#', $href);
      // Relace old path
      $pattern = '/href="(.*)"/';
      $replace = 'href=' . $href;
      $vars['fields']['nothing']->content = preg_replace($pattern, $replace, $vars['fields']['nothing']->content);
    }

    // Replace image
    // @see @4266
    if (trim(strip_tags($vars['fields']['nothing_1']->content,'<img>')) == '') {
      $vars['fields']['nothing_1']->content = $vars['fields']['field_contest_photos']->content;
    } else {
      $deviant = count($view->result);
      $img_styles = $img_styles_origin =  'frontpage_event_padding';
      if ($deviant == 1) {
        $img_styles = 'frontpage_event_padding_once';
      }
      if ($deviant == 2) {
        $img_styles = 'frontpage_event_padding_twice';
      }
      preg_match('/\/public\/([^?]*)/', $vars['fields']['nothing_1']->content, $matches);
      //image_style_url($img_styles, 'public://' . $matches[1]);
      $img = theme_image_style(array('style_name' => $img_styles, 'path' =>  'public://' . $matches[1], 'width' => NULL, 'height' => NULL));
      $vars['fields']['nothing_1']->content = preg_replace('/<img[^>]*>/', $img, $vars['fields']['nothing_1']->content);
    }
    unset($vars['fields']['field_contest_photos']);
  }
}

/**
 * Display the simple view of rows one after another
 */
function airtribune2_preprocess_views_view_unformatted(&$vars) {
  //print_r($vars);
  $view = $vars['view'];
  $rows = $vars['rows'];
  $style = $view->style_plugin;
  $options = $style->options;

  $vars['classes_array'] = array();
  $vars['classes'] = array();
  $default_row_class = isset($options['default_row_class']) ? $options['default_row_class'] : FALSE;
  $row_class_special = isset($options['row_class_special']) ? $options['row_class_special'] : FALSE;
  // Set up striping values.
  $count = 0;

  /* if view name is 'frontpage_events' looking for the highest multiple of excess */
  if ($view->name == 'frontpage_events' || $view->name == 'frontpage_live_events') {
    $standart = floor(count($view->result)/3) * 3;
    $deviant = count($view->result) - $standart;
    if ($deviant == 1) {
      $row_name = 'once';
    }
    if ($deviant == 2) {
      $row_name  = 'twice';
    }
  }
  $max = count($rows);
  foreach ($rows as $id => $row) {
    $count++;
    $vars['prefixes'][$id] = '';
    $vars['suffixes'][$id] = '';
    if ($default_row_class) {
      $vars['classes'][$id][] = 'views-row';
      $vars['classes'][$id][] = 'views-row-' . $count;
    }
    if (!empty($row_name) && $count > $standart) {
      $vars['classes'][$id][] = 'views-row-' . $row_name;      
    }
    if ($row_class_special) {
      $vars['classes'][$id][] = 'views-row-' . ($count % 2 ? 'odd' : 'even');
      if ($count == 1) {
        $vars['classes'][$id][] = 'views-row-first';
      }
      if ($count == $max) {
        $vars['classes'][$id][] = 'views-row-last';
      }
    }

    if ($count == 1 || !(($count - 1) % 3)) {
      $vars['prefixes'][$id] = '<div class="row-wrapper clearfix">';
    }
    if ($count == $max || !($count % 3)) {
      $vars['suffixes'][$id] = '</div>';
    }

    if ($row_class = $view->style_plugin->get_row_class($id)) {
      $vars['classes'][$id][] = $row_class;
    }

    // Flatten the classes to a string for each row for the template file.
    $vars['classes_array'][$id] = isset($vars['classes'][$id]) ? implode(' ', $vars['classes'][$id]) : '';
  }
}

/**
 * Alter Name field widget to remove fieldset.
 */
function _airtribune2_alter_name_widget(&$element) {
  $lang = $element['#language'];
  $element[$lang][0]['given']['#prefix'] = '';
  $element[$lang][0]['given']['#suffix'] = '';
  $element[$lang][0]['family']['#prefix'] = '';
  $element[$lang][0]['family']['#suffix'] = '';
  $element[$lang][0]['given']['#title_display'] = 'before';
  $element[$lang][0]['family']['#title_display'] = 'before';
  $element[$lang][0]['given']['#attributes']['rel'] = t('Enter your name');
  $element[$lang][0]['family']['#attributes']['rel'] = t('Enter your surname');
  // Temporary fix for Name label translation (see http://drupal.org/node/1788156)
  $element[$lang][0]['given']['#title'] = t('Name');
  $element[$lang][0]['family']['#title'] = t('Surname');
}

function _airtribune2_alter_birthdate_widget(&$element) {
  $lang = $element['#language'];
  $element[$lang][0]['#title'] = str_replace('Date of birth', t('Date of birth'), $element[$lang][0]['#title']);
  $element[$lang][0]['value']['day']['#title'] = $element[$lang][0]['#title'];
  $element[$lang][0]['#title'] = '';
}

/**
 * Implements theme_field_multiple_value_form().
 */
function airtribune2_field_multiple_value_form($variables) {
  //print_r($variables);
  $element = $variables['element'];
  $output = '';

  if ($element['#cardinality'] > 1 || $element['#cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
    $table_id = drupal_html_id($element['#field_name'] . '_values');
    $order_class = $element['#field_name'] . '-delta-order';
    $required = !empty($element['#required']) ? theme('form_required_marker', $variables) : '';

    $rows = array();

    // Sort items according to '_weight' (needed when the form comes back after
    // preview or failed validation)
    $items = array();
    foreach (element_children($element) as $key) {
      if ($key === 'add_more') {
        $add_more_button = &$element[$key];
      }
      else {
        $items[] = &$element[$key];
      }
    }
    usort($items, '_field_sort_items_value_helper');

    // Add the items as table rows.
    foreach ($items as $key => $item) {
      $item['_weight']['#attributes']['class'] = array($order_class);
      $delta_element = drupal_render($item['_weight']);
      $cells = array(
        array(
          'data' => '',
          'class' => array('field-multiple-drag'),
        ),
        drupal_render($item),
        array(
          'data' => $delta_element,
          'class' => array('delta-order'),
        ),
      );
      $rows[] = array(
        'data' => $cells,
        'class' => array('draggable'),
      );
    }

    $output = '<div class="form-item">';
    $output .= '<div class="inline-label"><label>' . $element['#title'] . ':&nbsp;</label></div>';
    $output .= '<div class="draggable_table">';

    $output .= theme('table', array('rows' => $rows, 'attributes' => array('id' => $table_id, 'class' => array('field-multiple-table'))));
    $output .= '</div>';
    $output .= $element['#description'] ? '<div class="description">' . $element['#description'] . '</div>' : '';
    $output .= '<div class="clearfix">' . drupal_render($add_more_button) . '</div>';
    $output .= '</div>';

    drupal_add_tabledrag($table_id, 'order', 'sibling', $order_class);
  }
  else {
    foreach (element_children($element) as $key) {
      $output .= drupal_render($element[$key]);
    }
  }

  return $output;
}

/**
 * Implements theme_date_combo().
 *
 * @see #3864
 * @author Valdimir Khodakov
 *
 */
function airtribune2_date_combo($variables) {

  $element = $variables['element'];
  $theme_element = 'fieldset';

  if ($element['#field_name'] == 'field_dates') {
  	$element['value']['date']['#title']= 'From';
  	$element['value']['date']['#extra_wrap'] = true;
  	$element['value2']['date']['#title'] = 'To';
  	$element['value2']['date']['#extra_wrap'] = true;
  	$element['#children'] = render($element['value']['date']) . render($element['value2']['date']);
  	$theme_element = 'form_element';
  }
  $field = field_info_field($element['#field_name']);
  $instance = field_info_instance($element['#entity_type'], $element['#field_name'], $element['#bundle']);

  // Group start/end items together in fieldset.
  $fieldset = array(
    '#title' => t($element['#title']) . ' ' . ($element['#delta'] > 0 ? intval($element['#delta'] + 1) : ''), 
    '#value' => '', 
    '#description' => !empty($element['#fieldset_description']) ? $element['#fieldset_description'] : '', 
    '#attributes' => array(), 
    '#children' => $element['#children'],
  );
  return theme($theme_element, array('element' => $fieldset));
}
