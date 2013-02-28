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
    <?php
      $wrapper_class = 'field-wrapper'; 
      if ($delta%2) {
        $wrapper_class .= ' even';
      } 
    ?>
    <div class="<?php print $wrapper_class; ?>">
      <h3><?php print $labels[$delta]; ?></h3>
      <div class="clearfix">
      <?php
        $entry['field_contacts_email']['#title'] = t('email');
        $entry['field_contacts_phone']['#title'] = t('tel');
      ?>
      <?php foreach($entry as $field_name => $field): ?>
        <div>
        <?php if(!empty($field[0]['#markup'])): ?>
          <?php print render($field); ?>
        <?php else: ?>
          <span class="field-is-empty"> </span>
        <?php endif; ?>
        </div>
      <?php endforeach; ?>
      </div>
    </div>
  <?php endforeach; ?>
</div>
