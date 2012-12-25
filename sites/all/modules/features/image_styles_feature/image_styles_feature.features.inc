<?php
/**
 * @file
 * image_styles_feature.features.inc
 */

/**
 * Implements hook_image_default_styles().
 */
function image_styles_feature_image_default_styles() {
  $styles = array();

  // Exported image style: contest_thumbnail.
  $styles['contest_thumbnail'] = array(
    'name' => 'contest_thumbnail',
    'effects' => array(
      2 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => '160',
          'height' => '100',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: user_pirctue_mini.
  $styles['user_pirctue_mini'] = array(
    'name' => 'user_pirctue_mini',
    'effects' => array(
      2 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => '24',
          'height' => '24',
        ),
        'weight' => '1',
      ),
    ),
  );

  return $styles;
}
