(function ($) {

  Drupal.behaviors.MemcacheStoragePC = {
    attach: function (context, settings) {

      $('fieldset#edit-memcache-storage-pc', context).drupalSetSummary(function(context) {
        var vals = [];

        if ($('#edit-memcache-storage-pc-node-override-defaults', context).is(':checked')) {
          vals.push(Drupal.t('Node expiration: settings are overriden'));
        }
        else {
          vals.push(Drupal.t('Node expiration: default settings'));
        }

        if ($('#edit-memcache-storage-pc-comment-override-defaults', context).is(':checked')) {
          vals.push(Drupal.t('Comment expiration: settings are overriden'));
        }
        else {
          vals.push(Drupal.t('Comment expiration: default settings'));
        }

        return vals.join(', ');
      });

    }
  };

})(jQuery);
