<?php

/**
 * @file
 * Hide Address2 component.
 */

$plugin = array(
  'title' => t('Hide address2'),
  'format callback' => 'addressfield_format_address_hide_address2',
  'type' => 'address',
  'weight' => -80,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_address_hide_address2(&$format, $address, $context = array()) {
  $format['street_block']['thoroughfare']['#title'] = t('Address');
  $format['street_block']['premise']['#access'] = FALSE;
}
