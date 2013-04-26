<?php
// Back to human file descriptions.
// See #3094-7.
foreach ($row->field_field_day_results as &$file) {
  $file['rendered']['#file']->description = airtribune_prize_categories($file['rendered']['#file']->description);
}
print $field->advanced_render($row);
