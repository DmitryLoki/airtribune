/**
 * Disable mouse wheel zoom until map focuesd by click.
 * Requires map object property `zoomWheelDisabledUntilClick`.
 */
Drupal.behaviors.disableZoomWheelBeforeClick = {
    attach:function (context) {
        if(!Drupal.settings.openlayers) {
            return;
        }
        var mapsContainers = Drupal.settings.openlayers.maps;
        for (var map in mapsContainers) {
            var mapContainer = jQuery('#' + mapsContainers[map].id),
                olObject = mapContainer.data('openlayers'),
                mapOptions = olObject.map,
                olMap = olObject.openlayers,
                navControls = olMap.getControlsByClass('OpenLayers.Control.Navigation');

            if(!mapOptions.zoomWheelDisabledUntilClick) {
                return;
            }

            for(var i = 0; i < navControls.length; ++i) {
                navControls[i].disableZoomWheel();
            }

            mapContainer.bind('click', function() {
                for(var i = 0; i < navControls.length; ++i)
                    navControls[i].enableZoomWheel();
                jQuery(this).unbind('click', arguments.callee);
            })
        }

    }
};