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
