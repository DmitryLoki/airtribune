(function ($) {
Drupal.behaviors.airtribune2 = {
  attach: function (context) {

  // Temporary disable these menu items,
  $('.pane-menu-footer-menu a, .menu-item-1338 a, .menu-item-1339 a, .menu-item-1340 a, .menu-item-1341 a')
    .attr('title', 'Under construction')
    .attr('href', '')
    .click(function(){return false;})

    $('.event-map-toggle-pane').click(function(){
      $(this).parent('h2').next().toggle();

    })


  }

}
})(jQuery);