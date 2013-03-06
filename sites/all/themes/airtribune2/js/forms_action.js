function updateForm(container) {
    var $ = jQuery,
        container = container || $(document);
    $( 'input, .pane-page-content form select', container).forms({disableChoiceOfFirstItemInSelection:true, file_bt: ''});
    $('.select .items_inner', container).each(function () {
        $(this).parent().show();
        $(this).jScrollPane({scrollbarWidth:4, showArrows:false});
        $(this).addClass('items_padding');
        $(this).parent().hide();

    });
    var select_z_index = 1000;
    $('select', container).each(function () {
        $(this).parents('.form-wrapper, .form-item').css({'z-index':select_z_index, 'position':'relative'})
        select_z_index--;
    });
}
jQuery(function ($) {
    $('#event_register').show();
    updateForm($('.pane-page-content form'));
    $('#event_register').hide();
    $('.reg_choice .form_show').click(function () {
        $('#event_register').show();
        Drupal.disableTabKey($('#event_register'));
        $(this).parent().hide();
        return false;
    });
});
