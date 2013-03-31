<?php
/**
 * @file
 *  Informs Views about Masquerade's tables and fields.
 */

/**
 * Implements hook_views_data().
 *
 * @see hook_views_data()
 */
function masquerade_views_views_data() {
  $data['masquerade']['table']['group'] = t('Masquerade');

  // Offer views that start on the "masquerade" table.
  // This will let site builders create a view of who is masquerading.
  $data['masquerade']['table']['base'] = array(
    'field' => 'uid_from',
    'title' => t('Masquerading Users'),
    'help' => t('A list of people who are masquerading as other users.'),
  );

  // The session ID of the masquerader.
  $data['masquerade']['sid'] = array(
    'title' => t('Session SID'),
    'help' => t('The session ID of the person masquerading. This is normally NEVER shown, so use it with extreme caution.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
    ),
  );
  
  // Who is BEING masqueraded.
  $data['masquerade']['uid_as'] = array(
    'title' => t('Masquerade As'),
    'help' => t('The user this person is posing as.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('Masquerading as'),
    ),
  );

  // Who actually IS masquerading.
  $data['masquerade']['uid_from'] = array(
    'title' => t('Masquerade From'),
    'help' => t('The user this person actually is.'),
    'relationship' => array(
      'handler' => 'views_handler_relationship',
      'base' => 'users',
      'base field' => 'uid',
      'label' => t('Who is masquerading'),
    ),
  );

  // Provide a pseudo field for user links.
  $data['users']['masquerade_as'] = array(
    'real field' => 'uid',
    'title' => t('Masquerade As'),
    'help' => t('Generate a link to masquerade as this user.'),
    'field' => array(
      'handler' => 'masquerade_handler_field_user',
      'click sortable' => FALSE,
    ),
  );

  return $data;
}
