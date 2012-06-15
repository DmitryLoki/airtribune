;(function ($) {
  Drupal.behaviors.viewsProximityValue = {
    attach: function (context, settings) {
      //$('#edit-options-proximity-components').hide(); // tmp
      $('#edit-options-source').change(function() {
        var input_source = $(this).val().replace('_', '-');
        var $newElement = $('#edit-options-proximity-components-' + input_source).clone();
        // Clean up $newElement based on source.
        // @TODO: Find a way to make this less hardcode-y.
        switch (input_source) {
          case 'manual':
            $newElement.find('.geofield-lat').val('').attr('name', 'options[value][origin][lat]');
            $newElement.find('.geofield-lon').val('').attr('name', 'options[value][origin][lon]');
            break;
        }
        $('.geofield-proximity-field-wrapper .geofield-proximity-origin').replaceWith($newElement);
      });
    }
  };
})(jQuery);