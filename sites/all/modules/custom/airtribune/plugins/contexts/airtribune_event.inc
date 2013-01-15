<?php

/**
 * @file
 *
 * Plugin to provide an event node context.
 */

// Plugin definition.
$plugin = array(
  'title' => t("Event beeing viewed"),
  'description' => t('A contest node object.'),
  'context' => 'airtribune_context_event',
  'edit form' => 'airtribune_context_event_settings_form',
  'keyword' => 'event',
  'context name' => 'airtribune_event',
  'convert list' => 'airtribune_context_event_convert_list',
  'convert' => 'airtribune_context_event_convert',
);

/**
 * It's important to remember that $conf is optional here, because contexts
 * are not always created from the UI.
 */
function airtribune_context_event($empty, $data = NULL, $conf = FALSE) {
  if (empty($data)) {
    return;
  }

  $context = new ctools_context('node');
  $context->plugin = 'node';

  $wrapper = entity_metadata_wrapper('node', (int) arg(1));
  if (!$wrapper->value()) {
    return $context;
  }

  if ($wrapper->getBundle() == AIRTRIBUNE_PG_CONTEST_TYPE) {
    $node = $wrapper->value();
  }
  // Fetch event node from OG.
  elseif (isset($wrapper->{AIRTRIBUNE_OG_GROUP_REF_FIELD})) {
    if ($wrapper->{AIRTRIBUNE_OG_GROUP_REF_FIELD}[0]->getBundle() == AIRTRIBUNE_PG_CONTEST_TYPE) {
      $node = $wrapper->{AIRTRIBUNE_OG_GROUP_REF_FIELD}[0]->value();
    }
  }

  if (!empty($node)) {
    $context->data     = $node;
    $context->title    = $node->title;
    $context->argument = $node->nid;
    $context->restrictions['type'] = array($node->type);
  }
  return $context;
}

/**
 * Context settings form.
 */
function airtribune_context_event_settings_form($form, &$form_state) {
  return $form;
}

/**
 * Provide a list of ways that this context can be converted to a string.
 */
function airtribune_context_event_convert_list() {
  $tokens = token_info();
  foreach ($tokens['tokens']['node'] as $id => $info) {
    if (!isset($list[$id])) {
      $list[$id] = $info['name'];
    }
  }
  return $list;
}

/**
 * Convert a context into a string.
 */
function airtribune_context_event_convert($context, $type) {
  $tokens = token_info();
  if (isset($tokens['tokens']['node'][$type])) {
    $values = token_generate('node', array($type => $type), array('node' => $context->data));
    if (isset($values[$type])) {
      return $values[$type];
    }
  }
}
