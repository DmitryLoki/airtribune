<?php

/**
 * @file
 * Airtribune2 theme implementation for entities.
 *
 * @see airtribune2_preprocess_entity()
 */

// See http://drupal.org/node/1356876
hide($content['title']);

?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="content"<?php print $content_attributes; ?>>
    <?php print render($content); ?>
  </div>
</div>
