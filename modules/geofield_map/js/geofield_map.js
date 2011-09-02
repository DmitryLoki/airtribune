(function ($) {
  $(document).ready(function() {
    var settings = Drupal.settings.geofield_map;
    var data = settings.data;
    var markers = [];
    
    var latlng = new google.maps.LatLng(41, -80);
    var myOptions = {
      zoom: 8,
      center: latlng,
      mapTypeId: google.maps.MapTypeId.ROADMAP
    };
    var map = new google.maps.Map(document.getElementById(settings.map_id),
        myOptions);
    
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
  });
})(jQuery);
