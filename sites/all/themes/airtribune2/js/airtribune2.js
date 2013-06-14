(function ($) {
  Drupal.behaviors.airtribune2 = {
    attach: function (context) {

      // Temporary disable these menu items,
      $('.pane-menu-footer-menu a, .menu-item-1338 a, .menu-item-1339 a, .menu-item-1340 a, .menu-item-1341 a')
        .attr('title', 'Under construction')
        .attr('href', '')
        .click(function () {
          return false;
        })

      $('.event-map-toggle-pane').once(function () {
        $(this).click(function () {
          $(this).toggleClass('event-map-toggle-pane-active').parent('h2').next().toggle();
        })

      })

      $(document.body).once(setRaceToggleBehavior);

    }

  }
  function setRaceToggleBehavior() {
    jQuery('body').bind('click', {parent: this}, bodyClick);
    function bodyClick(e) {
      //If e.target is not a child of el.handle then hide list
      if (jQuery(e.target).parents('.views-field-view, ' +
          '.views-field-field-pg-race-tracks, ' +
          '.views-field-pg-race-play-link')
        .size() == 0) {
        $('.pane-event-days-panel-pane-1 .views-field-view > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-field-pg-race-tracks > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-pg-race-play-link > .field-content').hide();
        $('.files_list_down').removeClass('files_list_down');
      }
    }

    $('.pane-event-days-panel-pane-1 .views-field-view .views-label, ' +
      '.pane-event-days-panel-pane-1 .views-field-field-pg-race-tracks .views-label, ' +
      '.pane-event-days-panel-pane-1 .views-field-pg-race-play-link .views-label')
      .click(function () {
        el = $(this).next();
        $('.pane-event-days-panel-pane-1 .views-field-view > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-field-pg-race-tracks > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-pg-race-play-link > .field-content')
          .each(function () {
            if ($(this)[0] != el[0]) {
              $(this).hide();
              //$('.files_list_down').removeClass('files_list_down');
            }
          });
        $(this).next().toggle().parents('.ui-accordion-content').toggleClass('files_list_down');
      })

    if (jQuery('.view-event-days .event-day').length > 1) {
      $('.pane-contest-blog-contest-full-pane h2.pane-title').toggleClass('expanded').next().hide()
    }
    $('.pane-contest-blog-contest-full-pane h2.pane-title').click(function () {
      $(this).toggleClass('expanded').next().slideToggle()
    })

    $('.ui-accordion-content').each(function () {
      el = $('<div class="ui-accordion-content-inner"></div>');
      el.append($(this).children());
      $(this).append(el);
    });

  };

})(jQuery);

