<?php

/**
 * @file
 * Airtribune team card header plugin
 */

// Plugin definition.
$plugin = array(
  'title' => t('Airtrubune team card header'),
  'single' => TRUE,
  'category' => array('Airtribune'),
  'required context' => array(
    new ctools_context_required(t('Contest'), 'node'),
    new ctools_context_required(t('Team Entity'), 'ent_team'),
  ),
);

/**
 * Render airtribune team card header pane.
 */
function airtribune_airtribune_teamcard_header_content_type_render(&$subtype, $conf, $panel_args, $context) {
  if (empty($context) || empty($context[0]->data) || empty($context[1]->data)) {
    return;
  }

  $contest = $context[0]->data;
  $team = $context[1]->data;

  $contest_time = airtribune_extract_time_from_contest($contest);
  $last_modified = date('M j, Y H:i:s', $team->changed + $contest_time['offset']);

  $teamlead = user_load($team->uid);
  $country = $team->field_country['und'][0]['iso2'];

  $email = $teamlead->mail;
  $country_full = country_load($country);

  $content['widget']['#markup'] =
    '<div class="teamcard-header">' .
    '<div class="country ' . $country . '">' . t('Team') . ' ' . t($country_full->name) . '</div>'.
    '<div class="declared">' . t('Declared by') . ' ' . airtrubune_format_username($teamlead, 20) . '</div>'.
    '<div class="teamlead-email">' . l($email, 'mailto:' . $email, array('absolute' => TRUE)) . '</div>'.
    '<div class="modified">' . t('Modified on') . ' ' . $last_modified . '</div>'.
    '</div>';
  $content['#theme_wrappers'] = array('container');
  $content['#attributes'] = array('id' => drupal_html_id('airtribune-teamcard-header'));

  return (object) array(
    'module' => 'airtribune',
    'content' => $content,
    'delta' => 1,
  );
}

/**
 * Panels module needs this empty form.
 */
function airtribune_airtribune_teamcard_header_content_type_edit_form_submit($form, &$form_state) {
  return $form;
}
