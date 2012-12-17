<div<?php print $css_id ? " id=\"$css_id\"" : ''; ?> class="<?php print $classes; ?>">

  <?php if (!empty($content['leaderboard'])): ?>
    <div id="leaderboard-wrapper">
      <div class="container clearfix">
        <div class="region region-leaderboard">
          <?php print render($content['leaderboard']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['header'])): ?>
    <div id="header-wrapper">
      <div class="container clearfix">
        <?php print render($content['header']); ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['menu_bar'])): ?>
    <div id="nav-wrapper">
      <div class="container clearfix">
        <div id="menu-bar" class="nav clearfix">
          <?php print render($content['menu_bar']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['help'])): ?>
    <div id="messages-help-wrapper">
      <div class="container clearfix">
        <div class="region region-help">
          <?php print render($content['help']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['secondary_content'])): ?>
    <div id="secondary-content-wrapper">
      <div class="container clearfix">
        <div class="region region-secondary-content">
          <?php print render($content['secondary_content']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <div id="content-wrapper">
    <div class="container">

      <div id="columns">
        <div class="columns-inner clearfix">
          <div id="content-column" role="main">
            <div class="content-inner">

              <?php if (!empty($content['highlighted'])): ?>
                <div class="region region-highlighted">
                  <?php print render($content['highlighted']); ?>
                </div>
              <?php endif; ?>

              <div id="main-content">
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
    </div>
  </div>

  <?php if (!empty($content['tertiary_content'])): ?>
    <div id="tertiary-content-wrapper">
      <div class="container clearfix">
        <div class="region region-tertiary-content">
          <?php print render($content['tertiary_content']); ?>
        </div>
      </div>
    </div>
  <?php endif; ?>

  <?php if (!empty($content['footer'])): ?>
    <div id="footer-wrapper">
      <div class="container clearfix">
        <footer id="footer" role="contentinfo">
          <?php print render($content['footer']); ?>
        </footer>
      </div>
    </div>
  <?php endif; ?>

</div>
