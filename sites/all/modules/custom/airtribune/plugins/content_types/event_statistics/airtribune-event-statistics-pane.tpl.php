<?php

/**
 * @file
 * Default theme implementation to display event statistics pane.
 *
 * @see template_preprocess_airtribune_statistics_pane()
 * @see theme_airtribune_event_statistics()
 */

?>
<div class="es-pane">
  <div class="es-pilots">
    <?php print $pilots_confirmed; ?>
    <?php print $pilots_waiting; ?>
    <div class="more-link">
      <?php print l(t('View pilots list'), $pilots_url); ?><br/>
    </div>
  </div>
  <div class="es-places">
     <?php print $accommodation; ?>
      <?php print $activities; ?>
    <div class="more-link">
      <?php print l(t('View event map'), $places_url); ?><br/>
    </div>
  </div>
</div>
