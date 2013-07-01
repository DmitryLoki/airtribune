<?php

/**
 * @file
 * Event days fields template.
 * 
 * 
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->wrapper_prefix: A complete wrapper containing the inline_html to use.
 *   - $field->wrapper_suffix: The closing tag for the wrapper.
 *   - $field->separator: an optional separator that may appear before a field.
 *   - $field->label: The wrap label text to use.
 *   - $field->label_html: The full HTML of the label to use including
 *     configured element type.
 * - $row: The raw result object from the query, with all data it fetched.
 *
 * @ingroup views_templates
 */
?>

<?php

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

$separator = '';

/*
 * Calculate number of days
 * @see #3339
 * @author Vyacheslav Malchik <info@vkey.biz>
 * @TODO: removed after implementation of the calculation of the number of the day
 */

global $day_number;
if (!$day_number && !($day_number === 0)) {
  $day_number = 0;
  foreach ($view->result as $key => $result) {
    if (!in_array($result->field_field_day_status[0]['raw']['value'], array(4,5))) {
      $day_number++;
    }
  }
}
?>
<?php 
/**
 *  Hide title if day is trainig or registration
 *  @see #3332
 *  @author Vyacheslav Malchik <info@vkey.biz>
 */
?>
<?php print $fields['title']->wrapper_prefix; ?>
<?php if ($fields['field_day_status']->content != 'Registration day' && $fields['field_day_status']->content != 'Training day'): ?>
  <?php
    $day = $day_number--;
    print "<div class=\"day-number\" data-href=\"#day_{$day}\"></div>";
    print $fields['title']->content;
    $separator = ' — ';
  ?>
  <?php if ($fields['title_1']->content): ?>
    <?php print ' — ' . $fields['title_1']->content; ?>
  <?php endif; ?>
<?php else: ?>
  <?php 
    $anchor = str_replace(' day', '',$fields['field_day_status']->content);
    print "<div class=\"day-number\" data-href=\"#{$anchor}\"></div>";
  ?>
<?php endif; ?>

<?php if ($fields['field_day_status']->content != 'Ok'): ?>
  <?php print $separator . $fields['field_day_status']->content; ?>
<?php endif; ?>
<?php if (date('Ymd') == date('Ymd', $fields['created']->raw)): ?>
  <?php print '<span class="posted">' . t('Today') . '</span>'; ?>
<?php else: ?>
  <?php print $fields['created']->content; ?>
<?php endif; ?>
<?php print $fields['title']->wrapper_suffix; ?>

<?php print $fields['day_set_a_task']->wrapper_prefix; ?>
<?php print $fields['day_set_a_task']->content; ?>
<?php print $fields['day_set_a_task']->wrapper_suffix; ?>

<?php if (!empty($fields['id_1']->raw) && !empty($fields['field_pg_race_points']->raw)): ?>
  <a href="#map" class="task_link"><span>Task</span></a>
<?php endif; ?>


<?php if (!empty($fields['view'])): ?>
  <?php print $fields['view']->wrapper_prefix; ?>
  <?php print $fields['view']->label_html; ?>
  <?php print $fields['view']->content; ?>
  <?php print $fields['view']->wrapper_suffix; ?>
<?php endif; ?>

<?php if (!empty($fields['field_pg_race_tracks'])): ?>
  <?php print $fields['pg_race_play_link']->wrapper_prefix; ?>
  <?php print $fields['pg_race_play_link']->label_html; ?>
  <?php print $fields['pg_race_play_link']->content; ?>
  <?php print $fields['pg_race_play_link']->wrapper_suffix; ?>
<?php endif; ?>

<?php if (!empty($fields['field_pg_race_tracks'])): ?>
  <?php print $fields['field_pg_race_tracks']->wrapper_prefix; ?>
  <?php print $fields['field_pg_race_tracks']->label_html; ?>
  <?php print $fields['field_pg_race_tracks']->content; ?>
  <?php print $fields['field_pg_race_tracks']->wrapper_suffix; ?>
<?php endif; ?>

<?php print $fields['field_dayblog_ref']->wrapper_prefix; ?>
<?php print $fields['field_dayblog_ref']->content; ?>
<?php print $fields['field_dayblog_ref']->wrapper_suffix; ?>

<?php print $fields['nothing']->wrapper_prefix; ?>
<?php print $fields['nothing']->content; ?>
<?php print $fields['nothing']->wrapper_suffix; ?>

<?php if ($photos): ?>
<div class="field-name-field-image">
  <?php print render($photos); ?>
</div>
<?php endif; ?>
