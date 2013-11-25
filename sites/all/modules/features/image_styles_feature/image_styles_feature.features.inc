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

  // Exported image style: advert_on_visualization.
  $styles['advert_on_visualization'] = array(
    'name' => 'advert_on_visualization',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '165',
          'height' => '110',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'advert_on_visualization',
  );

  // Exported image style: award.
  $styles['award'] = array(
    'name' => 'award',
    'effects' => array(
      14 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '80',
          'height' => '80',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'award',
  );

  // Exported image style: award_details.
  $styles['award_details'] = array(
    'name' => 'award_details',
    'effects' => array(
      16 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '140',
          'height' => '140',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'award_details',
  );

  // Exported image style: award_sponsor.
  $styles['award_sponsor'] = array(
    'name' => 'award_sponsor',
    'effects' => array(
      15 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '140',
          'height' => '80',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'award_sponsor',
  );

  // Exported image style: award_sponsor_details.
  $styles['award_sponsor_details'] = array(
    'name' => 'award_sponsor_details',
    'effects' => array(
      17 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '240',
          'height' => '140',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'award_sponsor_details',
  );

  // Exported image style: contest_gallery_thumb.
  $styles['contest_gallery_thumb'] = array(
    'name' => 'contest_gallery_thumb',
    'effects' => array(
      15 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '232',
          'height' => '150',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'contest_gallery_thumb',
  );

  // Exported image style: contest_thumbnail.
  $styles['contest_thumbnail'] = array(
    'name' => 'contest_thumbnail',
    'effects' => array(
      10 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => '173',
          'height' => '110',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'contest_thumbnail',
  );

  // Exported image style: event_blog_teaser_eighth.
  $styles['event_blog_teaser_eighth'] = array(
    'name' => 'event_blog_teaser_eighth',
    'effects' => array(
      9 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '76',
          'height' => '50',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_eighth',
  );

  // Exported image style: event_blog_teaser_fifth.
  $styles['event_blog_teaser_fifth'] = array(
    'name' => 'event_blog_teaser_fifth',
    'effects' => array(
      6 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '525',
          'height' => '349',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_fifth',
  );

  // Exported image style: event_blog_teaser_first.
  $styles['event_blog_teaser_first'] = array(
    'name' => 'event_blog_teaser_first',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '700',
          'height' => '350',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_first',
  );

  // Exported image style: event_blog_teaser_fourth.
  $styles['event_blog_teaser_fourth'] = array(
    'name' => 'event_blog_teaser_fourth',
    'effects' => array(
      5 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '232',
          'height' => '154',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_fourth',
  );

  // Exported image style: event_blog_teaser_second.
  $styles['event_blog_teaser_second'] = array(
    'name' => 'event_blog_teaser_second',
    'effects' => array(
      4 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '349',
          'height' => '230',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_second',
  );

  // Exported image style: event_blog_teaser_seventh.
  $styles['event_blog_teaser_seventh'] = array(
    'name' => 'event_blog_teaser_seventh',
    'effects' => array(
      8 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '115',
          'height' => '75',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_seventh',
  );

  // Exported image style: event_blog_teaser_sixth.
  $styles['event_blog_teaser_sixth'] = array(
    'name' => 'event_blog_teaser_sixth',
    'effects' => array(
      7 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '173',
          'height' => '115',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_sixth',
  );

  // Exported image style: event_blog_teaser_sixth_extra.
  $styles['event_blog_teaser_sixth_extra'] = array(
    'name' => 'event_blog_teaser_sixth_extra',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '174',
          'height' => '115',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_sixth_extra',
  );

  // Exported image style: event_blog_teaser_third.
  $styles['event_blog_teaser_third'] = array(
    'name' => 'event_blog_teaser_third',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '466',
          'height' => '310',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_blog_teaser_third',
  );

  // Exported image style: event_logo.
  $styles['event_logo'] = array(
    'name' => 'event_logo',
    'label' => 'event_logo',
    'effects' => array(
      11 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '230',
          'height' => '130',
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: event_logo_once.
  $styles['event_logo_once'] = array(
    'name' => 'event_logo_once',
    'label' => 'event_logo_once',
    'effects' => array(
      15 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '700',
          'height' => '130',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: event_logo_twice.
  $styles['event_logo_twice'] = array(
    'name' => 'event_logo_twice',
    'label' => 'event_logo_twice',
    'effects' => array(
      16 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '347',
          'height' => '130',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: event_map_picture_preview.
  $styles['event_map_picture_preview'] = array(
    'name' => 'event_map_picture_preview',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '230',
          'height' => '150',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'event_map_picture_preview',
  );

  // Exported image style: frontpage_event_padding.
  $styles['frontpage_event_padding'] = array(
    'name' => 'frontpage_event_padding',
    'label' => 'frontpage_event_padding',
    'effects' => array(
      13 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '230',
          'height' => '270',
        ),
        'weight' => '2',
      ),
    ),
  );

  // Exported image style: frontpage_event_padding_once.
  $styles['frontpage_event_padding_once'] = array(
    'name' => 'frontpage_event_padding_once',
    'label' => 'frontpage_event_padding_once',
    'effects' => array(
      14 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '700',
          'height' => '270',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: frontpage_event_padding_twice.
  $styles['frontpage_event_padding_twice'] = array(
    'name' => 'frontpage_event_padding_twice',
    'label' => 'frontpage_event_padding_twice',
    'effects' => array(
      17 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '347',
          'height' => '270',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: header.
  $styles['header'] = array(
    'name' => 'header',
    'effects' => array(
      3 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => '940',
          'height' => '380',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'header',
  );

  // Exported image style: header_thumbnail.
  $styles['header_thumbnail'] = array(
    'name' => 'header_thumbnail',
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
          'width' => '94',
          'height' => '38',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'header_thumbnail',
  );

  // Exported image style: hotel_preview.
  $styles['hotel_preview'] = array(
    'name' => 'hotel_preview',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '466',
          'height' => '310',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'hotel_preview',
  );

  // Exported image style: my_events_logo.
  $styles['my_events_logo'] = array(
    'name' => 'my_events_logo',
    'label' => 'My events logo 50x50',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '50',
          'height' => '50',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: node_image_first.
  $styles['node_image_first'] = array(
    'name' => 'node_image_first',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '700',
          'height' => '470',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'node_image_first',
  );

  // Exported image style: node_image_second.
  $styles['node_image_second'] = array(
    'name' => 'node_image_second',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '349',
          'height' => '230',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'node_image_second',
  );

  // Exported image style: node_image_third.
  $styles['node_image_third'] = array(
    'name' => 'node_image_third',
    'effects' => array(
      3 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '232',
          'height' => '150',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'node_image_third',
  );

  // Exported image style: node_userpic.
  $styles['node_userpic'] = array(
    'name' => 'node_userpic',
    'effects' => array(
      5 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '40',
          'height' => '40',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'node_userpic',
  );

  // Exported image style: organizer_details.
  $styles['organizer_details'] = array(
    'name' => 'organizer_details',
    'effects' => array(
      10 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '80',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
      14 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => '80',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
    ),
    'label' => 'organizer_details',
  );

  // Exported image style: organizer_info.
  $styles['organizer_info'] = array(
    'name' => 'organizer_info',
    'effects' => array(
      12 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '40',
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
      13 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => '40',
          'upscale' => 0,
        ),
        'weight' => '2',
      ),
    ),
    'label' => 'organizer_info',
  );

  // Exported image style: race_teaser.
  $styles['race_teaser'] = array(
    'name' => 'race_teaser',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '220',
          'height' => '140',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'race_teaser',
  );

  // Exported image style: scoring_winner.
  $styles['scoring_winner'] = array(
    'name' => 'scoring_winner',
    'effects' => array(
      14 => array(
        'label' => 'Aspect switcher',
        'help' => 'Use different effects depending on whether the image is landscape of portrait shaped. This re-uses other preset definitions, and just chooses between them based on the rule.',
        'effect callback' => 'canvasactions_aspect_image',
        'dimensions callback' => 'canvasactions_aspect_dimensions',
        'form callback' => 'canvasactions_aspect_form',
        'summary theme' => 'canvasactions_aspect_summary',
        'module' => 'imagecache_canvasactions',
        'name' => 'canvasactions_aspect',
        'data' => array(
          'portrait' => 'scoring_winner_vertical',
          'landscape' => 'scoring_winner_horizontal',
          'ratio_adjustment' => '1',
        ),
        'weight' => '2',
      ),
    ),
    'label' => 'scoring_winner',
  );

  // Exported image style: scoring_winner_horizontal.
  $styles['scoring_winner_horizontal'] = array(
    'name' => 'scoring_winner_horizontal',
    'effects' => array(
      11 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '440',
          'height' => '290',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'scoring_winner_horizontal',
  );

  // Exported image style: scoring_winner_vertical.
  $styles['scoring_winner_vertical'] = array(
    'name' => 'scoring_winner_vertical',
    'effects' => array(
      10 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '290',
          'height' => '440',
        ),
        'weight' => '1',
      ),
    ),
    'label' => 'scoring_winner_vertical',
  );

  // Exported image style: user_picture.
  $styles['user_picture'] = array(
    'name' => 'user_picture',
    'effects' => array(
      12 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => '150',
          'height' => '150',
        ),
        'weight' => '2',
      ),
    ),
    'label' => 'user_picture',
  );

  // Exported image style: user_picture_mini.
  $styles['user_picture_mini'] = array(
    'name' => 'user_picture_mini',
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
    'label' => 'user_picture_mini',
  );

  return $styles;
}
