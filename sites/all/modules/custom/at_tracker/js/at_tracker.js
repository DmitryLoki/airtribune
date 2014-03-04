(function ($) {

  Drupal.behaviors.at_tracker = {
    attach: function (context, settings) {
      var updateOptions = function ($select) {
        var apiUrl = Drupal.settings.at_core_sync.apiUrl;
        var contestId = $select.data("contestid") ? '&not_registered_at=' + $select.data("contestid") : '';
        apiUrl = apiUrl + '/tracker?device_type=tr203&device_type=telt_gh3000' + contestId;

        $.ajax({
          url: apiUrl,
          dataType: "json",
          success: function(result) {
            // Add empty value
            var opt = '<option value="none">' + Drupal.t('-- None selected --') + '</option>';
            var currVal = $select.val();
            if (currVal != 'none') {
              // Add curent value, if it is not empty
              var currText = $select.children(':selected').text();
              result[result.length] = {id : currVal, name : currText};
            }
            // Sort list by tracker name
            result.sort(SortByName);
            if (result.length > 0) {
              for (var i = 0; i< result.length; i++) {
                opt = opt + '<option value="' + result[i].id +'">' + result[i].name + '</option>';
              }
            }
            // Replace options for select
            $select.html(opt);
            // Select current value
            $select.val( currVal ).prop('selected',true);
          }
        });
      }

      $('.field-type-at-tracker select.form-select-at_tracker').each(function () {
        var $this = $(this);
        $this.on('focus', function(event) {
          updateOptions($this);
        });
      });

      // Sort your array of trackers by name
      function SortByName(a, b){
        var aName = a.name.toLowerCase();
        var bName = b.name.toLowerCase();
        return ((aName < bName) ? -1 : ((aName > bName) ? 1 : 0));
      }
    }
  }

})(jQuery);
