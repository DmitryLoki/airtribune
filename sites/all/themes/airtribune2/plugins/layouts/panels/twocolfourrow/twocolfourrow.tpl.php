<!-- -*-html-helper-*- -->

<div class="panel-display panel-twocol-fourrow clear-block" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div id="super">

    <header id="header" class="clearfix" role="banner">
      <div id="header_inner"><div class="region_inner">
        <?php print $content['header']; ?>
      </div></div>
    </header>

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
              <?php print $content['left']; ?>
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

  <footer id="footer" class="clearfix" role="contentinfo">
    <div id="footer_inner">
      <div class="region_inner">
      <?php print $content['footer']; ?>
      </div>
    </div>
  </footer>

</div>
