<?php

/**
 * @file
 * Hooks provided by the uLogin module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Alter the username for a user before creation.
 *
 * @param $name
 *   The username for the user being created, it must be unique.
 * @param $data
 *   The data object with all the properties from authentication provider.
 *
 * @see _ulogin_make_username()
 *
 * @ingroup ulogin
 */
function hook_ulogin_username_alter(&$name, $data) {
  
}

/**
 * @} End of "addtogroup hooks".
 */
