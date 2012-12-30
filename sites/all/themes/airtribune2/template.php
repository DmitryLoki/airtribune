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
}

/**
 * Preprocess Site Template
 */
function airtribune2_preprocess_airtribune2_site_template(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Add information about the number of sidebars.
  $content = $vars['content'];
  
  $sidebars = array();
  if (!empty($content['sidebar_first']) && !empty($content['sidebar_second'])) {
    $sidebars[] = 'two-sidebars';
  }
  elseif (!empty($content['sidebar_first'])) {
    $sidebars[] = 'one-sidebar sidebar-first';
  }
  elseif (!empty($content['sidebar_second'])) {
    $sidebars[] = 'one-sidebar sidebar-second';
  }
  else {
    $sidebars[] = 'no-sidebars';
  }
  $vars['classes_array'][] = implode(' ', $sidebars);

  // Add the container class, but only when the standard layout is selected,
  // if you add more layout plugsins you will need to add the "container" class
  // either using the logic below or directly to the template in the layout
  // plugin template (on the main wrapper or elsewhere, where you need it).
  if (at_get_setting('enable_extensions', $theme_name) === 0) {
    if (at_get_setting('enable_markup_overides', $theme_name) === 0) {
      if (at_get_setting('page_full_width_wrappers', $theme_name) === 0) {
        if ($vars['layout']['theme'] = 'airtribune2_site_template') {
          $vars['classes_array'][] = 'container';
        }
      }
    }
  }

  // Strip stupid contextual links region class, wtf?
  $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array('contextual-links-region')));

  // Generate page classes, in AT Core these are all Extensions
  if (at_get_setting('enable_extensions', $theme_name) === 1) {
    if ($page_classes = generate_page_classes($vars, $theme_name)) {
      foreach ($page_classes as $class_name) {
        $vars['classes_array'][] = $class_name;
      }
    }
  }
}

/**
 * Preprocess Site Template
 */
function airtribune2_preprocess_airtribune2_site_template_fww(&$vars) {
  global $theme_key;
  $theme_name = $theme_key;

  // Add information about the number of sidebars.
  $content = $vars['content'];
  
  $sidebars = array();
  if (!empty($content['sidebar_first']) && !empty($content['sidebar_second'])) {
    $sidebars[] = 'two-sidebars';
  }
  elseif (!empty($content['sidebar_first'])) {
    $sidebars[] = 'one-sidebar sidebar-first';
  }
  elseif (!empty($content['sidebar_second'])) {
    $sidebars[] = 'one-sidebar sidebar-second';
  }
  else {
    $sidebars[] = 'no-sidebars';
  }
  $vars['classes_array'][] = implode(' ', $sidebars);

  // Add the container class, but only when the standard layout is selected,
  // if you add more layout plugsins you will need to add the "container" class
  // either using the logic below or directly to the template in the layout
  // plugin template (on the main wrapper or elsewhere, where you need it).
  if (at_get_setting('enable_extensions', $theme_name) === 0) {
    if (at_get_setting('enable_markup_overides', $theme_name) === 0) {
      if (at_get_setting('page_full_width_wrappers', $theme_name) === 0) {
        if ($vars['layout']['theme'] = 'airtribune2_site_template') {
          $vars['classes_array'][] = 'container';
        }
      }
    }
  }

  // Strip stupid contextual links region class, wtf?
  $vars['classes_array'] = array_values(array_diff($vars['classes_array'], array('contextual-links-region')));

  // Generate page classes, in AT Core these are all Extensions
  if (at_get_setting('enable_extensions', $theme_name) === 1) {
    if ($page_classes = generate_page_classes($vars, $theme_name)) {
      foreach ($page_classes as $class_name) {
        $vars['classes_array'][] = $class_name;
      }
    }
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
}

function airtribune2_process_node(&$vars) {
	//print_r($vars);
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


function airtribune2_menu_link__user_menu(&$vars) {
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
	switch ($form_id) {
    	case 'user_login_block':
			//print_r($form);
			$form['name']['#attributes']['rel'] = t('Enter your e-mail');
			unset($form['name']['#title']);
			$form['pass']['#attributes']['rel'] = t('Enter your password');
			unset($form['pass']['#title']);
			$form['actions']['submit']['#value'] = t('Go');
			
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
		$vars[$k]['#image_style'] = $image_style;
		$is_count++;
		
	}
	return $vars;
}
