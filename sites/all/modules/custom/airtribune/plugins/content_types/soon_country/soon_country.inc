<?php

/**
 * @file
 * Airtribune 'Soon in country' pane plugin.
 *
 * @see #3543.
 */

// Plugin definition.
$plugin = array(
  'title' => t('Soon in country'),
  'single' => TRUE,
  'category' => array('Airtribune'),

);

/**
 * Get countries for Soon in country select list.
 */
function airtribune_soon_country_countries_list() {
  $view = views_get_view('frontpage_events');
  $view->set_display('soon_country_list_entityreference');
  $view->execute();
  $links = array();

  // @TODO: Implement distinct countries at views level.
  foreach ($view->result as $r) {
    $name = $r->field_field_country[0]['rendered']['#markup'];
    $code = strtolower($r->field_field_country_1[0]['raw']['iso2']);
    // Exclude the country if there is already have
    if (empty($links[$code])) {
      $links[$code] = array(
        'href'  => "soon_country/{$code}/",
        'title' => theme(
            'countryicons_icon_sprite',
            array('code' => $code, 'iconset' => AIRTRIBUNE_LANGUAGES_ICONSET)
          )
          .
          $name,
        'attributes' => array('class' => array('use-ajax'), 'rel' => array('nofollow')),
        'html' => TRUE,
      );
    }
  }

  return $links;
}

/**
 * Render event title pane.
 */
function airtribune_soon_country_content_type_render($subtype, $conf, $panel_args, $context) {

  $plugin_path = drupal_get_path('module', 'airtribune') . '/plugins/content_types/soon_country';
  drupal_add_library('system', 'drupal.ajax');
  $theme_path =  drupal_get_path('theme', 'airtribune2');
  drupal_add_js($theme_path . '/js/jquery.mousewheel.min.js');
  drupal_add_js($theme_path . '/js/jquery.jscrollpane.min.js');
  drupal_add_js($plugin_path . '/soon_country.js');


  $content = '<div id="soon-county-wrapper"></div>';
  $title = t('Soon in country');

  

  return (object) array(
    'module' => 'airtribune',
    'title' => '<span class="country_title">' . $title . '</span><div class="change_location"><span class="change_location_title">' . t('Change location') . '</span></div>',
    //'location' => render($location),
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_soon_country_content_type_edit_form($form, &$form_state) {
  return $form;
}


function airtribune_soon_country($country_code) {

  $view = views_get_view('frontpage_events');
  $view->set_arguments(array(strtoupper($country_code)));

  $output = $view->preview('soon_in_country_pane');
  // See ajax_example_advanced.inc for more details on the available commands
  // and how to use them.
  $commands[] = ajax_command_html('#soon-county-wrapper', $output);
  $page = array('#type' => 'ajax', '#commands' => $commands);
  ajax_deliver($page);
}
