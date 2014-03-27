function updateForm(container, formsObj) {
    var $ = jQuery,
        container = container || $(document);
        formsObj = formsObj || {disableChoiceOfFirstItemInSelection:true, file_bt:''}

    $('input:not(#edit-field-header-image-und-0-upload), .pane-page-content form select', container).forms(formsObj);
    $('#edit-field-header-image-und-0-upload', container).forms({file_bt:Drupal.t('Upload image')});
    $('.select .items_inner', container).each(function () {
        if(!$(this).hasClass('items_padding')){
            $(this).parent().show();
            $(this).jScrollPane({scrollbarWidth:4, showArrows:false, contentWidth: '0px'});
            handleKeyPressInSelect($(this).parent(), true);
            $(this).addClass('items_padding');
            $(this).parent().hide();
        }
    });
    if(!updateForm.zIndex) {
      updateForm.zIndex = 1000;
    }
  $('select', container).each(function () {
    //if(!$(this).parents('.form-item').parents('.form-wrapper')){
    var formItem = $(this).parents('.form-wrapper, .form-item');
    formItem.css({'z-index': ++updateForm.zIndex, 'position': 'relative'});
    /*}
     else {
     $(this).parents('.form-wrapper').css({'z-index':select_z_index, 'position':'relative'})
     }*/
  });

    function handleKeyPressInSelect(selectContainer, ignoreTitle) {
        var jsp = selectContainer.children().data('jsp'),
            body = jQuery('body'),
            options = selectContainer.find('span.option:gt(0)'),
            searchString = "";

        selectContainer.bind('select-showed', function () {
            body.bind('keypress', keyupHandler);
            body.bind('keydown', keydownHandler);
        });

        selectContainer.bind('select-hided', function () {
            body.unbind('keypress', keyupHandler);
            body.unbind('keydown', keydownHandler);
            searchString = "";
        });

        function keyupHandler(event) {
            var key = event.which || event.keyCode;
            //if pressed key is a letter or digit
            if ((key >= 65 && key <= 122) || (key >= 48 && key <= 57)) {
                searchString += String.fromCharCode(key);
            }
            scrollToOption();
        }

        function keydownHandler(event) {
            var key = event.which || event.keyCode;
            if (key == 8 /* backspace */) {
                //remove last symbol from search string
                searchString = searchString.slice(0, -1);
                event.preventDefault();
                scrollToOption();
            }
        }

        function scrollToOption() {
            if (searchString.length === 0) {
                return;
            }
            for (var i = 0, option, l = options.length; i < l; i++) {
                option = options.eq(i);
                if (option.text().toUpperCase().indexOf(searchString.toUpperCase()) == 0) {
                    jsp.scrollToElement(option, true, true);
                    return;
                }
            }
        }
    }

}
jQuery.fn.updateForm = function(options) {
  return updateForm(this, options);
};
jQuery(function ($) {
    updateForm($('.pane-page-content form'));
    $('.reg_choice .form_show').click(function () {
        $('#event_register').removeClass('event-register-form');
        $(this).parent().hide();
        return false;
    });
});

Drupal.behaviors.updateImageField = {
    attach: function(){
        updateForm('#user-profile-form');
        updateForm('.at-editablefield-list_integer .form-type-select', {disableChoiceOfFirstItemInSelection:false});

    }
}
