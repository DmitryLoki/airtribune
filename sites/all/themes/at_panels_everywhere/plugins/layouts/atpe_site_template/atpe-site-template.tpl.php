<div<?php print $css_id ? " id=\"$css_id\"" : ''; ?> class="container <?php print $classes; ?>">

  <?php if (!empty($content['leaderboard'])): ?>
    <div class="region region-leaderboard">
      <?php print render($content['leaderboard']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['header'])): ?>
    <?php print render($content['header']); ?>
  <?php endif; ?>

  <?php if (!empty($content['menu_bar'])): ?>
    <div id="menu-bar" class="nav clearfix">
      <?php print render($content['menu_bar']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['help'])): ?>
    <div class="region region-help">
      <?php print render($content['help']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['secondary_content'])): ?>
    <div class="region region-secondary-content">
      <?php print render($content['secondary_content']); ?>
    </div>
  <?php endif; ?>

  <div id="columns">
    <div class="columns-inner clearfix">
      <div id="content-column" role="main">
        <div class="content-inner">

          <?php if (!empty($content['highlighted'])): ?>
            <div class="region region-highlighted">
              <?php print render($content['highlighted']); ?>
            </div>
          <?php endif; ?>

          <div id="content">
            <div class="region region-content">
              <?php print render($content['content']); ?>
            </div>
          </div>

          <?php if (!empty($content['content_aside'])): ?>
            <div class="region region-content-aside">
              <?php print render($content['content_aside']); ?>
            </div>
          <?php endif; ?>

        </div>
      </div>

      <?php if (!empty($content['sidebar_first'])): ?>
        <div class="region region-sidebar-first sidebar">
          <?php print render($content['sidebar_first']); ?>
        </div>
      <?php endif; ?>

      <?php if (!empty($content['sidebar_second'])): ?>
        <div class="region region-sidebar-second sidebar">
          <?php print render($content['sidebar_second']); ?>
        </div>
      <?php endif; ?>

    </div>
  </div>

  <?php if (!empty($content['tertiary_content'])): ?>
    <div class="region region-tertiary-content">
      <?php print render($content['tertiary_content']); ?>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['footer'])): ?>
    <footer id="footer" role="contentinfo">
      <?php print render($content['footer']); ?>
    </footer>
  <?php endif; ?>

</div>
