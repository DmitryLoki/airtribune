<?php

/**
 * @file
 * The file contains a class that assists to test Double field formatter types.
 */


/**
 * Helper class to test Double field formatters.
 */
class DoubleFieldFormatter {

  protected $settings;
  protected $type;

  /**
   * Constructor for DoubleFieldFormatter.
   */
  public function __construct($formatter_type) {
    $this->type = $formatter_type;
    $formatters = self::getAllFormatterTypes();
    $this->label = $formatters[$this->type];

    foreach (array('first', 'second') as $subfield) {
      $this->settings[$subfield] = array(
        'hidden' => FALSE,
        'format' => '_none',
        'prefix' => '[' . DrupalTestCase::randomName(mt_rand(0, 128 - 2)) . ']',
        'suffix' => '[' . DrupalTestCase::randomName(mt_rand(0, 128 - 2)) . ']',
      );
    }

    $styles = array('block', 'inline', 'link');
    switch ($this->type) {
      case 'double_field_unformatted_list':
        $this->settings['style'] = $styles[mt_rand(0, 2)];
        break;

      case 'double_field_html_list':
        $this->settings['style'] = $styles[mt_rand(0, 2)];
        $this->settings['list_type'] = mt_rand(0, 1) ? 'ul' : 'ol';
        break;

      case 'double_field_fieldset':
        $this->settings['collapsible'] = (bool) mt_rand(0, 1);
        $this->settings['collapsed'] = (bool) mt_rand(0, 1);
        break;

      case 'double_field_table':
        $this->settings['table']['number_column'] = (bool) mt_rand(0, 1);
        $this->settings['table']['number_column_label'] = DrupalTestCase::randomName(mt_rand(0, 8));
        $this->settings['table']['first']['column_label'] = mt_rand(0, 1) ? DrupalTestCase::randomName(mt_rand(0, 32)) : '';
        $this->settings['table']['second']['column_label'] = mt_rand(0, 1) ? DrupalTestCase::randomName(mt_rand(0, 32)) : '';
        break;

    }

  }

  /**
   * Get formatter settings.
   */
  public function getSettings() {
    return $this->settings;
  }

  /**
   * Get formatter type.
   */
  public function getType() {
    return $this->type;
  }

  /**
   * Confirm that the formatter settings form is being displayed.
   */
  public function getSettingsFormValidators($field_name) {
    $prefix = "//div[contains(@class, 'field-formatter-settings-edit-form')]";
    $validators["Formatter settings form: formatter label was found"] = "$prefix//span[@class='formatter-name' and text()='{$this->label}']";

    foreach (array('first', 'second') as $subfield) {
      $subfield_prefix = "/fieldset[contains(@class, 'collapsible') and contains(@class, 'collapsed')]";
      $text = ucfirst("$subfield subfield");
      $validators["Formatter settings form: fieldset legend was found"] = "$prefix$subfield_prefix/legend//span[text()='$text']";

      $name = "fields[$field_name][settings_edit_form][settings][$subfield][hidden]";
      $checked = $this->settings[$subfield]['hidden'] ? '@checked' : 'not(@checked)';
      $validators["Formatter settings form: «hidden» value was found"] = "$prefix$subfield_prefix//input[@type='checkbox' and @name='$name' and $checked]";

      $name = "fields[$field_name][settings_edit_form][settings][$subfield][format]";
      $validators["Formatter settings form: «- None -» option was found"] = "$prefix$subfield_prefix//select[@name='$name']/option[@value='_none' and text()='- None -']";
      foreach (filter_formats() as $format) {
        $validators["Formatter settings form: «{$format->name}» option was found"] = "$prefix$subfield_prefix//select[@name='$name']/option[@value='$format->format' and text()='$format->name']";
      }

      $value = $this->settings[$subfield]['format'];
      $selected = $this->settings[$subfield]['format'] ? '@selected' : 'not(@selected)';
      $validators["Formatter settings form: «format» value was found"] = "$prefix$subfield_prefix//select[@name='$name']/option[@value='$value' and $selected]";

      $name = "fields[$field_name][settings_edit_form][settings][$subfield][prefix]";
      $value = $this->settings[$subfield]['prefix'];
      $validators["Formatter settings form: «prefix» value was found"] = "$prefix$subfield_prefix//input[@type='text' and @name='$name' and @value='$value']";

      $name = "fields[$field_name][settings_edit_form][settings][$subfield][suffix]";
      $value = $this->settings[$subfield]['suffix'];
      $validators["Formatter settings form: «suffix» value was found"] = "$prefix$subfield_prefix//input[@type='text' and @name='$name' and @value='$value']";
    }

    return $validators;
  }


  /**
   * Confirm that the formatter is being displayed.
   */
  public function getFormatterValidators($field_name, $items) {
    $cardinality = count($items);
    $prefix = "//div[contains(@class, 'field-name-$field_name')]/div[contains(@class, 'field-items')]";
    $validators[] = $prefix;

    switch ($this->type) {

      case 'double_field_unformatted_list':
        if ($this->settings['style'] == 'link') {
          for ($delta = 0; $delta < $cardinality; $delta++) {
            $text = $this->settings['first']['prefix'] . $items[$delta]['first'] . $this->settings['first']['suffix'];
            // See l().
            $href = check_plain(url($this->settings['second']['prefix'] . $items[$delta]['second'] . $this->settings['second']['suffix']));
            $validators[] = "//a[@href='$href' and text()='$text']";
          }
        }
        else {
          $class = $this->settings['style'] == 'block' ? 'clearfix' : 'container-inline';
          for ($delta = 0; $delta < $cardinality; $delta++) {
            foreach (array('first', 'second') as $subfield) {
              $text = $this->settings[$subfield]['prefix'] . $items[$delta][$subfield] . $this->settings[$subfield]['suffix'];
              $validators[] = "//div[@class='$class']/div[@class='double-field-$subfield' and text()='$text']";
            }
          }
        }
        break;

      case 'double_field_html_list':
        $prefix .= "//div[contains(@class, 'item-list')]/{$this->settings['list_type']}/li";
        if ($this->settings['style'] == 'link') {
          for ($delta = 0; $delta < $cardinality; $delta++) {
            $text = $this->settings['first']['prefix'] . $items[$delta]['first'] . $this->settings['first']['suffix'];
            // See l().
            $href = check_plain(url($this->settings['second']['prefix'] . $items[$delta]['second'] . $this->settings['second']['suffix']));
            $validators[] = "$prefix/a[@href='$href' and text()='$text']";
          }
        }
        else {
          $class = $this->settings['style'] == 'block' ? 'clearfix' : 'container-inline';
          for ($delta = 0; $delta < $cardinality; $delta++) {
            foreach (array('first', 'second') as $subfield) {
              $text = $this->settings[$subfield]['prefix'] . $items[$delta][$subfield] . $this->settings[$subfield]['suffix'];
              $validators[] = "$prefix/div[@class='$class']/div[@class='double-field-$subfield' and text()='$text']";
            }
          }
        }
        break;

      case 'double_field_fieldset':
        $collapsible = $this->settings['collapsible'] ? "contains(@class,'collapsible')" : "not(contains(@class,'collapsible'))";
        $collapsed = $this->settings['collapsed'] ? "contains(@class,'collapsed')" : "not(contains(@class,'collapsed'))";
        $prefix .= "//fieldset[$collapsible]";
        for ($delta = 0; $delta < $cardinality; $delta++) {
          $text = $this->settings['first']['prefix'] . $items[$delta]['first'] . $this->settings['first']['suffix'];
          $validators[] = "$prefix/legend/span[text()='$text']";
          $text = $this->settings['second']['prefix'] . $items[$delta]['second'] . $this->settings['second']['suffix'];
          $validators[] = "$prefix/div[@class='fieldset-wrapper' and text()='$text']";
        }
        break;

      case 'double_field_table':
        $prefix .= "//table";
        if ($this->settings['table']['first']['column_label'] || $this->settings['table']['second']['column_label']) {
          if ($this->settings['table']['number_column']) {
            $text = $this->settings['table']['number_column_label'];
            $validators[] = "$prefix/thead/tr/th[position()=1 and text()='$text']";
          }
          foreach (array('first', 'second') as $subfield) {
            if ($text = $this->settings['table'][$subfield]['column_label']) {
              $validators[] = "$prefix/thead/tr/th[text()='$text']";
            }
            else {
              // Column label can be empty.
              $validators[] = "$prefix/thead/tr/th[not(text())]";
            }
          }
        }
        else {
          // Verify that table head doesn't exist.
          $validators[] = "$prefix/*[position()=1 and not(name()='thead')]";
        }

        for ($delta = 0; $delta < $cardinality; $delta++) {
          $position = $this->settings['table']['number_column'] ? 2 : 1;
          if ($this->settings['table']['number_column']) {
            $text = $delta + 1;
            $validators[] = "$prefix/tbody/tr/td[position()=1 and text()='$text']";
          }
          foreach (array('first', 'second') as $subfield) {
            $text = $this->settings[$subfield]['prefix'] . $items[$delta][$subfield] . $this->settings[$subfield]['suffix'];
            $validators[] = "$prefix/tbody/tr/td[position()=$position and text()='$text']";
            $position++;
          }
        }
        break;

      case 'double_field_accordion':
        $prefix .= "//div[contains(@class, 'double-field-accordion')]";
        for ($delta = 0; $delta < $cardinality; $delta++) {
          $text = $this->settings['first']['prefix'] . $items[$delta]['first'] . $this->settings['first']['suffix'];
          $validators[] = "$prefix/h3/a[text()='$text']";
          $text = $this->settings['second']['prefix'] . $items[$delta]['second'] . $this->settings['second']['suffix'];
          $validators[] = "$prefix/div[not(@class)]";
        }
        $validators[] = "//head/script[contains(@src,'jquery.ui.accordion.min')]";
        $validators[] = "//head/script[not(@src) and contains(text(), 'jQuery(document).ready(function(){jQuery(\".double-field-accordion\").accordion({ collapsible: true, active: false });});')]";
        break;

      case 'double_field_tabs':
        $prefix .= "//div[contains(@class, 'double-field-tabs')]";
        $label_prefix = "//div[contains(@class, 'item-list')]/ul";
        for ($delta = 0; $delta < $cardinality; $delta++) {
          $id = "tabs-1-$delta";
          $tab_label = $this->settings['first']['prefix'] . $items[$delta]['first'] . $this->settings['first']['suffix'];
          $validators[] = "$label_prefix/li/a[@href='#$id' and text()='$tab_label']";
          $tab_value = $this->settings['second']['prefix'] . $items[$delta]['second'] . $this->settings['second']['suffix'];
          $validators[] = "$prefix/div[@id='$id' and text()='$tab_value']";
        }
        $validators[] = "//head/script[contains(@src,'jquery.ui.tabs.min')]";
        $validators[] = "//head/script[not(@src) and contains(text(), 'jQuery(document).ready(function(){jQuery(\".double-field-tabs\").tabs();});')]";
        break;

      case 'double_field_dialog':
        for ($delta = 0; $delta < $cardinality; $delta++) {
          $title = $this->settings['first']['prefix'] . $items[$delta]['first'] . $this->settings['first']['suffix'];
          $text = $this->settings['second']['prefix'] . $items[$delta]['second'] . $this->settings['second']['suffix'];
          $validators[] = "$prefix//div[@class='double-field-dialog' and @title='$title' and text()='$text']";
        }
        $validators[] = "//head/script[contains(@src,'jquery.ui.dialog.min')]";
        $validators[] = "//head/script[not(@src) and contains(text(), 'jQuery(document).ready(function(){jQuery(\".double-field-dialog\").dialog();});')]";
        break;

    }

    return $validators;
  }


  /**
   * Return input array for settings form submission.
   */
  public function getSettingsFormInput($field_name) {
    return $this->settingsToInput($this->settings, "fields[$field_name][settings_edit_form][settings]", TRUE);
  }

  /**
   * Convert settings to input array for post submission.
   */
  protected function settingsToInput($settings, $parents = '', $reset = FALSE) {
    static $result;
    if ($reset) {
      $result = array();
    }
    foreach ($settings as $key => $value) {
      if (is_array($value)) {
        $this->settingsToInput($value, $parents . "[$key]");
      }
      elseif ($parents) {
        $result[$parents . "[$key]"] = $value;
      }
    }
    return $result;
  }

  /**
   * All suported formatters.
   */
  public static function getAllFormatterTypes() {
    return array(
      'double_field_unformatted_list' => t('Unformatted list'),
      'double_field_fieldset'         => t('Fieldset'),
      'double_field_html_list'        => t('HTML list'),
      'double_field_table'            => t('Table'),
      'double_field_accordion'        => t('Accordion'),
      'double_field_tabs'             => t('Tabs'),
      'double_field_dialog'           => t('Dialog'),
    );
  }

}
