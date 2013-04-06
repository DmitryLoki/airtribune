jQuery(function ($) {
    var hasPageCollapseClass = $(document.body).hasClass('featured-header-collapsible');

    if (!hasPageCollapseClass) {
        return;
    }

    var headerContainer = $('.featured-header'),
        headerTitle = $('.featured-header-title'),
        headerContainerHeight = headerContainer.height(),
        headerTitleHeight = headerTitle.outerHeight() || 100,
        collapsedClass = 'featured-header-collapsed',
        collapseControl = $('<div class="collapse-control">');

    headerContainer.append(collapseControl);

    collapseControl.bind('click', function () {
        headerContainer.toggleClass(collapsedClass);
        toggleHeight();
    });
    toggleHeight();
    function toggleHeight() {
        if(headerContainer.hasClass(collapsedClass)) {
            headerContainer.height(headerTitleHeight)
        } else {
            headerContainer.height(headerContainerHeight);
        }
    }
});