<?php

/**
 * @file
 * Hide State component.
 */

$plugin = array(
  'title' => t('Hide state'),
  'format callback' => 'addressfield_format_address_hide_state',
  'type' => 'address',
  'weight' => -80,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function addressfield_format_address_hide_state(&$format, $address, $context = array()) {
  $format['locality_block']['administrative_area']['#access'] = FALSE;
}
