<div><?php print l(t('I have an Airtribune account.'), 'user/login', array('query' => array('destination' => $_GET['q'])));?></div>
<div><a href="#">I have never registered on Airtribune.com and events hosted on it.</a></div>
<?php

// multiform subforms indices
$og_ui_confirm_subscribe = 'og_ui_confirm_subscribe_0';
$user_register_form = 'user_register_form_1';

// user register_form
$reg_form = &$form['multiform'][$user_register_form];
// og_ui_confirm_subscribe
$og_form = &$form['multiform'][$og_ui_confirm_subscribe];

unset($reg_form['#theme']);
//------------------

drupal_render($og_form['actions']['cancel']);
$form['buttons']['Join']['#value'] = t('Register to this event!');

// Email
$reg_form['account']['mail']['#title'] = t('Email');
$reg_form['account']['mail']['#description'] = t('This will be your login.');
print drupal_render($reg_form['account']['mail']);


// Main profile Name field
$lang = $reg_form['profile_main']['field_full_name']['#language'];
$reg_form['profile_main']['field_full_name'][$lang][0]['given']['#prefix'] = '';
$reg_form['profile_main']['field_full_name'][$lang][0]['given']['#suffix'] = '';
$reg_form['profile_main']['field_full_name'][$lang][0]['family']['#prefix'] = '';
$reg_form['profile_main']['field_full_name'][$lang][0]['family']['#suffix'] = '';
$reg_form['profile_main']['field_full_name'][$lang][0]['given']['#title_display'] = 'before';
$reg_form['profile_main']['field_full_name'][$lang][0]['family']['#title_display'] = 'before';
$reg_form['profile_main']['field_full_name'][$lang][0]['given']['#description'] = t('Your name English transcription.');
$reg_form['profile_main']['field_full_name'][$lang][0]['family']['#description'] = t('Your surname English transcription.');;
// Print components.
print drupal_render($reg_form['profile_main']['field_full_name'][$lang][0]['given']);
print drupal_render($reg_form['profile_main']['field_full_name'][$lang][0]['family']);
drupal_render($reg_form['profile_main']['field_full_name']);



print drupal_render($reg_form['profile_main']['field_gender']);

print drupal_render($reg_form['profile_main']['field_birthdate']);

print drupal_render($reg_form['account']['pass']);

// Hide wrapping fieldsets.
drupal_render($reg_form['profile_main']);

// We don't need Register button in multiform since it is hidden in at_reg.pages.inc.
//$reg_form['actions']['submit']['#value'] = t('Register');


// Pilot profile
// =====================
// Address field
print drupal_render($reg_form['profile_pilot']['field_address']);

// Mobile phone
print drupal_render($reg_form['profile_pilot']['field_phone']);


// FAI license
print drupal_render($reg_form['profile_pilot']['field_fai_license_number']);

// CIVIL ID
print drupal_render($reg_form['profile_pilot']['field_civl_id']);

// Pilot's number
print drupal_render($og_form['field_contestant_number']);

// T-shirt.
print drupal_render($reg_form['profile_pilot']['field_t_shirt_size']);

// Paraglider manufacturer
print drupal_render($reg_form['profile_pilot']['field_paraglider_manufacturer']);

// Paraglider model
print drupal_render($reg_form['profile_pilot']['field_paraglider_model']);

// Paraglider color
print drupal_render($reg_form['profile_pilot']['field_paraglider_color']);

// Sponsors
print drupal_render($reg_form['profile_pilot']['field_sponsors']);

// Insurance company
print drupal_render($reg_form['profile_pilot']['field_insurance_company']);

// Insurance policy number
print drupal_render($reg_form['profile_pilot']['field_insurance_policy_number']);

// Name in national alphabet.
print drupal_render($reg_form['profile_pilot']['field_name_in_national_alphabet']);

// Person to contact in case of emergency
print drupal_render($reg_form['profile_pilot']['field_person_name']);

// Contact phone number in case of emergency
print drupal_render($reg_form['profile_pilot']['field_person_phone']);

// Blood type
print drupal_render($reg_form['profile_pilot']['field_blood_type']);

// Hide profile fieldsets
drupal_render($reg_form['profile_pilot']);








// Render everything else.
print drupal_render_children($form);
