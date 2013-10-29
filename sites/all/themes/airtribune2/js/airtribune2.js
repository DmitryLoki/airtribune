(function ($) {
  Drupal.behaviors.airtribune2 = {
    attach: function (context) {

      // Temporary disable these menu items,
      $('.pane-menu-footer-menu a, .pane-airtribune-primary-navigation .menu-item-1338 a, .pane-airtribune-primary-navigation .menu-item-1339 a, .pane-airtribune-primary-navigation .menu-item-1340 a, .pane-airtribune-primary-navigation .menu-item-1341 a')
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
          '.views-field-day-pg-race-play-link')
        .size() == 0) {
        $('.pane-event-days-panel-pane-1 .views-field-view > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-field-pg-race-tracks > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-day-pg-race-play-link .replay-link-content').hide();
        $('.files_list_down').removeClass('files_list_down');
      }
    }

    $('.pane-event-days-panel-pane-1 .views-field-view .views-label, ' +
      '.pane-event-days-panel-pane-1 .views-field-field-pg-race-tracks .views-label, ' +
      '.pane-event-days-panel-pane-1 .views-field-day-pg-race-play-link .replay-link-label')
      .click(function () {
        el = $(this).next();
        $('.pane-event-days-panel-pane-1 .views-field-view > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-field-pg-race-tracks > .field-content, ' +
          '.pane-event-days-panel-pane-1 .views-field-day-pg-race-play-link .replay-link-content')
          .each(function () {
            if ($(this)[0] != el[0]) {
              $(this).hide();
              //$('.files_list_down').removeClass('files_list_down');
            }
          });
        $(this).next().toggle().parents('.ui-accordion-content').toggleClass('files_list_down');
      });

    if (jQuery('.view-event-days .event-day').length > 1) {
      $('.pane-contest-blog-contest-full-pane h2.pane-title').toggleClass('expanded').next().hide()
    }
    $('.pane-contest-blog-contest-full-pane h2.pane-title').click(function () {
      $(this).toggleClass('expanded').next().slideToggle()
    });

    $('.ui-accordion-content').each(function () {
      el = $('<div class="ui-accordion-content-inner"></div>');
      el.append($(this).children());
      $(this).append(el);
    });

  };

})(jQuery);

jQuery(function ($) {
  var breadcrumb = $('.breadcrumb')
  if (breadcrumb.width() == 580) {
    var width = 0;
    breadcrumb.children().each(function () {
      if ($(this).width() > width) {
        width = $(this).width();
        el = $(this);
      }
      ;
    })
    var last = breadcrumb.children(':last-child');
    delta = last.position().left + last.width() - breadcrumb.width();
    //alert(el);
    el.find('span').css({'max-width': width - delta});
  }
  $('.solutions_accordeon .accordeon_inner').each(function () {
    $(this).height('auto');
    $(this).attr('rel', $(this).height());
    $(this).height(0);
  });
  $('.solutions_accordeon .accordeon_title').click(function () {
    el = $(this).next();
    if (el.height() == 0) {
      el.height(el.attr('rel'));
    }
    else {
      el.height(0);
    }
  })

  //Temp stub for "Create an event" button
  var createEventButton = $('.create_event'),
    //stubHtml = $('<span style="display: block">Contact <a class="create-event-mail" href="mailto:info@airtribune.com">info@airtribune.com</a> to publish your event</span><span style="font-size: 25px">Automatic event publication is coming soon.</span>'),
    stubHtml = $('<span style="display: block"></span>',
    mailLink = stubHtml.find('.create-event-mail'),
    link = createEventButton.find('a'),
    defaultText = link.text();

  createEventButton
    .bind('click', function (e) {
      e.preventDefault();
      link.html(stubHtml);
    })
    .bind('mouseleave', function (e) {
      setTimeout(function(){
        link.text(defaultText);
      }, 5000);
    });

  mailLink.bind('click', function (e) {
    e.stopPropagation();
  })
})

