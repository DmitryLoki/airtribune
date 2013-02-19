<?php
/**
 * @file
 * accommodation.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function accommodation_field_default_fields() {
  $fields = array();

  // Exported field: 'node-accommodation-body'.
  $fields['node-accommodation-body'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(
        0 => 'node',
      ),
      'field_name' => 'body',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
      ),
      'translatable' => '1',
      'type' => 'text_with_summary',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(),
          'type' => 'text_default',
          'weight' => '4',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'hidden',
          'module' => 'text',
          'settings' => array(
            'trim_length' => 600,
          ),
          'type' => 'text_summary_or_trimmed',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'body',
      'label' => 'Services and prices',
      'required' => 0,
      'settings' => array(
        'display_summary' => 1,
        'entity_translation_sync' => FALSE,
        'text_processing' => '1',
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'text',
        'settings' => array(
          'rows' => '20',
          'summary_rows' => 5,
        ),
        'type' => 'text_textarea_with_summary',
        'weight' => '12',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_accommodation_price_double'.
  $fields['node-accommodation-field_accommodation_price_double'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_accommodation_price_double',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'double_field',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'first' => array(
          'maxlength' => '32',
        ),
        'profile2_private' => FALSE,
        'second' => array(
          'maxlength' => '32',
        ),
      ),
      'translatable' => '0',
      'type' => 'double_field',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => array(
        0 => array(
          'first' => '0',
          'second' => 'eur',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'double_field',
          'settings' => array(
            'first' => array(
              'format' => '_none',
              'hidden' => 0,
              'prefix' => '',
              'suffix' => ' ',
            ),
            'second' => array(
              'format' => '_none',
              'hidden' => 0,
              'prefix' => '',
              'suffix' => '',
            ),
            'style' => 'inline',
          ),
          'type' => 'double_field_unformatted_list',
          'weight' => '1',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_accommodation_price_double',
      'label' => 'Double',
      'required' => 1,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'double_field',
        'settings' => array(
          'first' => array(
            'general' => array(
              'prefix' => '',
              'required' => 1,
              'suffix' => '',
            ),
            'textfield' => array(
              'size' => '10',
            ),
          ),
          'inline' => 1,
          'second' => array(
            'general' => array(
              'prefix' => '',
              'required' => 1,
              'suffix' => '',
            ),
            'select' => array(
              'allowed_values' => array(
                'eur' => 'EUR',
                'usd' => 'USD',
              ),
            ),
          ),
        ),
        'type' => 'textfield_&_select',
        'weight' => '18',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_accommodation_price_single'.
  $fields['node-accommodation-field_accommodation_price_single'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_accommodation_price_single',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'double_field',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'first' => array(
          'maxlength' => '32',
        ),
        'profile2_private' => FALSE,
        'second' => array(
          'maxlength' => '32',
        ),
      ),
      'translatable' => '0',
      'type' => 'double_field',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => array(
        0 => array(
          'first' => '0',
          'second' => 'eur',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'double_field',
          'settings' => array(
            'first' => array(
              'format' => '_none',
              'hidden' => 0,
              'prefix' => '',
              'suffix' => ' ',
            ),
            'second' => array(
              'format' => '_none',
              'hidden' => 0,
              'prefix' => '',
              'suffix' => '',
            ),
            'style' => 'inline',
          ),
          'type' => 'double_field_unformatted_list',
          'weight' => '0',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_accommodation_price_single',
      'label' => 'Single',
      'required' => 1,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'double_field',
        'settings' => array(
          'first' => array(
            'general' => array(
              'prefix' => '',
              'required' => 1,
              'suffix' => '',
            ),
            'textfield' => array(
              'size' => '10',
            ),
          ),
          'inline' => 1,
          'second' => array(
            'general' => array(
              'prefix' => '',
              'required' => 1,
              'suffix' => '',
            ),
            'select' => array(
              'allowed_values' => array(
                'eur' => 'EUR',
                'usd' => 'USD',
              ),
            ),
          ),
        ),
        'type' => 'textfield_&_select',
        'weight' => '17',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_address'.
  $fields['node-accommodation-field_address'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_address',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'addressfield',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'addressfield',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => array(
        0 => array(
          'element_key' => 'node|accommodation|field_address|und|0',
          'thoroughfare' => '',
          'premise' => '',
          'locality' => '',
          'administrative_area' => '',
          'postal_code' => '',
          'country' => 'US',
        ),
      ),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'addressfield',
          'settings' => array(
            'format_handlers' => array(
              0 => 'address',
            ),
            'use_widget_handlers' => 1,
          ),
          'type' => 'addressfield_default',
          'weight' => '8',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_address',
      'label' => 'Address',
      'required' => 1,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'addressfield',
        'settings' => array(
          'available_countries' => array(),
          'format_handlers' => array(
            'address' => 'address',
            'address-hide-country' => 0,
            'organisation' => 0,
            'name-full' => 0,
            'name-oneline' => 0,
          ),
        ),
        'type' => 'addressfield_standard',
        'weight' => '6',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_email'.
  $fields['node-accommodation-field_email'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_email',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'email',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'email',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'invisimail',
          'settings' => array(
            'encoder' => 'html_entities',
            'link' => 1,
          ),
          'type' => 'invisimail_html_entities',
          'weight' => '7',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_email',
      'label' => 'Email',
      'required' => 0,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'html5_tools',
        'settings' => array(),
        'type' => 'emailwidget',
        'weight' => '10',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_hotel_wifi'.
  $fields['node-accommodation-field_hotel_wifi'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_hotel_wifi',
      'foreign keys' => array(),
      'indexes' => array(
        'value' => array(
          0 => 'value',
        ),
      ),
      'locked' => '0',
      'module' => 'list',
      'settings' => array(
        'allowed_values' => array(
          0 => 'No',
          1 => 'Yes',
        ),
        'allowed_values_function' => '',
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'list_boolean',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => array(),
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'list',
          'settings' => array(),
          'type' => 'list_default',
          'weight' => '2',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_hotel_wifi',
      'label' => 'Wi-Fi',
      'required' => 1,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'options',
        'settings' => array(),
        'type' => 'options_buttons',
        'weight' => '1',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_location'.
  $fields['node-accommodation-field_location'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_location',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(
        'bbox' => array(
          0 => 'top',
          1 => 'bottom',
          2 => 'left',
          3 => 'right',
        ),
        'bottom' => array(
          0 => 'bottom',
        ),
        'centroid' => array(
          0 => 'lat',
          1 => 'lon',
        ),
        'geohash' => array(
          0 => 'geohash',
        ),
        'lat' => array(
          0 => 'lat',
        ),
        'left' => array(
          0 => 'left',
        ),
        'lon' => array(
          0 => 'lon',
        ),
        'right' => array(
          0 => 'right',
        ),
        'top' => array(
          0 => 'top',
        ),
      ),
      'locked' => '0',
      'module' => 'geofield',
      'settings' => array(
        'backend' => 'default',
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
        'srid' => '4326',
      ),
      'translatable' => '0',
      'type' => 'geofield',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '12',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_location',
      'label' => 'Location',
      'required' => 0,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'local_solr' => array(
          'enabled' => FALSE,
          'lat_field' => 'lat',
          'lng_field' => 'lng',
        ),
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'reverse_geocode_widget',
        'settings' => array(
          'field_address' => 'field_address',
          'map' => array(
            'center' => array(
              'lat' => '0',
              'lng' => '0',
            ),
            'height' => '400',
            'html5' => 0,
            'width' => '750',
            'zoom' => '9',
          ),
        ),
        'type' => 'reverse_geocode_widget_widget',
        'weight' => '4',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_phone'.
  $fields['node-accommodation-field_phone'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_phone',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'cck_phone',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'profile2_private' => 0,
        'size' => '15',
      ),
      'translatable' => '0',
      'type' => 'phone_number',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'cck_phone',
          'settings' => array(),
          'type' => 'global_phone_number',
          'weight' => '6',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_phone',
      'label' => 'Phone',
      'required' => 0,
      'settings' => array(
        'all_country_codes' => 1,
        'country_code_position' => 'before',
        'country_codes' => array(
          'country_selection' => array(
            'ad' => 0,
            'ae' => 0,
            'af' => 0,
            'ag' => 0,
            'ai' => 0,
            'al' => 0,
            'am' => 0,
            'an' => 0,
            'ao' => 0,
            'ar' => 0,
            'as' => 0,
            'at' => 0,
            'au' => 0,
            'aw' => 0,
            'az' => 0,
            'ba' => 0,
            'bb' => 0,
            'bd' => 0,
            'be' => 0,
            'bf' => 0,
            'bg' => 0,
            'bh' => 0,
            'bi' => 0,
            'bj' => 0,
            'bm' => 0,
            'bn' => 0,
            'bo' => 0,
            'br' => 0,
            'bs' => 0,
            'bt' => 0,
            'bw' => 0,
            'by' => 0,
            'bz' => 0,
            'ca' => 0,
            'cc' => 0,
            'cd' => 0,
            'cf' => 0,
            'cg' => 0,
            'ch' => 0,
            'ci' => 0,
            'ck' => 0,
            'cl' => 0,
            'cm' => 0,
            'cn' => 0,
            'co' => 0,
            'cr' => 0,
            'cu' => 0,
            'cv' => 0,
            'cx' => 0,
            'cy' => 0,
            'cz' => 0,
            'de' => 0,
            'dj' => 0,
            'dk' => 0,
            'dm' => 0,
            'do' => 0,
            'dz' => 0,
            'ec' => 0,
            'ee' => 0,
            'eg' => 0,
            'er' => 0,
            'es' => 0,
            'et' => 0,
            'fi' => 0,
            'fj' => 0,
            'fk' => 0,
            'fm' => 0,
            'fo' => 0,
            'fr' => 0,
            'ga' => 0,
            'gb' => 0,
            'gd' => 0,
            'ge' => 0,
            'gf' => 0,
            'gh' => 0,
            'gi' => 0,
            'gl' => 0,
            'gm' => 0,
            'gn' => 0,
            'gp' => 0,
            'gq' => 0,
            'gr' => 0,
            'gt' => 0,
            'gu' => 0,
            'gw' => 0,
            'gy' => 0,
            'hk' => 0,
            'hn' => 0,
            'hr' => 0,
            'ht' => 0,
            'hu' => 0,
            'id' => 0,
            'ie' => 0,
            'il' => 0,
            'in' => 0,
            'io' => 0,
            'iq' => 0,
            'ir' => 0,
            'is' => 0,
            'it' => 0,
            'jm' => 0,
            'jo' => 0,
            'jp' => 0,
            'ke' => 0,
            'kg' => 0,
            'kh' => 0,
            'ki' => 0,
            'km' => 0,
            'kn' => 0,
            'kp' => 0,
            'kr' => 0,
            'kw' => 0,
            'ky' => 0,
            'kz' => 0,
            'la' => 0,
            'lb' => 0,
            'lc' => 0,
            'li' => 0,
            'lk' => 0,
            'lr' => 0,
            'ls' => 0,
            'lt' => 0,
            'lu' => 0,
            'lv' => 0,
            'ly' => 0,
            'ma' => 0,
            'mc' => 0,
            'md' => 0,
            'me' => 0,
            'mg' => 0,
            'mh' => 0,
            'mk' => 0,
            'ml' => 0,
            'mm' => 0,
            'mn' => 0,
            'mo' => 0,
            'mp' => 0,
            'mq' => 0,
            'mr' => 0,
            'ms' => 0,
            'mt' => 0,
            'mu' => 0,
            'mv' => 0,
            'mw' => 0,
            'mx' => 0,
            'my' => 0,
            'mz' => 0,
            'na' => 0,
            'nc' => 0,
            'ne' => 0,
            'nf' => 0,
            'ng' => 0,
            'ni' => 0,
            'nl' => 0,
            'no' => 0,
            'np' => 0,
            'nr' => 0,
            'nu' => 0,
            'nz' => 0,
            'om' => 0,
            'pa' => 0,
            'pe' => 0,
            'pf' => 0,
            'pg' => 0,
            'ph' => 0,
            'pk' => 0,
            'pl' => 0,
            'pm' => 0,
            'pr' => 0,
            'ps' => 0,
            'pt' => 0,
            'pw' => 0,
            'py' => 0,
            'qa' => 0,
            'ro' => 0,
            'rs' => 0,
            'ru' => 0,
            'rw' => 0,
            'sa' => 0,
            'sb' => 0,
            'sc' => 0,
            'sd' => 0,
            'se' => 0,
            'sg' => 0,
            'sh' => 0,
            'si' => 0,
            'sk' => 0,
            'sl' => 0,
            'sm' => 0,
            'sn' => 0,
            'so' => 0,
            'sr' => 0,
            'ss' => 0,
            'st' => 0,
            'sv' => 0,
            'sy' => 0,
            'sz' => 0,
            'tc' => 0,
            'td' => 0,
            'tg' => 0,
            'th' => 0,
            'tj' => 0,
            'tk' => 0,
            'tm' => 0,
            'tn' => 0,
            'to' => 0,
            'tp' => 0,
            'tr' => 0,
            'tt' => 0,
            'tv' => 0,
            'tw' => 0,
            'tz' => 0,
            'ua' => 0,
            'ug' => 0,
            'us' => 0,
            'uy' => 0,
            'uz' => 0,
            'va' => 0,
            'vc' => 0,
            've' => 0,
            'vg' => 0,
            'vi' => 0,
            'vn' => 0,
            'vu' => 0,
            'wf' => 0,
            'ws' => 0,
            'ye' => 0,
            'yt' => 0,
            'za' => 0,
            'zm' => 0,
            'zw' => 0,
          ),
          'hide_single_cc' => 0,
        ),
        'default_country' => 'us',
        'enable_country_level_validation' => 1,
        'enable_default_country' => 1,
        'enable_extension' => 0,
        'entity_translation_sync' => FALSE,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'cck_phone',
        'settings' => array(
          'size' => 15,
        ),
        'type' => 'phone_number',
        'weight' => '8',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_photo'.
  $fields['node-accommodation-field_photo'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '10',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_photo',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(
        'fid' => array(
          'columns' => array(
            'fid' => 'fid',
          ),
          'table' => 'file_managed',
        ),
      ),
      'indexes' => array(
        'fid' => array(
          0 => 'fid',
        ),
      ),
      'locked' => '0',
      'module' => 'image',
      'settings' => array(
        'default_image' => 0,
        'entity_translation_sync' => array(
          0 => 'fid',
        ),
        'profile2_private' => FALSE,
        'uri_scheme' => 'public',
      ),
      'translatable' => '0',
      'type' => 'image',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'image',
          'settings' => array(
            'image_link' => '',
            'image_style' => 'thumbnail',
          ),
          'type' => 'image',
          'weight' => '3',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_photo',
      'label' => 'Photo',
      'required' => 0,
      'settings' => array(
        'alt_field' => 0,
        'default_image' => 0,
        'entity_translation_sync' => FALSE,
        'file_directory' => '',
        'file_extensions' => 'png gif jpg jpeg',
        'filefield_paths' => array(
          'active_updating' => 1,
          'file_name' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => '',
          ),
          'file_path' => array(
            'options' => array(
              'pathauto' => 1,
              'transliterate' => 1,
            ),
            'value' => 'hotels/[node:nid]-[node:title]',
          ),
          'retroactive_update' => 0,
        ),
        'max_filesize' => '5M',
        'max_resolution' => '2000x2000',
        'min_resolution' => '300x300',
        'title_field' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'media',
        'settings' => array(
          'allowed_schemes' => array(
            'public' => 'public',
          ),
          'allowed_types' => array(
            'audio' => 0,
            0 => 0,
            'default' => 0,
            'image' => 'image',
            'video' => 0,
          ),
          'progress_indicator' => 'throbber',
        ),
        'type' => 'media_generic',
        'weight' => '9',
      ),
    ),
  );

  // Exported field: 'node-accommodation-field_url'.
  $fields['node-accommodation-field_url'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_url',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(),
      'locked' => '0',
      'module' => 'link',
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'rel' => '',
          'target' => 'default',
        ),
        'display' => array(
          'url_cutoff' => 80,
        ),
        'enable_tokens' => 1,
        'entity_translation_sync' => FALSE,
        'profile2_private' => FALSE,
        'title' => 'optional',
        'title_maxlength' => 128,
        'title_value' => '',
        'url' => 0,
      ),
      'translatable' => '0',
      'type' => 'link_field',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'link',
          'settings' => array(),
          'type' => 'link_default',
          'weight' => '5',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_url',
      'label' => 'Web site',
      'required' => 0,
      'settings' => array(
        'attributes' => array(
          'class' => '',
          'configurable_title' => 0,
          'rel' => '',
          'target' => '_blank',
          'title' => '[node:title]',
        ),
        'display' => array(
          'url_cutoff' => '80',
        ),
        'enable_tokens' => 0,
        'entity_translation_sync' => FALSE,
        'title' => 'optional',
        'title_maxlength' => '128',
        'title_value' => '[node:title]',
        'url' => 0,
        'user_register_form' => FALSE,
        'validate_url' => 1,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'html5_tools',
        'settings' => array(),
        'type' => 'urlwidget',
        'weight' => '7',
      ),
    ),
  );

  // Exported field: 'node-accommodation-title_field'.
  $fields['node-accommodation-title_field'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'title_field',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(
        'format' => array(
          'columns' => array(
            'format' => 'format',
          ),
          'table' => 'filter_format',
        ),
      ),
      'indexes' => array(
        'format' => array(
          0 => 'format',
        ),
      ),
      'locked' => '0',
      'module' => 'text',
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'max_length' => 255,
        'profile2_private' => FALSE,
      ),
      'translatable' => '0',
      'type' => 'text',
    ),
    'field_instance' => array(
      'bundle' => 'accommodation',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => 'A field replacing node title.',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => '13',
        ),
        'event_blog_teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'title_field',
      'label' => 'Title',
      'required' => TRUE,
      'settings' => array(
        'entity_translation_sync' => FALSE,
        'text_processing' => 0,
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'module' => 'text',
        'settings' => array(
          'size' => 60,
        ),
        'type' => 'text_textfield',
        'weight' => '0',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('A field replacing node title.');
  t('Address');
  t('Double');
  t('Email');
  t('Location');
  t('Phone');
  t('Photo');
  t('Services and prices');
  t('Single');
  t('Title');
  t('Web site');
  t('Wi-Fi');

  return $fields;
}
