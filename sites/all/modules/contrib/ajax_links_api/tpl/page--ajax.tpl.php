<?php

/**
 * @file
 * Overridden theme implementation to display a ajax Drupal page.
 *
 * You can use any variable available in page.tpl.php.
 */
?>
<?php print $messages; ?>
<?php print render($title_prefix); ?>
<?php if ($title): ?><h1 id="page-title"><?php print $title; ?></h1><?php endif; ?>
<?php print render($title_suffix); ?>
<?php if ($tabs = render($tabs)): ?><div class="tabs"><?php print $tabs; ?></div><?php endif; ?>
<?php if ($action_links = render($action_links)): ?><ul class="action-links"><?php print $action_links; ?></ul><?php endif; ?>
<?php print render($page['content']); ?>
