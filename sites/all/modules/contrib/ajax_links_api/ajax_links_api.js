/**
 * @file
 * Handles ajax functionalities for Ajax Links API module.
 */
(function ($) {
  var ajaxLoading = false;
  Drupal.behaviors.ajaxLinksApi = {
    attach: function () {
      var trigger = Drupal.settings.ajax_links_api.trigger,
        negativeTrigger = Drupal.settings.ajax_links_api.negative_triggers;

      // match the elements from the positive selector
      var $elements = $(trigger);

      // remove elements if the negative trigger is specified
      if (negativeTrigger) {
        $elements = $elements.not(negativeTrigger);
      }

      // add the click handler
      $elements.click(function(e) {
        e.preventDefault();
        var selector;
        if(!ajaxLoading) {
          ajaxLoading = true;
          var url = $(this).attr("href");
          var id = $(this).attr("rel");
          if(id) {
            selector = $(this).attr("rel");
          } else {
            selector = Drupal.settings.ajax_links_api.selector;
          }
          ajaxBefore(selector);
          ajaxLink(selector, url);          
        }
      });
    }
  };
  function  ajaxLink(selector, url) {
    $.ajax({
      url: url,
      type: "GET",
      data: "ajax=1",
      success: function (data) {        
        ajaxAfter(selector, url, data, window, document);
        Drupal.attachBehaviors(selector);
      },
      error: function (xhr) {
        var data = xhr.response.replace("?ajax=1", "");
        ajaxAfter(selector, url, data, window, document);
      }
    });
  }
  function ajaxBefore(selector){
    // Preserve the height of the current content to avoid the entire page
    // collapsing.
    $(selector).css('height', $(selector).height() + 'px');

    // Replace the content with a throbber.
    $(selector).html("<div class='ajax-links-api-loading'></div>");
  }
  function ajaxAfter(selector, url, data, window, document){
    // Update the ajaxLoading indicator.
    ajaxLoading = false;
    data=' <style>@import url("http://validoll.inprog.ru/modules/system/system.base.css?mu3e8f");@import url("http://validoll.inprog.ru/modules/system/system.menus.css?mu3e8f");@import url("http://validoll.inprog.ru/modules/system/system.messages.css?mu3e8f");@import url("http://validoll.inprog.ru/modules/system/system.theme.css?mu3e8f");</style><style>@import url("http://validoll.inprog.ru/sites/all/modules/contrib/ajax_links_api/ajax_links_api.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/date/date_popup/themes/datepicker.1.7.css?mu3e8f");@import url("http://validoll.inprog.ru/modules/field/theme/field.css?mu3e8f");@import url("http://validoll.inprog.ru/modules/node/node.css?mu3e8f");@import url("http://validoll.inprog.ru/modules/user/user.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/views/css/views.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/admin_menu/admin_menu.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/admin_menu/admin_menu.uid1.css?mu3e8f");</style><style>@import url("http://validoll.inprog.ru/sites/all/modules/contrib/colorbox/styles/default/colorbox_style.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/ctools/css/ctools.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/l10n_client/l10n_client.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/panels/css/panels.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/views_slideshow/views_slideshow.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/default/files/ctools/css/ad57ff1546b4e3e493a0d16eb09e3ad9_0.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/themes/airtribune2/plugins/layouts/panels/twocolfourrow/twocolfourrow.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/views_slideshow/contrib/views_slideshow_cycle/views_slideshow_cycle.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/themes/airtribune2/plugins/layouts/panels/fourcoltworow/fourcoltworow.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/countryicons_shiny/shiny-sprite.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/custom/airtribune/plugins/content_types/user_links/user_links.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/custom/airtribune/plugins/content_types/airtribune_primary_navigation/airtribune_primary_navigation.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/custom/airtribune/plugins/content_types/airtribune_event_sharelinks/airtribune_event_sharelinks.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/modules/contrib/path_breadcrumbs/css/path_breadcrumbs.css?mu3e8f");</style><style media="screen">@import url("http://validoll.inprog.ru/sites/all/themes/adaptivetheme/at_core/css/at.layout.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/themes/airtribune2/css/global.base.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/themes/airtribune2/css/global.styles.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/all/themes/airtribune2/css/_to_top.css?mu3e8f");@import url("http://validoll.inprog.ru/sites/default/files/adaptivetheme/airtribune2_files/airtribune2.default.layout.css?mu3e8f");</style><!-- -*-html-helper-*- -->        <div class="panel-panel line">          <div class="panel-panel unit panel-col-seventy firstUnit">            <div class="inside">              <div class="panel-pane pane-page-title no-title block" >  <div class="pane-inner clearfix">                        <div class="pane-content">      <h1></h1>    </div>              </div></div><div class="panel-separator"></div><div class="panel-pane pane-page-content no-title block" >  <div class="pane-inner clearfix">                        <div class="pane-content">      <div class="view view-event-days view-id-event_days view-display-id-panel_event_day_on_page view-dom-id-14b360860e7bb05f3521aebbce6249c9">                  <div class="view-content">        <div>    <div class="views-field views-field-day-set-a-task"><span class="field-content"><a href="/at-inline/nojs/5999" class="use-ajax set-a-task-link" rel="nofollow">Edit task</a><div id="at-inline-5999" class="at-inline-set-a-task-wrapper"></div></span></div>  <a href="#map" class="task_link"><span>Task</span></a>  <span class="views-field dropdown_list views-field-view">  <span class="views-label views-label-view">Results tables</span><span class="field-content">          <span class="task_result">		  <span class="label">Competition results</span><span class="file"><div class="views-field views-field-field-pg-scoring-category"><div class="field-content"><a href="http://validoll.inprog.ru/sites/default/files/comp_result_20130718-1310_3.html" target="_blank">Overall</a></div></div></span><span class="file"><div class="views-field views-field-field-pg-scoring-category"><div class="field-content"><a href="http://validoll.inprog.ru/sites/default/files/comp_result_20130718-1311-women_3.html" target="_blank">Women</a></div></div></span><span class="file"><div class="views-field views-field-field-pg-scoring-category"><div class="field-content"><a href="http://validoll.inprog.ru/sites/default/files/team_result_20130718-1309_2.html" target="_blank">Nations</a></div></div></span>	  	  </span><span class="task_result">		  <span class="label">Task results</span><span class="file"><div class="views-field views-field-field-pg-scoring-category"><div class="field-content"><a href="http://validoll.inprog.ru/sites/default/files/task_result_2013-07-17_20130718-1308_3.html" target="_blank">Overall</a></div></div></span><span class="file"><div class="views-field views-field-field-pg-scoring-category"><div class="field-content"><a href="http://validoll.inprog.ru/sites/default/files/task_result_2013-07-17_20130718-1308-women_3.html" target="_blank">Women</a></div></div></span><span class="file"><div class="views-field views-field-field-pg-scoring-category"><div class="field-content"><a href="http://validoll.inprog.ru/sites/default/files/team_result_20130718-1309-t2_2.html" target="_blank">Nations</a></div></div></span>	  	  </span>  </span>  </span><span class="views-field dropdown_list views-field-day-pg-race-play-link"><span><span class="race-links race-replay" data-race-eid="53" data-contest-cid="cnts-130529-2717963794" data-race-cid="r-6a31d091-c481-491d-a84b-be5749b7411c" data-start-time="1374063300000" data-deadline-time="1374076800000"><span class="file"><a class="race-link 2d replay" target="_blank" rel="nofollow">Task Replay</a></span><span class="help-text">Race time</span><div id="time-counter" class="time">03:45:00</div></span></span></span><span class="views-field dropdown_list views-field-field-pg-race-tracks">  <span class="views-label views-label-field-pg-race-tracks">Tracks</span><span class="field-content"><span class="file"><a href="http://validoll.inprog.ru/sites/default/files/trackst2.zip" target="_blank">IGC</a></span></span>  </span><div class="views-field views-field-field-dayblog-ref"><div class="field-content"><div class="item-list"><ul><li class="even first last">  <div>                <div class="field-item posted">22:17</div>              <div class="field-item plain-body"><p>The weather was excellent! Solid thermals with strength of 4 m/s, conversion lines and zero turbulence. We had 120 pilots on goal. The results are published. The first pilot on Goal is Stephan Morgenthaler (SUI), the second is Luca Donini (ITA) and the third is Josh Cohn (USA). The first lady is Seiko Fukuoka (FRA).</p></div>    </div>  <div>                <div class="field-item posted">14:07</div>              <div class="field-item plain-body"><p>Provisional task was set to 75 km but after an hour of watching the task committee has changed it. The task is set 70 km - race to goal. Take off window opens at 14:15. Start is at 15:15.</p></div>    </div>  <div>                <div class="field-item posted">09:42</div>              <div class="field-item plain-body"><p>The weather looks suitable. Pilots take the sky lift to go up to the take off.</p></div>    </div>  <div>                <div class="field-item posted">08:29</div>              <div class="field-item plain-body"><p>Good day but everything will depend on take off conditions at launch. Cloudbase 2400m.<br />The Northern winds are still strong, but when they turn from NE , they get more blocked by the terrain (there are 2-3000 m high mountains 100 km SW from Sopot). The higher parts of Stara Planina (10-20 km ENE from Sopot) also protect from NE winds.<br />So we think it may be possible to fly today.</p></div>    </div></li></ul></div></div></div><div class="views-field views-field-field-image"><div class="field-content"><div class="item-list"><ul><li class="even first"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03737.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-3" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_3/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03737.jpg?itok=TZcAjjPN" width="2000" height="1413" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03678.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-4" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_4/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03678.jpg?itok=ioVGU46K" width="2000" height="1376" alt="" title="" /></a></li><li class="even"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-170713-14-26-17-copy.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-4" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_4/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-170713-14-26-17-copy.jpg?itok=tnaLi3mi" width="2000" height="1494" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/gopr3719.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/gopr3719.jpg?itok=6-ht6jfB" width="2000" height="1500" alt="" title="" /></a></li><li class="even"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03526.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03526.jpg?itok=JN8vttAw" width="2000" height="1329" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03539.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03539.jpg?itok=gbnMJ6Ss" width="2000" height="1434" alt="" title="" /></a></li><li class="even"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/d3-2-1_1.png" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/d3-2-1_1.png?itok=Onewc-qJ" width="1306" height="979" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/d3-1_1.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/d3-1_1.jpg?itok=inWwoy7F" width="640" height="480" alt="" title="" /></a></li><li class="even"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/safety-c_1.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/safety-c_1.jpg?itok=fhUMEhB8" width="640" height="480" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-21-52.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-21-52.jpg?itok=UMvOkSJv" width="2000" height="1494" alt="" title="" /></a></li><li class="even"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-22-48.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-22-48.jpg?itok=1yeA_39H" width="2000" height="1494" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-26-30.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-26-30.jpg?itok=fTIBdo0R" width="2000" height="1494" alt="" title="" /></a></li><li class="even"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-22-56.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/foto-17.07.13-14-22-56.jpg?itok=hXKXH1Pv" width="2000" height="1494" alt="" title="" /></a></li><li class="odd"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03645.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03645.jpg?itok=y9hpstbE" width="2000" height="1329" alt="" title="" /></a></li><li class="even last"><a href="http://validoll.inprog.ru/sites/default/files/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03693.jpg" title="Day 3" class="colorbox" rel="gallery-node-5999-field_image"><img typeof="foaf:Image" class="image-style-bricks-b-7" src="http://validoll.inprog.ru/sites/default/files/styles/bricks_b_7/public/pg-contests/5364-13-fai-world-paragliding-championship/17-jul-2013/dsc03693.jpg?itok=bBaWy9rF" width="2000" height="1380" alt="" title="" /></a></li></ul></div></div></div>  </div>    </div>            </div>    </div>              </div></div>            </div>          </div>        </div>';
    // Reset the height of the container.
    $(selector).css('height', '');

    // Replace the contents of the container with the data.
    $(selector).html(data);

    // Update active class.
    $('a.active').removeClass('active').parents('li').removeClass('active-trail');
    $('a').filter(function() {
      return $(this).attr('href')== url
    }).addClass('active').parents('li').addClass('active-trail');

    // Change Url if option is selected and for html5 compatible browsers.
    var html5 = Drupal.settings.ajax_links_api.html5;
    if(html5 == 1 && window.history.replaceState) {
      // get title of loaded content.
      var matches = data.match("<title>(.*?)</title>");
      if (matches) {
        // Decode any HTML entities.
        var title = $('<div/>').html(matches[1]).text();
        // Since title is not changing with window.history.pushState(),
        // manually change title. Possible bug with browsers.
        document.title = title;
      }
      // store current url.
      window.history.replaceState({page : 0} , document.title, window.location.href);
      // Change url.
      window.history.pushState({page : 1} , title, url);
      window.onpopstate = function (e) {
        window.history.go(0);
      };
    }

    // Views Pager.
    // Please check http://drupal.org/node/1907376 for details.
    var viewsPager = Drupal.settings.ajax_links_api.vpager;
    if(viewsPager == 1) {
      $(selector + " .view .pager a").each(function(){
        var href = $(this).attr('href');
        href = href.replace("?ajax=1", "");
        href = href.replace("&ajax=1", "");
        $(this).attr('href', href);
      });
    }

    // Form Validation.
    // Plese check http://drupal.org/node/1760414 for details.
    var formAction = $(selector + " form").attr('action');
    if (formAction) {
      formAction = formAction.replace("?ajax=1", "");
      $("form").attr('action', formAction);
    }    
  }
})(jQuery);
