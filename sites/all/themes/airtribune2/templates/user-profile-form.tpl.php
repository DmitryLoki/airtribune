<?php

// Main profile Name field
$lang = $form['profile_main']['field_full_name']['#language'];
$form['profile_main']['field_full_name'][$lang][0]['given']['#prefix'] = '';
$form['profile_main']['field_full_name'][$lang][0]['given']['#suffix'] = '';
$form['profile_main']['field_full_name'][$lang][0]['family']['#prefix'] = '';
$form['profile_main']['field_full_name'][$lang][0]['family']['#suffix'] = '';
$form['profile_main']['field_full_name'][$lang][0]['given']['#description'] = t('Your name in English transcription.');
$form['profile_main']['field_full_name'][$lang][0]['family']['#description'] = t('Your surname in English transcription.');
$form['profile_main']['field_full_name'][$lang][0]['given']['#attributes']['rel'] = t('Enter your name');
$form['profile_main']['field_full_name'][$lang][0]['family']['#attributes']['rel'] = t('Enter your surname');

$lang = $form['profile_main']['field_birthdate']['#language'];
$form['profile_main']['field_birthdate'][$lang][0]['value']['month']['#title'] = $form['profile_main']['field_birthdate'][$lang][0]['#title'];
$form['profile_main']['field_birthdate'][$lang][0]['#title'] = '';

$form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';

print drupal_render_children($form);
