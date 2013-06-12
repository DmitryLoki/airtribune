<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>

<?php
// @TODO: remove from template

$field_alias = 'field_'.$field->field;
$raw_items = $row->{$field_alias};
$urls = '';
$logos = '';

foreach ($raw_items as $delta => $raw_item) {
  $separator = ($delta == count($raw_items)-1)?'':', ';
  foreach($raw_item['rendered']['entity']['field_collection_item'] as $key => $value) {
    $urls .= render($value['field_url']) . $separator;
    $logos .= render($value['field_organizer_logo']);
  }
}

$prefix = '<span>' . t('Prizes by') . '</span>';
?>
<?php if ($urls) :?>
  <?php print $prefix . str_replace($prefix, '', $urls); ?>
<?php endif; ?>
<?php print $logos; ?>
