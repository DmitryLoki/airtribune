<?php

if (module_exists('views')) {
  $plugin = array(
    'title' => t('Views: Filter by an entity reference view with tokens'),
    'class' => 'Airtribune_SelectionHandler_EventViews',
    'weight' => 0,
  );
}
