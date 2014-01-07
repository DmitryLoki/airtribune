<?php

/**
 * @file
 * Template to display a view as a table.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $header: An array of header labels keyed by field id.
 * - $header_classes: An array of header classes keyed by field id.
 * - $fields: An array of CSS IDs to use for each field id.
 * - $classes: A class or classes to apply to the table, based on settings.
 * - $row_classes: An array of classes to apply to each row, indexed by row
 *   number. This matches the index in $rows.
 * - $rows: An array of row items. Each row is an array of content.
 *   $rows are keyed by row number, fields within rows are keyed by field ID.
 * - $field_classes: An array of classes to apply to each field, indexed by
 *   field id, then row number. This matches the index in $rows.
 * @ingroup views_templates
 */
?>
<table id="manage-pilots-confirmed" <?php if ($classes) { print 'class="'. $classes . '" '; } ?><?php print $attributes; ?>>
  <?php if (!empty($title)) : ?>
    <caption>
        <?php
          switch ($title) {
            case 'Male': print '<div class="sex male">' . t('Men') .'</div>';
              break;
            case 'Female': print '<div class="sex female">' . t('Women') .'</div>';
              break;
          }
        ?>
    </caption>
  <?php endif; ?>
  <?php if (!empty($header)) : ?>
    <thead>
      <tr>
        <th class="views-field-counter">#</th>
        <?php $number_label = ""; ?>
        <?php foreach ($header as $field => $label): ?>
          <?php
          // Issue #4026 remove number column, add number label to pilot's name
          if ($field == "field_contestant_number") {
            $number_label = $label;
            continue;
          }
          if ($field == "field_full_name") {
            $label .= $number_label;
          }          
          ?>
          <th <?php if ($header_classes[$field]) { print 'class="'. $header_classes[$field] . '" '; } ?>>
            <div><?php print $label; ?>
            </div>
          </th>
        <?php endforeach; ?>
      </tr>
    </thead>
  <?php endif; ?>
  <tbody>
    <?php $counter = 1; foreach ($rows as $row_count => $row): ?>
      <tr <?php if ($row_classes[$row_count]) { print 'class="' . implode(' ', $row_classes[$row_count]) .'"';  } ?>>
        <td class="views-field-counter"><?php print $counter++; ?></td>
        <?php foreach ($row as $field => $content): ?>
          <?php
          if ($field == "field_contestant_number") {
            continue;
          }
          ?>
          <td <?php if ($field_classes[$field][$row_count]) { print 'class="'. $field_classes[$field][$row_count] . '" '; } ?><?php print drupal_attributes($field_attributes[$field][$row_count]); ?>>
            <div class="td_inner"><?php print $content; ?></div>
          </td>
        <?php endforeach; ?>
      </tr>
    <?php endforeach; ?>
  </tbody>
</table>
