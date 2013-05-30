<?php
/**
 * @file
 * pages_feature.ctools_content.inc
 */

/**
 * Implements hook_default_ctools_custom_content().
 */
function pages_feature_default_ctools_custom_content() {
  $export = array();

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'airtribune_race_preview';
  $content->admin_title = 'Airtribune race preview';
  $content->admin_description = 'Airtribune race preview';
  $content->category = 'Airtribune';
  $content->settings = array(
    'admin_title' => '',
    'title' => 'Race preview',
    'body' => '<script src="/sites/all/modules/custom/airtribune/js/day-blog-airvis-controller.js"></script>
      <script data-main="http://vis.airtribune.com/js/initSimple" src="http://vis.airtribune.com/js/require.js"></script>
<!-- ko widget: { data: page, contestId: "", raceId: "", width: "940px", height: "380px", callback: window.airvisPageLoadedCallback } --><!-- /ko -->',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $export['airtribune_race_preview'] = $content;

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'coming_soon';
  $content->admin_title = 'Coming soon';
  $content->admin_description = 'Coming soon';
  $content->category = '';
  $content->settings = array(
    'admin_title' => 'Coming soon',
    'title' => '',
    'body' => 'Coming soon',
    'format' => 'filtered_html',
    'substitute' => 1,
  );
  $export['coming_soon'] = $content;

  return $export;
}
