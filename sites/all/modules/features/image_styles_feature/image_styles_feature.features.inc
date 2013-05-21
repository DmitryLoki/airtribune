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

  // Exported image style: award.
  $styles['award'] = array(
    'name' => 'award',
    'effects' => array(
      4 => array(
        'label' => 'Resize',
        'help' => 'Resizing will make images an exact set of dimensions. This may cause images to be stretched or shrunk disproportionately.',
        'effect callback' => 'image_resize_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_resize',
        'data' => array(
          'width' => '45',
          'height' => '45',
        ),
        'weight' => '1',
      ),
    ),
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
  );

  // Exported image style: scoring_winner_horizontal.
  $styles['scoring_winner_horizontal'] = array(
    'name' => 'scoring_winner_horizontal',
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
          'width' => '400',
          'height' => '260',
        ),
        'weight' => '1',
      ),
    ),
  );

  // Exported image style: scoring_winner_vertical.
  $styles['scoring_winner_vertical'] = array(
    'name' => 'scoring_winner_vertical',
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
          'width' => '300',
          'height' => '450',
        ),
        'weight' => '1',
      ),
    ),
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
  );

  return $styles;
}
