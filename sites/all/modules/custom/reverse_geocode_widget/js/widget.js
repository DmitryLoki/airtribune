(function($) {
  Drupal.reverse_widget = Drupal.reverse_widget || {};
  Drupal.geocoder = new google.maps.Geocoder();
  Drupal.behaviors.geofield_widget = {
    attach : attach
  };
  // Search in Google Maps answer
  function getValueByKey(set, key) {
    var result = "";
    jQuery(set).each(function(i, item) {
      if (item.types[0] == key) {
        result = (key == "country" || key == "administrative_area_level_1") ? item.short_name : item.long_name;
      }
    });
    return result;
  }

  function updateMap(latLng) {
    if (Drupal.geocoder_map) {

      if (Drupal.geocoder_marker) {
        Drupal.geocoder_marker.setMap(null);
      }

      Drupal.geocoder_marker = new google.maps.Marker({
        map : Drupal.geocoder_map,
        position : latLng
      });

      // Set lat and lon
      jQuery(Drupal.settings.reverse_geocode_widget.lat).val(latLng.lat());
      jQuery(Drupal.settings.reverse_geocode_widget.lng).val(latLng.lng());

      Drupal.geocoder.geocode({
        'latLng' : latLng
      }, function(results, status) {
        if (status == google.maps.GeocoderStatus.OK) {
          if (results[0]) {
            var infowindow = new google.maps.InfoWindow();
            infowindow.setContent(results[0].formatted_address);
            infowindow.open(Drupal.geocoder_map, Drupal.geocoder_marker);

            Drupal.geocoder_marker.title = results[0].formatted_address;
            var set = results[0].address_components;
            Drupal.debuger = results[0];
            if (Drupal.settings.reverse_geocode_widget.field_address) {
              // Fill country field
              var country = getValueByKey(set, "country");
              var autochange = jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .country').val() != country;
              if (country) {
                jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .country option[value="' + country + '"]').attr("selected", "selected");
              }
              // Fill state field
              var state = getValueByKey(set, "administrative_area_level_1");
              if (state) {
                jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .state option').attr("selected", "");
                jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .state option[value="' + state + '"]').attr("selected", "selected");
              }

              // Fill address field
              var address = new Array();

              address.push(getValueByKey(set, "sublocality"));
              address.push(getValueByKey(set, "route"));
              address.push(getValueByKey(set, "street_number"));

              // Kill empty address components
              while (address.indexOf("") !== -1) {
                address.splice(address.indexOf(""), 1);
              }
              jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .thoroughfare').val('').val(address.join(", "));

              // Fill postal field
              jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .postal-code').val('').val(getValueByKey(set, "postal_code"));

              // Fill city field
              jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .locality').val('').val(getValueByKey(set, "locality"));

              if (autochange) {
                jQuery(Drupal.settings.reverse_geocode_widget.field_address + ' .country').change();
              }
            }

          } else {
            // Location not found
            var infowindow = new google.maps.InfoWindow();
            infowindow.setContent("Location not found");
            infowindow.open(Drupal.geocoder_map, Drupal.geocoder_marker);
          }
        } else {
          // Geocoding crashes
          var infowindow = new google.maps.InfoWindow();
          infowindow.setContent("Geocoder failed due to: " + status);
          infowindow.open(Drupal.geocoder_map, Drupal.geocoder_marker);
        }
      });
    }
  }

  function attach(context, settings) {
    jQuery('.geocode-widget').once().each(function(i, item) {
      var center = new google.maps.LatLng(Drupal.settings.reverse_geocode_widget.center_lat, Drupal.settings.reverse_geocode_widget.center_lng);
      if (Drupal.settings.reverse_geocode_widget.default_value.lat != '' && Drupal.settings.reverse_geocode_widget.default_value.lon != '') {
        center = new google.maps.LatLng(Drupal.settings.reverse_geocode_widget.default_value.lat, Drupal.settings.reverse_geocode_widget.default_value.lon);
      }
      // Initialize Google Map
      var myOptions = {
        zoom : parseInt(Drupal.settings.reverse_geocode_widget.zoom),
        center : center,
        mapTypeId : google.maps.MapTypeId.ROADMAP
      };

      // Initialize Google Map Geocoder
      Drupal.geocoder_map = new google.maps.Map(document.getElementById(jQuery(item).attr("id")), myOptions);

      if (Drupal.settings.reverse_geocode_widget.default_value.lat != '' && Drupal.settings.reverse_geocode_widget.default_value.lng != '') {
        Drupal.geocoder_marker = new google.maps.Marker({
          map : Drupal.geocoder_map,
          position : new google.maps.LatLng(Drupal.settings.reverse_geocode_widget.default_value.lat, Drupal.settings.reverse_geocode_widget.default_value.lon)
        });
      }

      google.maps.event.addListener(Drupal.geocoder_map, 'click', function(event) {
        updateMap(event.latLng, settings);
      });
    });
  }

}(jQuery));
