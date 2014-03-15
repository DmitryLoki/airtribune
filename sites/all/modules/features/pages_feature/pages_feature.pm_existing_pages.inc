<?php
/**
 * @file
 * pages_feature.pm_existing_pages.inc
 */

/**
 * Implements hook_pm_existing_pages_info().
 */
function pages_feature_pm_existing_pages_info() {
  $export = array();

  $pm_existing_page = new stdClass();
  $pm_existing_page->api_version = 1;
  $pm_existing_page->name = 'contestant_edit_template';
  $pm_existing_page->label = 'Contestant edit template';
  $pm_existing_page->context = '';
  $pm_existing_page->paths = 'profile-pilot/%profile2_by_uid/edit';
  $export['contestant_edit_template'] = $pm_existing_page;

  return $export;
}
