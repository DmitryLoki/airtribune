<?php

/**
 * @file
 * Default theme implementation to display event statistics pane.
 *
 * @see template_preprocess_airtribune_statistics_pane().
 */

?>
<div class="es-pane">
  <div class="es-pilots">
    <div class="es-pilots-confirmed">
      <div class="es-count"><?php print $pilots_confirmed; ?></div>
      <div class="es-label">
        <?php print t('Pilots'); ?><br/>
        <span><?php print t('confirmed'); ?></span>
      </div>
    </div>
    <div class="es-pilots-waiting">
      <div class="es-count"><?php print $pilots_waiting; ?></div>
      <div class="es-label">
        <?php print t('Pilots'); ?><br/>
        <span><?php print t('in waiting list'); ?></span>
      </div>
    </div>
    <div class="more-link">
      <?php print $pilots_list_link; ?>
    </div>
  </div>
  <div class="es-places">
    <div class="es-accommodation">
      <div class="es-count">
        <?php print $accommodation; ?>
      </div>
      <div class="es-label">
        <?php print t('Accommodation'); ?><br/>
        <span><?php print t('places'); ?></span>
      </div>
    </div>
    <div class="es-activities">
      <div class="es-count">
        <?php print $activities; ?>
      </div>
      <div class="es-label">
        <?php print t('Activities'); ?><br/>
        <span><?php print t('places'); ?></span>
      </div>
    </div>
    <div class="more-link">
      <?php print $event_map_link; ?>
    </div>
  </div>
</div>
