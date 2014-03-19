/* 
	Created by Vladimir Khodakov (web-interface.info team)
	version 1.3
 */
jQuery.fn.forms = function(options){ // custom form elements
	var options = jQuery.extend({
		checkbox: true,
		radio: true,
		file: true,
		select: true,
        //Prevent first item in options list to be selectable (Title of list)
        disableChoiceOfFirstItemInSelection:false,
		file_bt: 'Обзор',
		ie: jQuery.browser.msie
	},options);
	var opt = options;
	return this.each(function() {
		var el = jQuery(this);
		el.type = el.attr('type') || el[0].tagName.toLowerCase();
		if (el.type.indexOf('select') + 1) {
			el.type = 'select'
		}
		if (el.is('input') && opt[el.type] == true && !el.hasClass('styled_element')) {
			el.name = el.attr('name').replace(/[\[\]]/g, '');
			el.replace = (el.type != 'file') ? '<span class="'+el.type+' el-name-'+el.name+'"></span>' : '<span class="'+el.type+'"><span class="input"></span><span class="button">'+opt.file_bt+'</span></span>';
			el.before(el.replace);
			//el.hide();
			switch (el.type){
				case 'checkbox':
					if (el.attr('checked')) {
						el.prev().addClass('check_'+el.type);
					}
					el.show().css({'position':'absolute', 'top':'auto', 'left':'-10000px'})
					el.prev().click(function(){
            //skip disabled elements
            if(el.is(':disabled')) {
              return;
            }
						jQuery(this).toggleClass('check_'+el.type);
						if (!el.is(':checked')) {
							el.attr('checked', true)
						}
						else {
							el.attr('checked', false);
						}
            el.trigger('change', {selfTriggeredEvent:true});
					});	
					if(opt.ie) {
						el.focus(function(){
							el.prev().toggleClass('check_'+el.type);
						})
					}
					else {
						el.change(function(e, data){
              if(!data.selfTriggeredEvent)
							  el.prev().toggleClass('check_'+el.type);
						})
					}
					el.addClass('styled_element');
				break;
				case 'radio':
					if (el.attr('checked')) {
						el.prev().addClass('check_'+el.type);
					}
					el.show().css({'position':'absolute', 'top':'auto', 'left':'-10000px'})
					el.prev().click(function(){
						if (!el.is(':checked')) {
							jQuery('.el-name-'+el.name).removeClass('check_'+el.type);
							el.attr('checked', true);
              el.trigger('change');
							jQuery(this).addClass('check_'+el.type);
						}
					});	
					if(opt.ie) {
						el.focus(function(){
							jQuery('.el-name-'+el.name).removeClass('check_'+el.type);
							el.attr('checked', true);
							el.prev().addClass('check_'+el.type);
						});
					}
					else {
						el.change(function(){
							jQuery('.el-name-'+el.name).removeClass('check_'+el.type);
							el.attr('checked', true);
							el.prev().addClass('check_'+el.type);
						});
					}
					el.addClass('styled_element');
				break;
				case 'file':
					el.id = el.attr('id');
					el.show()
					el.emulate = el.prev();
					el.emulate.append('<span class="emulate-click"></span><span class="emulate-click-plus"></span>');
					el.emulate.children('.emulate-click').css({'position':'absolute', 'top':0, 'right':0, 'width':'100%', 'height':'100%', 'overflow':'hidden'});
					el.emulate.children('.emulate-click').append(el);
					el.emulate.children('.emulate-click-plus').hover(
						function(){
							jQuery(this).append(el);
						},
						function(){
							jQuery(this).parent().find('.emulate-click').append(el);
						}
					);
					el.emulate.css({'position':'relative'})
					el.emulate.find('input').css({'opacity':'0', 'font-size':'199px', 'top':'0', 'left':'0', 'position':'absolute', 'cursor':'pointer', 'padding':'0', 'margin':'0 0 0 0', 'border':'none', 'z-index':'10000', 'background':'#000000', 'direction':'rtl'})
					el.emulate.find('input').change(function(){
						el.emulate.find('.input').html(jQuery(this).val())
					})
					el.serch = el.parents('.form-wrapper').attr('id');
					el.addClass('styled_element');
				break;
			}
		}
		else if (el.is('select') && opt[el.type] == true && !el.hasClass('styled_element')) {
			el.css({'position':'absolute', 'top':'auto', 'left':'-10000px'})
			el.name = el.attr('name').replace(/[\[\]]/g, '');
			el.replace = '<span class="'+el.type+' el-name-'+el.name+'"><span class="checked_option_wrap"><span class="checked_option"></span></span><span class="items"><span class="items_inner">';
			el.children().each(function(i, item){
				el.option = el.children().eq(i);
				el.option.selected = (el.option.attr('selected')) ? ' selected' : '';
				el.option.html = el.option.html();
				if (el.parents('.field-type-list-integer').size()) {
					el.option.html = '<span class="status-value-' + el.option.attr('value') + '"><span class="status-value">' + el.option.html + '</span></span>';
				};
                el.replace += '<span class="option'+el.option.selected+' hi">'+el.option.html+'</span>';
			});
			el.replace += '</span></span></span>';
			el.before(el.replace);
			el.handle = el.prev();
			el.handle.items = el.handle.find('.items')
			el.handle.cheked = el.handle.find('.checked_option');
			el.handle.cheked.html(el.handle.find('.selected').html() || el.handle.find('.option:first-child').html()).click(function(event){
        jQuery('body').bind('click', {parent: this}, bodyClick);
        function bodyClick(e) {
          //If e.target is not a child of el.handle then hide list
          if (jQuery(e.target).parents('.' + el.handle.attr('class').split(' ').join('.')).length == 0) {
            el.handle.items.hide();
            el.handle.removeClass('select_opened');
            el.handle.items.trigger('select-hided');
            jQuery('body').unbind('click', bodyClick);
            el.trigger('blur');
            el.handle.css({zIndex:0})
            el[0].blur();
          }
        }
				el.handle.items.toggle();
        el.handle.toggleClass('select_opened');
        var isShown = el.handle.items.is(':visible');
        el.handle.items.trigger(jQuery.Event(isShown ? 'select-showed' : 'select-hided'));
        el.handle.css({'z-index': (isShown ? 1000 : 0)});
        if (opt.disableChoiceOfFirstItemInSelection) {
          el.handle.items.find('span.option:eq(0)').addClass('option-title').hide();
        }
      })
        .mouseup(function() {
          el.trigger(!el.handle.hasClass('select_opened') ? 'focus' : 'blur');
        });
			el.handle.css({'position':'relative', 'display':'inline-block'})
			el.handle.find('span').css('display', 'block')
			el.handle.items.css({'position':'absolute', 'top':'100%', 'left':0}).hide()
			el.handle.find('.option').click(function(){
				el.handle.items.children('.items_inner').find('.selected').removeClass('selected');
				jQuery(this).addClass('selected');
				el.handle.index = el.handle.items.children('.items_inner').find('.option').index(jQuery(this));
				//el.find('option').removeAttr('selected');
				el.find('option').eq(el.handle.index).attr('selected', '');
				el.handle.cheked.html(el.handle.items.children('.items_inner').find('.selected').html())
				el.handle.items.hide();
        el.handle.items.trigger('select-hided');
				el.change();
        el.trigger('change');
			});
			el.addClass('styled_element');
		}
	});	
}