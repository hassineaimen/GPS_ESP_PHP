<?php
	$file1 = 'test1.txt';
	$file2 = 'test2.txt';
	//date_default_timezone_set('Australia/Melbourne');
	if (file_exists($file1)){
		$tempdata1 = file_get_contents($file1);
		//$lastmodified = "Last captured: ".date ("d M y h:i:s. A", filemtime($file));
	}
	if (file_exists($file2)){
		$tempdata2 = file_get_contents($file2);
		//$lastmodified = "Last captured: ".date ("d M y h:i:s. A", filemtime($file));
	}
	//echo $tempdata1;
	//echo "<br>";
	//echo $tempdata2;
	?>
  <html>
  <head>
    <style>
       #map {
        height: 400px;
        width: 100%;
       }
    </style>
  </head>
  <body>
    <h3>QTAG MAP</h3>
    <div id="map"></div>
    <script>
      function initMap() {
		 var uluru = {lat: <?php echo $tempdata1 ; ?> , lng: <?php echo $tempdata2; ?>}; 
        //var uluru = {lat: 46.3199577, lng: -72.5767136};
        var map = new google.maps.Map(document.getElementById('map'), {
          zoom: 15,
          center: uluru
        });
        var marker = new google.maps.Marker({
          position: uluru,
          map: map
        });
      }
    </script>
    <script async defer
    src="https://maps.googleapis.com/maps/api/js?key=AIzaSyDZpqo--to4O5Y3cdVj1cUpkSWEkQFa-5I&callback=initMap">
    </script>
  </body>
</html>
