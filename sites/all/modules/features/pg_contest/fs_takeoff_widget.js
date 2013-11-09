/**
 * @file
 * Javascript for Flying site Take-off widget.
 */
(function ($) {
    Drupal.behaviors.pg_contest_takeoff = {
        attach: function(context) {
            // Hide field, in which we store take offs ids.
//            $('.edit-field-takeoffs').hide();
            $("#edit-field-flying-site-ref-und").change(function () {
                var FS = $(this).find(":selected").val();
                console.log(FS);
                $.ajax({
                    url: '/flyingsite/' + FS,
                    type: "GET",
                    success: function(data){
                        console.log(data);
                        // TODO ReWrite this code
                        $('#edit-field-take-offs-und-0-serialized-to').val(data);
                        // Make here checkboxes from JSON data
//                        $('#field-takeoffs-checkboxes').replaceWith('<div id="field-takeoffs-checkboxes">'+data+'</div>');
                    }
                });
            });
        }
    }
})(jQuery);
