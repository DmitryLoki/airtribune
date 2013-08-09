/**
 * @file
 * Handles ajax functionalities for Ajax Links API module.
 */
(function ($) {
  var ajaxLoading = false;
  Drupal.behaviors.ajaxLinksApi = {
    attach: function (context, settings) {
      var trigger = Drupal.settings.ajax_links_api.trigger;
      $(trigger).click(function(e) {
        e.preventDefault();
        if(!ajaxLoading) {
          ajaxLoading = true;
          var url = $(this).attr("href");
          var id = $(this).attr("rel");
          if(id) {
            selector = $(this).attr("rel");
          } else {
            selector = Drupal.settings.ajax_links_api.selector;
          }
          $(selector).html("<div class='ajax-links-api-loading'></div>");
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
      success: function (data, textStatus, xhr) {
        $(selector).html(data);
        Drupal.attachBehaviors(selector);
        
        // Update active class.
        $('a.active').removeClass('active').parent().removeClass('active-trail');
        $('a').filter(function() {
          return $(this).attr('href')== url
        }).addClass('active').parent().addClass('active-trail');
        
        // HTML5
        var html5 = Drupal.settings.ajax_links_api.html5;
        if(html5 == 1) {
          // get title of loaded content.
          var title = data.match("<title>(.*?)</title>")[1];
          // store current url.
          window.history.replaceState({page : 0} , document.title, window.location.href);
          // Change url.
          window.history.pushState({page : 1} , title, url);
          // Since title is not changing with window.history.pushState(),
          // manually change title. Possible bug with browsers.
          document.title = title;
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
      },
      error: function (xhr, textStatus, errorThrown) {
        (selector).html("Access denied or page not found");
      }
    });
  }
})(jQuery);
