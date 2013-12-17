jQuery(function ($) {
  var parentLiInc = 0;
  $('.pane-airtribune-primary-navigation ul ul').each(function () {
    var parentLi = $(this).parent();
    parentLi.children('a').attr('href', 'javascript: void(0);');
    var dropItemWrap = $('<div class="drop-item main-menu-item" id="drop-menu-' + parentLiInc + '"><div class="pane-inner-wrapper"><div class="pane-inner"></div></div></div>');
    parentLi.attr('rel', 'drop-menu-' + parentLiInc);
    dropItemWrap.insertAfter(parentLi.parent());
    dropItemWrap.find('.pane-inner').append($(this));
    dropItemWrap.css({'position': 'absolute', 'left': parentLi.position().left + 7, 'width': parentLi.width() - 10});

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

    //set drop item wrap height
    dropItemWrap.height(dropItemWrap.find('.pane-inner-wrapper').outerHeight() + 20);
    dropItemWrap.hide();

    parentLi.click(function () {
      var slideElement = $('#' + $(this).attr('rel')),
        that = this;

      Drupal.slideUp(slideElement.siblings('.drop-item'), function(){
        parentLi.parent()
          .find('[rel="'+this.id+'"]')
          .removeClass('menu_active')
          .children('a')
          .removeClass('menu_active');
      });

      if (!$(this).hasClass('menu_active')) {
        $(this).addClass('menu_active').children('a').addClass('menu_active');
        Drupal.toggle(slideElement)
      }
      else {
        Drupal.toggle(slideElement, function () {
          $(that).removeClass('menu_active').children('a').removeClass('menu_active');
        })
      }

    });


    parentLiInc++;

  });
  $('body').click(function (e) {
    if (!($(e.target).parents('.pane-airtribune-primary-navigation ul li, .main-menu-item').length)) {
      var visibleMenuItem = $('.main-menu-item:visible');
      if (visibleMenuItem.size() > 0) {
        Drupal.toggle(visibleMenuItem, function () {
          $('[rel="' + this.getAttribute('id') + '"]').removeClass('menu_active').children('a').removeClass('menu_active');
        });
      }

    }
  })
})