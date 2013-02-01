jQuery(function($){

    var dropItems = $('#sign-in .drop-item'),
        flagDropItem = $('.flags'),
        flagDropItemHeader = $('#sign-in .lang-icon span'),
        userLoginDropItem = $('.user-login, .user-menu'),
        userLoginDropItemHeader = $('#sign-in .user-button a, #sign-in .user-picture a');

    dropItems.hide();

    userLoginDropItemHeader.click(function(event){
        slideUp(flagDropItem);
        flagDropItemHeader.removeClass('active');

        $('.user-login, .user-menu').slideToggle();
        $(this).toggleClass('active');

        event.preventDefault();
    }).removeClass('active');

    flagDropItemHeader.click(function(event){
        slideUp(userLoginDropItem);
        userLoginDropItemHeader.removeClass('active');
        $('.flags').slideToggle();
        $(this).toggleClass('active');

        event.preventDefault();
    });

    $('body').click(function (e) {
        if (!($(e.target).parents('#sign-in').length)) {
            slideUp(dropItems);
            flagDropItemHeader.removeClass('active');
            userLoginDropItemHeader.removeClass('active');
        }
    });

    setPlaceholder('.form-item input');

    function slideUp(dropItems){
        dropItems.each(function(i, item){
            $(item).slideUp().removeClass('active');
        })
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