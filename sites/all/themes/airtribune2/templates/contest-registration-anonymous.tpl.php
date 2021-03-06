<?php // Team registration link?>
<?php $team_registration = isset($form['team_reg_link']) ? drupal_render($form['team_reg_link']) : '';?>
<?php if (!empty($team_registration)): ?>
  <div class='anonymous-team-registration-pilot-caption'><?php print t('Pilot registration');?></div>
<?php endif;?>




<div class="reg_choice">
	<?php print l('<span>'.t('I have an Airtribune account.').'</span><span class="valign"></span>', 'user/login', array('html' => true, 'query' => array('destination' => $_GET['q'])));?>
	<a href="#" class="form_show"><span><?php print t('I have never registered on Airtribune.com and events hosted on it.'); ?></span><span class="valign"></span></a>
</div>
<div id="event_register" class="event-register-form">

<?php

// Note: user-register-form.tpl.php is also used here to theme user_register_form subform.

// Hide OG registration Cancel link
drupal_render($form['multiform'][1]['actions']['cancel']);

drupal_render($form['multiform'][2]['actions']);

$form['multiform'][3]['register']['#prefix'] = '<div class="form-actions">';
$form['multiform'][3]['register']['#suffix'] = '</div>';



// Remove user_register_form subform theme function.
//~ $form['multiform'][0]['#theme'] = array();
//~ $form['multiform'][0]['#theme'] = '';
unset($form['multiform'][0]['#theme']);

$ur_form = &$form['multiform'][0];
$og_form = &$form['multiform'][1];
$pp_form = &$form['multiform'][2];


// TODO: Use theme() function instead.
// -- Note: This is copy-paste from user-register-form.tpl.php

print drupal_render($ur_form['account']['mail']);

// Print Name components.
$lang = $ur_form['profile_main']['field_full_name']['#language'];
_airtribune2_alter_name_widget($ur_form['profile_main']['field_full_name']);
print drupal_render($ur_form['profile_main']['field_full_name'][$lang][0]['given']);
print drupal_render($ur_form['profile_main']['field_full_name'][$lang][0]['family']);
drupal_render($ur_form['profile_main']['field_full_name']);

print drupal_render($ur_form['profile_main']['field_gender']);

// Print Birthdate
_airtribune2_alter_birthdate_widget($ur_form['profile_main']['field_birthdate']);
print drupal_render($ur_form['profile_main']['field_birthdate']);

//print_r($form['account']['pass']);
$ur_form['account']['pass']['#attached']['js'][0] = 'sites/all/themes/airtribune2/js/user.js';
print drupal_render($ur_form['account']['pass']);

// Hide wrapping fieldsets.
drupal_render($ur_form['profile_main']);

print drupal_render_children($ur_form);

// -- End of user-register-form.tpl.php


print drupal_render($pp_form['profile_pilot']['field_address']);
print drupal_render($pp_form['profile_pilot']['field_phone']);
print drupal_render($pp_form['profile_pilot']['field_fai_license_number']);
print drupal_render($pp_form['profile_pilot']['field_civl_id']);
print drupal_render($pp_form['profile_pilot']['field_nat_license_id']);
print drupal_render($pp_form['profile_pilot']['field_team']);
print drupal_render($pp_form['profile_pilot']['field_accom_during_comp']);

// Print pilot's number
print drupal_render($og_form['field_contestant_number']);


print drupal_render_children($form);

?>
</div>

<?php // Team registration link?>
<?php if (!empty($team_registration)):?>
  <div class='anonymous-team-registration'><?php print $team_registration;?></div>
<?php endif;?>
