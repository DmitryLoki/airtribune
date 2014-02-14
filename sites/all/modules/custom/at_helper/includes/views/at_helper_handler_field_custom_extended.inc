<?php


/**
 * Based on views_handler_field_custom handler
 */
class at_helper_handler_field_custom_extended extends views_handler_field {
  function query() {
    // do nothing -- to override the parent query.
  }

  function option_definition() {
    $options = parent::option_definition();

    // Override the alter text option to always alter the text.
    $options['alter']['contains']['alter_text'] = array('default' => TRUE, 'bool' => TRUE);
    $options['hide_alter_empty'] = array('default' => FALSE, 'bool' => TRUE);
    $options['renderer_plugin'] = array('default' => '', 'bool' => FALSE);
    return $options;
  }

  // @todo: add validation
  // In validation check token keys, required by plugin. Required keys must be given by plugin.
  // Also remove components textarea from translatables if possible.
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove the checkbox
    unset($form['alter']['alter_text']);
    unset($form['alter']['text']['#dependency']);
    unset($form['alter']['text']['#process']);
    unset($form['alter']['help']['#dependency']);
    unset($form['alter']['help']['#process']);
    $form['#pre_render'][] = 'at_helper_handler_field_custom_extended_pre_render_move_text';


    $form['alter']['text']['#title'] = t('Components');
    $form['alter']['text']['#description'] = t('Add components in "!pattern" form', array('!pattern' => 'key|[token]'));
    $form['alter']['text']['#required'] = TRUE;

    $plugins = ctools_get_plugins('at_helper', 'nothing_extended');
    $options = array();
    foreach ($plugins as $k => $plugin) {
      $options[$k] = $plugin['title'];
    }
    $form['renderer_plugin'] = array(
      '#type' => 'select',
      '#title' => t('Renderer plugin'),
      '#options' => $options,
      '#default_value' => $this->options['renderer_plugin'],
      '#required' => TRUE,
      '#weight' => 0,
    );
  }

  function render($values) {
    $text = $this->options['alter']['text'];
    $components = at_helper_handler_field_custom_extended_get_components($text);
    $tokens = $this->get_render_tokens($this->options['alter']);

    /**
     * @todo:
     * load plugin
     * process text and tokens
     */
    $plugins = ctools_get_plugins('at_helper', 'nothing_extended');
    if (!empty($plugins[$this->options['renderer_plugin']])) {
      $plugin = $plugins[$this->options['renderer_plugin']];
      $functon = $plugin['renderer'];
      $text = $functon($components, $tokens);
    }
    else {
      // @todo: set error
    }

    $this->options['alter']['text'] = $text;

    // Return the text, so the code never thinks the value is empty.
    return $text;
  }
}

/**
 * Prerender function to move the textarea to the top.
 */
function at_helper_handler_field_custom_extended_pre_render_move_text($form) {
  $form['text'] = $form['alter']['text'];
  $form['help'] = $form['alter']['help'];
  unset($form['alter']['text']);
  unset($form['alter']['help']);

  return $form;
}

/**
 * Return components or FALSE in case of error.
 * @todo: check for valid text
 */
function at_helper_handler_field_custom_extended_get_components($string) {
  $components = list_extract_allowed_values($string, 'list_text', FALSE);
  return $components;
}
