(function ($) {
  Drupal.behaviors.views_accordion = {
    attach: function () {
      if (Drupal.settings.views_accordion) {
        $.each(Drupal.settings.views_accordion, function (id) {
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
            var hash = "#!day_" + (headersLength - i); // hash to use for accordion navigation option
            var $this = $(this);
            var $link = $this.find('a');
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
              $link.get(0).href = hash;
            }

            // Wrap the accordion content within a div if necessary
            if (!usegroupheader) {
              $this.siblings().wrapAll('<div></div>');
            }
          });
          var activePane = Drupal.behaviors.views_accordion.getDayFromHash() || this.rowstartopen;
          /* jQuery UI accordion call */
          var accordionElement = $(displaySelector + ':not(.ui-accordion)');
          if (accordionElement.length === 0) {
            return;
          }
          accordionElement.accordion({
            header: headerSelector,
            animated: this.animated,
            active: activePane,
            collapsible: this.collapsible,
            autoHeight: this.autoheight,
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
        });
      }
    },
    scrollToActiveTab: function (accordion) {
      var $active = $(accordion.active);
      if ($active.length !== 0) {
        $('body,html').animate({scrollTop:$active.offset().top}, 400);
      }
    },
    getDayFromHash: function () {
      var hash = location.hash.match(/day_\d+$/);
      if (hash !== null) {
        return parseInt(hash, 10);
      } else if (location.hash === '#!') {
        return -1;
      }
      return undefined;
    },
    updateHash: function (accordion) {
      //if there is active page - set hash with its
      if (accordion.active.length !== 0) {
        location.hash = accordion.active.find('a').attr('href');
      } else {
        location.hash = '#!';
      }
    }
  };
})(jQuery.noConflict());