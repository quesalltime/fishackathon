<?php
//echo phpinfo();
//echo get_include_path();
//print_r($_SERVER);


?>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01//EN" "http://www.w3.org/tr/html4/strict.dtd">
<html>
  <head>
    <meta http-equiv="X-UA-Compatible" content="IE=EmulateIE9">
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
	  <link rel="shortcut icon" href="Image/favicon.ico">
    <link href='https://fonts.googleapis.com/css?family=Yanone+Kaffeesatz:400,300,200,700' rel='stylesheet' type='text/css'>
    <link href='https://fonts.googleapis.com/css?family=Archivo+Narrow:400,700' rel='stylesheet' type='text/css'>
    <script language="javascript" src="java/jquery-2.1.4.min.js"></script>  
    <script src="https://code.highcharts.com/stock/highstock.js"></script>
    <script src="https://code.highcharts.com/highcharts-more.js"></script>
    <script src="https://code.highcharts.com/highcharts-3d.js"></script>
    <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAO8RjJjI_WQiwU2mp1fZmmmwgFO17EsPs&signed_in=true&callback=initMap" async defer></script>
    
    
    <title>AKUBIC</title>
    <script language="javascript">
      
    $(document).ready(function() {
      
    })
    var map;
    var pin_icon = "image/pin_c.png";
    var akubic_pin = "image/b_pin.png";
    
    var akubic_sensor = [];
    
    var sensor_pos = [];
    sensor_pos.push({lat:42.309,lng:-82.446})
    sensor_pos.push({lat:42.281,lng:-82.644})
    sensor_pos.push({lat:42.212,lng:-83.111})
    sensor_pos.push({lat:42.155,lng:-83.106})
    sensor_pos.push({lat:41.975,lng:-82.781})
    
    sensor_pos.push({lat:46.157,lng:-83.056})
    sensor_pos.push({lat:46.172,lng:-82.776})
    sensor_pos.push({lat:46.160,lng:-82.337})
    sensor_pos.push({lat:44.774,lng:-79.716})
    sensor_pos.push({lat:44.469,lng:-80.051})
    
    sensor_pos.push({lat:44.625,lng:-81.254})
    sensor_pos.push({lat:44.071,lng:-81.743})
    sensor_pos.push({lat:43.711,lng:-81.705})
    sensor_pos.push({lat:43.456,lng:-81.699})
    sensor_pos.push({lat:43.205,lng:-81.881})
    
    sensor_pos.push({lat:42.240,lng:-81.930})
    sensor_pos.push({lat:42.629,lng:-81.183})
    sensor_pos.push({lat:42.613,lng:-80.793})
    sensor_pos.push({lat:42.577,lng:-80.436})
    sensor_pos.push({lat:42.763,lng:-80.046})
    
    sensor_pos.push({lat:42.827,lng:-79.568})
    sensor_pos.push({lat:44.733,lng:-79.796})
    sensor_pos.push({lat:44.736,lng:-79.738})
    
    
    
//    sensor_pos.push({lat:,lng:-})
//    sensor_pos.push({lat:,lng:-})

  akubic_sensor.push({lat:44.9609111593886,lng:-79.93377685546875})
akubic_sensor.push({lat:45.061881623213026,lng:-80.057373046875})
akubic_sensor.push({lat:45.19945769007777,lng:-80.14251708984375})
akubic_sensor.push({lat:45.4427897646004,lng:-80.386962890625})
akubic_sensor.push({lat:45.58328975600631,lng:-80.52978515625})
akubic_sensor.push({lat:45.75027686430363,lng:-80.6396484375})
akubic_sensor.push({lat:45.88044870856467,lng:-80.760498046875})
akubic_sensor.push({lat:45.92631906688103,lng:-81.199951171875})
akubic_sensor.push({lat:45.97406038956237,lng:-81.419677734375})
akubic_sensor.push({lat:46.03701597174875,lng:-81.7108154296875})
akubic_sensor.push({lat:46.08085173686787,lng:-81.96075439453125})
akubic_sensor.push({lat:45.33670190996811,lng:-80.2386474609375})
akubic_sensor.push({lat:43.80678314779554,lng:-79.08233642578125})
akubic_sensor.push({lat:43.620170616189924,lng:-79.3707275390625})
akubic_sensor.push({lat:43.40903821777056,lng:-79.6893310546875})
akubic_sensor.push({lat:43.84839376489157,lng:-78.804931640625})
akubic_sensor.push({lat:43.89393401411192,lng:-78.46435546875})
akubic_sensor.push({lat:43.95921358836687,lng:-77.93975830078125})
akubic_sensor.push({lat:44.010595521219145,lng:-77.6513671875})
akubic_sensor.push({lat:44.09744824027575,lng:-76.8768310546875})
akubic_sensor.push({lat:44.21764696919354,lng:-76.47308349609375})
akubic_sensor.push({lat:44.18417357325395,lng:-76.4813232421875})
akubic_sensor.push({lat:44.203866109361435,lng:-76.63787841796875})
akubic_sensor.push({lat:42.494377798972465,lng:-82.4908447265625})
akubic_sensor.push({lat:42.500453028125584,lng:-82.55126953125})
akubic_sensor.push({lat:42.427511326390906,lng:-81.705322265625})
akubic_sensor.push({lat:42.53891577257117,lng:-81.529541015625})
akubic_sensor.push({lat:42.64608143458068,lng:-80.98297119140625})
akubic_sensor.push({lat:42.65416193033991,lng:-80.3155517578125})
akubic_sensor.push({lat:42.809506838324204,lng:-79.837646484375})
akubic_sensor.push({lat:42.85381962412133,lng:-79.3707275390625})
akubic_sensor.push({lat:42.85381962412133,lng:-79.0740966796875})
akubic_sensor.push({lat:42.867912483915305,lng:-79.26910400390625})
akubic_sensor.push({lat:42.8699254870066,lng:-78.92852783203125})
akubic_sensor.push({lat:42.577354839557856,lng:-80.60943603515625})
akubic_sensor.push({lat:42.23055108552289,lng:-82.11456298828125})
akubic_sensor.push({lat:42.14304156290939,lng:-82.32330322265625})
akubic_sensor.push({lat:41.990118840968094,lng:-82.4853515625})
akubic_sensor.push({lat:42.01052981889534,lng:-83.00994873046875})
akubic_sensor.push({lat:42.12267315117256,lng:-83.111572265625})
akubic_sensor.push({lat:42.071723466810774,lng:-83.11431884765625})
akubic_sensor.push({lat:42.04317376494972,lng:-83.11981201171875})
akubic_sensor.push({lat:43.006655665959244,lng:-82.33154296875})
akubic_sensor.push({lat:43.066881271984954,lng:-82.1832275390625})
akubic_sensor.push({lat:43.16712591500031,lng:-82.03765869140625})
akubic_sensor.push({lat:43.31318813919643,lng:-81.78497314453125})
akubic_sensor.push({lat:43.834526782236814,lng:-81.73004150390625})
akubic_sensor.push({lat:44.01257086123087,lng:-81.74102783203125})
akubic_sensor.push({lat:44.231424604494165,lng:-81.59271240234375})
akubic_sensor.push({lat:44.36509667482153,lng:-81.54327392578125})
akubic_sensor.push({lat:44.54742015866826,lng:-81.331787109375})
akubic_sensor.push({lat:44.958967675170506,lng:-81.37847900390625})
akubic_sensor.push({lat:45.15880073835211,lng:-81.595458984375})
akubic_sensor.push({lat:44.76428680790121,lng:-81.30706787109375})
akubic_sensor.push({lat:44.89285004222294,lng:-81.35650634765625})
akubic_sensor.push({lat:44.54742015866826,lng:-80.386962890625})
akubic_sensor.push({lat:44.5924231071787,lng:-80.57647705078125})
akubic_sensor.push({lat:44.60415728007794,lng:-80.892333984375})
akubic_sensor.push({lat:44.69794535297578,lng:-80.92254638671875})
akubic_sensor.push({lat:44.809121700077355,lng:-79.92828369140625})
akubic_sensor.push({lat:44.85002749260051,lng:-80.08758544921875})
akubic_sensor.push({lat:44.76623687516233,lng:-80.1617431640625})
akubic_sensor.push({lat:44.60024615241099,lng:-80.02166748046875})
akubic_sensor.push({lat:46.210249600187204,lng:-83.3203125})
akubic_sensor.push({lat:46.25584681848034,lng:-83.64990234375})
akubic_sensor.push({lat:46.28622391806708,lng:-83.84765625})
akubic_sensor.push({lat:43.897892391257976,lng:-77.376708984375})
akubic_sensor.push({lat:43.82660134505384,lng:-77.080078125})
akubic_sensor.push({lat:43.977004674964085,lng:-76.83837890625})
akubic_sensor.push({lat:43.23019571266878,lng:-79.2169189453125})
akubic_sensor.push({lat:43.1811470593997,lng:-79.37347412109375})
akubic_sensor.push({lat:43.29020157325698,lng:-79.86442565917969})
akubic_sensor.push({lat:43.28320393686986,lng:-79.80812072753906})
akubic_sensor.push({lat:43.25920592943641,lng:-79.08645629882812})
akubic_sensor.push({lat:43.226193219295475,lng:-79.62615966796875})

    
    
function initMap() {
  map = new google.maps.Map(document.getElementById('map'), {
    center: {lat: 43.638, lng: -82.381},
    zoom: 7
  });
  
  for(var i in sensor_pos){
    var marker = new google.maps.Marker({
      position: sensor_pos[i],
      map: map,
      icon: pin_icon
    });
    marker.setMap(map);
  }
  
  for(var i in akubic_sensor){
    var marker = new google.maps.Marker({
      position: akubic_sensor[i],
      map: map,
      icon: akubic_pin
    });
    marker.setMap(map);
  }
  
  
  map.addListener('click', function(e) {
//    var lat = e.latLng.lat();
//    var lng = e.latLng.lng();
//    console.log(lat,lng)

    var marker = new google.maps.Marker({
      position: {lat: e.latLng.lat(), lng: e.latLng.lng()},
      map: map,
      icon: akubic_pin
    });
    marker.setMap(map);
    $("#ta").val($("#ta").val()+"akubic_sensor.push({lat:"+e.latLng.lat()+",lng:"+e.latLng.lng()+"})\n");
  });
  map.addListener('mousemove', function(e) {
    var lat = e.latLng.lat();
    var lng = e.latLng.lng();
    $("#lat_v").text(lat);
    $("#lng_v").text(lng);
  });
  
  //marker.addListener('click', function()
}

  </script>
  <link href="css/main.css" type="text/css" rel="stylesheet">
  </head>
  <body>
    <div id='main_container'>
      <div style='width:1000px;height:1000px;' id="map"></div>
      <table id='cord-t'>
        <tr><td class='title'>lat</td><td id='lat_v' class='value'></td></tr>
        <tr><td class='title'>lng</td><td id='lng_v' class='value'></td></tr>
      </table>
      <textarea style='position:absolute;top:100px;right:200px;width:300px;height:400px; ' id='ta'></textarea>>
    </div>
  </body>
</html>

