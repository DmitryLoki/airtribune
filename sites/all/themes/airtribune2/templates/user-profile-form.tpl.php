<?php

//print_r($form);
$lang = $form['profile_main']['field_full_name']['#language'];
$form['field_user_avatar'][$lang][0]['#title'] = '';
$form['field_avatar']['#attached']['js'][0] = drupal_get_path('module', 'at_user') . '/js/auto_upload.js';

print drupal_render($form['field_user_avatar']);

$form['account']['mail']['#title'] = t('Email');
$form['account']['mail']['#title']['#attributes']['rel'] = t('Enter your email');
$form['account']['mail']['#description'] = t('This will be your login');
$form['account']['current_pass']['#title'] = t('Old password');
$form['account']['current_pass']['#description'] = t('Minimun 6 symbols');
$form['account']['pass']['pass1']['#title'] = t("New password");
$form['account']['pass']['pass2']['#title'] = t("Repeat new password");
$form['account']['pass']['#description'] = t('Minimun 6 symbols');
$form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';

print drupal_render($form['account']['mail']);

// Main profile Name field
if (!empty($form['profile_main'])) {
	
  $lang = $form['profile_main']['field_full_name']['#language'];
  $form['profile_main']['field_full_name'][$lang][0]['given']['#prefix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#suffix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#prefix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#suffix'] = '';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#title_display'] = 'before';
  $form['profile_main']['field_full_name'][$lang][0]['family']['#title_display'] = 'before';
  $form['profile_main']['field_full_name'][$lang][0]['given']['#description'] = t('Your name English transcription.');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#description'] = t('Your surname English transcription.');
  $form['profile_main']['field_full_name'][$lang][0]['given']['#attributes']['rel'] = t('Enter your name');
  $form['profile_main']['field_full_name'][$lang][0]['family']['#attributes']['rel'] = t('Enter your surname');

  print drupal_render($form['profile_main']['field_full_name'][$lang][0]['given']);
  print drupal_render($form['profile_main']['field_full_name'][$lang][0]['family']);
  drupal_render($form['profile_main']['field_full_name']);
  print drupal_render($form['profile_main']['field_gender']);

  $lang = $form['profile_main']['field_birthdate']['#language'];
  $form['profile_main']['field_birthdate'][$lang][0]['value']['month']['#title'] = $form['profile_main']['field_birthdate'][$lang][0]['#title'];
  $form['profile_main']['field_birthdate'][$lang][0]['#title'] = '';
  print drupal_render($form['profile_main']['field_birthdate']);
}

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

// Hide wrapping fieldsets.
drupal_render($form['profile_main']);
print drupal_render_children($form);