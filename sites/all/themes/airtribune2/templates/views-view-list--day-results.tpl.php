<?php

/**
 * @file
 * Default simple view template to display a list of rows.
 *
 * - $title : The title of this group of rows.  May be empty.
 * - $options['type'] will either be ul or ol.
 * @ingroup views_templates
 */

?>
<?php print $wrapper_prefix; ?>
  <span class="task_result">
	<?php if (!empty($title)) : ?>
	  <span class="label"><?php print $title == 'Field collection field_day_results' ? t('Task results') : t('Competition results'); ?></span>
	<?php endif; ?>
	
	  <?php foreach ($rows as $id => $row): ?>

	    <span class="file"><?php print str_replace(array('  ', "\n", "\r"), '', $row); ?></span>
	  <?php endforeach; ?>
	
  </span>
<?php print $wrapper_suffix; ?>