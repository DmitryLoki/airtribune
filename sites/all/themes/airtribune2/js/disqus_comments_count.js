jQuery(document).ready(function () {
    if(!Drupal.settings.disqus) return;
    var $ = jQuery;

    var commentsCountLink = $('<a id="comments-count-link" style="display:none" href="' + location.href + '#disqus_thread" ></a>');

    $('.posted').append(commentsCountLink);

    //Load count.js
    var s = document.createElement('script');
    s.type = 'text/javascript';
    s.src = 'http://'+disqus_shortname+'.disqus.com/count.js';
    s.onload = readyHandler;
    s.onreadystatechange = function () {
        if (s.readyState == 'complete') {
            readyHandler();
        }
    };
    document.getElementsByTagName('HEAD')[0].appendChild(s);

    //When count.js loaded
    function readyHandler() {
        DISQUSWIDGETS.displayCount = function(commentsData){
            var commentsCount = commentsData.counts[0].comments;
            commentsCountLink.html(commentsCount);
            commentsCountLink.show();
        };
    }
});