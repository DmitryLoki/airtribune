<?php
/**
 * @file
 *  Views field handler.
 */

/**
 * Field handler that allows a link to be generated for a user so you may
 * masquerade as them.
 */
class masquerade_handler_field_user extends views_handler_field_user_link {

  /**
   * Set custom options and defaults on this handler.
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array(
      'default' => 'masquerade',
      'translatable' => TRUE,
    );
    $options['masquerade_views']['custom_destination'] = array(
      'default' => FALSE
    );
    $options['masquerade_views']['destination'] = array(
      'default' => ''
    );
    return $options;
  }

  /**
   * Adds additional options to the Field options form
   */
  function options_form(&$form, &$form_state) {    
    parent::options_form($form, $form_state);
    $form['masquerade_views'] = array(
      '#tree' => TRUE,
    );
    $form['masquerade_views']['custom_destination'] = array(
      '#title' => t('Provide a custom destination.'),
      '#description' => t('This is helpful for providing a shortcut to a certain function of the site from one area or another.'),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['masquerade_views']['custom_destination']) ? $this->options['masquerade_views']['custom_destination'] : FALSE,
    );

    // Provide an optional redirect immediately after switching to another user
    $form['masquerade_views']['destination'] = array(
      '#title' => t('Alternate destination'),
      '#description' => t('Redirect the browser to this page immediately after switching to another user. There is a caveat, however. When you switch back, masquerade will not remember where you last were.'),
      '#type' => 'textfield',
      '#default_value' => !empty($this->options['masquerade_views']['destination']) && valid_url($this->options['masquerade_views']['destination']) ? $this->sanitize_value($this->options['masquerade_views']['destination']) : '',
    );

    // Override the normal link-to title and description.
    $form['link_to_user']['#title'] = t('Generate a link to Masquerade as this user.');
    $form['link_to_user']['#description'] = t('Be careful not to rewrite this field with tokens that generate links. This field will only display a link to users who have permission to masquerade.');
  }

  /**
   * Prevent users that don't have permission to masquerade from accessing this function.
   */
  function access() {
    return user_access('masquerade as user');
  }

  /**
   * Generates a link.
   */
  function render_link($data, $values) {
    global $user;
    $text = !empty($this->options['text']) ? $this->options['text'] : t('masquerade');

    // Do not generate a link to masquerade as yourself.
    if (isset($user->uid) && $user->uid == $data) {
     return $text;
    }

    if (isset($values->{$this->aliases['uid']}) && $data !== NULL && $data !== '') {
      // Make sure any data being used to generate the link is clean.
      $switchto = $this->sanitize_value($values->{$this->aliases['uid']});
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "masquerade/switch/" . $switchto;

      // Let drupal know who we are before we switch users.
      $this->options['alter']['query'] = array('token' => drupal_get_token($this->options['alter']['path']));

      // If the user provided a custom destination (that isn't blank), tack it onto the link.
      if ($this->options['masquerade_views']['custom_destination']== TRUE && $this->options['masquerade_views']['destination'] != '') {
        $this->options['alter']['query'] += array('destination' => $this->options['masquerade_views']['destination']);
      }
    }

    return $text;
  }
}
