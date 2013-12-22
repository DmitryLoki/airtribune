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

<?php print $fields['day_set_a_task']->wrapper_prefix; ?>
<?php print $fields['day_set_a_task']->content; ?>
<?php print $fields['day_set_a_task']->wrapper_suffix; ?>

<?php if (!empty($fields['id_1']->raw) && !empty($fields['field_pg_race_points']->raw)): ?>
  <a href="#map" class="task_link"><span>Task</span></a>
<?php endif; ?>


<?php if (!empty($fields['view'])): ?>
  <span class="views-field dropdown_list views-field-view">
  <?php print $fields['view']->label_html; ?>
  <?php print $fields['view']->content; ?>
  </span>
<?php endif; ?>

<?php if ($fields['pg_race_retrieve_links']->content): ?>
  <span class="views-field dropdown_list views-field-field-pg-race-retrieve-links">
    <?php
      // output retrieve links
       print $fields['pg_race_retrieve_links']->label_html;
       print $fields['pg_race_retrieve_links']->content;
    ?>
  </span>
<?php endif; ?>

<?php 
if (strpos($fields['day_pg_race_play_link']->content, t('Watch Live')) !== false) {
  $fields['day_pg_race_play_link']->wrapper_prefix = '<span class="views-field dropdown_list views-field-day-pg-race-play-live-link">';
  $fields['day_pg_race_play_link']->wrapper_suffix = '</span>';
}
else {
  $fields['day_pg_race_play_link']->wrapper_prefix = '<span class="views-field dropdown_list views-field-day-pg-race-play-link">';
}?>
<?php print $fields['day_pg_race_play_link']->wrapper_prefix; ?>
<?php print $fields['day_pg_race_play_link']->label_html; ?>
<?php print $fields['day_pg_race_play_link']->content; ?>
</span>

<?php if (!empty($fields['field_pg_race_tracks'])): ?>
  <span class="views-field dropdown_list views-field-field-pg-race-tracks">
  <?php print $fields['field_pg_race_tracks']->label_html; ?>
  <?php print $fields['field_pg_race_tracks']->content; ?>
  </span>
<?php endif; ?>

<?php print $fields['field_dayblog_ref']->wrapper_prefix; ?>
<?php print $fields['field_dayblog_ref']->content; ?>
<?php print $fields['field_dayblog_ref']->wrapper_suffix; ?>

<?php print $fields['field_image']->wrapper_prefix; ?>
<?php print $fields['field_image']->content; ?>
<?php print $fields['field_image']->wrapper_suffix; ?>
