<?php
/**
 * @file
 * user_feature.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function user_feature_field_default_fields() {
  $fields = array();

  // Exported field: 'user-user-field_header_image'.
  $fields['user-user-field_header_image'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_header_image',
      'field_permissions' => array(
        'type' => '0',
      ),
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
        'default_image' => 0,
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
      'bundle' => 'user',
      'default_value' => array(),
      'deleted' => '0',
      'description' => 'Jpeg, png, gif.<br/>
Size: not less than 940x380.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => '',
          ),
          'type' => 'image',
          'weight' => 11,
        ),
      ),
      'entity_type' => 'user',
      'exclude_cv' => 0,
      'field_name' => 'field_header_image',
      'label' => 'Header image',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'entity_translation_sync' => FALSE,
        'exclude_cv' => FALSE,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'filefield_paths' => array(
          'active_updating' => 0,
          'file_name' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => '[user:uid]-header-[file:ffp-name-only-original].[file:ffp-extension-original]',
          ),
          'file_path' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => 'pictures/users',
          ),
          'retroactive_update' => 0,
        ),
        'filefield_paths_enabled' => 1,
        'max_filesize' => '3 MB',
        'max_resolution' => '',
        'min_resolution' => '940x380',
        'title_field' => 0,
        'user_register_form' => 0,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'allowed_schemes' => array(
            'public' => 'public',
            'vimeo' => 0,
            'youtube' => 0,
          ),
          'allowed_types' => array(
            'audio' => 0,
            'document' => 0,
            'image' => 'image',
            'video' => 0,
          ),
          'browser_plugins' => array(
            'media_default--media_browser_1' => 0,
            'media_default--media_browser_my_files' => 0,
            'media_internet' => 0,
            'upload' => 0,
            'youtube' => 0,
          ),
          'insert' => 0,
          'insert_absolute' => FALSE,
          'insert_class' => '',
          'insert_default' => array(
            0 => 'auto',
          ),
          'insert_styles' => array(
            0 => 'auto',
          ),
          'insert_width' => '',
          'preview_image_style' => 'thumbnail',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => '3',
      ),
    ),
  );

  // Exported field: 'user-user-field_social_links'.
  $fields['user-user-field_social_links'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '5',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_social_links',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'link',
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'rel' => '',
          'target' => 'default',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
        'title' => 'optional',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
      ),
      'translatable' => '0',
      'type' => 'link_field',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => 12,
        ),
      ),
      'entity_type' => 'user',
      'exclude_cv' => 0,
      'field_name' => 'field_social_links',
      'label' => 'Social links',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'configurable_title' => 0,
          'rel' => 'nofollow',
          'target' => 'default',
          'title' => '',
        ),
        'display' => array(
          'url_cutoff' => '80',
        ),
        'enable_tokens' => 0,
        'entity_translation_sync' => FALSE,
        'exclude_cv' => FALSE,
        'title' => 'none',
        'title_maxlength' => '128',
        'title_value' => '',
        'url' => 0,
        'user_register_form' => 0,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'link',
        'settings' => array(),
        'type' => 'link_field',
        'weight' => '5',
      ),
    ),
  );

  // Exported field: 'user-user-field_user_avatar'.
  $fields['user-user-field_user_avatar'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_user_avatar',
      'field_permissions' => array(
        'type' => '0',
      ),
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
        'default_image' => 0,
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
      'bundle' => 'user',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => 'user_picture',
          ),
          'type' => 'image',
          'weight' => '1',
        ),
      ),
      'entity_type' => 'user',
      'exclude_cv' => 0,
      'field_name' => 'field_user_avatar',
      'label' => 'Your photo',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'entity_translation_sync' => FALSE,
        'exclude_cv' => FALSE,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'filefield_paths' => array(
          'active_updating' => 1,
          'file_name' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => '[user:uid]-[user:name].[file:ffp-extension-original]',
          ),
          'file_path' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => 'pictures/users',
          ),
          'retroactive_update' => 0,
        ),
        'filefield_paths_enabled' => 1,
        'image_field_caption' => 0,
        'max_filesize' => '',
        'max_resolution' => '',
        'min_resolution' => '400x400',
        'title_field' => 0,
        'user_register_form' => 0,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'image',
        'settings' => array(
          'insert' => 0,
          'insert_absolute' => 0,
          'insert_class' => '',
          'insert_default' => 'auto',
          'insert_styles' => array(
            'auto' => 'auto',
            'colorbox__advert_on_visualization' => 0,
            'colorbox__award' => 0,
            'colorbox__award_details' => 0,
            'colorbox__award_sponsor' => 0,
            'colorbox__award_sponsor_details' => 0,
            'colorbox__contest_gallery_thumb' => 0,
            'colorbox__contest_thumbnail' => 0,
            'colorbox__event_blog_teaser_eighth' => 0,
            'colorbox__event_blog_teaser_fifth' => 0,
            'colorbox__event_blog_teaser_first' => 0,
            'colorbox__event_blog_teaser_fourth' => 0,
            'colorbox__event_blog_teaser_second' => 0,
            'colorbox__event_blog_teaser_seventh' => 0,
            'colorbox__event_blog_teaser_sixth' => 0,
            'colorbox__event_blog_teaser_sixth_extra' => 0,
            'colorbox__event_blog_teaser_third' => 0,
            'colorbox__event_logo' => 0,
            'colorbox__event_logo_once' => 0,
            'colorbox__event_logo_twice' => 0,
            'colorbox__event_map_picture_preview' => 0,
            'colorbox__frontpage_event_padding' => 0,
            'colorbox__frontpage_event_padding_once' => 0,
            'colorbox__frontpage_event_padding_twice' => 0,
            'colorbox__header' => 0,
            'colorbox__header_thumbnail' => 0,
            'colorbox__hotel_preview' => 0,
            'colorbox__jcarousel-thumbnail' => 0,
            'colorbox__large' => 0,
            'colorbox__media_thumbnail' => 0,
            'colorbox__medium' => 0,
            'colorbox__node_image_first' => 0,
            'colorbox__node_image_second' => 0,
            'colorbox__node_image_third' => 0,
            'colorbox__node_userpic' => 0,
            'colorbox__organizer_details' => 0,
            'colorbox__organizer_info' => 0,
            'colorbox__race_teaser' => 0,
            'colorbox__scoring_winner' => 0,
            'colorbox__scoring_winner_horizontal' => 0,
            'colorbox__scoring_winner_vertical' => 0,
            'colorbox__thumbnail' => 0,
            'colorbox__user_picture' => 0,
            'colorbox__user_picture_mini' => 0,
            'icon_link' => 0,
            'image' => 0,
            'image_advert_on_visualization' => 0,
            'image_award' => 0,
            'image_award_details' => 0,
            'image_award_sponsor' => 0,
            'image_award_sponsor_details' => 0,
            'image_contest_gallery_thumb' => 0,
            'image_contest_thumbnail' => 0,
            'image_event_blog_teaser_eighth' => 0,
            'image_event_blog_teaser_fifth' => 0,
            'image_event_blog_teaser_first' => 0,
            'image_event_blog_teaser_fourth' => 0,
            'image_event_blog_teaser_second' => 0,
            'image_event_blog_teaser_seventh' => 0,
            'image_event_blog_teaser_sixth' => 0,
            'image_event_blog_teaser_sixth_extra' => 0,
            'image_event_blog_teaser_third' => 0,
            'image_event_logo' => 0,
            'image_event_logo_once' => 0,
            'image_event_logo_twice' => 0,
            'image_event_map_picture_preview' => 0,
            'image_frontpage_event_padding' => 0,
            'image_frontpage_event_padding_once' => 0,
            'image_frontpage_event_padding_twice' => 0,
            'image_header' => 0,
            'image_header_thumbnail' => 0,
            'image_hotel_preview' => 0,
            'image_jcarousel-thumbnail' => 0,
            'image_large' => 0,
            'image_media_thumbnail' => 0,
            'image_medium' => 0,
            'image_node_image_first' => 0,
            'image_node_image_second' => 0,
            'image_node_image_third' => 0,
            'image_node_userpic' => 0,
            'image_organizer_details' => 0,
            'image_organizer_info' => 0,
            'image_race_teaser' => 0,
            'image_scoring_winner' => 0,
            'image_scoring_winner_horizontal' => 0,
            'image_scoring_winner_vertical' => 0,
            'image_thumbnail' => 0,
            'image_user_picture' => 0,
            'image_user_picture_mini' => 0,
            'link' => 0,
          ),
          'insert_width' => '',
          'preview_image_style' => 'user_picture',
          'progress_indicator' => 'throbber',
        ),
        'type' => 'image_image',
        'weight' => '2',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Header image');
  t('Jpeg, png, gif.<br/>
Size: not less than 940x380.');
  t('Social links');
  t('Your photo');

  return $fields;
}
