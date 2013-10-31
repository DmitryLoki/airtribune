<?php



drupal_render($form['multiform'][0]['actions']);

// Hide OG registration Cancel link
drupal_render($form['multiform'][1]['actions']['cancel']);

drupal_render($form['multiform'][2]['actions']);

$form['multiform'][3]['register']['#prefix'] = '<div class="form-actions">';
$form['multiform'][3]['register']['#suffix'] = '</div>';

// profile main form
$pm_form = &$form['multiform'][0];
// og registration form
$og_form = &$form['multiform'][1];
// profile pilot form
$pp_form = &$form['multiform'][2];


// Hide collapsible fieldset wrapper.
unset($pm_form['profile_main']['#fieldgroups']);

print drupal_render($og_form['account']['mail_dummy']);

// Print Name components.
$lang = $pm_form['profile_main']['field_full_name']['#language'];
_airtribune2_alter_name_widget($pm_form['profile_main']['field_full_name']);
print drupal_render($pm_form['profile_main']['field_full_name'][$lang][0]['given']);
print drupal_render($pm_form['profile_main']['field_full_name'][$lang][0]['family']);
drupal_render($pm_form['profile_main']['field_full_name']);

// Print Birthdate
_airtribune2_alter_birthdate_widget(&$pm_form['profile_main']['field_birthdate']);
print drupal_render($pm_form['profile_main']['field_birthdate']);

// Print profile_main fields left.
print drupal_render_children($pm_form);


print drupal_render($pp_form['profile_pilot']['field_address']);
print drupal_render($pp_form['profile_pilot']['field_phone']);
print drupal_render($pp_form['profile_pilot']['field_fai_license_number']);
print drupal_render($pp_form['profile_pilot']['field_civl_id']);

// Print pilot's number
print drupal_render($og_form['field_contestant_number']);

// 

print drupal_render_children($form);
