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
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_rdf_default_mappings().
 */
function pg_contest_rdf_default_mappings() {
  $schemaorg = array();

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
  );

  return $schemaorg;
}
