<?php
/**
 * @file
 * panels_default_template.panels_default.inc
 */

/**
 * Implements hook_default_panels_mini().
 */
function panels_default_template_default_panels_mini() {
  $export = array();

  $mini = new stdClass();
  $mini->disabled = FALSE; /* Edit this to true to make a default mini disabled initially */
  $mini->api_version = 1;
  $mini->name = 'footer_four_blocks';
  $mini->category = 'Blocks';
  $mini->admin_title = 'Footer four blocks';
  $mini->admin_description = '';
  $mini->requiredcontexts = array();
  $mini->contexts = array();
  $mini->relationships = array();
  $display = new panels_display();
  $display->layout = 'four_4x25';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'five_first' => NULL,
      'five_second' => NULL,
      'five_third' => NULL,
      'five_fourth' => NULL,
      'five_fifth' => NULL,
      'four_first' => NULL,
      'four_second' => NULL,
      'four_third' => NULL,
      'four_fourth' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'four_first';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Contacts',
      'title' => '',
      'body' => '<div class="logo"><img src="/sites/all/themes/airtribune2/images/logo_footer.png" alt="" /></div>
<p>22/5 L’va Tolstogo Street,<br />
Moscow, 119021, Russia</p>
<p> </p>
<p>Ph.: +7 (985) 762-72-38<br />
Fax: +7 (499) 246-25-93<br />
e-mail: info@airtribune.com</p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'block-contacts',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['four_first'][0] = 'new-1';
    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'four_fourth';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Follow us',
      'title' => 'Follow us',
      'body' => '<div id="social">
   <ul>
    <li><a href="" class="tw"><span>Twitter</span></a></li>
    <li><a href="" class="vk"><span>VKontakte</span></a></li>
    <li><a href="" class="lj"><span>Livejournal</span></a></li>
    <li><a href="" class="fb"><span>Facebook</span></a></li>
    <li><a href="" class="yt"><span>Youtube</span></a></li>
   </ul>
  </div>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'follow-us',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-2'] = $pane;
    $display->panels['four_fourth'][0] = 'new-2';
    $pane = new stdClass();
    $pane->pid = 'new-3';
    $pane->panel = 'four_second';
    $pane->type = 'block';
    $pane->subtype = 'system-main-menu';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 1,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'footer-menu',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-3'] = $pane;
    $display->panels['four_second'][0] = 'new-3';
    $pane = new stdClass();
    $pane->pid = 'new-4';
    $pane->panel = 'four_third';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'Solutions',
      'title' => 'Solutions',
      'body' => '<p>The project is aimed at uniting paragliding community, viewers and sponsors.<br />
We started with service for paragliding competitions and we are moving into services for free-flying pilots worldwide.<br />
Basic idea is - all pilots may use personal livetrackers for safety reasons and for </p>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array(
      'css_id' => 'solutions',
      'css_class' => '',
    );
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-4'] = $pane;
    $display->panels['four_third'][0] = 'new-4';
  $display->hide_title = PANELS_TITLE_NONE;
  $display->title_pane = 'new-1';
  $mini->display = $display;
  $export['footer_four_blocks'] = $mini;

  return $export;
}
