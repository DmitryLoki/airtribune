<?php

/**
 * @file
 * Airtribune simple view template to all the fields as a row.
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
// Hide WiFi if empty.
if (empty($row->field_field_hotel_wifi[0]['raw']['value'])) {
  unset($fields['field_hotel_wifi']);
}
else {
  // See #2884.
  $fields['field_hotel_wifi']->content = 'Wi-Fi';
}

// Mark headquater hotel.
if ($fields['nid_1']) {
  // $fields['field_geofield_distance']->wrapper_prefix = '<div class="hq-hotel">';
  // $fields['field_geofield_distance']->wrapper_suffix = '</div>';
  $fields['field_geofield_distance']->content = t('Headquarter');
  unset($fields['nid_1']);
}

?>
<div class="row-inner">
<?php foreach ($fields as $id => $field): ?>
  <?php if (!empty($field->separator)): ?>
    <?php print $field->separator; ?>
  <?php endif; ?>

  <?php print $field->wrapper_prefix; ?>
    <?php print $field->label_html; ?>
    <?php print $field->content; ?>
  <?php print $field->wrapper_suffix; ?>
  <?php if ($id == 'field_photo') {
  	print '<div class="other_fields"><div class="other_fields_inner">';
  }?>
<?php endforeach; ?>
</div></div>
</div>
