<!-- -*-html-helper-*- -->

<div class="panel-display panel-twocol-fourrow clear-block" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>
  <div id="super">
    <header id="header" class="clearfix" role="banner">
      <div id="header_inner"><div class="region_inner">
        <?php print $content['header']; ?>
      </div></div>
    </header>
    <div id="page"><div class="region_inner">
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

       <div class="panel-panel panel-col-thirty lastUnit">
        <div class="inside">
          <?php print $content['right']; ?>
        </div>
       </div>
      </div></div>
    </div>
  </div>
  <footer id="footer" class="clearfix" role="contentinfo">
    <div id="footer_inner"><div class="region_inner">
      <?php print $content['footer']; ?>
    </div></div>
  </footer>
</div>
