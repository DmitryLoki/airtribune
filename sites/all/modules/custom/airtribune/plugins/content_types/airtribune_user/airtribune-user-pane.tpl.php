<?php

/**
 * @file
 * Default theme implementation to display user pane.
 */

?>
<div id="sign-in">
  <div id="airtribune-user">

    <div class="lang-icon">
      <span>
        <?php print $lang_icon; ?>
      </span>
    </div>
    <?php if ($logged_in): ?>
      <div class="user-button">
        <a href="<?php print $user_profile_link; ?>">
          <span><?php print $user_name; ?></span>
        </a>
      </div>
      <?php print $user_picture; ?>
    <?php else: ?>
      <div class="user-button">
        <?php print l(t('Sign in'), 'user'); ?>
      </div>
    <?php endif; ?>

    <div class="drop-item flags">
      <div class="pane-inner">
        <?php print $lang_links; ?>
      </div>
    </div>
    <?php if ($logged_in): ?>
      <div class="drop-item user-menu">
        <div class="pane-inner">
          <?php print $user_menu; ?>
        </div>
      </div>
    <?php else: ?>
      <div class="drop-item user-login">
        <div class="pane-inner">
          <?php print $login_form; ?>
        </div>
      </div>
     <?php endif; ?>

  </div>
</div>
