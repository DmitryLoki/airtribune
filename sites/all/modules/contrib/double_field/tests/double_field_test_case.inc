<?php

/**
 * @file
 * Tests for Double field module.
 * 
 * Some field settings are initializated by random values.
 * So it is recommended to run these tests several times.
 * @code
 * for i in {1..10};
 * do
 *   php scripts/run-tests.sh --url http://example.com/ --color 'Double field';
 * done
 * @endcode
 */

/**
 * Tests for double field types.
 */
class DoubleFieldTestCase extends DrupalWebTestCase {

  /**
   * Double field test group.
   */
  const GROUP = 'Double field';

  /**
   * Prepare environment.
   */
  public function setUp() {
    parent::setUp('double_field');

    // Create content type.
    $this->type_name = strtolower($this->randomName(8));
    $this->drupalCreateContentType(array('name' => $this->type_name, 'type' => $this->type_name));

    // Create test field.
    $this->field_name = strtolower($this->randomName(8));

    $field = array(
      'field_name' => $this->field_name,
      'type' => 'double_field',
      'cardinality' => 1,
    );
    $this->field = field_create_field($field);

    $instance = array(
      'field_name' => $this->field_name,
      'entity_type' => 'node',
      'label' => 'Test double field',
      'bundle' => $this->type_name,
      'widget' => array(
        'module' => 'double_field',
        'type' => 'textfield_&_textfield',
      ),
    );
    $widget = new DoubleFieldWidget($instance['widget']['type']);
    $instance['widget']['settings'] = $widget->getSettings();
    field_create_instance($instance);
    // Field create instance doesn't return all field properties.
    $this->instance = field_read_instance($instance['entity_type'], $instance['field_name'], $instance['bundle']);

    $this->user = $this->drupalCreateUser(
      array(
        'access administration pages',
        'administer content types',
        'create ' . $this->type_name . ' content',
        'edit own ' . $this->type_name . ' content',
      )
    );
    $this->drupalLogin($this->user);

    // Create a node with actual data for the field.
    $edit = array(
      'type' => $this->type_name,
      'uid' => $this->user->uid,
    );
    for ($delta = 0; $delta < $this->field['cardinality']; $delta++) {
      $edit[$this->field_name][LANGUAGE_NONE][] = $widget->getValue($delta);
    }
    $this->node = $this->drupalCreateNode($edit);

    $this->value = &$this->node->{$this->field_name}[LANGUAGE_NONE][0];

    $this->widgets = DoubleFieldWidget::getAllWidgetTypes();
  }

  /**
   * Create subfield name.
   */
  protected function getSubfieldName($index, $delta = 0) {
    return $this->field_name . '[' . LANGUAGE_NONE . '][' . $delta . '][' . $index . ']';
  }

  /**
   * Run validators.
   */
  protected function validate($validators, $success_message) {
    foreach ($validators as $xpath) {
      if (!$this->xpath($xpath)) {
        $this->fail($success_message);
        return;
      }
    }
    $this->pass($success_message);
  }

}
