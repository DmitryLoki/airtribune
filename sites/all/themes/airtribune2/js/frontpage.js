(function($){
  Drupal.behaviors.frontpage = {
    attach: function(context){
      $('section.front_live_events').each(function(i,section){
        var $section = $(section),
          clickCounter = 1,
          itemsPerRow = 3,
          maxRowsCount = 3,
          items = $section.find('.views-row'),
          rowsCount = Math.ceil(items.length / itemsPerRow),
          rowsContainer = $section.find('.view-frontpage-events > .view-content'),
          rowsContainerHeight = rowsContainer.height(),
          expandButton = $section.find('.frontpage-show-more-events'),
          viewAllEventsButton = $section.find('h2.pane-title a');

        expandButton.bind('click', function() {
          if(clickCounter == rowsCount && viewAllEventsButton.attr('href')) {
            location.href = viewAllEventsButton.attr('href');
            return;
          }
          if(clickCounter < maxRowsCount) {
            rowsContainer.height(rowsContainerHeight * ++clickCounter);
          }

        });
      })
    }
  }

})(jQuery);