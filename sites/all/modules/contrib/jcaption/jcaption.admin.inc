<?php

/**
 * @file
 * Contains the administration pages for jCaption.
 *
 */

function jcaption_settings($form_state) {

  $form['jcaption_alt_title'] = array(
    '#type' => 'radios',
    '#title' => t('Do you want jQuery Caption to use ALT or TITLE?'),
    '#options' => array(
    'title' => t('TITLE (default)'),
    'alt' => t('ALT')
    ),
    '#default_value' => variable_get('jcaption_alt_title', 'title'),
  );
  $form['jcaption_selectors'] = array(
    '#title' => t('What selectors do you want jQuery Caption to run on?'),
    '#type' => 'textarea',
    '#default_value' => variable_get('jcaption_selectors', '.content .content img'),
    '#description' => t('For example: .content .content img. Add one selector per line.'),
  );
  $form['jcaption_requireText'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require Text'),
    '#description' => t('Only create captions if there is content for the caption.'),
    '#default_value' => variable_get('jcaption_requireText', TRUE),
  );
  $form['jcaption_copyStyle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Copy Style'),
    '#description' => t('Copy style from image to container div.'),
    '#default_value' => variable_get('jcaption_copyStyle', TRUE),
  );
  $form['jcaption_removeStyle'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove Style'),
    '#description' => t('Remove style from image.'),
    '#default_value' => variable_get('jcaption_removeStyle', TRUE),
  );
  $form['jcaption_copyClassToClass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Copy Class'),
    '#description' => t('Transfers the class from the image to the caption container.'),
    '#default_value' => variable_get('jcaption_copyClassToClass', TRUE),
  );
  $form['jcaption_removeClass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove Class'),
    '#description' => t('Remove class from image.'),
    '#default_value' => variable_get('jcaption_removeClass', TRUE),
  );
  $form['jcaption_copyAlignmentToClass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Copy Alignment'),
    '#description' => t('Copy alignment from image to image container. If there is an alignment on the image (for example align="left") add "left" as a class on the caption. This helps deal with older Text Editors like TinyMCE.'),
    '#default_value' => variable_get('jcaption_copyAlignmentToClass', FALSE),
  );
  $form['jcaption_removeAlign'] = array(
    '#type' => 'checkbox',
    '#title' => t('Remove Align'),
    '#description' => t('Remove alignment from image.'),
    '#default_value' => variable_get('jcaption_removeAlign', TRUE),
  );
  $form['jcaption_copyFloatToClass'] = array(
    '#type' => 'checkbox',
    '#title' => t('Copy Float'),
    '#description' => t('Transfers the float style from the image to the caption container.'),
    '#default_value' => variable_get('jcaption_copyFloatToClass', TRUE),
  );
  $form['jcaption_autoWidth'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto Width'),
    '#description' => t('Properly size the caption div based on the loaded images size.'),
    '#default_value' => variable_get('jcaption_autoWidth', TRUE),
  );
  $form['jcaption_keepLink'] = array(
    '#type' => 'checkbox',
    '#title' => t('Keep Link'),
    '#description' => t('Keep the caption linked if a image is linked.'),
    '#default_value' => variable_get('jcaption_keepLink', FALSE),
  );
  $form['jcaption_styleMarkup'] = array(
    '#type' => 'textfield',
    '#title' => t('Style markup for Image Caption paragraph'),
    '#description' => t('If you want a <strong>style</strong> attribute on the <strong>p</strong> containing the caption, for example: <em>font-size: 14px; color: #888888; font-style: italic; text-align: center;</em>'),
    '#default_value' => variable_get('jcaption_styleMarkup', ''),
    '#size' => 150,
    '#maxlength' => 255,
  );
  $form['jcaption_animate'] = array(
    '#type' => 'checkbox',
    '#title' => t('Animate'),
    '#description' => t('Animate the image caption text.'),
    '#default_value' => variable_get('jcaption_animate', FALSE),
  );
  $form['jcaption_showDuration'] = array(
    '#type' => 'textfield',
    '#title' => t('Show Duration'),
    '#description' => t('Duration for showing animation.'),
    '#default_value' => variable_get('jcaption_showDuration', '200'),
    '#size' => 15,
    '#maxlength' => 5,
    '#required' => TRUE,
  );
  $form['jcaption_hideDuration'] = array(
    '#type' => 'textfield',
    '#title' => t('Hide Duration'),
    '#description' => t('Duration for hiding animation.'),
    '#default_value' => variable_get('jcaption_hideDuration', '200'),
    '#size' => 15,
    '#maxlength' => 5,
    '#required' => TRUE,
  );

  return system_settings_form($form);
}
