<?php

/**
 * @file
 * Event days fields.
 */
$photos = array();
if($row->field_field_image){
    $count = count($row->field_field_image);
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
  foreach($row->field_field_image as $k => $v){
    if(!empty($image_styles[$is_count])){
      $image_style = $image_style_other = $image_styles[$is_count];
    }
    else{
      $image_style = $image_style_other;
    }
    if($v['rendered']['#theme'] != 'colorbox_image_formatter'){
      $v['rendered']['#image_style'] = $image_style;
    }
    else{
      $v['rendered']['#display_settings']['colorbox_node_style'] = $image_style;
    }
    $photos[] = $v['rendered'];
    $is_count++;
    
  }

}

if ($fields['field_day_status']->content != t('Ok')) {
  $fields['title']->content .= ' — ' . $fields['field_day_status']->content;
}
if ($fields['title_1']->content) {
  $fields['title']->content .= ' — ' . $fields['title_1']->content;
}
if (date('Ymd') == date('Ymd', $fields['created']->raw)) {
  $fields['created']->content = '<span class="posted">' . t('Today') . '</span>';
}
$fields['title']->content .= $fields['created']->content;
unset($fields['field_day_status'], $fields['title_1'], $fields['created']);
?>

<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php if ($id == 'field_image') {
      print '<div class="field-name-field-image">' . render($photos) . '</div>';
    }
    else{
      print $field->content;
    }?>
  <?php print $field->wrapper_suffix; ?>
<?php endforeach; ?>

