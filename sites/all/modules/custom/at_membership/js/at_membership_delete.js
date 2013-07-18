(function ($) {
  Drupal.behaviors.atMembershipDelete = {
    attach: function(context, settings) {
      $('.cancel-participation', context).click(function(){
        var event_name = $(this).prev().find('span.title').text();
        if (confirm(Drupal.t('Are you sure that you want to completely sign out from ') + $.trim(event_name) + '?')) {
          var
            a = $(this),
            row = a.parents('.views-row').eq(0);
          var
            deleteSuccess = function(data){
              alert(data.message);
              row.slideUp('fast', function () { $(this).remove(); });
            },
            deleteError = function(data){
              alert(Drupal.t('Cancel your participation fails.'));
            },
            deleteComplete = function(){
              a.show();
              $('.cancel-participation-process', row).remove();
            }
          a.hide();
          row.append('<span class="cancel-participation-process">' + Drupal.t('Process...') + '</span>');
          $.ajax({
            type: 'POST',
            url: this.href,
            dataType: 'json',
            success: deleteSuccess,
            error: deleteError,
            complete: deleteComplete,
            data: 'js=1'
          });
        }
        return false;
      });
    }
  };
})(jQuery);
