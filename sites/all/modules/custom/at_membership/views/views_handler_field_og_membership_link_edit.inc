<?php

/**
 * @file
 * Definition of views_handler_field_og_membership_link_edit.
 */

/**
 * Field handler to present a link to the OG membership.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_og_membership_link_edit extends views_handler_field_entity {

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    if ($entity = $this->get_value($values)) {
      return $this->render_link($entity, $values);
    }
  }

  /**
   * Renders the link.
   */
  function render_link($og_membership, $values) {
    // Ensure user has access to edit this node.
    if (!at_membership_access($og_membership) || $og_membership->entity_type != 'user') {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "group-membership/$og_membership->id/edit";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    return $text;
  }
}
