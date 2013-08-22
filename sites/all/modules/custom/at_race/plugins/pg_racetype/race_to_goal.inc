<?php

define('AT_RACE_RTG_MINIMUM_POINTS', 4);

define('AT_RACE_ITEM_NONE_ID', 'none');
define('AT_RACE_ITEM_TAKE_OF_ID', 'takeoff');
define('AT_RACE_ITEM_SS_ID', 'ss');
define('AT_RACE_ITEM_ES_ID', 'es');
define('AT_RACE_ITEM_GOAL_ID', 'goal');

$plugin = array(
  'pg_racetype' => AT_RACE_RACETYPE_RACE_TO_GOAL,
  'validate_callback' => 'at_race_racetype_race_to_goal_validate',
  'add_new_validate_callback' => 'at_race_racetype_race_to_goal_add_new_validate',
  'remove_point_validate_callback' => 'at_race_racetype_race_to_goal_remove_point_validate',
);

/**
 * "Remove point" submit validation.
 */
function at_race_racetype_race_to_goal_remove_point_validate($form, &$form_state) {
  return;

  $button = $form_state['triggering_element'];
  $parents = $form_state['triggering_element']['#array_parents'];

  $offset = -2;

  // Get $element_parents for form_state_error
  $element = drupal_array_get_nested_value($form, array_slice($button['#array_parents'], 0, $offset));
  $elem_parents = $element['#parents'];


  $submitted_values = drupal_array_get_nested_value($form_state['values'], array_slice($button['#array_parents'], 0, $offset));
  unset($submitted_values['add_new_point']);

  $items = $submitted_values;

  $errors = array();

  // Check count after remove for minimum_items_limit
  if (count($items) - 1 < AT_RACE_RTG_MINIMUM_POINTS) {
    $errors[] = t('Minimim number of values is @num', array('@num' => AT_RACE_RTG_MINIMUM_POINTS));
  }
  else {
    // Perform other checks
    // Remove delta that won't be checked
    // Get element for $parents without remove_button
    $item_element = drupal_array_get_nested_value($form, array_slice($parents, 0, -1));
    //$parents = $element['#parents'];

    // We don't need this delta to perform further validation
    //$delta = $parents[count($parents) - 1];
    $delta = $item_element['#parents'][count($item_element['#parents']) - 1];

    unset($items[$delta]);

    // Sort $items by weight in case it was changed
    uasort($items, '_field_sort_items_helper');
    $items = array_values($items);

    // Do nothing in case there no points
    if (empty($items)) {
      return;
    }

    // Perform validation
    $perform_checks = _ract_to_goal_default_checks_list();
    $errors = _race_to_goal_common_checks($items, $errors, $perform_checks);
  }

  // Set form errors
  foreach ($errors as $error) {
    form_set_error(implode('][', $elem_parents), $error);
  }
  //dsm($errors);
}


/**
 * "Add new point" submit validation.
 */
function at_race_racetype_race_to_goal_add_new_validate($form, &$form_state) {
  return;

  // TODO:

  $button = $form_state['triggering_element'];
  $parents = $form_state['triggering_element']['#array_parents'];
  $offset = -1;

  // Get $element_parents for form_state_error
  $element = drupal_array_get_nested_value($form, array_slice($button['#array_parents'], 0, $offset));
  $elem_parents = $element['#parents'];

  $submitted_values = drupal_array_get_nested_value($form_state['values'], array_slice($button['#array_parents'], 0, $offset));
  unset($submitted_values['add_new_point']);

  $items = $submitted_values;

  // Do nothing in case there no points
  if (empty($items)) {
    return;
  }

  // Sort $items by weight in case it was changed
  uasort($items, '_field_sort_items_helper');

  // We don't need deltas here but need only order
  $items = array_values($items);
  $errors = array();

  // Perform validation
  $perform_checks = _ract_to_goal_default_checks_list();
  $errors = _race_to_goal_common_checks($items, $errors, $perform_checks);

  // Set form errors
  foreach ($errors as $error) {
    form_set_error(implode('][', $elem_parents), $error);
  }


  // TODO: Here we should check each individual point and all at the at once
  // TODO: Use generic function.
  // TODO: Into field validation check "exactly one ss-es point"
}


/**
 * Perform checks.
 */
function _race_to_goal_common_checks($items, $errors, $perform_checks) {

  $count_ss_es = _race_to_goal_ss_es();

  // Check SS-ES position and count limit
  foreach ($items as $position => $item) {
    if (in_array($item['ss_es'], array_keys($count_ss_es))) {
      $count_ss_es[$item['ss_es']]['count']++;
      if ($count_ss_es[$item['ss_es']]['position'] == -1) {
        $count_ss_es[$item['ss_es']]['position'] = $position;
      }
    }
  }

  // Check SS-ES count limit
  foreach ($count_ss_es as $ss_es => $v) {
    if ($v['count'] > $v['count_limit']) {
      $errors[] = $v['error_message'];
      // Check if there is sence to validate position
      $count_ss_es[$ss_es]['check_position'] = FALSE;
    }
    elseif ($v['count'] != -1) {
      $count_ss_es[$ss_es]['check_position'] = TRUE;
    }
  }

  // Check Take-off position
  if ($count_ss_es[AT_RACE_ITEM_TAKE_OF_ID]['check_position'] && $count_ss_es[AT_RACE_ITEM_TAKE_OF_ID]['position'] != 0) {
    $errors[] = t('Point Take-off must be first in the list.');
  }

  // Check SS-ES position
  if ($count_ss_es['ss']['check_position'] && $count_ss_es['es']['check_position'] && $count_ss_es['ss']['position'] > $count_ss_es['es']['position']) {
    $errors[] = t('Point SS must be before ES.');
  }

  // TODO: Check only that Goal is after all Take-off/SS/ES points
  /*
  if ($count_ss_es[AT_RACE_ITEM_GOAL_ID]['check_position'] && $count_ss_es[AT_RACE_ITEM_GOAL_ID]['position'] != (count($items) - 1)) {
    $errors[] = t('Point Goal must be last in the list.');
  }
  */

  return $errors;
}


/**
 * List of possible checks
 */
function _ract_to_goal_default_checks_list() {
  $perform_checks = array(
    'takeoff_first',
    'ss_before_es',
    'goal_last',
  );
}


// We don't need it here because it doesn't depend on widget but waypoint type is set in it
// Or use instance settings
function at_race_racetype_race_to_goal_validate($entity_type, $entity, &$errors) {
  // works
  dsm($entity);
  return;
  if ($entity_type == 'ent_racetype') {
    $items = field_get_items('ent_racetype', $entity, AIRTRIBUNE_PG_RACE_POINTS_FIELD);
    // TODO: Remove add_new_point somewhere else for all cases (see also at_race.module). I.e. #value_callback
    unset($items['add_new_point']);

    // Check items number
    if (count($items) < AT_RACE_RTG_MINIMUM_POINTS) {
      $errors['field_pg_race_points']['und'][0][] = array(
        'error' => 'pg_race_rtg_minimum_poins',
        'message' => t('Minimum number of values is @num', array('@num' => AT_RACE_RTG_MINIMUM_POINTS)),
      );
      return;

      /*
      foreach ($invalid_entities as $id => $delta) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => 'pg_race_rtg_minimum_poins',
          'message' => t('The referenced entity (@type: @id) is invalid.', array('@type' => $field['settings']['target_type'], '@id' => $id)),
        );
      }
      */

    }

  }
}

function _race_to_goal_ss_es() {
  $count_ss_es = array(
    'takeoff' => array(
      'count' => 0,
      'count_limit' => 1,
      'error_message' => t('There must be exactly one element of type Take-off.'),
      'position' => -1,
      'check_position' => FALSE,
    ),
    'ss' => array(
      'count' => 0,
      'count_limit' => 1,
      'error_message' => t('There must be exactly one element of type SS.'),
      'position' => -1,
      'check_position' => FALSE,
    ),
    'es' => array(
      'count' => 0,
      'count_limit' => 1,
      'error_message' => t('There must be exactly one element of type ES.'),
      'position' => -1,
      'check_position' => FALSE,
    ),
    'goal' => array(
      'count' => 0,
      'count_limit' => 1,
      'error_message' => t('There must be exactly one element of type Goal.'),
      'position' => -1,
      'check_position' => FALSE,
    ),
  );

  return $count_ss_es;
}
