(function ($) {
    Drupal.behaviors.jcarouselCircular = {
        attach:function (context, settings) {

            settings = settings || Drupal.settings;

            // If no carousels exist on this part of the page, work no further.
            if (!settings.jcarousel || !settings.jcarousel.carousels) {
                return;
            }

            $.each(settings.jcarousel.carousels, function (key, options) {
                if(options.wrap != "circular") {
                    return;
                }
                var $carouselContainer = $(options.selector, context);
                if (!$carouselContainer.length) {
                    return;
                }

                var jcarousel = $carouselContainer.data('jcarousel'),
                    prevButton = jcarousel.buttonPrev,
                    nextButton = jcarousel.buttonNext;

                prevButton.unbind('click').bind('click', prevClick);
                nextButton.unbind('click').bind('click', nextClick);

                //if there are only 2 photos in list, duplicate them
                var li = jcarousel.list.find('li');
                if(li.length === 2){
                    var newLI = li.clone(),
                        oldWidth = jcarousel.list.width();
                    jcarousel.list.append(newLI);
                    jcarousel.list.width(oldWidth+newLI.width());
                }

                function prevClick(event) {
                    var last = jcarousel.list.find('li:last');
                    last.css({width:'0px'});
                    jcarousel.list.prepend(last);
                    last.animate({width:'466px'});
                    event.stopImmediatePropagation();
                }

                function nextClick(event) {
                    var first = jcarousel.list.find('li:first');
                    first.animate({width:'0px'}, {complete:function () {
                        jcarousel.list.append(first);
                        first.animate({width:'466px'});
                    }});
                    event.stopImmediatePropagation();
                }
            });

        }
    }
})(jQuery);
