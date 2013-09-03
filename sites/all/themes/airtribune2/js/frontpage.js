jQuery(function($){
  $('section.front_live_events').each(function(i,section){
    var $section = $(section),
      clickCounter = 1,
      rowsContainer = $section.find('.view-frontpage-events > .view-content'),
      rowsContainerHeight = rowsContainer.height(),
      expandButton = $section.find('.frontpage-show-more-events'),
      viewAllEventsButton = $section.find('h2.pane-title a');

    expandButton.bind('click', function() {
      if(clickCounter == 3) {
        location.href = viewAllEventsButton.attr('href');
        return;
      }
      rowsContainer.height(rowsContainerHeight * ++clickCounter);

    });
  })
});