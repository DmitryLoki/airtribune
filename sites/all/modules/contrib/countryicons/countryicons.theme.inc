<?php

/**
 * @file
 * Theme functions for the countryicons module.
 */

/**
 * Theme a country icon.
 *
 * @param $variables
 *   An associative array containing:
 *   - code: A two letter ISO3166 country code.
 *   - iconset: The icon set to use.
 *   - alt: The alternative text for text-based browsers
 *     (the two letter ISO3166 country code is the default).
 *   - title: The title text is displayed when the image is hovered in some
 *     popular browsers.
 *   - attributes: Associative array of attributes to be placed in the img tag.
 *   - display_unknown: If set to TRUE, if a icon don't exists it tries to
 *     return a transparant image instead.
 * @return
 *   A string containing the image tag.
 */
function theme_countryicons_icon($variables) {
  $icon_path = countryicons_get_icon_path($variables['code'], $variables['iconset']);
  
  if (!empty($icon_path)) {
    $image = array(
      'path' => $icon_path,
      'alt' => $variables['alt'] ? $variables['alt'] : $variables['code'],
      'title' => $variables['title'],
      'attributes' => $attributes = $variables['attributes'] ? $variables['attributes'] : array(),
    );
    $image['attributes']['class'] = 'countryicon iconset-' . $variables['iconset'] . ' countrycode-' . drupal_strtolower($variables['code']) . (empty($image['attributes']['class']) ? '' : ' ' . $image['attributes']['class']);

    return theme('image', $image);
  }
  elseif ($variables['display_unknown']) {
    $var = array(
      'code' => 'unknown',
      'iconset' => $variables['iconset'],
      'attributes' => $variables['attributes'],
      'display_unknown' => FALSE,
    );
    return theme('countryicons_icon', $var);
  }
}

/**
 * Theme a country icon with CSS sprite.
 *
 * @param $variables
 *   An associative array containing:
 *   - code: A two letter ISO3166 country code.
 *   - iconset: The icon set to use.
 * @return
 *   A string containing a image tag rendered using a css sprite techniquie.
 */
function theme_countryicons_icon_sprite($variables) {
  $code = $variables['code'];
  $iconset = countryicons_get_iconset($variables['iconset']);
  
  if (!empty($iconset) && $iconset->css_sprite && !empty($code)) {
    drupal_add_css($iconset->css_sprite);
    return '<div class="countryicon-sprite iconset-' . $iconset->key . ' countrycode-' . drupal_strtolower($code) . '"></div>';
  }
}
