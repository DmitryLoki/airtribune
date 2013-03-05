jQuery(function($){

    var dropItems = $('#sign-in .drop-item'),
        flagDropItem = $('.flags'),
        flagDropItemHeader = $('#sign-in .lang-icon span'),
        userLoginDropItem = $('.user-login, .user-menu'),
        userLoginDropItemHeader = $('#sign-in .user-button a, #sign-in .user-picture a');

    dropItems.hide();

    userLoginDropItemHeader.click(function(event){
        var $that = $(this);
        slideUp(flagDropItem, function onSlideComplete(){
            flagDropItemHeader.removeClass('active');
            toggle($('.user-login, .user-menu'));
            $that.toggleClass('active');
        });

        event.preventDefault();
    }).removeClass('active');

    flagDropItemHeader.click(function(event){
        var $that = $(this);
        slideUp(userLoginDropItem, function onSlideComplete(){
            userLoginDropItemHeader.removeClass('active');
            toggle($('.flags'));
            $that.toggleClass('active');
        });

        event.preventDefault();
    });

    $('body').click(function (e) {
        if (!($(e.target).parents('#sign-in').length)) {
            slideUp(dropItems, function onSlideUpComplete(){
                flagDropItemHeader.removeClass('active');
                userLoginDropItemHeader.removeClass('active');
            });
        }
    });

    setPlaceholder('.form-item input');

    function toggle(item, cb){
        if(item.is(':visible')){
            slideUp(item,cb);
        } else {
            item.slideDown({duration:600,easing:'easeOutCubic',complete:cb})
        }
    }

    Drupal.toggle = toggle;
    function slideUp(dropItems, cb){
        dropItems.slideUp({duration:400,easing:'easeInCubic', complete:cb}).removeClass('active');
    }
});

jQuery.extend( jQuery.easing,{
    easeInCubic: function (x, t, b, c, d) {
        return c*(t/=d)*t*t + b;
    },
    easeOutCubic: function (x, t, b, c, d) {
        return c*((t=t/d-1)*t*t + 1) + b;
    }
});

function setPlaceholder(id, setRequiredMark) {
    var requiredSpan = '<span class="form-required">*</span>';
    jQuery(id).each(function (index, input) {
        if (typeof jQuery(this).attr('rel') !== 'undefined') {
            /*if (jQuery.browser.webkit){
             jQuery(this).attr({'autocomplete':'off'})
             }*/
            var span = jQuery('<span class="label">'
                + jQuery(this).attr('rel')
                + (setRequiredMark ? requiredSpan : '')
                + '</span>');
            jQuery(this).parent().append(span);
            setTimeout(function () {
                if (input.value.length > 0)
                    span.hide();
            }, 1000);
            if (jQuery(this).attr('value') != '') {
                jQuery(this).parent().children('span.label').hide();
            }
            jQuery(this).focus(function () {
                jQuery(this).parent().children('span.label').hide();
            });
            jQuery(this).blur(function () {
                if (jQuery(this).attr('value') == '') {
                    jQuery(this).parent().children('span.label').show();
                }
            });
            jQuery(this).bind('keyup', function () {
                jQuery(this).parents('form').find('.form-item input').each(function () {
                    //alert(1)
                    if (jQuery(this).attr('value') != '') {
                        jQuery(this).parent().children('span.label').hide();
                    }
                })
            });
            span.click(function () {
                jQuery(this).parent().find('input').focus();
                jQuery(this).hide();
            });
        }

    });
}