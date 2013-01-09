jQuery(function($){
	var parentLiInc = 0;
	$('.pane-airtribune-primary-navigation ul ul').each(function(){
		var parentLi = $(this).parent();
		parentLi.children('a').attr('href', 'javascript: void(0);');
		var dropItemWrap = $('<div class="drop-item main-menu-item" id="drop-menu-'+parentLiInc+'"><div class="pane-inner-wrapper"><div class="pane-inner"></div></div></div>');
		parentLi.attr('rel', 'drop-menu-'+parentLiInc);
		dropItemWrap.insertAfter(parentLi.parent());
		dropItemWrap.find('.pane-inner').append($(this));
		dropItemWrap.css({'position':'absolute', 'left':parentLi.position().left + 7, 'width':parentLi.width() - 10})
		setTimeout(function(){
			dropItemWrap.hide();
		},100);
		/*dropItemWrap.hover(
			function(){
				$(this).addClass('mouseover');
			},
			function(){
				$(this).removeClass('mouseover');
				blockSlide($(this), 0);
			}
		);
		parentLi.hover(
			function(){
				$('#'+$(this).attr('rel')).addClass('lihover')
				blockSlide($('#'+$(this).attr('rel')), 1);
			},
			function(){
				$('#'+$(this).attr('rel')).removeClass('lihover')
				setTimeout(function(){					
					if(!$('.pane-airtribune-primary-navigation .mouseover').size()){
						blockSlide($('.pane-airtribune-primary-navigation .drop-item:visible:not(".lihover")'), 0);
					}
				}, 50)
			}
		);*/
		
		parentLi.click(function(){
			if(!$(this).hasClass('active')){
				$(this).addClass('active').children('a').addClass('active')
				blockSlide($('#'+$(this).attr('rel')), 1)
			}
			else {
				//$(this).removeClass('active')
				blockSlide($('#'+$(this).attr('rel')), 0)
			}
			
		})
		
		
		parentLiInc++;
		
	});
	$('body').click(function (e) {
		if (!($(e.target).parents('.pane-airtribune-primary-navigation ul li, .main-menu-item').length)) {
			if($('.main-menu-item:visible').size() > 0){
				blockSlide($('.main-menu-item:visible'), 0, false);
			}
			
		}
	})
})