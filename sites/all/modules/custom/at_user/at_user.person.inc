<?php

// @todo: Add access callback

/**
 * User "Person" page callback.
 *
 * @todo
 */
function at_user_person_page($user) {
  drupal_set_title($user->name);
  // dsm($user);
  return t('Comming soon.');
}


