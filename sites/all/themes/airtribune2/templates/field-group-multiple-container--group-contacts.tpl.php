<?php
/**
 * - group
 * - items
 *  - delta + field_name + value render_array or null if empty
 */

$labels = array(
  t('General questions'),
  t('Selection and entry'),
  t('Transportation'),
  t('Accomodation')
);

?>
<div class="clearfix">
  <?php foreach($entries as $delta => $entry): ?>
    <h3><?php print $labels[$delta]; ?></h3>
    <div class="clearfix">
    <?php foreach($entry as $field_name => $field): ?>
      <div>
      <?php if(!is_null($field)): ?>
        <?php print render($field); ?>
      <?php else: ?>
        <span class="field-is-empty"> </span>
      <?php endif; ?>
      </div>
    <?php endforeach; ?>
    </div>
  <?php endforeach; ?>
</div>
