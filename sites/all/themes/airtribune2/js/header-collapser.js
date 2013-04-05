jQuery(function ($) {
    var hasPageCollapseClass = $(document.body).hasClass('featured-header-collapsible');

    if (!hasPageCollapseClass) {
        return;
    }

    var headerContainer = $('.featured-header'),
        collapsedClass = 'featured-header-collapsed',
        collapseControl = $('<div class="collapse-control">');


    headerContainer.append(collapseControl);

    collapseControl.bind('click', function () {
        headerContainer.toggleClass(collapsedClass);
    });

});