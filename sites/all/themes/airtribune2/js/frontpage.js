(function ($) {
  Drupal.behaviors.frontpage = {
    attach: function (context) {
      $('section.front_live_events').each(function (i, section) {
        var $section = $(section),
          clickCounter = $section.data('click-counter') || 1,
          itemsPerRow = 3,
          items = $section.find('.view-frontpage-events > .view-content > .views-row'),
          rowsCount = Math.ceil(items.length / itemsPerRow),
          rowsContainer = $section.find('.view-frontpage-events > .view-content'),
          rowsContainerHeight = rowsContainer.height(),
          expandButton = $section.find('.frontpage-show-more-events'),
          viewAllEventsButton = $section.find('h2.pane-title a');

        expandButton.unbind('click.shom-more-events').bind('click.shom-more-events', function () {
          if (clickCounter == rowsCount && viewAllEventsButton.attr('href')) {
            location.href = viewAllEventsButton.attr('href');
            return;
          }
          if (clickCounter < rowsCount) {
            rowsContainer.height(rowsContainerHeight * ++clickCounter);
          }

          //need to store click counter in case of re-applying this function
          $section.data('click-counter', clickCounter);
        });
      })
    }
  }

})(jQuery);