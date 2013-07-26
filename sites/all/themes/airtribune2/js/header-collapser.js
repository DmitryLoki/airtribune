jQuery(function ($) {
    var hasPageCollapseClass = $(document.body).hasClass('featured-header-collapsible');
    // Classes body of the page, where header is collapsed
    $('.page-event-pilots, .page-user, .node-type-accommodation, .node-type-activity, .page-account').find('.featured-header').addClass('featured-header-collapsed');

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

    if ($('#facebook-fan-gate').size()) {
        $('#page > .region_inner').addClass('facebook-fan-gate');
    };
});