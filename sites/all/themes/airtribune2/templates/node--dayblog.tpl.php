<?php
/**
 * @file
 * Airtribune2 implementation to display a node.
 */
?>
<article class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div>
    <?php print render($content['time']); ?>
  </div>
  <div>
    <?php print render($content['field_plain_body']); ?>
  </div>
</article>
