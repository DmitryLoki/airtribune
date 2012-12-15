jQuery(function($){
	$('#sign_in .signin a').click(function(){
		//$('#user_login').toggle();
		if($('#user_login').height() == 1){
			var direct = 1
		}
		else {
			var direct = 0
		}
		blockSlide($('#user_login'), direct);
		return false;
	});
	$('body').click(function (e) {
		if (!($(e.target).parents('#user_login').length)) {
			if($('#user_login').height() != 1){
				blockSlide($('#user_login'), 0);
			}
			
		}
	})
	
	$('.form-item input').each(function(){
		if($(this).attr('rel')){
			if($(this).val() == '') {
				$(this).val($(this).attr('rel'))
			}
			else {
				$(this).addClass('focus');
			}
		}
		$(this).focus(function(){
			if($(this).val() == $(this).attr('rel')){
				$(this).val('').addClass('focus');
			}
		});
		$(this).blur(function(){
			if($(this).val() == ''){
				$(this).removeClass('focus').val($(this).attr('rel'));
			}
		});
	});
	
});

Object.size = function(obj) {
    var size = 0, key;
    for (key in obj) {
        if (obj.hasOwnProperty(key)) size++;
    }
    return size;
};

function blockSlide(activeEl, direction, callback){
	if(typeof callback != 'object'){
		var callback = {};
		activeEl.addClass('active');
		callback.speeds = {90:100, 95:120, 100:140};
		callback.height = itemSizes(activeEl.find('.pane-inner'))['vert'];
		callback.size = Object.size(callback.speeds);
		if(direction){
			callback.currentSpeed = 1;
			callback.currentSize = 1;
		}
		else {
			callback.currentSpeed = callback.size;
			callback.currentSize = callback.size - 1;
		}
		
	}
	
	var speedSize = 0, speedKey;
	for (speedKey in callback.speeds) {
        if (callback.speeds.hasOwnProperty(speedKey)) {			
			speedSize++;
			if (callback.currentSpeed == speedSize){
				var speed = callback.speeds[speedKey];
			}
			if (callback.currentSize == speedSize){
				var speedHeight = speedKey;
			}
		}
    }
	
	
	if(callback.currentSize == 0){
		speedHeight = 1;
	}
	else {
		speedHeight = height*speedHeight/100;
	}
	
	if(direction){
		callback.currentSpeed++;
		callback.currentSize++;
	}
	else {
		callback.currentSpeed--;
		callback.currentSize--;
	}
	
	
	activeEl.animate({'height':speedHeight}, speed, function(){
		if(!(callback.currentSpeed == 0 || callback.currentSpeed == callback.size + 1)){
			blockSlide(activeEl, direction, callback);
		}
		if(callback.currentSpeed == 0){
			activeEl.removeClass('active');
		}
		/*activeEl.animate({'height':height*95/100}, 150, function(){
			activeEl.animate({'height':height*100/100}, 200)
		})*/
	})
}

function itemSizes (el) {
	sizes = {
		hor : Array ('padding-right', 'padding-left', 'margin-right', 'margin-left'),
		vert : Array ('padding-top', 'padding-bottom', 'margin-top', 'margin-bottom')
	}
	width = el.width();
	for (i = 0; i < sizes.hor.length; i++) {
		width = width + ((el.css(sizes.hor[i]) != 'auto') ? parseInt(el.css(sizes.hor[i]).replace('px', '')) : 0);
	}
	height = el.height();
	for (i = 0; i < sizes.vert.length; i++) {
		height = height + ((el.css(sizes.vert[i]) != 'auto') ? parseInt(el.css(sizes.vert[i]).replace('px', '')) : 0);
	}
	sizes = {
		hor : width,
		vert : height
	}
	return sizes
}