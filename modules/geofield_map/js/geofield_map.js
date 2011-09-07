(function ($) {
  Drupal.behaviors.geofieldMap = {
    attach: function(context) {
      var settings = Drupal.settings.geofieldMap;
      
      var myOptions = {
        zoom: 8,
        mapTypeId: google.maps.MapTypeId.ROADMAP
      };
      
      $('.geofieldMap:not(.processed)').each(function(index, element) {
        var data = undefined;
        for (var i in settings) {
          if (settings[i].map_id == $(element).attr('id')) {
            data = settings[i].data;
            break;
          }
        }
        
        if (data != undefined) {
          var markers = [];
          
          var map = new google.maps.Map(document.getElementById($(element).attr('id')), myOptions);
          
          
          var range = new google.maps.LatLngBounds();
      
          var infowindow = new google.maps.InfoWindow({
            content: ''
          });
          
          for (var i in data) {
            var point = new google.maps.LatLng(data[i].lat, data[i].lon);
            range.extend(point);
            var marker = new google.maps.Marker({
              position: point,
              map: map,
              title: "test"
            });
      
            if (data[i].icon != undefined) {
              marker.setIcon(data[i].icon);
            }
            marker.setValues({'data_id': i});
            
            google.maps.event.addListener(marker, 'click', function() {
              if (data[this.data_id].text) {
                infowindow.setContent(data[this.data_id].text);
                infowindow.open(map, this);
              }
            });
          }
          
          if (i > 0) {
            map.fitBounds(range);
          } else {
            map.setCenter(range.getCenter());
          }
        }
      });
    }
  }
})(jQuery);
