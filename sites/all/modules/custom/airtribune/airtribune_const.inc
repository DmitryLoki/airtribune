<?php

/**
 * @file
 * Airtribune constants.
 */

define('AIRTRIBUNE_VIS_URL', 'http://vis.airtribune.com');
define('AIRTRIBUNE_RETRIEVE_URL', 'http://retrieve.airtribune.com');

// Profiles
define('AIRTRIBUNE_USER_MAIN_PROFILE', 'main');
define('AIRTRIBUNE_USER_PILOT_PROFILE', 'pilot');

// Content types
define('AIRTRIBUNE_PG_CONTEST_TYPE', 'pg_contest');
define('AIRTRIBUNE_HG_CONTEST_TYPE', 'hg_contest');
define('AIRTRIBUNE_PG_RACE_TYPE', 'pg_race');
define('AIRTRIBUNE_NEWSBLOG_TYPE', 'newsblog');
define('AIRTRIBUNE_ACCOMMODATION_TYPE', 'accommodation');
define('AIRTRIBUNE_ACTIVITY_TYPE', 'activity');
define('AIRTRIBUNE_DAY_TYPE', 'day');
define('AIRTRIBUNE_PG_FLYINGSITE_TYPE', 'pg_flyingsite');
define('AIRTRIBUNE_PG_NATION_TEAM_TYPE', 'pg_nation_team');

// Entity types
define('AIRTRIBUNE_RACE_ENTITY_TYPE', 'ent_race');
define('AIRTRIBUNE_RACETYPE_ENTITY_TYPE', 'ent_racetype');
define('AIRTRIBUNE_POINT_ENTITY_TYPE', 'ent_point');
define('AIRTRIBUNE_CONTEST_POINT_ENTITY_TYPE', 'ent_contest_point');
define('AIRTRIBUNE_CUSTOMOBJECT_TYPE', 'ent_customobject');
define('AIRTRIBUNE_TRACKER_TYPE', 'ent_tracker');
define('AIRTRIBUNE_TEAM_TYPE', 'ent_team');

// Memberships
define('AIRTRIBUNE_MEMBERSHIP_CONTESTANT', 'pg_contestant');
define('AT_MEMBERSHIP_HG_CONTESTANT', 'hg_contestant');
define('AIRTRIBUNE_MEMBERSHIP_WINDDUMMY', 'pg_winddummy');
define('AIRTRIBUNE_MEMBERSHIP_ORGANIZER', 'pg_organizer');
define('AIRTRIBUNE_MEMBERSHIP_TRACKEDOBJECT', 'tracked_object');

// Visualisation types
define('AIRTRIBUNE_VIS_STATE_ONLINE', 'online');
define('AIRTRIBUNE_VIS_STATE_REPLAY', 'replay');
define('AIRTRIBUNE_VIS_STATE_AWAITING', 'awaiting');

// See field_pg_contestant_status allowed values list
define('AIRTRIBUNE_PG_CONTESTANT_WAITING_LIST', 10);
define('AIRTRIBUNE_PILOT_STATUS_WAITING_FOR_PAYMENT', 20);
define('AIRTRIBUNE_PILOT_STATUS_PAYMENT_IN_PROGRESS', 30);
define('AIRTRIBUNE_PILOT_STATUS_WINDDUMMY', 40);
define('AIRTRIBUNE_PG_CONTESTANT_CONFIRMED', 50);

define('AIRTRIBUNE_FAI_CATEGORY_NONE', 0);
define('AIRTRIBUNE_FAI_CATEGORY_1', 1);
define('AIRTRIBUNE_FAI_CATEGORY_2', 2);

// Fields
define('AIRTRIBUNE_USER_FULLNAME_FIELD', 'field_full_name');
define('AIRTRIBUNE_GETTING_THERE_FIELD', 'field_collection_getting_there');
define('AIRTRIBUNE_COUNTRY_FIELD', 'field_country');
define('AIRTRIBUNE_CITY_FIELD', 'field_city');
define('AIRTRIBUNE_DATES_FIELD', 'field_dates');
define('AIRTRIBUNE_TIMEZONE_FIELD', 'field_time_zone');
define('AIRTRIBUNE_PG_CONTESTANT_STATUS_FIELD', 'field_pg_contestant_status');
define('AIRTRIBUNE_CONTEST_PHOTOS_FIELD', 'field_contest_photos');
define('AIRTRIBUNE_FLYING_SITE_PHOTOS_FIELD', 'field_flying_site_photos');
define('AIRTRIBUNE_AWARDS_PHOTOS_FIELD', 'field_awards_photos');
define('AIRTRIBUNE_FAI_CATEGORY_FIELD', 'field_fai_category');
define('AIRTRIBUNE_HQ_LOCATION_FIELD', 'field_hq_location');
define('AIRTRIBUNE_LOCATION_FIELD', 'field_location');
define('AIRTRIBUNE_POINTS_FILE_FIELD', 'field_points_file');
define('AIRTRIBUNE_REGISTRATION_SW_FIELD', 'field_registration_sw');
define('AIRTRIBUNE_DAY_RESULTS_FIELD', 'field_day_results');
define('AIRTRIBUNE_DAY_REF_FIELD', 'field_day_ref');
define('AIRTRIBUNE_COMPETITION_RESULTS_FIELD', 'field_competition_results');
define('AIRTRIBUNE_RACE_START_END_FIELD', 'field_race_start_end');
define('AIRTRIBUNE_RACE_NUMBER', 'field_race_number');
define('AIRTRIBUNE_DAY_NUMBER', 'field_day_number');
define('AIRTRIBUNE_PG_RACE_WINDOW_OPEN_CLOSE_FIELD', 'field_pg_race_window_open_close');
define('AIRTRIBUNE_DOWNLOADS_FIELD', 'field_downloads');
define('AIRTRIBUNE_PG_RACETYPE_REF_FIELD', 'field_pg_racetype_ref');
define('AIRTRIBUNE_IMAGE_FIELD', 'field_image');
define('AIRTRIBUNE_BIRTHDATE_FIELD', 'field_birthdate');
define('AIRTRIBUNE_CONTESTANT_NUMBER_FIELD', 'field_contestant_number');
define('AIRTRIBUNE_PG_SCORING_CATEGORY_FIELD', 'field_pg_scoring_category');
define('AIRTRIBUNE_SCORING_CATEGORY_REF_FIELD', 'field_scoring_category_ref');
define('AIRTRIBUNE_ADDRESS_FIELD', 'field_address');
define('AIRTRIBUNE_PG_RACE_TRACKS_FIELD', 'field_pg_race_tracks');

define('AIRTRIBUNE_PG_RACE_POINTS_FIELD', 'field_pg_race_points');
define('AIRTRIBUNE_PG_RACE_AZIMUTH_FIELD', 'field_pg_race_azimuth');
define('AIRTRIBUNE_POINT_RADIUS_FIELD', 'field_point_radius');
define('AIRTRIBUNE_POINT_TYPE_FIELD', 'field_point_type');
define('AIRTRIBUNE_POINT_SS_ES_FIELD', 'field_point_ss_es');
define('AIRTRIBUNE_POINT_REF_FIELD', 'field_point_ref');
define('AIRTRIBUNE_POINT_LOCATION_FIELD', 'field_point_location');

define('AIRTRIBUNE_MEDIA_DESCRIPTION_FIELD', 'field_media_description');
define('AIRTRIBUNE_FILE_IMAGE_ALT_TEXT_FIELD', 'field_file_image_alt_text');
define('AIRTRIBUNE_FILE_IMAGE_TITLE_TEXT_FIELD', 'field_file_image_title_text');
define('AIRTRIBUNE_COUNTRY_ISO2_FIELD', 'field_country_iso2');
define('AIRTRIBUNE_TEAM_MEMBER_FIELD', 'field_team_member');
define('AIRTRIBUNE_USERS_REF_FIELD', 'field_users_ref');

define('AIRTRIBUNE_SINGLE_DOWNLOAD_FIELD', 'field_single_download');

// Bundles for basicmark
define('AIRTRIBUNE_BASICMARK_BUNDLE_PG_LANDING', 'pg_landing');
define('AIRTRIBUNE_BASICMARK_BUNDLE_PG_TAKEOFF', 'pg_takeoff');

// Templates
define('DEFAULT_USER_PICTURE_PATH', 'pictures/default_user_picture.png');
define('SOLUTIONS_REGEXT_PATTERN', '/[^\/]{2,}[^\/]/');
define('AIRTRIBUNE_LANGUAGES_ICONSET', 'shiny');

// Views
define('AIRTRIBUNE_PARAGLIDING_PILOTS_LIST', 'paragliding_pilots_list');
define('AIRTRIBUNE_DAY_BLOG_VIEW', 'day_blog');
define('VIEWS_EVENTS_LIST', 'events_list');
define('VIEWS_EVENTS_LIST_NEXT', 'page_events_next');
define('VIEWS_EVENTS_LIST_CURRENT', 'page_events_current');
define('VIEWS_EVENTS_LIST_PAST', 'page_events_past');

// Other
define('AT_VIEWS_TABS_CACHE_CID', 'at_views_tabs');

define('PG_RACE_NO_TRACKS_TEXT',"We haven't got any data from pilots' live trackers yet. Please, try again later."); //

defuine('AT_SESSION_VAR_KEY', 'airtribune');
