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

      setRaceToggleBehavior();
      $(document.body).once(function(){
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
      })
    }


  }

  function setRaceToggleBehavior() {
    jQuery('body')
      .unbind('click.bodyClick')
      .bind('click.bodyClick', {parent: this}, bodyClick);
    function bodyClick(e) {
      //If e.target is not a child of el.handle then hide list
      if (jQuery(e.target).parents('.views-field-view, ' +
          '.views-field-field-pg-race-tracks, ' +
          '.views-field-day-pg-race-play-link')
        .size() == 0) {
        $('.views-field-view > .field-content, ' +
          '.views-field-field-pg-race-tracks > .field-content, ' +
          '.views-field-day-pg-race-play-link .replay-link-content').hide();
        $('.files_list_down').removeClass('files_list_down');
      }
    }

    $('.views-field-view .views-label, ' +
      '.views-field-field-pg-race-tracks .views-label, ' +
      '.views-field-day-pg-race-play-link .replay-link-label')
      .unbind('click')
      .click(function () {
        if($(this).hasClass('processed'))
        $(this).addClass('processed');
        el = $(this).next();
        $('.views-field-view > .field-content, ' +
          '.views-field-field-pg-race-tracks > .field-content, ' +
          '.views-field-day-pg-race-play-link .replay-link-content')
          .each(function () {
            if ($(this)[0] != el[0]) {
              $(this).hide();
              //$('.files_list_down').removeClass('files_list_down');
            }
          });
        $(this).next().toggle().parents('.ui-accordion-content').toggleClass('files_list_down');
      });


    //Scroll to map from day
    var scrollBody = $('html,body'),
      mapTopOffset = $('#map').offset().top;

    $('.task_link').bind('click', function (event) {
      event.preventDefault();
      scrollBody.animate({scrollTop: mapTopOffset}, 400);
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
  var defaultText =
    $('.create_event a')
      .bind('click', function (e) {
        e.preventDefault();
        $(this).text('Sorry, coming soon!');
      })
      .bind('mouseout', function (e) {
        $(this).text(defaultText);
      })
      .text()
})

