<?php
/**
 * @file
 * Adativetheme implementation to present a Panels layout.
 *
 * Available variables:
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout.
 * - $css_id: unique id if present.
 * - $panel_prefix: prints a wrapper when this template is used in certain context,
 *   such as when rendered by Display Suite or other module - the wrapper is
 *   added by Adaptivetheme in the appropriate process function.
 * - $panel_suffix: closing element for the $prefix.
 *
 * @see adaptivetheme_preprocess_event_brick()
 * @see adaptivetheme_preprocess_node()
 * @see adaptivetheme_process_node()
 */

// Ensure variables are always set. In the last hours before cutting a stable
// release I found these are not set when inside a Field Collection using Display
// Suite, even though they are initialized in the templates preprocess function.
// This is a workaround, that may or may not go away.
$panel_prefix = isset($panel_prefix) ? $panel_prefix : '';
$panel_suffix = isset($panel_suffix) ? $panel_suffix : '';
?>
<?php print $panel_prefix; ?>
<div class="at-panel panel-display two-brick panel_info clearfix" <?php if (!empty($css_id)): print "id=\"$css_id\""; endif; ?>>
  <?php if ($content['event_brick_top']): ?>
    <div class="region region-two-brick-top region-conditional-stack">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_top']; ?>
      </div>
    </div>
  <?php endif; ?>
  <div class="panel-row row-1 clearfix">
    <div class="region region-two-brick-left-above">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_left_above']; ?>
      </div>
    </div>
    <div class="region region-two-brick-right-above">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_right_above']; ?>
      </div>
    </div>
  </div>
  <?php if ($content['event_brick_middle']): ?>
    <div class="region region-two-brick-middle region-conditional-stack">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_middle']; ?>
      </div>
    </div>
  <?php endif; ?>
  <div class="panel-row row-1-2 clearfix">
    <div class="region region-two-brick-left-middle">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_left_middle']; ?>
      </div>
    </div>
    <div class="region region-two-brick-right-middle">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_right_middle']; ?>
      </div>
    </div>
  </div>
  <?php if ($content['event_brick_middle_second']): ?>
    <div class="region region-two-brick-middle-second region-conditional-stack">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_middle_second']; ?>
      </div>
    </div>
  <?php endif; ?>
  <div class="panel-row row-2 clearfix">
    <div class="region region-two-big-brick-left-below">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_left_below']; ?>
      </div>
    </div>
    <div class="region region-two-small-brick-right-below">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_right_below']; ?>
      </div>
    </div>
  </div>
  <div class="panel-row row-2-2 clearfix">
    <div class="region region-two-big-brick-left-below">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_left_below_2']; ?>
      </div>
    </div>
    <div class="region region-two-small-brick-right-below">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_right_below_2']; ?>
      </div>
    </div>
  </div>
  <div class="panel-row row-3 clearfix">
    <div class="region region-two-big-brick-left-below">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_left_bottom']; ?>
      </div>
    </div>
    <div class="region region-two-small-brick-right-below">
      <div class="region-inner clearfix">
        <?php print $content['event_brick_right_bottom']; ?>
      </div>
    </div>
  </div>
</div>
<?php print $panel_suffix; ?>
