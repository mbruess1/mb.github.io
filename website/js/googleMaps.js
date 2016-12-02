var home = new google.maps.LatLng(50.937531, 6.960279);

function initialize() {
    var mapOptions = {
        center: home,
        zoom: 12,
        scrollwheel: false,
        draggable: false,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    };

    var map = new google.maps.Map(document.getElementById("googleMap"), mapOptions);

    var iconBase = 'http://maps.google.com/mapfiles/kml/pushpin/'; //http://kml4earth.appspot.com/icons.html
    var marker = new google.maps.Marker({
        position: home,
        title: "Cologne",
        icon: iconBase + 'blue-pushpin.png'
    });

    marker.setMap(map);
}

//google.maps.event.addDomListener(window, 'load', initialize);
map = new google.maps.Map(document.getElementById("googleMap"),
                          initialize);
