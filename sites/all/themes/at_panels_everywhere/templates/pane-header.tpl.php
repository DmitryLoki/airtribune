<header id="header" class="clearfix" role="banner">

  <?php if ($site_logo || $site_name || $site_slogan): ?>
    <!-- start: Branding -->
    <div id="branding" class="branding-elements clearfix">

      <?php if ($site_logo): ?>
        <div id="logo">
          <?php print $site_logo; ?>
        </div>
      <?php endif; ?>

      <?php if ($site_name || $site_slogan): ?>
        <!-- start: Site name and Slogan hgroup -->
        <hgroup id="name-and-slogan"<?php print $hgroup_attributes; ?>>

          <?php if ($site_name): ?>
            <h1 id="site-name"<?php print $site_name_attributes; ?>><?php print $site_name; ?></h1>
          <?php endif; ?>

          <?php if ($site_slogan): ?>
            <h2 id="site-slogan"<?php print $site_slogan_attributes; ?>><?php print $site_slogan; ?></h2>
          <?php endif; ?>

        </hgroup><!-- /end #name-and-slogan -->
      <?php endif; ?>

    </div><!-- /end #branding -->
  <?php endif; ?>

</header>
