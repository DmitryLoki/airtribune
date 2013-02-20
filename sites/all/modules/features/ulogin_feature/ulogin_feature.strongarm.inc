<?php
/**
 * @file
 * ulogin_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function ulogin_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_destination';
  $strongarm->value = '';
  $export['ulogin_destination'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_disable_username_change';
  $strongarm->value = 1;
  $export['ulogin_disable_username_change'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_display';
  $strongarm->value = 'buttons';
  $export['ulogin_display'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_display_name';
  $strongarm->value = '[user:ulogin:first_name] [user:ulogin:last_name]';
  $export['ulogin_display_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_duplicate_emails';
  $strongarm->value = '1';
  $export['ulogin_duplicate_emails'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_email_confirm';
  $strongarm->value = 0;
  $export['ulogin_email_confirm'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_fields';
  $strongarm->value = array(
    'first_name' => 'first_name',
    'last_name' => 'last_name',
    'email' => 'email',
    'nickname' => 'nickname',
    'bdate' => 'bdate',
    'sex' => 'sex',
    'photo' => 'photo',
    'photo_big' => 'photo_big',
    'country' => 'country',
    'city' => 'city',
    'phone' => 0,
  );
  $export['ulogin_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_forms';
  $strongarm->value = array(
    'user_login' => 'user_login',
    'user_login_block' => 'user_login_block',
    'user_register_form' => 0,
    'comment_form' => 0,
  );
  $export['ulogin_forms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_hidden';
  $strongarm->value = array(
    'vkontakte' => 0,
    'odnoklassniki' => 0,
    'mailru' => 0,
    'facebook' => 0,
    'twitter' => 0,
    'google' => 0,
    'yandex' => 0,
    'livejournal' => 0,
    'openid' => 0,
    'lastfm' => 0,
    'linkedin' => 0,
    'liveid' => 0,
    'soundcloud' => 0,
    'steam' => 0,
    'flickr' => 0,
    'vimeo' => 0,
    'youtube' => 0,
    'webmoney' => 0,
  );
  $export['ulogin_hidden'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_icons_path';
  $strongarm->value = 'sites/all/themes/airtribune2/images/ulogin';
  $export['ulogin_icons_path'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_override_realname';
  $strongarm->value = 0;
  $export['ulogin_override_realname'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_pictures';
  $strongarm->value = 1;
  $export['ulogin_pictures'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_providers';
  $strongarm->value = array(
    'facebook' => 'facebook',
    'vkontakte' => 0,
    'odnoklassniki' => 0,
    'mailru' => 0,
    'twitter' => 0,
    'google' => 0,
    'yandex' => 0,
    'livejournal' => 0,
    'openid' => 0,
    'lastfm' => 0,
    'linkedin' => 0,
    'liveid' => 0,
    'soundcloud' => 0,
    'steam' => 0,
    'flickr' => 0,
    'vimeo' => 0,
    'youtube' => 0,
    'webmoney' => 0,
  );
  $export['ulogin_providers'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_remove_password_fields';
  $strongarm->value = 1;
  $export['ulogin_remove_password_fields'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ulogin_username';
  $strongarm->value = '[user:ulogin:first_name]_[user:ulogin:last_name]';
  $export['ulogin_username'] = $strongarm;

  return $export;
}
