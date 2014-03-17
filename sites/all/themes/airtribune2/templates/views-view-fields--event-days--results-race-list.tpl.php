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

$separator = ' — ';

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


<?php print $fields['pg_race_preview_image']->wrapper_prefix; ?>
<?php print $fields['pg_race_preview_image']->content; ?>
<?php print $fields['pg_race_preview_image']->wrapper_suffix; ?>

<div class="views-field results_head">
  <?php if ($fields['field_day_status']->content != 'Registration day' && $fields['field_day_status']->content != 'Training day'): ?>
    
    <?php if ($fields['title_1']->content): ?>
      <div class="task_title"><?php print $fields['title_1']->content; ?></div>
    <?php endif; ?>
  <?php else: ?>
    <?php 
      $anchor = str_replace(' day', '',$fields['field_day_status']->content);
      print "<div class=\"day-number\" data-href=\"#{$anchor}\"></div>";
    ?>
  <?php endif; ?>

  <?php 
  // output srting date
  // event/%nid/blog
  $contest_nid = arg(1);
  print '<span class="posted">' . airtribune_get_string_date_of_contest_day($contest_nid, $fields['created']->raw) . '</span>';
  ?>

<?php
print $fields['type']->wrapper_prefix;
if (!empty($fields['field_optdistance']->content)) {
  print "<b>" . $fields['field_optdistance']->content . t(" km") . "</b>" . $separator;
}
print $fields['type']->content;
print $fields['type']->wrapper_suffix; ?>
</div>

<?php if (!empty($fields['field_pg_race_tracks'])): ?>
  <?php print $fields['pg_race_play_link']->wrapper_prefix; ?>
  <?php print $fields['pg_race_play_link']->label_html; ?>
  <?php print str_replace(array('  ', "\n", "\r"), '', $fields['pg_race_play_link']->content); ?>
  <?php print $fields['pg_race_play_link']->wrapper_suffix; ?>
<?php endif; ?>

<?php if (!empty($fields['view'])): ?>
  <?php print $fields['view']->wrapper_prefix; ?>
  <?php print $fields['view']->label_html; ?>
  <?php print $fields['view']->content; ?>
  <?php print $fields['view']->wrapper_suffix; ?>
<?php endif; ?>

<?php if (!empty($fields['field_pg_race_tracks'])): ?>
  <?php print $fields['field_pg_race_tracks']->wrapper_prefix; ?>
  <?php print $fields['field_pg_race_tracks']->label_html; ?>
  <?php print $fields['field_pg_race_tracks']->content; ?>
  <?php print $fields['field_pg_race_tracks']->wrapper_suffix; ?>
<?php endif; ?>

<?php print $fields['nothing']->wrapper_prefix; ?>
<?php print $fields['nothing']->content; ?>
<?php print $fields['nothing']->wrapper_suffix; ?>
