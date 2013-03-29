<?php
/**
 * @file Combination of event-brick and twocolfourrow
 * @author Vadim Valuev <gease@mail.ru>
 */
?>
<div class="panel-display" <?php
if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
    <div id="page">
      <div class="region_inner">

        <div class="featured-header at-panel clearfix">

          <?php if ($content['featured_header_title']): ?>
            <div class="featured-header-title">
              <?php print $content['featured_header_title']; ?>
            </div>
          <?php endif; ?>

          <?php if ($content['featured_header_padding']): ?>
            <div class="featured-header-padding">
              <?php print $content['featured_header_padding']; ?>
            </div>
          <?php endif; ?>

        </div>

        <div id="top" class="clearfix">
          <div id="top_inner">
           <?php print $content['top']; ?>
          </div>
        </div>

        <div class="panel-panel line">

          <div class="panel-panel unit panel-col-seventy firstUnit">
            <div class="inside">
              <div class="at-panel panel-display two-brick panel_info clearfix" >
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
            </div>
          </div>

          <div class="panel-panel panel-col-thirty second_sidebar lastUnit">
            <div class="inside">
              <?php print $content['right']; ?>
            </div>
          </div>

        </div>

      </div>
    </div>
</div>

