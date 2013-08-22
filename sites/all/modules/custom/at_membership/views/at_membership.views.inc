<?php

/**
 * @file
 * Provide views data and handlers for node.module.
 *
 * @ingroup views_module_handlers
 */

/**
 * Implements hook_views_data().
 */
function at_membership_views_data() {
  // Define some fields based upon views_handler_field_entity in the entity
  // table so they can be re-used with other query backends.
  // @see views_handler_field_entity

  $data['views_entity_og_membership']['table']['group'] = t('OG membership');

  $data['og_membership']['edit_og_membership']['moved to'] = array('views_entity_og_membership', 'edit_og_membership');
  $data['views_entity_og_membership']['edit_og_membership'] = array(
    'field' => array(
      'title' => t('OG membership edit link'),
      'help' => t('Provide a simple link to edit the OG membership.'),
      'handler' => 'views_handler_field_og_membership_link_edit',
    ),
  );

  return $data;
}


