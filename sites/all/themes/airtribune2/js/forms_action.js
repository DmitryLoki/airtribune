jQuery(function($){
	
	$('.pane-page-content form input, .pane-page-content form select').forms({disableChoiceOfFirstItemInSelection:true, file_bt:''});
	$('.pane-page-content form .select .items_inner').each(function(){
		$(this).parent().show();
		$('#event_register').show()
		$(this).jScrollPane({scrollbarWidth:4, showArrows:false});
		//$(this).height($(this).height());
		//$(this).width($(this).width());
		$(this).addClass('items_padding');
		$(this).parent().hide();
		$('#event_register').hide()
	});
	var select_z_index = 1000;
	$('.pane-page-content form select').each(function(){
		$(this).parents('.form-wrapper, .form-item').css({'z-index':select_z_index, 'position':'relative'})
		select_z_index --;
	});

	$('.reg_choice .form_show').click(function(){
		$('#event_register').show();
		$(this).parent().hide();
		return false;
	})
	
	
});
