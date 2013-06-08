-- SUMMARY --

The Extrafield Views Integration Module enables all Drupal core extra fields in
the system from type "display" as fields in views. A special greeting to
Daniel Wehner, he gave me with his views training
(sponsored by comm-press GmbH) the knowledge to write this module.

-- REQUIREMENTS --

Views
Entity

 -- INSTALLATION --

For installing the module, just download the source code and enable the module.
That's all.

-- CONFIGURATION --

The module itself needs no configuration, because the extra fields that you
want to use need an callback key and a callback function. Every module can use
hook_field_extra_fields() to register the extra fields. Normally it looks like
this:

function hook_field_extra_fields() {
  $extra_fields = array(
    'entity_type' => array(
      'bundle' => array(
        'display' => array(
           'field_name' => array(
            'label' => 'field label',
            'description' => 'field description',
            'weight' => 0,
            'callback' => 'field_callback_function',
          ),
        ),
      ),
   ),
);

return $extra_fields;
}

function field_callback_function($entity) {
  return 'Field content to display in views or entity display';
}

The module needs both, the callback key and an existing callback function
defined in the callback key. The module only registers extra fields from type
"display" with the required key and the existing callback function. Views then
passes the entity to the callback function of the field.

-- FAQ --

Q:  I register an extra field for node type "article". But views doesn't show
    me the extra field.

A:  Ensure that you add the callback key to the extra field array and that the
    function you defined in the callback key exists.

Q:  I see my field for the node type "article" but I don't see any output.

A:  Ensure that your callback function returns a value.
