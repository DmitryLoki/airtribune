<?php

define('DEFAULT_USER_PICTURE_PATH','pictures/default_user_picture.png');

/**
 * Preprocess html.tpl.php
 */
function airtribune2_preprocess_html(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

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
  if($vars['is_front']) {
    //$vars['title'] = t('Activity feed');
    drupal_set_title(t('Activity feed'));
  }
  if(!empty($vars['page']['content']['system_main']['nodes'])){

    $nodes = $vars['page']['content']['system_main']['nodes'];
    $nodes_k = array_keys($vars['page']['content']['system_main']['nodes']);
  
    if(count($nodes) == 2 && !empty($nodes[$nodes_k[0]]['#node']) && $nodes[$nodes_k[0]]['#node']->promote == 1){
      $vars['classes_array'][] = 'logo_in_title';
    }  
  }
  /* Adding specific class for activity and accommodation pages */
  $pemaa = array('node-type-activity', 'node-type-accommodation');
  $result_ar = array_intersect($pemaa, $vars['classes_array']);
  if (!empty($result_ar)) {
    $vars['classes_array'][] = 'page-event-map-activity-accommodation';
  }

  /* If event register page */
  if(arg(0) == 'event' && arg(2) && arg(2) == 'register'){
    $vars['classes_array'][] = 'page-user';
  }

  /* If profile pilot page */
  if (!empty($vars['page']['content']['system_main']['profile_pilot'])) {
    $vars['classes_array'][] = 'page-user';
  }
    /* If pilot status list */
  if (in_array('page-event-pilots', $vars['classes_array']) && !arg(3)) {
    $vars['classes_array'][] = 'page-event-pilots-status';
  }
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
      )
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
      )
    ));
  }
}

/**
 * Preprocess pane twocolfourrow
 */
function airtribune2_process_twocolfourrow(&$vars) {

}

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
  if(!empty($vars['primary_local_tasks'])){
    foreach($vars['primary_local_tasks'] as $k => $v){
      if($v['#link']['path'] == 'event/%/register'){
        $vars['primary_local_tasks'][$k]['#link']['localized_options']['attributes']['class'][] = 'registration';
      }
      if($v['#link']['path'] == 'events/add'){
        $vars['primary_local_tasks'][$k] = array(
          '#theme' => 'links',
          '#links' => array(
            'event_add' => array(
              'title' => $vars['primary_local_tasks'][$k]['#link']['title'],
              'href' => $vars['primary_local_tasks'][$k]['#link']['href'],
              'attributes' => array(
                'class' => array('registration'),
              )              
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
 * @param array $variables
 * @autor Vyacheslav "ValiDoll" Malchik <info@vkey.biz>
 */
function airtribune2_preprocess_panels_pane(&$variables) {
  $base = 'panels_pane';
  $delimiter = '__';
  $variables['theme_hook_suggestions'][] = $base . $delimiter . $variables['pane']->type; 
  global $user;
  if($variables['pane']->type == 'node' && $variables['content']['#node']->nid == '5363'){
    //$variables['title'] = '';
  }
  if($variables['pane']->type == 'page_title' && arg(0) == 'user' && $user->uid == 0) {

   if(arg(1)){
     if(arg(1) == 'register'){
       drupal_set_title(t('Register new user'));
     }
     if(arg(1) == 'password'){
       drupal_set_title(t('Request new password'));
     }
   }
   else{
     drupal_set_title(t('Sign in'));
   }
  }
  if($variables['pane']->subtype == 'paragliding_pilots_list-fai'){
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
  if(!empty($autor->picture->uri)){
    $userpic = $autor->picture->uri;
  }
  else {
    $userpic = file_build_uri(DEFAULT_USER_PICTURE_PATH);
  }
  $vars['user_picture'] = '<span class="user-picture">'.theme('image_style', array( 'path' =>  $userpic, 'style_name' => 'node_userpic')).'</span>';
  $vars['notitle'] = false;
  if($vars['node']->nid == '5363' || $vars['node']->nid == '5362') {
    $vars['notitle'] = true;
    $vars['title'] = '';
    $vars['user_picture'] = '';
  }

}

function airtribune2_process_node(&$vars) {
  $vars['event_blog'] = false;
  $account = profile2_load_by_user($vars['node']->uid, 'main');

  /* If view mode is event_blog_teaser */
  if($vars['view_mode'] == 'event_blog_teaser'){
    $vars['event_blog'] = true;
    $vars['title'] = '<a href="' . $vars['node_url'] . '" rel="bookmark">' . $vars['title'] . '</a>';

    /* Changing the style of the output image */
    if(!empty($vars['content']['field_image'])){
      $vars['content']['field_image'] = _airtribune2_img_dinamic_scaling_event_blog_teaser($vars['content']['field_image']);
    }

    /* Read more link */
    $vars['content']['links']['node-readmore'] = array(
      '#theme' => 'links__node__node',
      '#links' => array(
        'node-readmore' => array(
          'title' => l(t('View more'), 'node/' . $vars['node']->nid),
          'html' => true
        )
      )
    );

    /* Disqus comment counter */
    if(drupal_get_path('module', 'disqus')){
      $vars['content']['links']['disqus'] = array(
        '#theme' => 'links',
        '#links' => array(
          'disqus_comments_num' => array(
            'title' => 'Comments',
            'href' => 'node/' . $vars['node']->nid,
            'fragment' => 'disqus_thread',
            'attributes' => array(
              'data-disqus-identifier' => 'node/' . $vars['node']->nid,
            )
          )
        ),
        '#attributes'=> array(
          'class' => array( 'links', 'inline')
        )
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
  else if ($vars['node']->type == 'activity' || $vars['node']->type == 'accommodation') {
    $vars['notitle'] = true;
    $vars['title'] = '';
    $vars['user_picture'] = '';
    $vars['display_submitted'] = '';
    if (!empty($vars['content']['body'])) {
      $vars['content']['body']['#prefix'] = '<h2 class="field_title">' . $vars['content']['body']['#title'] . '</h2>';
    }
    if (!empty($vars['content']['field_address'])) {
      $vars['content']['field_address']['#prefix'] = '<h2 class="field_title">' . t('Contacts') . '</h2>';
    }
  }

  /* If teaser */
  else if ($vars['teaser']){
    $vars['user_picture'] = false;
    $vars['display_submitted'] = false;
    $vars['content']['links']['created'] = array(
      '#theme' => 'links__node__node',
      '#links' => array(
        'node-create' => array(
          'title' => format_date($vars['created'], 'custom', 'd M, Y')
        )
      )
    );
    if(!empty($vars['content']['field_image']['#items'])){
      $vars['content']['field_image']['#items'] = array($vars['content']['field_image']['#items'][0]);
    }
  }

  /* Change of specific nodes */
  else if($vars['node']->nid != '5363' && $vars['node']->nid != '5362') {
    if (isset($account->field_full_name)) {
      $vars['full_name'] = field_view_field('profile2', $account, 'field_full_name', array('label' => 'hidden'));
    } else {
      $vars['full_name'] = $vars['name'];
    }
    $vars['content']['links']['created'] = array(
      '#theme' => 'links__node__node',
      '#links' => array(
        'node-create' => array(
          'title' => t('Posted by !user on !date', array('!user' => render($vars['full_name']), '!date' => format_date($vars['created'], 'custom', 'd M, Y'))),
          'html' => true
        )
      )
    );
    if(!empty($vars['content']['field_image'])){
      $vars['content']['field_image'] = _airtribune2_img_dinamic_scaling($vars['content']['field_image']);
    }
  }

  if(!$vars['notitle'] && empty($vars['title'])){
    $vars['title'] = 'Верните заголовки емае';
  }
  $vars['classes'] .= ' node_view_mode_' . $vars['view_mode'];
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
  if(!empty($element['#localized_options']['attributes']['class'])){
    $element['#attributes']['class'] = array_merge($element['#attributes']['class'], $element['#localized_options']['attributes']['class']);
  }
  $output = l($element['#title'], $element['#href'], $element['#localized_options']);
  if (!empty($element['#localized_options']['attributes']['title'])) {
    $output .= '<div>' . $element['#localized_options']['attributes']['title'] . '</div>';
  }
  return '<li' . drupal_attributes($element['#attributes']) . '>' . $output . $sub_menu . "</li>\n";
}

/**
 * Implements hook_form_alter().
 */
function airtribune2_form_alter(&$form, $form_state, $form_id) {
  $form_id_ar = array('og_ui_confirm_subscribe', 'user_register_form', 'user_login', 'user_pass', 'user_profile_form', 'profile2_edit_pilot_form');
  if(in_array($form_id, $form_id_ar)) {
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
          'title' => t('Create a new user account.'))
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
        $form['hybridauth']['#prefix'] = '<div class="hybridauth_prefix">'.t('or').'</div>';
        $form['hybridauth']['#weight'] = 89;
        $form['actions']['#weight'] = 79;
    break;
      case 'user_profile_form':
        
        //print_r($form);
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

function _airtribune2_img_dinamic_scaling($vars){
  
  $count = count($vars['#items']);
  $excess = $count-3*floor($count/3);
  $image_style_other = 'node_image_third';
  if($count%3 == 0) {
    $image_styles = array('node_image_first', 'node_image_second', 'node_image_second');
  }
  elseif($excess == 2){
    $image_styles = array('node_image_second', 'node_image_second');
  }
  else {
    $image_styles = array('node_image_first');
  }
  $is_count = 0;
  foreach($vars['#items'] as $k => $v){
    if(!empty($image_styles[$is_count])){
      $image_style = $image_styles[$is_count];
    }
    else{
      $image_style = $image_style_other;
    }
    if($vars[$k]['#theme'] != 'colorbox_image_formatter'){
      $vars[$k]['#image_style'] = $image_style;
    }
    else{
      $vars[$k]['#display_settings']['colorbox_node_style'] = $image_style;
    }
    $is_count++;
    
  }
  return $vars;
}

function _airtribune2_img_dinamic_scaling_event_blog_teaser($vars){
  $count = count($vars['#items']);
  //$excess = $count-3*floor($count/3);
  //$image_style_other = 'node_image_third';
  switch($count){
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
  foreach($vars['#items'] as $k => $v){
    if(!empty($image_styles[$is_count])){
      $image_style = $image_style_other = $image_styles[$is_count];
    }
    else{
      $image_style = $image_style_other;
    }
    if($vars[$k]['#theme'] != 'colorbox_image_formatter'){
      $vars[$k]['#image_style'] = $image_style;
    }
    else{
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
  $li_previous = theme('pager_previous', array('text' => (isset($tags[1]) ? $tags[1] : t('‹ previous')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
  $li_next = theme('pager_next', array('text' => (isset($tags[3]) ? $tags[3] : t('next ›')), 'element' => $element, 'interval' => 1, 'parameters' => $parameters));
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
            'data' => '<span><span>'.$i.'</span></span>',
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
        t('« first') => t('Go to first page'), 
        t('‹ previous') => t('Go to previous page'), 
        t('next ›') => t('Go to next page'), 
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
  if (isset($variables['field_collection_item']) && $variables['field_collection_item']->field_name == 'field_collection_getting_there') {
  if ($variables['view_mode'] == 'event_details_page') {  
    $field_gt_col_left = array(
      '#theme' => 'field',
    '#label_display' => 'hidden',
        '#access' => 1,
        '#view_mode' => 'event_details_page',
        '#weight' => 99,
    '#field_name' => 'field_gt_col_left',
    '#items' => array(),
    '#field_type' => 'markup',
    '#language' => 'und',
        '#entity_type' => 'field_collection_item',
        '#bundle' => 'field_collection_getting_there',
    '#formatter' => 'text_default',
    );
    $field_gt_col_right = array(
      '#theme' => 'field',
    '#label_display' => 'hidden',
        '#access' => 1,
        '#view_mode' => 'event_details_page',
        '#weight' => 100,
    '#field_name' => 'field_gt_col_right',
    '#items' => array(),
    '#field_type' => 'markup',
    '#language' => 'und',
        '#entity_type' => 'field_collection_item',
        '#bundle' => 'field_collection_getting_there',
    '#formatter' => 'text_default',
    );
    $count = 1;
    foreach($variables['content'] as $k => $v){
      if($k != 'field_gt_general' && $v['#theme'] == 'field'){
        if($count%2 == 0){
          $field_gt_col_right[] = $field_gt_col_right['#items'][] = array('#markup' => render($variables['content'][$k]));
        }
        else{
          $field_gt_col_left[] = $field_gt_col_left['#items'][] = array('#markup' => render($variables['content'][$k]));
        }
        unset($variables['content'][$k]);
        $count++;
      }
    }
    $variables['content']['field_gt_col_right'] = $field_gt_col_right;
    $variables['content']['field_gt_col_left'] = $field_gt_col_left;
    
    }
    if ($variables['view_mode'] == 'event_info_page') {
    $transport = array(
      'plane' => array(
        '#title' => t('Plane'),
      '#fragment' => 'gt_plane',
      '#attributes' => array('class' => 'plane'),
      ),
      'train' => array(
        '#title' => t('Train'),
      '#fragment' => 'gt_train',
      '#attributes' => array('class' => 'train'),
      ),
      'bus' => array(
        '#title' => t('Bus'),
      '#fragment' => 'gt_bus',
      '#attributes' => array('class' => 'bus'),
      ),
      'car' => array(
        '#title' => t('Car'),
      '#fragment' => 'gt_car',
      '#attributes' => array('class' => 'car'),
      ),
      'taxi' => array(
        '#title' => t('Taxi'),
      '#fragment' => 'gt_taxi',
      '#attributes' => array('class' => 'taxi'),
      ),
    );
    $contest_id = (int) arg(1);
    foreach($transport as $k => $v){
      $item_key = 'field_gt_' . $k;
      $object = get_object_vars($variables['field_collection_item']);
      if(!empty($variables['field_collection_item']->$item_key)){
        $links[] = array(
              'href' => 'event/' . $contest_id . '/info/details',
              'title' => $transport[$k]['#title'],
              'fragment' => $transport[$k]['#fragment'],
              'attributes' => $transport[$k]['#attributes'],
            );
      }
    }

      

      if(!empty($links)){
      $variables['content']['transport'] = array(
          '#theme' => 'links',
          '#links' => $links,
        );
    }
    }
  }
  
  if (isset($variables['field_collection_item']) && $variables['field_collection_item']->field_name == 'field_collection_organizers' && $variables['view_mode'] == 'event_info_page') {
  if(arg(0) == 'event' && !empty($variables['content']['field_organizer_logo'])) {
    //print_r($variables['field_collection_item']);
    $variables['content']['field_organizer_logo'][0] = array(
      //'#markup' => l(render($variables['content']['field_organizer_logo'][0]), $variables['field_collection_item']->field_url['und'][0]['url'], array('html' => true, 'attributes' => array('target'=>'_blank'))),
      '#markup' => l(render($variables['content']['field_organizer_logo'][0]), 'event/'.arg(1).'/info/details', array('html' => true, 'fragment' => 'organizer_' . $variables['field_collection_item']->item_id)),
    ) ;
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
 * Implements theme_field__field_collection_getting_there().
 */
function airtribune2_field__field_collection_getting_there($variables) {
  //print_r($variables);
  $output = '';
  $colon = ':&nbsp;';
  if($variables['element']['#bundle'] == 'field_collection_getting_there') {
   $colon = '';
   $variables['classes'] .= ($variables['element']['#weight'] % 2 ? ' field_odd' : ' field_even');
  }
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
    if(!empty($item['entity']['field_collection_item'])){
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
  if($variables['field_view_mode'] == '_custom_display'){
    return drupal_render($item);
  }
  $output = '';
  $colon = ':&nbsp;';
  if($variables['element']['#bundle'] == 'field_collection_getting_there') {
   $colon = '';
   $variables['classes'] .= ($variables['element']['#weight'] % 2 ? ' field_odd' : ' field_even');
  }
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
 * Implements theme_field__field_full_name.
 */
function airtribune2_field($variables) {
  $element = $variables['element'];
  //print $variables['element']['#field_name'];
  $colon = ':&nbsp;';
  switch ($variables['element']['#field_name']) {
    case 'field_price_single':
    case 'field_price_double':
    
      $colon = '&nbsp;';
      $variables['classes'] .= ' field_buttons';
      $currency = field_view_field('node', $element['#object'], 'field_price_currency');
      if (isset($variables['items'][0], $currency)) {
        $variables['items'][0]['#suffix'] = ' ' . render($currency);
      }

      break;
    case 'field_hotel_wifi':
      $colon = '&nbsp;';
      $variables['field_view_mode'] = '';
      $variables['label_hidden'] = '';
      $variables['classes'] .= ' field_buttons';

      if ($variables['element']['#field_name'] == 'field_hotel_wifi' && !$variables['element']['#items'][0]['value']) {
        $variables['classes'] .= ' field_wifi_no';
      }

      break;
    case 'field_address':
      $variables['label'] = t('Address');
    case 'field_email':
    case 'field_phone':
    case 'field_url':
      $variables['field_view_mode'] = '';
      $variables['label_hidden'] = '';
      $variables['classes'] .= ' fields_contacts';
      break;
    
    default:
      //print $variables['element']['#field_name'];
      # code...
      break;
  }
  //print_r($variables);
  if($variables['field_view_mode'] == '_custom_display'){
    return drupal_render($item);
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
  $output = '<div class="' . $variables['classes'] . '"' . $variables['attributes'] . '>' . $output . '</div>';

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
  );
  $file = $variables['file'];
  $icon_directory = $variables['icon_directory'];

  $mime = check_plain($file->filemime);
  $path_info = pathinfo($file->filename);
  if(!empty($icons[$path_info['extension']])){
  $icon_url = '/' . path_to_theme() . '/images/icons/' . $icons[$path_info['extension']];
  }
  else{
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
    $categories = airtribune_get_awards_prize_categories();
    foreach ($vars['items'] as $delta => $item) {
      if (isset($categories[$item['#item']['title']])) {
        $vars['items'][$delta]['#item']['title'] = $categories[$item['#item']['title']];
        $vars['items'][$delta]['#suffix'] = $categories[$item['#item']['title']];
      }
    }
  }

  if ($element['#field_name'] == AIRTRIBUNE_CONTEST_PHOTOS_FIELD) {
    $settings = array(
      'full_image_modal' => 'colorbox',
      'jcarousel_image_style' => AIRTRIBUNE_INFO_CAROUSEL_IMAGE_STYLE,
      'full_image_style' => 'large',
    );
    $flying_site_photos = field_view_field('node', $element['#object'], AIRTRIBUNE_FLYING_SITE_PHOTOS_FIELD, array('type' => 'jcarousel_formatter', 'settings' => $settings));

    if (isset($flying_site_photos[0])) {
      foreach ($flying_site_photos[0]['#items'] as $item) {
        $vars['items'][0]['#items'][] = $item;
      }
    }
  }
}

/**
 * Implements theme_preprocess_openlayers_map.
 */
function airtribune2_preprocess_openlayers_map(&$variables, $hook){
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
    return '<span class="arrow_sort arrow-asc" title="' . t('sort ascending') . '"></span>'; //theme('image', array('path' => 'misc/arrow-asc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort ascending'), 'title' => t('sort ascending')));
  }
  else {
    return '<span class="arrow_sort arrow-desc" title="' . t('sort descending') . '"></span>'; //theme('image', array('path' => 'misc/arrow-desc.png', 'width' => 13, 'height' => 13, 'alt' => t('sort descending'), 'title' => t('sort descending')));
  }
}

/**
 * Implements theme_colorbox_image_field().
 */
function airtribune2_colorbox_imagefield($variables) {

  static $counter;
  $gid = $variables['gid'];

  if ($counter == NULL) {
    $counter['contest_photos'] = $counter['flying_site_photos'] = 0;
    $counter['contest_photos_details'] = $counter['flying_site_photos_details'] = 0;
  }

  if (isset($counter[$gid])) {
    $counter[$gid]++;
    if ($gid == 'contest_photos_details') {
      $hidden = $counter[$gid] > 4;
    }
    elseif ($gid == 'flying_site_photos_details') {
      $hidden = $counter[$gid] > 8;
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

  // The leading whitespace helps visually separate fields from inline labels.
  return ' <div class="inline-label"><label' . drupal_attributes($attributes) . '>' . $t('!title!required', array('!title' => str_replace(' <', '<', $title), '!required' => $required)) . "</label><span class=\"valign\"></span></div>\n";
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
      $output .= $messages[0] . '<span class="valign"></span>';
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
