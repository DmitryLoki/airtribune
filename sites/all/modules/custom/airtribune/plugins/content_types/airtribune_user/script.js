jQuery(function($){
	
	$('#sign-in .drop-item').hide();
	
	$('#sign-in .user-button a, #sign-in .user-picture a').click(function(){
		if($('.main-menu-item:visible').size() > 0){
			blockSlide($('.main-menu-item:visible'), 0, false);
		}
		if($('.user-login').height() == 1 || $('.user-menu').height() == 1 ){
			var direct = 1
			if($('.flags:visible').size() > 0){
				var calldackFunc = {
					activeEl:$('.user-login, .user-menu'), 
					direct:direct, 
					eventEl:$(this)
				};
				blockSlide($('.flags'), 0, false, false, calldackFunc);
				return false;
			}
		}
		else {
			var direct = 0
		}
		blockSlide($('.user-login, .user-menu'), direct, $(this));
		return false;
	});
	
	$('#sign-in .lang-icon span').click(function(){
		if($('.main-menu-item:visible').size() > 0){
			blockSlide($('.main-menu-item:visible'), 0, false);
		}
		if($('.flags').height() == 1){
			var direct = 1;
			if($('.user-login:visible, .user-menu:visible').size() > 0){
				var calldackFunc = {
					activeEl:$('.flags'), 
					direct:direct, 
					eventEl:$(this)
				};
				blockSlide($('.user-login:visible, .user-menu:visible'), 0, false, false, calldackFunc);
				return false;
			}
		}
		else {
			var direct = 0
		}
		blockSlide($('.flags'), direct, $(this));
		return false;
	});
	
	$('body').click(function (e) {
		if (!($(e.target).parents('#sign-in').length)) {
			if($('.user-login:visible, .user-menu:visible, .flags:visible').size() > 0){
				blockSlide($('.user-login:visible, .user-menu:visible, .flags:visible'), 0, false);
			}
			
		}
	})
	
	setPlaceholder('.form-item input');
	
});


Object.size = function(obj) {
    var size = 0, key;
    for (key in obj) {
        if (obj.hasOwnProperty(key)) size++;
    }
    return size;
};

// @see http://api.jquery.com/slideToggle/
function blockSlide(activeEl, direction, eventEl, callback, calldackFunc){
	//alert(calldackFunc)
	if(typeof calldackFunc == 'undefined'){
		calldackFunc = false;
	}
	if(typeof callback != 'object'){
		var callback = {};
		activeEl.show().addClass('active');
		if(eventEl){
			eventEl.addClass('active');
		}
		callback.speeds = {90:100, 95:120, 100:140};
		//callback.height = itemSizes(activeEl.find('.pane-inner'))['vert'];
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
	callback.height = itemSizes(activeEl.find('.pane-inner'))['vert'];
	
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
			blockSlide(activeEl, direction, eventEl, callback, calldackFunc);
		}
		if(callback.currentSpeed == 0){
			activeEl.removeClass('active');
			jQuery('#airtribune-user .active, .pane-airtribune-primary-navigation ul li.expanded.active, .pane-airtribune-primary-navigation ul li.expanded a.active').removeClass('active');
			activeEl.hide();			
		}
		if(calldackFunc && (callback.currentSpeed == 0 || callback.currentSpeed == callback.size + 1)){
			blockSlide(calldackFunc.activeEl, calldackFunc.direct, calldackFunc.eventEl);
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