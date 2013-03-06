<?php print $messages; ?>
<?php print render($page['help']); ?>
<?php if ($primary_local_tasks || $secondary_local_tasks || $action_links): ?>
  <div id="tasks">
    <?php if ($primary_local_tasks): ?>
      <ul class="tabs primary clearfix"><?php print render($primary_local_tasks); ?></ul>
    <?php endif; ?>
    <?php if ($secondary_local_tasks): ?>
      <ul class="tabs secondary clearfix"><?php print render($secondary_local_tasks); ?></ul>
    <?php endif; ?>
    <?php if ($action_links = render($action_links)): ?>
      <ul class="action-links clearfix"><?php print $action_links; ?></ul>
    <?php endif; ?>
  </div>
<?php endif; ?>
