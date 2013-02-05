/**
 * Disable mouse wheel zoom until map focuesd by click.
 * Requires map object property `zoomWheelDisabledUntilClick`.
 */
Drupal.behaviors.disableZoomWheelBeforeClick = {
    attach:function (context) {
            var mapContainer = jQuery(context),
                olObject = mapContainer.data('openlayers');

            if (!olObject) return;

            var mapOptions = olObject.map,
                olMap = olObject.openlayers,
                navControls = olMap.getControlsByClass('OpenLayers.Control.Navigation');

            if (mapOptions.zoomWheelDisabledUntilClick === false) {
                return;
            }

            for (var i = 0; i < navControls.length; ++i) {
                navControls[i].disableZoomWheel();
            }

            mapContainer.bind('click', function () {
                for (var i = 0; i < navControls.length; ++i)
                    navControls[i].enableZoomWheel();
                jQuery(this).unbind('click', arguments.callee);
            })

    }
};