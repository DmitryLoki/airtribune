(function ($) {
  Drupal.behaviors.atMembershipDelete = {
    attach: function(context, settings) {
      $('.event-signout', context).click(function(){
        var
          a = $(this),
          td = a.parents('td').eq(0),
          tr = td.parents('tr').eq(0);
        var
          deleteSuccess = function(data){
            alert(data.message);
            tr.remove();
          },
          deleteError = function(data){
            alert(Drupal.t('Sign out fails.'));
          },
          deleteComplete = function(){
            a.show();
            $('.event-signout-process', td).remove();
          }
        a.hide();
        td.append('<span class="event-signout-process">' + Drupal.t('Process...') + '</span>');
        $.ajax({
          type: 'POST',
          url: this.href,
          dataType: 'json',
          success: deleteSuccess,
          error: deleteError,
          complete: deleteComplete,
          data: 'js=1'
        });
        return false;
      });
    }
  };
})(jQuery);
