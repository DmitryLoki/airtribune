jQuery(function($){
	$('.pane-page-content form input').forms();
});


(function ($) {
Drupal.behaviors.airtribune2 = {
  attach: function (context) {

  // Temporary disable these menu items,
  $('.pane-menu-footer-menu a, .menu-item-1338 a, .menu-item-1339 a, .menu-item-1340 a, .menu-item-1341 a')
    .attr('title', 'Under construction')
    .attr('href', '')
    .click(function(){return false;})

  }
}
})(jQuery);