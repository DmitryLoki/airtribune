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


?>
<?php print $fields['title']->wrapper_prefix; ?>
<?php print $fields['title']->content; ?>
<?php print $fields['title']->wrapper_suffix; ?>

<span class="views-field views-field-field-day-results">
  <span class="views-label"><?php print t('Results'); ?></span>
  <span class="field-content">
    <span><?php print t('Task results') ?></span>
    <?php print $fields['field_day_results']->content; ?>
    <span><?php print t('Competition results') ?></span>
    <?php print $fields['field_competition_results']->content; ?>
  </span>
</span>

<?php print $fields['field_pg_race_tracks']->wrapper_prefix; ?>
<?php print $fields['field_pg_race_tracks']->label_html; ?>
<?php print $fields['field_pg_race_tracks']->content; ?>
<?php print $fields['field_pg_race_tracks']->wrapper_suffix; ?>

<?php print $fields['field_day_blog']->wrapper_prefix; ?>
<?php print $fields['field_day_blog']->content; ?>
<?php print $fields['field_day_blog']->wrapper_suffix; ?>

<?php if ($photos): ?>
<div class="field-name-field-image">
  <?php print render($photos); ?>
</div>
<?php endif; ?>
