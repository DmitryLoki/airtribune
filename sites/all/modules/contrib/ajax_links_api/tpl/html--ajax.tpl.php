<?php

/**
 * @file
 * Overridden theme implementation to display the basic html structure of a 
 * single Ajax Drupal page.
 *
 * You can use any variable available in html.tpl.php.
 */
?>
<!-- title is required if html5 settings enabled in module config page -->
<title><?php echo $head_title; ?></title>
<?php echo $scripts ?>
<?php echo $styles ?>
<?php echo $page_top; ?>
<?php echo $page; ?>
<?php echo $page_bottom; ?>
