<?php

/**
 * @file
 * Event days fields.
 */

?>
<h3>
<?php print $fields['title']->content; ?> — <?php print $fields['field_day_status']->content; ?>
<?php if ($fields['field_pg_race_ref']->content): ?>
  — <?php print $fields['field_pg_race_ref']->content; ?>
<span><?php print $fields['created']->content; ?></span>
<?php endif; ?>
</h3>
<?php print $fields['field_day_blog']->content; ?>
<?php print $fields['field_photos']->content; ?>
