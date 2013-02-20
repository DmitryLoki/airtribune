<?php


print drupal_render($form['account']['mail']);


// Main profile Name field
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

// Print components.
print drupal_render($form['profile_main']['field_full_name'][$lang][0]['given']);
print drupal_render($form['profile_main']['field_full_name'][$lang][0]['family']);
drupal_render($form['profile_main']['field_full_name']);



print drupal_render($form['profile_main']['field_gender']);


$lang = $form['profile_main']['field_birthdate']['#language'];
$form['profile_main']['field_birthdate'][$lang][0]['value']['month']['#title'] = $form['profile_main']['field_birthdate'][$lang][0]['#title'];
$form['profile_main']['field_birthdate'][$lang][0]['#title'] = '';
print drupal_render($form['profile_main']['field_birthdate']);

//print_r($form['account']['pass']);
$form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';
print drupal_render($form['account']['pass']);

// Hide wrapping fieldsets.
drupal_render($form['profile_main']);

print drupal_render_children($form);
