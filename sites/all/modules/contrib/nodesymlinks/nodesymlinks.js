(function ($) {

Drupal.behaviors.nodesymlinks = {

  attach: function(context) {
    $('#nodesymlinks-items tr:not(.ns-processed)', context).each(function(i){

      // Attach checkbox click handler
      $('#edit-menu-nodesymlinks-items-'+i+'-alias-pathauto').click( function(){
        // Auto-alias checked; disable input.
        if ($('#edit-menu-nodesymlinks-items-'+i+'-alias-pathauto').is(':checked')) {
          $('#edit-menu-nodesymlinks-items-'+i+'-alias-path').attr('disabled', 'disabled');
        }
        // Auto-alias unchecked; enable input.
        else {
          $('#edit-menu-nodesymlinks-items-'+i+'-alias-path').removeAttr('disabled').focus();
        }
      });

      // Disable input
      if ($('#edit-menu-nodesymlinks-items-'+i+'-alias-pathauto').is(':checked')) {
        $('#edit-menu-nodesymlinks-items-'+i+'-alias-path').attr('disabled', 'disabled');
      }

    }).addClass('ns-processed');
  }
};

})(jQuery);