<?php

$pilot_uid = arg(1);
drupal_set_title(at_user_get_full_name($pilot_uid));

global $user;

//print_r($form);
$form['actions']['submit']['#suffix'] = '<a id="mail-edit-cancel-link">or Cancel</a>';

print "<div id='name-gender-dob'>"; // #name-gender-dob start

$lang = $form['profile_main']['field_full_name']['#language'];
$form['field_user_avatar'][$lang][0]['#title'] = '';
$form['field_avatar']['#attached']['js'][] = drupal_get_path('module', 'at_user') . '/js/auto_upload.js';

print drupal_render($form['field_user_avatar']);

$form['account']['mail']['#title'] = t('Email');
$form['account']['mail']['#attributes']['placeholder'] = t('Enter your email');
$form['account']['mail']['#description'] = t('Your email is your login in the system. To change email you must enter your new email. Your email will be changed after confirmation.');
$form['account']['current_pass']['#title'] = t('Current password');
$form['account']['current_pass']['#description'] = t('Your current password. If your forgot your password, you can reset it <a href="/user/password">here</a>.');
$form['account']['pass']['pass1']['#title'] = t("New password");
$form['account']['pass']['pass2']['#title'] = t("Confirm new password");
$form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';

$form['account']['mail_dummy'] = array(
  '#type' => 'item',
  '#title' => t('Email'),
  '#markup' => $form['account']['mail']['#value'],
  '#prefix' => '<div id="mail-dummy">', // form api "item" haven't #attributes
  '#suffix' => '<div id="mail-edit-pencil">✎</div></div>',
);

print drupal_render($form['account']['mail_dummy']);

// Main profile Name field
if (!empty($form['profile_main'])) {
  
  $lang = $form['profile_main']['field_full_name']['#language'];
  $form['profile_main']['field_full_name'][$lang][0]['given']['#prefix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#suffix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#prefix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#suffix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#title_display'] = 'before';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#title_display'] = 'before';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#attributes']['placeholder'] = t('Enter your name');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#attributes']['placeholder'] = t('Enter your surname');
  // Temporary fix for Name label translation (see http://drupal.org/node/1788156)
  $form['profile_main']['field_full_name'][$lang][0]['given']['#title'] = t('Name');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#title'] = t('Surname');
  print drupal_render($form['profile_main']['field_full_name'][$lang][0]['given']);
  print drupal_render($form['profile_main']['field_full_name'][$lang][0]['family']);
  drupal_render($form['profile_main']['field_full_name']);
  print drupal_render($form['profile_main']['field_gender']);

  $lang = $form['profile_main']['field_birthdate']['#language'];
  $form['profile_main']['field_birthdate'][$lang][0]['#title'] = str_replace('Date of birth', t('Date of birth'), $form['profile_main']['field_birthdate'][$lang][0]['#title']);
  $form['profile_main']['field_birthdate'][$lang][0]['value']['day']['#title'] = $form['profile_main']['field_birthdate'][$lang][0]['#title'];
  $form['profile_main']['field_birthdate'][$lang][0]['#title'] = '';
  print drupal_render($form['profile_main']['field_birthdate']);
}

print "</div>"; // #name-gender-dob end

// Personalisation.
$socials = array('Facebook', 'GooglePlus', 'Youtube', 'Vimeo', 'Instagram');
$soc_links = &$form['field_social_links']['und'];
foreach (array_keys($soc_links) as $element) {
  // [und][0], [und][1], ...
  if (is_int($element)) {
    // Add placeholder & class to social links field
    $form['field_social_links']['und'][$element]['url']['#class'] = array($socials[$element]);
    $form['field_social_links']['und'][$element]['url']['#attributes']['placeholder'] = $socials[$element];
    // Override Drupal field value, to the value obtained from the CoreAPI.
    if (isset($form['#core_user_fields']->facebook_url)) {
      $soc_name = strtolower($socials[$element]) . '_url';
      $form['field_social_links']['und'][$element]['url']['#value'] = $form['#core_user_fields']->$soc_name;
    }
  }
}
$form['field_header_image']['und'][0]['select']['#title'] = t('Add image');
$form['field_header_image']['und'][0]['remove']['#title'] = t('Delete');

$form['personalisation']['basic_url'] = $form['basic_url'];
$form['personalisation']['optional_url'] = $form['optional_url'];
$form['personalisation']['field_header_image'] = $form['field_header_image'];
$form['personalisation']['field_social_links'] = $form['field_social_links'];
unset($form['basic_url']);
unset($form['optional_url']);
unset($form['field_header_image']);
unset($form['field_social_links']);


$form['pass_fieldset']['current_pass'] = $form['account']['current_pass'];
$form['pass_fieldset']['pass']         = $form['account']['pass'];

print "<div id='mail-change'>";
print drupal_render($form['account']['mail']);
print drupal_render($form['account']['current_pass']);
print "</div>";

// hide elements
hide($form['account']['pass']);
hide($form['timezone']);
hide($form['locale']);

hide($form['og_user_node']);
hide($form['xmlsitemap']);
hide($form['metatags']);
hide($form['mimemail']);

hide($form['name_gender_dob']);
hide($form['name_gender_dob']);
// Hide wrapping fieldsets.
drupal_render($form['profile_main']);
print drupal_render_children($form);