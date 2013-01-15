<?php
/**
 * @file
 * feeds_importers.feeds_importer_default.inc
 */

/**
 * Implements hook_feeds_importer_default().
 */
function feeds_importers_feeds_importer_default() {
  $export = array();

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_accom';
  $feeds_importer->config = array(
    'name' => 'import_accom',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsEntityProcessorNode',
      'config' => array(
        'values' => array(
          'type' => 'accommodation',
          'language' => 'und',
          'status' => '1',
          'promote' => 0,
          'sticky' => 0,
          'author' => '1',
          'log' => '',
          'revision' => 0,
        ),
        'mappings' => array(
          0 => array(
            'source' => 'Nid',
            'target' => 'nid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'Title',
            'target' => 'title_field',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Email',
            'target' => 'field_email',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Web site',
            'target' => 'field_url:url',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'WiFi',
            'target' => 'field_hotel_wifi',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'index',
            'target' => 'field_hotel_address:postal_code',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'country_machine',
            'target' => 'field_hotel_address:country',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'City',
            'target' => 'field_hotel_address:locality',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'Address',
            'target' => 'field_hotel_address:thoroughfare',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'Сurrency_machine',
            'target' => 'field_price_currency',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'Single',
            'target' => 'field_price_single',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'Double',
            'target' => 'field_price_double',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'Services',
            'target' => 'body',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'Images',
            'target' => 'field_photo',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'Coordinates',
            'target' => 'field_location:combined',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_accom'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_events';
  $feeds_importer->config = array(
    'name' => 'import_events',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsEntityProcessorNode',
      'config' => array(
        'values' => array(
          'type' => 'pg_contest',
          'language' => 'und',
          'status' => '1',
          'promote' => 0,
          'sticky' => 0,
          'author' => '1',
          'log' => '',
          'revision' => 0,
        ),
        'mappings' => array(
          0 => array(
            'source' => 'nid',
            'target' => 'nid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'name',
            'target' => 'author',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Category',
            'target' => 'field_fai_category',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Event info',
            'target' => 'field_info',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Selection and entry fee',
            'target' => 'field_selection',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Flying site info',
            'target' => 'field_flying_info',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Prize fund and categories awards',
            'target' => 'field_prizes',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'General schedule',
            'target' => 'field_schedule',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'Daily schedule',
            'target' => 'field_sample_schedule',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'Registration',
            'target' => 'field_registration_sw',
            'unique' => FALSE,
          ),
          11 => array(
            'source' => 'Headquarter information',
            'target' => 'field_headquarter_info',
            'unique' => FALSE,
          ),
          12 => array(
            'source' => 'date_from',
            'target' => 'field_dates:start',
            'unique' => FALSE,
          ),
          13 => array(
            'source' => 'date_to',
            'target' => 'field_dates:end',
            'unique' => FALSE,
          ),
          14 => array(
            'source' => 'Downloads',
            'target' => 'field_downloads',
            'unique' => FALSE,
          ),
          15 => array(
            'source' => 'Waypoints file',
            'target' => 'field_points_file',
            'unique' => FALSE,
          ),
          16 => array(
            'source' => 'field_logo',
            'target' => 'field_contest_photos',
            'unique' => FALSE,
          ),
          17 => array(
            'source' => 'Add photo block',
            'target' => 'field_contest_photos',
            'unique' => FALSE,
          ),
          18 => array(
            'source' => 'City',
            'target' => 'field_city',
            'unique' => FALSE,
          ),
          19 => array(
            'source' => 'Country',
            'target' => 'node:pg_contest:field_country:name',
            'unique' => FALSE,
          ),
          20 => array(
            'source' => 'Country',
            'target' => 'node:pg_contest:field_country:official_name',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '1',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_events'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_newsblog';
  $feeds_importer->config = array(
    'name' => 'import_newsblog',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsEntityProcessorNode',
      'config' => array(
        'values' => array(
          'type' => 'newsblog',
          'language' => 'en',
          'status' => '1',
          'promote' => 0,
          'sticky' => 0,
          'author' => '1',
          'log' => '',
          'revision' => 0,
        ),
        'mappings' => array(
          0 => array(
            'source' => 'Nid',
            'target' => 'nid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'Title',
            'target' => 'title_field',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'Body',
            'target' => 'body',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'eventnews_photos',
            'target' => 'field_image',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'Post date',
            'target' => 'created',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Event',
            'target' => 'og_group_ref',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'filtered_html',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_newsblog'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_tasks';
  $feeds_importer->config = array(
    'name' => 'import_tasks',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsEntityProcessorNode',
      'config' => array(
        'values' => array(
          'type' => 'pg_race',
          'language' => 'en',
          'status' => '1',
          'promote' => 0,
          'sticky' => 0,
          'author' => '1',
          'log' => '',
          'revision' => 0,
        ),
        'mappings' => array(
          0 => array(
            'source' => 'nid',
            'target' => 'nid',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'created',
            'target' => 'created',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'field_task_status',
            'target' => 'field_pg_race_status',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'field_task_photos',
            'target' => 'field_photos',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'TD',
            'target' => 'field_day_results',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'TC',
            'target' => 'field_competition_results',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Task date',
            'target' => 'field_pg_race_date:start',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Task date',
            'target' => 'field_pg_race_date:end',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'body',
            'target' => 'field_day_blog',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'title',
            'target' => 'title_field',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'title',
            'target' => 'title',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => '2',
        'input_format' => 'plain_text',
        'skip_hash_check' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_tasks'] = $feeds_importer;

  $feeds_importer = new stdClass();
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'import_trackers';
  $feeds_importer->config = array(
    'name' => 'import_trackers',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'allowed_extensions' => 'txt csv tsv xml opml',
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => '|',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'FeedsEntityProcessorEnt_tracker',
      'config' => array(
        'values' => array(),
        'mappings' => array(
          0 => array(
            'source' => 'Title',
            'target' => 'title',
            'unique' => FALSE,
          ),
          1 => array(
            'source' => 'IMEI',
            'target' => 'identifier',
            'unique' => FALSE,
          ),
        ),
        'update_existing' => 0,
        'input_format' => NULL,
        'skip_hash_check' => FALSE,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
    'process_in_background' => 0,
  );
  $export['import_trackers'] = $feeds_importer;

  return $export;
}
