(function ($) {
    Drupal.behaviors.jcarouselCircular = {
        attach:function (context, settings) {

            settings = settings || Drupal.settings;

            // If no carousels exist on this part of the page, work no further.
            if (!settings.jcarousel || !settings.jcarousel.carousels) {
                return;
            }

            $.each(settings.jcarousel.carousels, function (key, options) {
                if (options.wrap != "circular") {
                    return;
                }
                var $carouselContainer = $(options.selector, context);
                if (!$carouselContainer.length) {
                    return;
                }

                var jcarousel = $carouselContainer.data('jcarousel'),
                    prevButton = jcarousel.buttonPrev,
                    nextButton = jcarousel.buttonNext,
                    currentIndex = options.start;

                $carouselContainer.once(function () {
                    prevButton.unbind('click').bind('click', prevClick);
                    nextButton.unbind('click').bind('click', nextClick);

                    //if there are only 2 photos in list, duplicate them
                    var li = jcarousel.list.find('li');
                    li.bind('click', function(){
                        currentIndex = this.getAttribute('jcarouselindex')
                    });
                    if (li.length === 2) {
                        var newLI = li.clone(),
                            oldWidth = jcarousel.list.width();
                        jcarousel.list.append(newLI);
                        jcarousel.list.width(oldWidth + newLI.width());
                    }

                    function prevClick(event) {
                        var last = jcarousel.list.find('li:last');
                        last.css({width:'0px'});
                        jcarousel.list.prepend(last);
                        last.animate({width:last.find('img').width()}, 200);
                        currentIndex = currentIndex == 1 ? li.length : currentIndex - 1;
                        event.stopImmediatePropagation();
                    }

                    function nextClick(event) {
                        var first = jcarousel.list.find('li:first');
                        first.animate({width:'0px'}, {complete:function () {
                            jcarousel.list.append(first);
                            first.animate({width:first.find('img').width()}, 200);
                        }});
                        currentIndex = currentIndex % li.length  + 1;
                        event.stopImmediatePropagation();
                    }

                    //fix for #2818
                    var $document = $(document),
                        cboxCurrent = $('#cboxCurrent');

                    $document.bind('cbox_open', function () {

                        $document.bind('cbox_complete', function () {

                            var nextClickElements = $('#cboxNext,#cboxLoadedContent'),
                                prevClickElements = $('#cboxPrevious');

                            nextClickElements.bind('click', nextClick);
                            prevClickElements.bind('click', prevClick);

                            cboxCurrent.html(currentIndex + ' of '+li.length);
                            $document.unbind('cbox_closed').bind('cbox_closed', function () {
                                nextClickElements.unbind('click', nextClick);
                                prevClickElements.unbind('click', prevClick);

                                //Event handlers for cbox_complete comes from nowhere, so unbind them to free memory
                                $document.unbind('cbox_complete');
                            });
                        });
                    });

                });
            });


        }
    }
})(jQuery);
