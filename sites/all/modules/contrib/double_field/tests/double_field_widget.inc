<?php

/**
 * @file
 * The file contains a class that assists to test Double field widget types.
 */

/**
 * Helper class to test Double field widget types.
 */
class DoubleFieldWidget {

  const MAXLENGTH = 255;
  const MAXCARDINALITY = 10;

  protected $settings;
  protected $subwidgets;
  protected $value;

  /**
   * Constructor for DoubleFieldWidget.
   */
  public function __construct($widget_type) {
    // The order of the elements compared in
    // which order they were written in the list().
    list($this->subwidgets['second'], $this->subwidgets['first']) = array_reverse(explode('_&_', $widget_type));

    $this->settings['inline'] = (bool) mt_rand(0, 1);
    foreach ($this->subwidgets as $index => $subwidget) {
      $this->settings[$index]['general'] = array(
        'required' => (bool) mt_rand(0, 1),
        'prefix' => '(' . DrupalTestCase::randomName(mt_rand(0, 126)) . ')',
        'suffix' => '(' . DrupalTestCase::randomName(mt_rand(0, 126)) . ')',
      );
      $this->settings[$index][$subwidget] = $this->getSubWidgetSettings($subwidget);

      // Generate field value based on current widget settings.
      for ($delta = 0; $delta < self::MAXCARDINALITY; $delta++) {
        if ($subwidget == 'select') {
          // Take value for select list subwidget from allowed values.
          $this->value[$delta][$index] = array_rand($this->settings[$index][$subwidget]['allowed_values']);
        }
        elseif ($subwidget == 'checkbox') {
          $this->value[$delta][$index] = mt_rand(0, 1) ? '' : $this->settings[$index][$subwidget]['on_value'];
        }
        else {
          $this->value[$delta][$index] = DrupalTestCase::randomName(mt_rand(1, self::MAXLENGTH));
        }
      }

    }

  }

  /**
   * Get widget settings.
   */
  public function getSettings() {
    return $this->settings;
  }


  /**
   * Get field value.
   */
  public function getValue($delta = 0) {
    return $this->value[$delta];
  }

  /**
   * Get widget type.
   */
  public function getType() {
    return implode('_&_', $this->subwidgets);
  }

  /**
   * Return subwidget related settings.
   */
  protected function getSubWidgetSettings($subwidget) {

    switch ($subwidget) {

      case 'textfield':
        $settings['size'] = mt_rand(1, 50);
        break;

      case 'checkbox':
        $settings['on_value'] = DrupalTestCase::randomName(mt_rand(0, 25));;
        break;

      case 'select':
        $settings = array();
        for ($i = 0, $cnt = mt_rand(1, 10); $i < $cnt; $i++) {
          $value = DrupalTestCase::randomName(mt_rand(0, self::MAXLENGTH));
          $settings['allowed_values'][$value] = ucfirst($value);
        }
        break;

      case 'textarea':
        $settings['cols'] = mt_rand(1, 25);
        $settings['rows'] = mt_rand(1, 25);
        $settings['resizable'] = (bool) mt_rand(0, 1);
        break;

      default:
        throw new Exception('Undefined subwidget type: ' . $subwidget);
    }

    return $settings;
  }

  /**
   * Create widget settings form validators.
   */
  public function getSettingsFormValidators() {

    $form_xpath = '//form[@id="field-ui-field-edit-form"]';

    $checked = $this->settings['inline'] ? '@checked' : 'not(@checked)';
    $validators[] = "$form_xpath//input[@name='instance[widget][settings][inline]' and $checked]";

    foreach ($this->subwidgets as $index => $subwidget) {
      $prefix = "$form_xpath//fieldset[@id='edit-instance-widget-settings-$index']";
      $text = ($index == 'first' ? t('First subfield') : t('Second subfield')) . ' (' . double_field_get_subwidgets($subwidget) . ')';
      $validators[] = "$prefix//legend//span[text()='$text']";

      // Check subwidget related elements.
      switch ($subwidget) {

        case 'textfield':
          $value = $this->settings[$index][$subwidget]['size'];
          $validators[] = "$prefix//input[@name='instance[widget][settings][$index][$subwidget][size]' and @value='$value']";
          break;

        case 'textarea':
          $value = $this->settings[$index][$subwidget]['cols'];
          $validators[] = "$prefix//input[@name='instance[widget][settings][$index][$subwidget][cols]' and @value='$value']";
          $value = $this->settings[$index][$subwidget]['rows'];
          $validators[] = "$prefix//input[@name='instance[widget][settings][$index][$subwidget][rows]' and @value='$value']";
          $checked = $this->settings[$index][$subwidget]['resizable'] ? '@checked' : 'not(@checked)';
          $validators[] = "$prefix//input[@name='instance[widget][settings][$index][$subwidget][resizable]' and $checked]";
          break;

        case 'select':
          $value = list_allowed_values_string($this->settings[$index][$subwidget]['allowed_values']);
          $validators[] = "$prefix//textarea[@name='instance[widget][settings][$index][$subwidget][allowed_values]' and text()='$value']";
          break;

        case 'checkbox':
          $value = $this->settings[$index][$subwidget]['on_value'];
          $validators[] = "$prefix//input[@name='instance[widget][settings][$index][$subwidget][on_value]' and @value='$value']";
          break;

      }

      // Walk down to general fieldset (should be collapsed).
      $prefix .= "//fieldset[@id='edit-instance-widget-settings-$index-general' and @class='collapsible collapsed form-wrapper']";

      $checked = $this->settings[$index]['general']['required'] ? '@checked' : 'not(@checked)';
      $validators[] = "$prefix//input[@name='instance[widget][settings][$index][general][required]' and $checked]";

      $value = $this->settings[$index]['general']['prefix'];
      $validators[] = "$prefix//input[@name='instance[widget][settings][$index][general][prefix]' and @value='$value']";

      $value = $this->settings[$index]['general']['suffix'];
      $validators[] = "$prefix//input[@name='instance[widget][settings][$index][general][suffix]' and @value='$value']";
    }

    return $validators;
  }

  /**
   * Create widget fornm validators.
   */
  public function getFormValidators($field_name) {
    $prefix = "//div[@id='edit-$field_name']";

    $class = $this->settings['inline'] ? 'double-field-elements container-inline form-wrapper' : 'double-field-elements form-wrapper';

    // Verify prefix and suffix.
    $validators[] = "$prefix//div[@class='$class' and starts-with(text(), {$this->settings['first']['general']['prefix']})]";
    $validators[] = "$prefix//div[@class='$class' and contains(text(), {$this->settings['first']['general']['suffix']})]";
    $validators[] = "$prefix//div[@class='$class' and contains(text(), {$this->settings['second']['general']['prefix']})]";
    // It seems that ends-with() is an XPath 2.0 function.
    $validators[] = "$prefix//div[@class='$class' and contains(text(), {$this->settings['second']['general']['suffix']})]";

    $prefix .= "//div[@class='$class']";

    foreach ($this->subwidgets as $index => $subwidget) {
      $name = $field_name . '[' . LANGUAGE_NONE . '][0][' .  $index . ']';
      $value = $this->value[0][$index];

      // Check subwidget related elements.
      switch ($subwidget) {
        case 'textfield':
          $size = $this->settings[$index][$subwidget]['size'];
          $validators[] = "$prefix//input[@name='$name' and @type='text' and @size='$size' and @value='$value']";
          break;

        case 'textarea':
          $cols = $this->settings[$index][$subwidget]['cols'];
          $rows = $this->settings[$index][$subwidget]['rows'];
          $wrapper_class = $this->settings[$index][$subwidget]['resizable'] ? 'form-textarea-wrapper resizable' : 'form-textarea-wrapper';
          $validators[] = "$prefix//div[@class='$wrapper_class']//textarea[@name='$name' and @cols='$cols' and @rows='$rows' and text()='$value']";
          break;

        case 'select':
          $validators[] = "$prefix//select[@name='$name']//option[@value='$value' and @selected='selected']";
          break;

        case 'checkbox':
          $checked = $value ? '@checked' : 'not(@checked)';
          $validators[] = "$prefix//input[@name='$name' and @type='checkbox' and '$checked']";
          break;
      }
    }

    return $validators;
  }

  /**
   * Return input array for post submission.
   */
  public function getSettingsFormInput() {
    return $this->settingsToInput($this->settings, 'instance[widget][settings]', TRUE);
  }

  /**
   * Convert settings to input array.
   */
  protected function settingsToInput($settings, $parents = '', $reset = FALSE) {
    static $result;
    if ($reset) {
      $result = array();
    }
    foreach ($settings as $key => $value) {
      if (is_array($value) && $key != 'allowed_values') {
        $this->settingsToInput($value, $parents . "[$key]");
      }
      elseif ($parents) {
        $result[$parents . "[$key]"] = $key == 'allowed_values' ? list_allowed_values_string($value) : $value;
      }
    }
    return $result;
  }

  /**
   * Create widget form input values.
   */
  public function getFormInput($field_name, $delta = 0) {
    return array(
      $field_name . '[' . LANGUAGE_NONE . '][' . $delta . '][first]' => $this->value[$delta]['first'],
      $field_name . '[' . LANGUAGE_NONE . '][' . $delta . '][second]' => $this->value[$delta]['second'],
    );
  }

  /**
   * Get all suported widget types.
   */
  public static function getAllWidgetTypes() {
    $subwidgets = array(
      'textfield' => t('Text field'),
      'checkbox'  => t('Checkbox'),
      'select'    => t('Select list'),
      'textarea'  => t('Textarea'),
    );
    foreach ($subwidgets as $first_subwidget => $first_subwidget_label) {
      foreach ($subwidgets as $second_subwidget => $second_subwidget_label) {
        $widgets[$first_subwidget . '_&_' . $second_subwidget] = array(
          'label' => $first_subwidget_label . ' & ' . $second_subwidget_label,
        );
      }
    }
    return $widgets;
  }
}
