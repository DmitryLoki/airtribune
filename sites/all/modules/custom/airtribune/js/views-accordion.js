(function ($) {
  Drupal.behaviors.views_accordion = {
    attach: function () {
      Drupal.settings.ajax_links_api.html5 = 0;
      if (Drupal.settings.views_accordion) {
        $.each(Drupal.settings.views_accordion, function (id) {

          if(this.processed) return;
          /* Our view settings */
          var usegroupheader = this.usegroupheader;
          var viewname = this.viewname;
          var display = this.display;

          /* the selectors we have to play with */
          var displaySelector = '.view-id-' + viewname + '.view-display-id-' + display + ' .view-content';
          var headerSelector = this.header;

          /* Prepare our markup for jquery ui accordion */
          var headers = $(displaySelector + ' ' + headerSelector + ':not(.ui-accordion-header)'),
            headersLength = headers.length;
          headers.each(function (i) {
            var $this = $(this);
            var hash = '#!' + $this.find('div.day-number').data('href').substr(1); // hash to use for accordion navigation option
            var $link = $this.find('a');
            //special tricks for ajax links api
            $link.attr('href', $link.data('href'));
            $link.bind('click', function(e) {
              $($link.attr('rel')).css('height','70px');
              $(this).unbind('click').removeClass('ajax-link')
              //$(this).bind('click',accordionElement.data('accordion')._clickHandler.bind(accordionElement.data('accordion')));
            });
            // if the header is not already using an anchor tag, add one
            if ($link.length == 0) {
              // setup anchor tag for navigation
              $this.wrapInner('<a href="' + hash + '" rel="nofollow"></a>');
            }
            // if there are already, they wont be clickable with js enabled, we'll use them for accordion navigation
            else {
              // @FIXME ?
              // We are currently destroying the original link, though search crawlers will stil see it.
              // Links in accordions are NOT clickable and leaving them would kill deep linking.
              //$link.get(0).href = hash;
            }

            // Wrap the accordion content within a div if necessary
            if (!usegroupheader) {
              $this.siblings().wrapAll('<div></div>');
            }
          });
          var accordionElement = $(displaySelector + ':not(.ui-accordion)');
          if (accordionElement.length === 0) {
            return;
          }
          var activePane = Drupal.behaviors.views_accordion.getDayFromHash(accordionElement) || this.rowstartopen;
          /* jQuery UI accordion call */

          accordionElement.accordion({
            header: headerSelector,
            animated: this.animated,
            active: activePane,
            collapsible: 0,//this.collapsible,
            autoHeight: false,//this.autoheight,
            event: this.event,
            fillSpace: this.fillspace,
            navigation: this.navigation,
            clearstyle: this.clearstyle,
            change: function () {
              var accordion = $(this).data('accordion');
              Drupal.behaviors.views_accordion.updateHash(accordion);
              Drupal.behaviors.views_accordion.scrollToActiveTab(accordion);
            }
          });
          Drupal.behaviors.views_accordion.updateHash(accordionElement.data('accordion'));
          Drupal.behaviors.views_accordion.scrollToActiveTab(accordionElement.data('accordion'));
          accordionElement.find('.ui-state-active a').trigger('click');
          accordionElement.data('accordion').options.collapsible = 1;//this.collapsible
          this.processed = true;
        });
      }
    },
    scrollToActiveTab: function (accordion) {
      var $active = $(accordion.active);
      if ($active.length !== 0) {
        $('body,html').animate({scrollTop: $active.offset().top}, 400);
      }
    },
    getDayFromHash: function (accordionElement) {
      var hash = location.hash.match(/#!(.*)/i);
      if (hash !== null && hash.length > 1 && hash[1] !== '') {
        var activeDayNumber = -1;
        accordionElement.find('div.views-accordion-header .day-number').each(function(i,link){
          if($(link).attr('data-href').substr(1) == hash[0].substr(2)) activeDayNumber = i;
        });
        return activeDayNumber;
      } else if (location.hash === '#!') {
        return -1;
      }
      return undefined;
    },
    updateHash: function (accordion) {
      //if there is active page - set hash with its
      if (accordion.active.length !== 0) {
        location.hash = '#!' + accordion.active.parent().find('div.views-accordion-header .day-number').attr('data-href').substr(1);
      } else {
        location.hash = '#!';
      }
    }
  };


})(jQuery.noConflict());