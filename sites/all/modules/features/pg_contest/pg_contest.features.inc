<?php
/**
 * @file
 * pg_contest.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function pg_contest_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_validation" && $api == "default_field_validation_rules") {
    return array("version" => "2");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_rdf_default_mappings().
 */
function pg_contest_rdf_default_mappings() {
  $schemaorg = array();

  // Exported RDF mapping: field_collection_organizers
  $schemaorg['field_collection_item']['field_collection_organizers'] = array(
    'field_organizer_logo' => array(
      'predicates' => array(),
      'type' => 'rel',
    ),
    'field_url' => array(
      'predicates' => array(),
    ),
    'field_organizer' => array(
      'predicates' => array(),
    ),
    'field_position' => array(
      'predicates' => array(),
    ),
    'field_contacts_phone' => array(
      'predicates' => array(),
    ),
  );

  // Exported RDF mapping: pg_contest
  $schemaorg['node']['pg_contest'] = array(
    'rdftype' => array(
      0 => 'schema:SportsEvent',
      1 => 'sioc:Item',
      2 => 'foaf:Document',
    ),
    'title' => array(
      'predicates' => array(
        0 => 'schema:name',
      ),
    ),
    'created' => array(
      'predicates' => array(
        0 => 'dc:date',
        1 => 'dc:created',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'changed' => array(
      'predicates' => array(
        0 => 'dc:modified',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'body' => array(
      'predicates' => array(
        0 => 'content:encoded',
      ),
    ),
    'uid' => array(
      'predicates' => array(
        0 => 'sioc:has_creator',
      ),
      'type' => 'rel',
    ),
    'name' => array(
      'predicates' => array(
        0 => 'schema:name',
      ),
    ),
    'comment_count' => array(
      'predicates' => array(
        0 => 'sioc:num_replies',
      ),
      'datatype' => 'xsd:integer',
    ),
    'last_activity' => array(
      'predicates' => array(
        0 => 'sioc:last_activity_date',
      ),
      'datatype' => 'xsd:dateTime',
      'callback' => 'date_iso8601',
    ),
    'field_dates' => array(
      'predicates' => array(
        0 => 'schema:startDate',
      ),
    ),
    'url' => array(
      'predicates' => array(
        0 => 'schema:url',
      ),
      'type' => 'rel',
    ),
    'field_country' => array(
      'predicates' => array(
        0 => 'schema:addressCountry',
      ),
    ),
    'field_city' => array(
      'predicates' => array(
        0 => 'schema:addressLocality',
      ),
    ),
    'field_organizer' => array(
      'predicates' => array(
        0 => 'schema:performers',
      ),
    ),
    'field_info' => array(
      'predicates' => array(
        0 => 'schema:summary',
        1 => 'schema:description',
      ),
    ),
    'field_headquarter_info' => array(
      'predicates' => array(
        0 => 'schema:performers',
      ),
    ),
    'field_collection_organizers' => array(
      'predicates' => array(),
    ),
    'title_field' => array(
      'predicates' => array(),
    ),
    'field_contest_rules' => array(
      'predicates' => array(),
      'type' => 'rel',
    ),
    'field_registration_sw' => array(
      'predicates' => array(),
    ),
    'field_open_class' => array(
      'predicates' => array(),
    ),
    'field_fai_category' => array(
      'predicates' => array(),
    ),
    'field_schedule' => array(
      'predicates' => array(),
    ),
    'field_sample_schedule' => array(
      'predicates' => array(),
    ),
    'field_collection_getting_there' => array(
      'predicates' => array(),
    ),
    'field_awards_photos' => array(
      'predicates' => array(),
      'type' => 'rel',
    ),
    'field_selection' => array(
      'predicates' => array(),
    ),
    'field_prizes' => array(
      'predicates' => array(),
    ),
    'field_header' => array(
      'predicates' => array(),
      'type' => 'rel',
    ),
    'field_header_image' => array(
      'predicates' => array(),
      'type' => 'rel',
    ),
    'og_roles_permissions' => array(
      'predicates' => array(),
    ),
    'field_social_link' => array(
      'predicates' => array(),
    ),
    'field_social_links' => array(
      'predicates' => array(),
    ),
    'field_contacts_email' => array(
      'predicates' => array(),
    ),
    'field_contacts_phone' => array(
      'predicates' => array(),
    ),
    'field_address' => array(
      'predicates' => array(),
    ),
    'field_hq_location' => array(
      'predicates' => array(),
    ),
    'field_downloads' => array(
      'predicates' => array(),
      'type' => 'rel',
    ),
    'field_full_name' => array(
      'predicates' => array(),
    ),
    'field_position' => array(
      'predicates' => array(),
    ),
  );

  return $schemaorg;
}
