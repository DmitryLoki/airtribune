jQuery(document).ready(function () {
    var $ = jQuery,
        commentsCountLink = $('a[href$="#disqus_thread"]');

    $(document).ajaxComplete(function (event, xhr, ajaxOptions) {
        //if this ajax request was for count.js
        if (ajaxOptions.url.indexOf('count.js') > -1) {
            replaceDisplayCountFunction();
        }
    });

    //When count.js loaded
    function replaceDisplayCountFunction() {
        //replace displayCount function from count.js
        DISQUSWIDGETS.displayCount = function (commentsData) {
            var commentsCounts = commentsData.counts;
            for (var i = 0; i < commentsCounts.length; ++i) {
                var commentsCount = commentsCounts[i].comments;
                commentsCountLink.eq(i).html(commentsCount).css({'display':'block'});
            }
        };
    }
});