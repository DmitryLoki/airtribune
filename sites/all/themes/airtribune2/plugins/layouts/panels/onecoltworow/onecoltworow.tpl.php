<!-- -*-html-helper-*- -->

<div class="panel-display panel-twocol-fourrow clear-block" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div id="super">

    <div id="page">
      <div class="region_inner">

        <div class="featured-header at-panel clearfix"><a id="map"></a>

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
              <?php print $content['left']; ?>
            </div>
          </div>

        </div>

      </div>
    </div>

  </div>

</div>
