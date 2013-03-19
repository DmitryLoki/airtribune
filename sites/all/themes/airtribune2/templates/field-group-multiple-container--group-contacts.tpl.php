<?php
/**
 * - group
 * - items
 *  - delta + field_name + value render_array or null if empty
 */

?>
<div class="clearfix">
  <?php foreach($entries as $delta => $entry): ?>
  <div class="clearfix">
    <?php foreach($entry as $field_name => $field): ?>
      <?php if (!empty($field[0]['#markup'])): ?>
        <div class="field-item-<?php print $field_name; ?>">
          <?php print render($field); ?>
        </div>
      <?php endif; ?>
    <?php endforeach; ?>
  </div>
  <?php endforeach; ?>
</div>
