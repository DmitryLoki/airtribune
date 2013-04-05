jQuery(function ($) {
    var hasPageCollapseClass = $(document.body).hasClass('featured-header-collapsible');

    if (!hasPageCollapseClass) {
        return;
    }

    var headerContainer = $('.featured-header'),
        collapseCookieName = 'header-collapse-state',
        headerCollapseState = readCookie(collapseCookieName),
        collapsedClass = 'featured-header-collapsed',
        collapseControl = $('<div class="collapse-control">');

    if (headerCollapseState == "collapsed") {
        headerContainer.addClass(collapsedClass);
    }

    headerContainer.append(collapseControl);

    collapseControl.bind('click', function () {
        headerContainer.toggleClass(collapsedClass);

        if (headerContainer.hasClass(collapsedClass)) {
            writeCookie(collapseCookieName, 'collapsed', 30);
        } else {
            writeCookie(collapseCookieName, '', -1);
        }
    });

    function readCookie(name) {
        var nameEQ = name + "=";
        var ca = document.cookie.split(';');
        for (var i = 0; i < ca.length; i++) {
            var c = ca[i];
            while (c.charAt(0) == ' ') c = c.substring(1, c.length);
            if (c.indexOf(nameEQ) == 0) return c.substring(nameEQ.length, c.length);
        }
        return null;
    }

    function writeCookie(name, value, days) {
        if (days) {
            var date = new Date();
            date.setTime(date.getTime() + (days * 24 * 60 * 60 * 1000));
            var expires = "; expires=" + date.toGMTString();
        }
        else var expires = "";
        document.cookie = name + "=" + value + expires + "; path=/";
    }
});