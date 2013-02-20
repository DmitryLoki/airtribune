jQuery(function($){
	
	$('.pane-page-content form input, .pane-page-content form select').forms({disableChoiceOfFirstItemInSelection:true});
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
	
	//$('.pane-content form').each(function(){
		/*var formObj = {};
		$('.required').each(function(){
		  if (typeof formObj[$(this).parents('form').attr('id')] == 'undefined') {
			  formObj[$(this).parents('form').attr('id')] = {}
		  }
		  var flag = false;
		  //alert($(this)[0].tagName)
		  switch($(this).get(0).tagName){
			  case 'INPUT':
		  		switch ($(this).get(0).type) {
					case 'password':
					case 'text':
						if ($(this).val() != '') {
							flag = true;
						}
						$(this).bind('keyup change', function(e){
							//alert($(this).get(0).tagName)
							var falg = false;
							if($(this).val() != '') {
								falg = true;
							}
							formsRequired($(this), falg)
						})
					break;
					case 'checkbox':
					 //alert(1)
						if ($(this).is(':checked')) {
							flag = true;
						}
						$(this).change(function(){
							var falg = false;
							if($(this).attr('checked')) {
								falg = true;
							}
							formsRequired($(this), falg);
						})
						$(this).next().click(function(){
							var falg = false;
							if($(this).prev().attr('checked')) {
								falg = true;
							}
							formsRequired($(this).prev(), falg);
						})
					break;
				}
			  break;
			  case 'TEXTAREA':
					if ($(this).val() != '') {
						flag = true;
					}
					$(this).bind('keyup change', function(e){
						var falg = false;
						if($(this).val() != '') {
							falg = true;
						}
						formsRequired($(this), falg)
					})
		  
			  break;
		  }
		  formObj[$(this).parents('form').attr('id')][$(this).attr('id')] = flag;
	  });
	  for (var key in formObj) {
		var reqFlag = true;
		for (var key_inner in formObj[key]) {
			if(!formObj[key][key_inner]) {
				reqFlag = false;
			}
		}
		if (!reqFlag) {
			$('#'+key).find('.form-submit').attr('disabled', 'disabled').addClass('disabled');
		}
	  }
	    function formsRequired(el, flag){
	  formObj[el.parents('form').attr('id')][el.attr('id')] = flag;
	  setSubmitButtonDisabled(el, !checkAllFieldsFilled(el));
  }

  function checkAllFieldsFilled(el){
	  var formObjFlag = true;
	  for (var key in formObj[el.parents('form').attr('id')]) {
		  if(!formObj[el.parents('form').attr('id')][key]) {
			 formObjFlag = false;
			  break;
		  }
	  }
	  return formObjFlag;
  }

	/**
	 * Disables or enables submit button of el's form
	 * @param el
	 * @param {Boolean} disabled
	 */
  /*function setSubmitButtonDisabled(el, disabled) {
	  if(!disabled) {
		  $('#'+el.parents('form').attr('id')).find('.form-submit').removeAttr('disabled').removeClass('disabled');
	  }
	  else {
		  $('#'+el.parents('form').attr('id')).find('.form-submit').attr('disabled', 'disabled').addClass('disabled');
	  }
  }*/
//	});
});

/*(function ($) {
Drupal.behaviors.airtribune2 = {
  attach: function (context) {

  // Temporary disable these menu items,
  alert(1);

}
})(jQuery);*/
