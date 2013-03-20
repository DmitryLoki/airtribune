<div class="reg_choice">
	<?php print l(t('I have an Airtribune account.'), 'user/login', array('query' => array('destination' => $_GET['q'])));?>
	<a href="#" class="form_show"><?php print t('I have never registered on Airtribune.com and events hosted on it.'); ?></a>
</div>
<div id="event_register">
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
$form['buttons']['Join']['#value'] = t('Register');

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
$reg_form['profile_main']['field_full_name'][$lang][0]['given']['#attributes']['rel'] = t('Enter your name');
$reg_form['profile_main']['field_full_name'][$lang][0]['family']['#attributes']['rel'] = t('Enter your surname');
// Print components.
print drupal_render($reg_form['profile_main']['field_full_name'][$lang][0]['given']);
print drupal_render($reg_form['profile_main']['field_full_name'][$lang][0]['family']);
drupal_render($reg_form['profile_main']['field_full_name']);



print drupal_render($reg_form['profile_main']['field_gender']);


$lang = $reg_form['profile_main']['field_birthdate']['#language'];
$reg_form['profile_main']['field_birthdate'][$lang][0]['value']['day']['#title'] = $reg_form['profile_main']['field_birthdate'][$lang][0]['#title'];
$reg_form['profile_main']['field_birthdate'][$lang][0]['#title'] = '';
print drupal_render($reg_form['profile_main']['field_birthdate']);

$reg_form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';
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


//$reg_form['actions']['#prefix'] = '<div class="form-actions">';
//$reg_form['actions']['#suffix'] = '</div>';
//print_r($reg_form);



print '<div class="form-actions">' . drupal_render($form['buttons']['Join']) . '</div>';

// Render everything else.
print drupal_render_children($form);
?>
</div>
