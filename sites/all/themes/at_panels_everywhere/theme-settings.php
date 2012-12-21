<?php
function at_panels_everywhere_form_system_theme_settings_alter(&$form, &$form_state)  {

  // Hide most of the responsive settings until I figure out what to do with them for this theme
  /*
  $form['at']['bigscreen']['bigscreen-layout-wrapper']['#attributes'] = array('class' => array('element-invisible'));
  $form['at']['bigscreen']['bigscreen-sidebar-wrapper']['#attributes'] = array('class' => array('element-invisible'));

  $form['at']['tablet']['landscape']['tablet-landscape-layout-wrapper']['#attributes'] = array('class' => array('element-invisible'));
  $form['at']['tablet']['landscape']['tablet-landscape-sidebar-width-wrapper']['#attributes'] = array('class' => array('element-invisible'));
  $form['at']['tablet']['portrait']['tablet-portrait-layout-wrapper']['#attributes'] = array('class' => array('element-invisible'));
  $form['at']['tablet']['portrait']['tablet-portrait-sidebar-width-wrapper']['#attributes'] = array('class' => array('element-invisible'));

  $form['at']['smartphone']['landscape']['smartphone-landscape-layout-wrapper']['#attributes'] = array('class' => array('element-invisible'));
  $form['at']['smartphone']['landscape']['smartphone-landscape-sidebar-width-wrapper']['#attributes'] = array('class' => array('element-invisible'));

  $form['at']['smartphone']['#description'] = t('<h3>Smartphone Layout</h3><p>Smartphone devices such as iPhone, Android and Windows phones have two orientations - landscape and portrait.</p>');
  $form['at']['smartphone']['portrait']['#description'] = t('<h4>Portrait smartphone</h4><p>The smartphone portrait layout always displays in one column with all regions/panes stacked vertically. All widths are always 100%.</p>');
  */
}
