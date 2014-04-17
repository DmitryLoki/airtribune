<?php

// @todo: move this plugin into pg_race.module

$plugin = array(
  'title' => t('Frontpage Live event photo'),
  'renderer' => 'at_helper__frontpage_live_event_photo__renderer',
  'required_tokens' => 'at_helper__frontpage_live_event_photo__required_keys',
);


function at_helper__frontpage_live_event_photo__renderer(array $components, array $tokens) {
  $values = array();
  foreach ($components as $k => $token) {
    $values[$k] = $tokens[$token];
  }

  $index = $values['counter'];
  $image_style = 'frontpage_event_padding';

  // set in airtribune2_views_pre_render()
  // get total number of view elements and number of the current element
  global $front_live_event_total;
  if (!empty($front_live_event_total)) {
    $standart = floor($front_live_event_total/3) * 3;
    $deviant = $front_live_event_total - $standart;
    if ($deviant == 1) {
      $img_styles = array('frontpage_event_padding_once', 'event_logo_once');
    }
    if ($deviant == 2) {
      $img_styles = array('frontpage_event_padding_twice', 'event_logo_twice');
    }

    if ($index > $standart) {
      $image_style = $img_styles['0'];
    }
  }


  $event_nid = $values['event_nid'];

  $query = new EntityFieldQuery();
  $query->entityCondition('entity_type', 'node');
  $query->entityCondition('bundle', AIRTRIBUNE_DAY_TYPE);
  $query->fieldCondition(OG_AUDIENCE_FIELD, 'target_id', $event_nid);
  $query->fieldCondition(AIRTRIBUNE_IMAGE_FIELD, 'fid', 0, '>');
  $query->propertyOrderBy('created', 'DESC');
  $result = $query->execute();
  $output = '';
  if (!empty($result['node'])) {
    $node = array_shift($result['node']);
    $node = node_load($node->nid);

    $wrapper = entity_metadata_wrapper('node', $node);
    $day_images = $wrapper->{AIRTRIBUNE_IMAGE_FIELD}->value();

    // get last image
    $image_file = array_pop($day_images);

    $file = file_load($image_file['fid']);
    $file_view = file_view($file);

    $file_data = $file_view['file'];
    $file_data['#style_name'] = $image_style;  // for video
    $file_data['#image_style'] = $image_style; // for images
    $output = render($file_data);
  }
  return $output;
}

/**
 * Required token keys.
 */
function at_helper__frontpage_live_event_photo__required_keys() {
  return array(
    'counter',  // current element number
    'event_nid',  // event nid
  );
}
