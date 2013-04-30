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
    'body' => '<script data-main="http://vis.airtribune.com/js/initSimple" src="http://vis.airtribune.com/js/require.js"></script>
<!-- ko widget: { data: page, contestId: "", raceId: "", width: "940px", height: "380px" } --><!-- /ko -->',
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

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'share_links';
  $content->admin_title = 'Share links';
  $content->admin_description = '';
  $content->category = 'Airtribune';
  $content->settings = array(
    'admin_title' => 'Share links',
    'title' => '',
    'body' => '<script type="text/javascript">var __st_loadLate=true;</script><script type="text/javascript">var switchTo5x=false;</script><script type="text/javascript" src="http://w.sharethis.com/button/buttons.js"></script><script type="text/javascript">stLight.options({publisher: "77e50a8c-2e6c-4d8c-883f-2ab1460a9f2c", nativeCount: true});</script><span class=\'st_facebook_vcount\' displayText=\'Facebook\'></span><span class=\'st_twitter_vcount\' displayText=\'Tweet\'></span><span class=\'st_googleplus_vcount\' displayText=\'Google +\'></span></span></span><span class=\'st_sharethis_vcount\' displayText=\'Share\'></span>',
    'format' => 'full_html',
    'substitute' => 1,
  );
  $export['share_links'] = $content;

  $content = new stdClass();
  $content->disabled = FALSE; /* Edit this to true to make a default content disabled initially */
  $content->api_version = 1;
  $content->name = 'small_share_links';
  $content->admin_title = 'Small share links';
  $content->admin_description = '';
  $content->category = 'Airtribune';
  $content->settings = array(
    'admin_title' => 'Small share links',
    'title' => '',
    'body' => '<script type="text/javascript">var __st_loadLate=true;</script><script type="text/javascript">var switchTo5x=false;</script><script type="text/javascript" src="http://w.sharethis.com/button/buttons.js"></script><script type="text/javascript">stLight.options({publisher: "77e50a8c-2e6c-4d8c-883f-2ab1460a9f2c", nativeCount: true});</script><span class=\'st_facebook_hcount\' displayText=\'Facebook\'></span><span class=\'st_twitter_hcount\' displayText=\'Tweet\'></span><span class=\'st_googleplus_hcount\' displayText=\'+1\'></span></span><span class=\'st_sharethis_hcount\' displayText=\'Share\'></span>',
    'format' => 'full_html',
    'substitute' => 0,
  );
  $export['small_share_links'] = $content;

  return $export;
}
