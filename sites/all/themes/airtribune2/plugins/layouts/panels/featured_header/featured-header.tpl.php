<?php
/**
 * @file
 * Header panels layout.
 */
?>
<div class="featured-header at-panel clearfix">
  <?php if ($content['title']): ?>
    <div class="featured-header-title">
      <?php print $content['title']; ?>
    </div>
  <?php endif; ?>
  <?php if ($content['padding']): ?>
    <div class="featured-header-padding">
      <?php print $content['padding']; ?>
    </div>
  <?php endif; ?>
</div>
