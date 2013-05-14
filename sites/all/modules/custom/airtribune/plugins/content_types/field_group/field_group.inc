<?php

/**
 * field_group.inc
 * Handle rendering fieldgroups as panes.
 * @See http://drupal.org/sandbox/Hydra/1608256
 */
$plugin = array(
  'title' => t('Field Group formatter'),
  'category' => 'Airtribune',
  'content type' => 'airtribune_field_group_content_type',
  'required context' => new ctools_context_required(t('entity'), 'entity'),
);

function airtribune_field_group_content_type_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];

  // Force to load this file, that the callbackfunction could be loaded.
  $form_state['build_info']['files'][] = array(
    'type' => 'inc',
    'module' => 'airtribune',
    'name' => 'plugins/content_types/field_group/field_group',
  );

  // Ajax Call when the Entity is changed.
  $form['context']['#ajax'] = array(
    'event' => 'change',
    'wrapper' => 'field-group-bundles-container',
    'callback' => 'airtribune_bundle_callback'
  );
  $form['context']['#submit'] = array('airtribune_field_group_content_type_submit_temporary');
  $form['context']['#executes_submit_callback'] = TRUE;

  // Get valid context value.
  $context = empty($conf['context']) ? reset($form_state['contexts']) : $form_state['contexts'][$conf['context']];

  // Not sure if this is always valid?
  $entity_type = $context->type[2];
  $entity_info = entity_get_info($entity_type);

  // TODO: Trying to handle arguments like nids.
  if ($entity_type == 'node' && !empty($context->argument)) {
    $bundle_key = $entity_info['entity keys']['bundle'];
    $entity_id = $context->argument;
    $bundle = $context->data->$bundle_key;
  }

  // Reading all field_groups.
  $groups = field_group_read_groups(array('entity_type' => $entity_type));

  // Get all available bundles, having a fieldgroups attached.
  $bundles = array();
  foreach ($groups as $entitys => $entity) {
    foreach (array_keys($entity) as $key => $value) {
      $bundles[$value] = $value;
    }
  }

  $form['bundle'] = array(
    '#title' => t('Bundle'),
    '#type' => 'select',
    '#description' => t('Select a bundle for this @entity_type.', array('@entity_type' => $entity_info['label'])),
    '#options' => $bundles,
    '#default_value' => $conf['bundle'],
    '#ajax' => array(
      'event' => 'change',
      'wrapper' => 'field-group-build-mode-container',
      'callback' => 'airtribune_build_mode_callback'
    ),
    '#submit' => array('airtribune_field_group_content_type_submit_temporary'),
    '#executes_submit_callback' => TRUE,
  );

  // Get the valid bundle depending on the previous selection.
  $bundle = !empty($conf['bundle']) && in_array($conf['bundle'], $bundles) ? $conf['bundle'] : reset($bundles);

  // Get all build_modes for the current selection of entity_type + bundle.
  $build_mode_options = array();
  foreach ($groups[$entity_type][$bundle] as $field_groups_modes => $field_groups) {
    $build_mode_options[$field_groups_modes] = $field_groups_modes;
  }

  $form['build_mode'] = array(
    '#title' => t('Build mode'),
    '#type' => 'select',
    '#description' => t('Select a build mode for this @entity_type.', array('@entity_type' => $entity_info['label'])),
    '#options' => $build_mode_options,
    '#default_value' => $conf['build_mode'],
    '#ajax' => array(
      'event' => 'change',
//      'path' => 'ctools/content/ajax',
      'wrapper' => 'field-group-field-group-container',
      'callback' => 'airtribune_avalible_field_groups_callback'
    ),
    '#submit' => array('airtribune_field_group_content_type_submit_temporary'),
    '#executes_submit_callback' => TRUE,
  );

  // if build_mode exists in the options, it's kept as selected, otherwise the first value will be set
  $build_mode = in_array($conf['build_mode'], $form['build_mode']['#options']) ? $conf['build_mode'] : reset($form['build_mode']['#options']);

  // Get all field_groups for the current selectin of mode + bundle + entity_type.
  $field_groups = array();
  foreach ($groups[$entity_type][$bundle][$build_mode] as $grouup_name => $field_group) {
    $field_groups[$grouup_name] = $grouup_name;
  }

  $form['field_group'] = array(
    '#type' => 'select',
    '#options' => $field_groups,
    '#default_value' => $conf['field_group'],
    '#title' => t('Select Field Group'),
  );

  $form['#pre_render'][] = 'airtribune_field_group_content_type_pre_render';
  return $form;
}

/**
 * A pre_render function to move the fields into different divs, so ajax can work as expected.
 */
function airtribune_field_group_content_type_pre_render($form) {
  $field_group = $form['field_group'];

  $form['field_group'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'field-group-bundles-container'),
    // On pre_render the weight of other elements is already done,
    // so 0 would move the element before the context selection.
    '#weight' => 1,
  );
  $form['field_group']['bundle'] = $form['bundle'];
  unset($form['bundle']);

  $form['field_group']['build_mode_container'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'field-group-build-mode-container'),
    '#weight' => 1,
  );
  $form['field_group']['build_mode_container']['build_mode'] = $form['build_mode'];
  unset($form['build_mode']);

  $form['field_group']['build_mode_container']['field_group_container'] = array(
    '#type' => 'container',
    '#attributes' => array('id' => 'field-group-field-group-container'),
    '#weight' => 1,
  );
  $form['field_group']['build_mode_container']['field_group_container']['field_group'] = $field_group;

  return $form;
}

/**
 * Helperfunction to save the values into conf for further using.
 */
function airtribune_field_group_content_type_submit_temporary($form, &$form_state) {
  $form_state['conf']['context'] = $form_state['values']['context'];
  $form_state['conf']['label'] = $form_state['values']['label'];
  $form_state['conf']['bundle'] = $form_state['values']['bundle'];
  $form_state['conf']['build_mode'] = $form_state['values']['build_mode'];
  $form_state['conf']['field_group'] = $form_state['values']['field_group'];

  $form_state['rebuild'] = TRUE;
  $form_state['rerender'] = TRUE;
}

/**
 * Ajax callback to return the bundles container.
 * The pre_render function is called manually to be able to return
 * the container, not only the form element.
 */
function airtribune_bundle_callback($form, &$form_state) {
  $form = airtribune_field_group_content_type_pre_render($form);
  return $form['field_group'];
}

/**
 * Ajax callback to return the build_modes container.
 */
function airtribune_build_mode_callback($form, &$form_state) {
  $form = airtribune_field_group_content_type_pre_render($form);
  return $form['field_group']['build_mode_container'];
}

/**
 * Ajax callback to return the field_groups.
 */
function airtribune_avalible_field_groups_callback($form, &$form_state) {
  $form = airtribune_field_group_content_type_pre_render($form);
  return $form['field_group']['build_mode_container']['field_group_container'];
}

/**
 * Validate the node selection.
 */
function airtribune_field_group_content_type_edit_form_submit($form, &$form_state) {
  foreach (array('context', 'build_mode', 'field_group', 'bundle') as $key) {
    $form_state['conf'][$key] = $form_state['values'][$key];
  }
}

/**
 * Render a field_group as pane.
 */
function airtribune_field_group_content_type_render($subtype, $conf, $panel_args, $context) {
  // Get some better names
  $view_mode = $conf['build_mode'];
  $group_name = $conf['field_group'];
  $entity_type = $context->type[2];

  // Load the entitys
  $entitys = entity_get_info($entity_type);
  $entity_key = $entitys['entity keys']['id'];
  $bundle_key = $entitys['bundle keys']['bundle'];

  // pickup the right entity
  $entity = isset($context->data) ? clone($context->data) : NULL;
  $entity_id = $entity->$entity_key;

  $elements = entity_view($entity_type, array($entity_id => $entity), $view_mode);
  if (count($elements) > 1) {
    $entity_types = $entity_type . 's';
  }
  else {
    $entity_types = $entity_type;
  }
  $element = $elements[$entity_types][$entity_id];

  if (isset($element['#pre_render'])) {
    foreach ($element['#pre_render'] as $function) {
      if (function_exists($function)) {
        $element = $function($element);
      }
    }
    unset($element['#pre_render']);
  }

  // If we're using Field Group 7.x-2.x, we need to do some extra processing.
  if (function_exists('field_group_build_entity_groups')) {
    // Needs to be form to get a return value
    $element = field_group_build_entity_groups($element, 'form');
  }

  drupal_alter('airtribune_field_group_content', $element[$group_name]);

  $block = new StdClass();
  $block->module = 'airtribune';
  $block->delta = 'field_group';
  $block->content = drupal_render($element[$group_name]);

  return $block;
}

/**
 * Returns the administrative title for a type.
 */
function airtribune_field_group_content_type_admin_title($subtype, $conf, $context) {
  $entity_type = $context->type[2];
  if (empty($conf['field_group'])) {
    $group_name = t('undefined');
  }
  else {
    $group_name = $conf['field_group'];
  }
  return t('"@s" @group_name', array('@s' => $entity_type, '@group_name' => $group_name));
}
