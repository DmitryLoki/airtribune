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
        <?php print $pilots_confirmed_link; ?><br/>
        <span><?php print t('confirmed'); ?></span>
      </div>
    </div>
    <div class="es-pilots-waiting">
      <div class="es-count"><?php print $pilots_waiting; ?></div>
      <div class="es-label">
        <?php print $pilots_waiting_link; ?><br/>
        <span><?php print t('total registered'); ?></span>
      </div>
    </div>
    <div class="more-link">
      <?php print l(t('View pilots list'), $pilots_url); ?><br/>
    </div>
  </div>
  <div class="es-places">
    <div class="es-accommodation">
      <div class="es-count">
        <?php print $accommodation; ?>
      </div>
      <div class="es-label">
        <?php print l(t('Accommodation', array(), array('context' => 'event-statistics')), $map_url, array('fragment' => 'event-accommodations')); ?><br/>
        <span><?php print t('places', array(), array('context' => 'event-statistics-accommodation')); ?></span>
      </div>
    </div>
    <div class="es-activities">
      <div class="es-count">
        <?php print $activities; ?>
      </div>
      <div class="es-label">
        <?php print l(t('Activities', array(), array('context' => 'event-statistics')), $map_url, array('fragment' => 'event-activities')); ?><br/>
        <span><?php print t('places', array(), array('context' => 'event-statistics-activities')); ?></span>
      </div>
    </div>
    <div class="more-link">
      <?php print l(t('View event map'), $map_url); ?><br/>
    </div>
  </div>
</div>
