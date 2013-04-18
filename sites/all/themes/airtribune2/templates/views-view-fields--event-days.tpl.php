<?php

/**
 * @file
 * Event days fields.
 */
?>
<h3>
<?php print $fields['title']->content; ?> — <?php print $fields['field_day_status']->content; ?>
<?php if ($fields['title_1']->content): ?>
  — <?php print $fields['title_1']->content; ?>
<span><?php print $fields['created']->content; ?></span>
<?php endif; ?>
</h3>
<?php print $fields['field_day_blog']->content; ?>
<?php print $fields['field_photos']->content; ?>
