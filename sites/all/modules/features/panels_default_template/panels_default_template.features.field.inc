<?php
/**
 * @file
 * panels_default_template.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function panels_default_template_field_default_fields() {
  $fields = array();

  // Exported field: 'fieldable_panels_pane-fieldable_panels_pane-field_header'.
  $fields['fieldable_panels_pane-fieldable_panels_pane-field_header'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_header',
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => '0',
      'module' => 'image',
      'settings' => array(
        'default_image' => '10321',
        'entity_translation_sync' => array(
          0 => 'fid',
        ),
        'profile2_private' => FALSE,
        'uri_scheme' => 'public',
      ),
      'translatable' => '0',
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'fieldable_panels_pane',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'field_slideshow',
          'settings' => array(
            'slideshow_caption' => '',
            'slideshow_caption_link' => '',
            'slideshow_carousel_circular' => 0,
            'slideshow_carousel_follow' => 0,
            'slideshow_carousel_image_style' => '',
            'slideshow_carousel_scroll' => '1',
            'slideshow_carousel_speed' => '500',
            'slideshow_carousel_vertical' => 0,
            'slideshow_carousel_visible' => '3',
            'slideshow_colorbox_image_style' => '',
            'slideshow_colorbox_slideshow' => '',
            'slideshow_colorbox_slideshow_speed' => '4000',
            'slideshow_colorbox_speed' => '350',
            'slideshow_colorbox_transition' => 'elastic',
            'slideshow_controls' => 0,
            'slideshow_controls_pause' => 0,
            'slideshow_controls_position' => 'after',
            'slideshow_field_collection_image' => '',
            'slideshow_fx' => 'fade',
            'slideshow_image_style' => 'header',
            'slideshow_link' => '',
            'slideshow_order' => 'random',
            'slideshow_pager' => '',
            'slideshow_pager_image_style' => '',
            'slideshow_pager_position' => 'after',
            'slideshow_pause' => 0,
            'slideshow_speed' => '2000',
            'slideshow_start_on_hover' => 0,
            'slideshow_timeout' => '7000',
          ),
          'type' => 'slideshow',
          'weight' => '0',
        ),
      ),
      'entity_type' => 'fieldable_panels_pane',
      'field_name' => 'field_header',
      'label' => 'Header image',
      'required' => 1,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'entity_translation_sync' => FALSE,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'filefield_paths' => array(
          'active_updating' => 1,
          'file_name' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => '[file:ffp-name-only-original].[file:ffp-extension-original]',
          ),
          'file_path' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => 'header_images',
          ),
          'retroactive_update' => 0,
        ),
        'max_filesize' => '',
        'max_resolution' => '940x380',
        'min_resolution' => '940x380',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => '42',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Header image');

  return $fields;
}
