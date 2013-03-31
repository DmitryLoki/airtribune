<!-- -*-html-helper-*- -->

<div class="panel-display panel-onecol-threerow clear-block" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>  
  <div id="super">
    <header id="header" class="clearfix" role="banner">
      <div id="header_inner"><div class="region_inner">
        <?php print $content['header']; ?>
      </div></div>
    </header>
      <?php print $content['middle']; ?>
  </div>
  <footer id="footer" class="clearfix" role="contentinfo">
    <div id="footer_inner">
      <div class="region_inner">
        <?php print $content['footer']; ?>
      </div>
    </div>
  </footer>
</div>
