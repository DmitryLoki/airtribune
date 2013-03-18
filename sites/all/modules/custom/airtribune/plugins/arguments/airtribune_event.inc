<?php

/**
 * @file Class to load event context from argument
 * @author Vadim Valuev<gease@mail.ru>
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Event: nid"),
  // keyword to use for %substitution
  'keyword' => 'event',
  'description' => t('Creates an event node context from the arg.'),
  'context' => 'airtribune_arg_event_context',
  // 'settings form' => 'simplecontext_arg_settings_form',

  // placeholder_form is used in panels preview, for example, so we can
  // preview without getting the arg from a URL
  'placeholder form' => array(
    '#type' => 'textfield',
    '#description' => t('Enter the event nid'),
  ),
);

function airtribune_arg_event_context($arg = NULL, $conf = NULL, $empty = FALSE){
   // If $empty == TRUE it wants a generic, unfilled context.
  if ($empty) {
    return ctools_context_create_empty('event');
  }
  // Do whatever error checking is required, returning FALSE if it fails the test
  // Normally you'd check
  // for a missing object, one you couldn't create, etc.
  if (empty($arg)) {
    return FALSE;
  }
  
  $wrapper = entity_metadata_wrapper('node', $arg);
  if (!$wrapper->value()) {
    return FALSE;
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
  if (!$node) {
    return FALSE;
  }
  return ctools_context_create('node', $node);
}
?>
