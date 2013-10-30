<?php

drupal_render($form['multiform'][0]['actions']);

// Hide OG registration Cancel link
drupal_render($form['multiform'][1]['actions']['cancel']);

drupal_render($form['multiform'][2]['actions']);

$form['multiform'][3]['register']['#prefix'] = '<div class="form-actions">';
$form['multiform'][3]['register']['#suffix'] = '</div>';

$pm_form = &$form['multiform'][0];
$og_form = &$form['multiform'][1];
$pp_form = &$form['multiform'][2];

unset($pm_form['profile_main']['#fieldgroups']);


//~ dsm($form);
$pm_form['profile_main']['field_birthdate']['und'][0]['value']['day']['#title'] = t('Date of birth');
unset($pm_form['profile_main']['field_birthdate']['und'][0]['#title']);


print drupal_render($og_form['account']['mail_dummy']);

$pm_form['profile_main']['field_full_name']['und'][0]['given']['#title_display'] = TRUE;
$pm_form['profile_main']['field_full_name']['und'][0]['family']['#title_display'] = TRUE;
print drupal_render($pm_form['profile_main']['field_full_name']['und'][0]['given']);
print drupal_render($pm_form['profile_main']['field_full_name']['und'][0]['family']);
drupal_render($pm_form['profile_main']['field_full_name']);

print drupal_render_children($pm_form);

print drupal_render($pp_form['profile_pilot']['field_address']);
print drupal_render($pp_form['profile_pilot']['field_phone']);
print drupal_render($pp_form['profile_pilot']['field_fai_license_number']);
print drupal_render($pp_form['profile_pilot']['field_civl_id']);

print drupal_render($og_form['field_contestant_number']);

// 

print drupal_render_children($form);
