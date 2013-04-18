<?php

$pilot_uid = arg(1);
drupal_set_title(at_user_get_full_name($pilot_uid));

global $user;

print "<div id='name_and_birthday'>"; // #name_and_birthday start

$lang = $form['profile_main']['field_full_name']['#language'];
$form['field_user_avatar'][$lang][0]['#title'] = '';
$form['field_avatar']['#attached']['js'][] = drupal_get_path('module', 'at_user') . '/js/auto_upload.js';

print drupal_render($form['field_user_avatar']);

$form['account']['mail']['#title'] = t('Email');
$form['account']['mail']['#attributes']['rel'] = t('Enter your email');
unset($form['account']['mail']['#description']);
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
  '#suffix' => '<div id="mail-edit-pencil">✎ edit</div></div>',
);

$form['account']['mail']['#attached']['js'][] = drupal_get_path('module', 'at_user') . '/js/mail_change.js';
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
  //$form['profile_main']['field_full_name'][$lang][0]['given']['#description'] = t('Your Name in English transcription.');
  //$form['profile_main']['field_full_name'][$lang][0]['family']['#description'] = t('Your surname in English transcription.');
  $form['profile_main']['field_full_name'][$lang][0]['given']['#attributes']['rel'] = t('Enter your name');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#attributes']['rel'] = t('Enter your surname');
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

print "</div>"; // #name_and_birthday end

$form['pass_fieldset'] = array(
  '#type' => 'fieldset',
  '#title' => t('Change password'),
  '#prefix' => '<div id="password-fieldset">',
  '#suffix' => '</div>',
  '#collapsible' => TRUE,
  '#collapsed' => TRUE,
  '#attributes' => array('class' => array('collapsible', 'collapsed')),
);

$form['pass_fieldset']['current_pass'] = $form['account']['current_pass'];
$form['pass_fieldset']['pass']         = $form['account']['pass'];
print drupal_render($form['pass_fieldset']);

// hide elements
hide($form['account']['pass']);
hide($form['account']['current_pass']);
hide($form['timezone']);
hide($form['locale']);

hide($form['og_user_node']);
hide($form['xmlsitemap']);
hide($form['metatags']);
hide($form['mimemail']);

// Hide wrapping fieldsets.
drupal_render($form['profile_main']);
print drupal_render_children($form);
