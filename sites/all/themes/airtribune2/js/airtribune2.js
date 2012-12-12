jQuery(function($){
	$('#sign_in .signin a').click(function(){
		$('#user_login').toggle();
		return false;
	});
	$('body').click(function (e) {
				if (!($(e.target).parents('#user_login').length)) {
					$('#user_login').hide();
				}
			})
});