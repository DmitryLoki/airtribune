/**
 * В этом файле описан функционал, который добавляет панель в правую часть сайта, которая позволяет промотать экран вверх.
 */

/*   ==libs/jquery.scrollTo-1.4.2-min==   */
/**
 * jQuery.ScrollTo - Easy element scrolling using jQuery.
 * Copyright (c) 2007-2009 Ariel Flesler - aflesler(at)gmail(dot)com | http://flesler.blogspot.com
 * Dual licensed under MIT and GPL.
 * Date: 5/25/2009
 * @author Ariel Flesler
 * @version 1.4.2
 *
 * http://flesler.blogspot.com/2007/10/jqueryscrollto.html
 */
;(function(d){var k=d.scrollTo=function(a,i,e){d(window).scrollTo(a,i,e)};k.defaults={axis:'xy',duration:parseFloat(d.fn.jquery)>=1.3?0:1};k.window=function(a){return d(window)._scrollable()};d.fn._scrollable=function(){return this.map(function(){var a=this,i=!a.nodeName||d.inArray(a.nodeName.toLowerCase(),['iframe','#document','html','body'])!=-1;if(!i)return a;var e=(a.contentWindow||a).document||a.ownerDocument||a;return d.browser.safari||e.compatMode=='BackCompat'?e.body:e.documentElement})};d.fn.scrollTo=function(n,j,b){if(typeof j=='object'){b=j;j=0}if(typeof b=='function')b={onAfter:b};if(n=='max')n=9e9;b=d.extend({},k.defaults,b);j=j||b.speed||b.duration;b.queue=b.queue&&b.axis.length>1;if(b.queue)j/=2;b.offset=p(b.offset);b.over=p(b.over);return this._scrollable().each(function(){var q=this,r=d(q),f=n,s,g={},u=r.is('html,body');switch(typeof f){case'number':case'string':if(/^([+-]=)?\d+(\.\d+)?(px|%)?$/.test(f)){f=p(f);break}f=d(f,this);case'object':if(f.is||f.style)s=(f=d(f)).offset()}d.each(b.axis.split(''),function(a,i){var e=i=='x'?'Left':'Top',h=e.toLowerCase(),c='scroll'+e,l=q[c],m=k.max(q,i);if(s){g[c]=s[h]+(u?0:l-r.offset()[h]);if(b.margin){g[c]-=parseInt(f.css('margin'+e))||0;g[c]-=parseInt(f.css('border'+e+'Width'))||0}g[c]+=b.offset[h]||0;if(b.over[h])g[c]+=f[i=='x'?'width':'height']()*b.over[h]}else{var o=f[h];g[c]=o.slice&&o.slice(-1)=='%'?parseFloat(o)/100*m:o}if(/^\d+$/.test(g[c]))g[c]=g[c]<=0?0:Math.min(g[c],m);if(!a&&b.queue){if(l!=g[c])t(b.onAfterFirst);delete g[c]}});t(b.onAfter);function t(a){r.animate(g,j,b.easing,a&&function(){a.call(this,n,b)})}}).end()};k.max=function(a,i){var e=i=='x'?'Width':'Height',h='scroll'+e;if(!d(a).is('html,body'))return a[h]-d(a)[e.toLowerCase()]();var c='client'+e,l=a.ownerDocument.documentElement,m=a.ownerDocument.body;return Math.max(l[h],m[h])-Math.min(l[c],m[c])};function p(a){return typeof a=='object'?a:{top:a,left:a}}})(jQuery);


jQuery(function($) {

	window.last_scroll_position = 0;
	
	var show = false
	//var close_button = g_is_guest ? '<div class="close_panel" title="Убрать панель прокрутки"><span class="close dotted">убрать</span></div>' : ''
	var close_button = ''
	
	//console.log( g_is_guest , close_button)
	
	var to_top_button = $('<div class="to_top" ><div class="to_top_panel" ><div class="to_top_button" title="Наверх"><span class="arrow">&uarr;</span> <span class="label">наверх</span></div>  '+ close_button +'</div></div>')	
		
	$('body').append(to_top_button);
	
	// наверх
	$('.to_top_panel', to_top_button).click(function(){
		if(to_top_button.hasClass('has_position')){
			to_top_button.removeClass('has_position');
			$('.to_top_button .arrow', to_top_button).html('&uarr;');
			$('.to_top_button .label', to_top_button).html('наверх');
			$.scrollTo( window.last_scroll_position , 100,  { axis: 'y' } );
			window.last_scroll_position = 0;
		}else{
			to_top_button.addClass('has_position');
			$('.to_top_button .arrow', to_top_button).html('&darr;');
			$('.to_top_button .label', to_top_button).html('вниз');
			window.last_scroll_position = window.pageYOffset;
			$.scrollTo( $('body') , 100,  { axis: 'y' } );
		}
	})
	
	// закрыть
	$('.close_panel', to_top_button).click(function(){
		$.post('/json/settings/disable_scrollup/', { 'action': 'disable' }, function(json){
			if(json.messages == 'ok'){
				$('.to_top').remove()
				$.jGrowl('Панель отключена. Вы можете настроить показ панели в <a href="/settings/others/">настройках</a>.', { sticky: true })
			}else{
				show_system_error(json)
			}
		})
		return false;
	})
	

	var last_position = 0;
		      
	$(window).scroll(function () {   
		show_or_hide()
		if( last_position < window.pageYOffset){
			//console.log('скролл вниз', last_position , window.pageYOffset);
			if( to_top_button.hasClass('has_position') ){
				//to_top_button.removeClass('has_position');
				//$('.to_top_button .arrow', to_top_button).html('&uarr;');
				//$('.to_top_button .label', to_top_button).html('наверх');
				//to_top_button.hide()
				show = false
			}
		}else{
			//console.log('скролл вверх', last_position , window.pageYOffset);
		}
		last_position = window.pageYOffset;
	})
	

	function show_or_hide(){
		if( window.pageYOffset > 400){
			if(!show){
				to_top_button.show()
				to_top_button.removeClass('has_position');
				$('.to_top_button .arrow', to_top_button).html('&uarr;');
				$('.to_top_button .label', to_top_button).html('наверх');
				show = true
			}
		}else{
			if(show && !to_top_button.hasClass('has_position')){
				to_top_button.hide()
				show = false
			}
		}
	}


	show_or_hide()
	
});