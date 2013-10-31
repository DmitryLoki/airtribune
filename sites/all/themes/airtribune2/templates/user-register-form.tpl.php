<?php

print drupal_render($form['account']['mail']);

// Print Name components.
$lang = $form['profile_main']['field_full_name']['#language'];
_airtribune2_alter_name_widget($form['profile_main']['field_full_name']);
print drupal_render($form['profile_main']['field_full_name'][$lang][0]['given']);
print drupal_render($form['profile_main']['field_full_name'][$lang][0]['family']);
drupal_render($form['profile_main']['field_full_name']);

print drupal_render($form['profile_main']['field_gender']);

// Print Birthdate
_airtribune2_alter_birthdate_widget(&$form['profile_main']['field_birthdate']);
print drupal_render($form['profile_main']['field_birthdate']);

//print_r($form['account']['pass']);
$form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';
print drupal_render($form['account']['pass']);

// Hide wrapping fieldsets.
drupal_render($form['profile_main']);

print drupal_render_children($form);
