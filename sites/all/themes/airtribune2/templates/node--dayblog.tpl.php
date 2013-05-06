<?php
/**
 * @file
 * Airtribune2 implementation to display a node.
 */
?>
<div class="item">
  <div class="posted">
    <?php print render($content['time']); ?>
  </div>
  <div>
    <?php print render($content); ?>
  </div>
</div>
