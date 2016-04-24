<?php
date_default_timezone_set('UTC');
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
    <script language="javascript" src="java/common.js"></script>  
    <script language="javascript" src="java/anychart.js"></script>  
    <script src="https://code.highcharts.com/stock/highstock.js"></script>
    <script src="https://code.highcharts.com/highcharts-more.js"></script>
    <script src="https://code.highcharts.com/highcharts-3d.js"></script>
    <script src="https://maps.googleapis.com/maps/api/js?key=AIzaSyAO8RjJjI_WQiwU2mp1fZmmmwgFO17EsPs&signed_in=true&callback=initMap" async defer></script>
    
    
    <title>AKUBIC</title>
    <script language="javascript">
      
    var chart_timer = null;
    var marker_timer = null;
    var map;
    var pin_icon = "image/pin_c.png";
    var akubic_pin = "image/b_pin.png";
    
    var akubic_sensor = [];
    
    var sensor_pos = [];
//    sensor_pos.push({lat:42.309,lng:-82.446})
//    sensor_pos.push({lat:42.281,lng:-82.644})
//    sensor_pos.push({lat:42.212,lng:-83.111})
//    sensor_pos.push({lat:42.155,lng:-83.106})
//    sensor_pos.push({lat:41.975,lng:-82.781})
//    
//    sensor_pos.push({lat:46.157,lng:-83.056})
//    sensor_pos.push({lat:46.172,lng:-82.776})
//    sensor_pos.push({lat:46.160,lng:-82.337})
//    sensor_pos.push({lat:44.774,lng:-79.716})
//    sensor_pos.push({lat:44.469,lng:-80.051})
//    
//    sensor_pos.push({lat:44.625,lng:-81.254})
//    sensor_pos.push({lat:44.071,lng:-81.743})
//    sensor_pos.push({lat:43.711,lng:-81.705})
//    sensor_pos.push({lat:43.456,lng:-81.699})
//    sensor_pos.push({lat:43.205,lng:-81.881})
//    
//    sensor_pos.push({lat:42.240,lng:-81.930})
//    sensor_pos.push({lat:42.629,lng:-81.183})
//    sensor_pos.push({lat:42.613,lng:-80.793})
//    sensor_pos.push({lat:42.577,lng:-80.436})
//    sensor_pos.push({lat:42.763,lng:-80.046})
//    
//    sensor_pos.push({lat:42.827,lng:-79.568})
//    sensor_pos.push({lat:44.733,lng:-79.796})
//    sensor_pos.push({lat:44.736,lng:-79.738})
    
    
    
//    sensor_pos.push({lat:,lng:-})
//    sensor_pos.push({lat:,lng:-})


akubic_sensor.push({lat:42.309,lng:-82.446})
    akubic_sensor.push({lat:42.281,lng:-82.644})
    akubic_sensor.push({lat:42.212,lng:-83.111})
    akubic_sensor.push({lat:42.155,lng:-83.106})
    akubic_sensor.push({lat:41.975,lng:-82.781})
    
    akubic_sensor.push({lat:46.157,lng:-83.056})
    akubic_sensor.push({lat:46.172,lng:-82.776})
    akubic_sensor.push({lat:46.160,lng:-82.337})
    akubic_sensor.push({lat:44.774,lng:-79.716})
    akubic_sensor.push({lat:44.469,lng:-80.051})
    
    akubic_sensor.push({lat:44.625,lng:-81.254})
    akubic_sensor.push({lat:44.071,lng:-81.743})
    akubic_sensor.push({lat:43.711,lng:-81.705})
    akubic_sensor.push({lat:43.456,lng:-81.699})
    akubic_sensor.push({lat:43.205,lng:-81.881})
    
    akubic_sensor.push({lat:42.240,lng:-81.930})
    akubic_sensor.push({lat:42.629,lng:-81.183})
    akubic_sensor.push({lat:42.613,lng:-80.793})
    akubic_sensor.push({lat:42.577,lng:-80.436})
    akubic_sensor.push({lat:42.763,lng:-80.046})
    
    akubic_sensor.push({lat:42.827,lng:-79.568})
    akubic_sensor.push({lat:44.733,lng:-79.796})
    akubic_sensor.push({lat:44.736,lng:-79.738})

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

  
akubic_sensor.push({lat:45.25362179991922,lng:-74.1851806640625})
akubic_sensor.push({lat:45.174292524076705,lng:-74.344482421875})
akubic_sensor.push({lat:45.09873027414909,lng:-74.48455810546875})
akubic_sensor.push({lat:45.00947686967287,lng:-74.871826171875})
akubic_sensor.push({lat:44.750634493861064,lng:-75.4266357421875})
akubic_sensor.push({lat:44.66474608911831,lng:-75.574951171875})
akubic_sensor.push({lat:44.90257799628887,lng:-75.1300048828125})
akubic_sensor.push({lat:44.549377532663684,lng:-75.706787109375})
akubic_sensor.push({lat:44.39454219215587,lng:-75.87982177734375})
akubic_sensor.push({lat:44.30812668488613,lng:-76.13525390625})
akubic_sensor.push({lat:44.23536047945612,lng:-76.278076171875})
akubic_sensor.push({lat:44.26683800273895,lng:-76.45523071289062})
akubic_sensor.push({lat:44.34054743171772,lng:-76.39892578125})
akubic_sensor.push({lat:44.3906169787868,lng:-76.33575439453125})
akubic_sensor.push({lat:44.45436907523842,lng:-76.30142211914062})
akubic_sensor.push({lat:44.50042343601631,lng:-76.24786376953125})
akubic_sensor.push({lat:44.39454219215587,lng:-76.50466918945312})
akubic_sensor.push({lat:46.1912395780416,lng:-79.859619140625})
akubic_sensor.push({lat:46.118941506107056,lng:-80.0518798828125})
akubic_sensor.push({lat:46.05417324177816,lng:-80.2056884765625})
akubic_sensor.push({lat:46.01222384063236,lng:-80.4583740234375})
akubic_sensor.push({lat:46.0007775685566,lng:-80.74951171875})
akubic_sensor.push({lat:46.18363372751014,lng:-81.3812255859375})
akubic_sensor.push({lat:46.293815562333684,lng:-81.2384033203125})
akubic_sensor.push({lat:46.37346430137336,lng:-81.0845947265625})
akubic_sensor.push({lat:46.32796494040749,lng:-83.375244140625})
akubic_sensor.push({lat:46.505954445520516,lng:-83.375244140625})
akubic_sensor.push({lat:46.29001987172955,lng:-82.9248046875})
akubic_sensor.push({lat:46.45678142812658,lng:-82.8863525390625})
  
akubic_sensor.push({lat:45.30193900072717,lng:-73.9764404296875})
akubic_sensor.push({lat:45.40616374516014,lng:-73.6907958984375})
akubic_sensor.push({lat:45.598665689820656,lng:-73.49853515625})
akubic_sensor.push({lat:45.82497145796607,lng:-73.3282470703125})
akubic_sensor.push({lat:46.01603873833416,lng:-73.1304931640625})
akubic_sensor.push({lat:46.126556302418514,lng:-72.9107666015625})
akubic_sensor.push({lat:46.244451065485094,lng:-72.66357421875})
akubic_sensor.push({lat:46.38483322349276,lng:-72.3504638671875})
akubic_sensor.push({lat:46.53997127029103,lng:-72.125244140625})
akubic_sensor.push({lat:46.638122462379634,lng:-71.7352294921875})
akubic_sensor.push({lat:46.702202151643455,lng:-71.3671875})
akubic_sensor.push({lat:46.81885778879604,lng:-71.070556640625})
akubic_sensor.push({lat:46.90524554642921,lng:-70.7958984375})
akubic_sensor.push({lat:47.178512264439085,lng:-70.37841796875})
akubic_sensor.push({lat:47.372314620566925,lng:-70.1806640625})
akubic_sensor.push({lat:47.63948497925488,lng:-69.906005859375})
akubic_sensor.push({lat:47.87214396888731,lng:-69.642333984375})
akubic_sensor.push({lat:48.09275716032735,lng:-69.27978515625})
akubic_sensor.push({lat:48.308774443523276,lng:-69.2962646484375})

var markers = [];
var marker_color_map = [];
marker_color_map[0] = "image/b_pin_low.png";
marker_color_map[1] = "image/b_pin_normal.png";
marker_color_map[2] = "image/b_pin_warn.png";
marker_color_map[3] = "image/b_pin_alert.png";

var pre_select = null;

function rand_sensor_value()
{
  for(var i in akubic_sensor){
    var level = 0;
    akubic_sensor[i].select = 0;
    akubic_sensor[i].TEMP =  Math.round(10*(Math.random()*3+15))/10;
    akubic_sensor[i].PH = Math.round(10*(Math.random()*2+6.5))/10;
    akubic_sensor[i].SA = Math.round(10*(Math.random()*7+3))/10;
    akubic_sensor[i].DO = Math.round(1*(Math.random()*96+4));
    akubic_sensor[i].ORP = Math.round(1*(Math.random()*200+200));
    akubic_sensor[i].FLOW = Math.round(1*(Math.random()*6+4))/10;
    akubic_sensor[i].TDS = Math.round(1*(Math.random()*200));
    
    akubic_sensor[i].lat = Math.round(1000*akubic_sensor[i].lat)/1000;
    akubic_sensor[i].lng = Math.round(1000*akubic_sensor[i].lng)/1000;
    akubic_sensor[i].ided = Math.round(3.6*233855*Math.pow(akubic_sensor[i].TEMP,-2.4915)*akubic_sensor[i].FLOW)
    akubic_sensor[i].mold = Math.round(3.6*22456*Math.pow(akubic_sensor[i].TEMP,-2.0989)*akubic_sensor[i].FLOW)
    akubic_sensor[i].picd = Math.round(3.6*233855*Math.pow(akubic_sensor[i].TEMP,-2.822)*akubic_sensor[i].FLOW)
    
    
    if(akubic_sensor[i].TEMP>17&&akubic_sensor[i].FLOW>0.7)level = 3;
    else if(akubic_sensor[i].TEMP>17&&akubic_sensor[i].FLOW<=0.7)level = 2;
    else if(akubic_sensor[i].TEMP<=17&&akubic_sensor[i].FLOW>0.7)level = 1;
    else if(akubic_sensor[i].TEMP<=17&&akubic_sensor[i].FLOW<=0.7)level = 0;
    markers[i].setIcon(marker_color_map[level]);
    akubic_sensor[i].level = level;
  }
  if(pre_select!=null){
    akubic_sensor[pre_select].select = 1;
    for(var i in akubic_sensor[pre_select]){
      $("#sensor_detail td.value#"+i+" span.v").text(akubic_sensor[pre_select][i]);
    }
    $("#ctrl_window .level").attr("id","_"+akubic_sensor[pre_select].level);
    $("#ctrl_window").attr("level",akubic_sensor[pre_select].level);
    markers[pre_select].setIcon("image/b_pin_select.png");
  }
}
function initMap() {
  map = new google.maps.Map(document.getElementById('map'), {
    center: {lat: 45.638, lng: -75.881},
    zoom: 6
  });
  
  var k = 0;
  for(var i in sensor_pos){
    var marker = new google.maps.Marker({
      position: sensor_pos[i],
      map: map,
      icon: pin_icon,
      metadata_id:k
    });
    marker.setMap(map);
    marker.addListener('click',get_marker_detail)
    k++;
  }
  
  for(var i in akubic_sensor){
    var marker = new google.maps.Marker({
      position: akubic_sensor[i],
      map: map,
      icon: akubic_pin,
      metadata_id:k
    });
    marker.setMap(map);
    marker.addListener('click',get_marker_detail)
    k++;
    markers.push(marker);
  }
  rand_sensor_value();
  window.clearInterval(marker_timer);marker_timer = null;
  marker_timer = setInterval(function () {rand_sensor_value();},5000);
  
}

  $(document).ready(function() {
    
    server_exchange("get_chart_data.php",{},function(){
//        console.log(this)
        var rtn_obj = this
        GetLineChart(rtn_obj.series,$("#chart-frame .plot"))
        },function(){
//          window.location = "";
        })
        
     $(".runingbt").bind("click",function(){
       if(!$(this).hasClass("active")){
         
         window.clearInterval(chart_timer);chart_timer = null;
          chart_timer = setInterval(function () {chart_timer_proc($(".plot").highcharts());},5000);
         
         $(this).addClass("active").html("STOP CAPTURE");
       }
       else{
         window.clearInterval(chart_timer);chart_timer = null;
          $(this).removeClass("active").html("START CAPTURE");
       }
     })   
        
        
  })
  
  

  </script>
  <link href="css/main.css" type="text/css" rel="stylesheet">
  </head>
  <body>
    <div id='main_container'>
      <div id="map"></div>
      <div level='' id="ctrl_window">
        <div class='level'></div>
        <table id='sensor_detail'>
          <tr><td class='title'>TEMP:</td><td id='TEMP' class='value'><span class='v'>0</span><span class='ind'>&#176;C</span></td></tr>
          <tr><td class='title'>SALINITY:</td><td id='SA' class='value'><span class='v'>0</span><span class='ind'>ppt</span></td></tr>
          <tr><td class='title'>PH:</td><td id='PH' class='value'><span class='v'>0</span><span class='ind'></span></td></tr>
          <tr><td class='title'>TDS:</td><td id='TDS' class='value'><span class='v'>0</span><span class='ind'>ppm</span></td></tr>
          <tr><td class='title'>FLOW SPIKE:</td><td id='FLOW' class='value'><span class='v'>0</span><span class='ind'>m/s</span></td></tr>
          <tr><td class='title'>DO:</td><td id='DO' class='value'><span class='v'>0</span><span class='ind'>%</span></td></tr>
          <tr><td class='title'>ORP:</td><td id='ORP' class='value'><span class='v'>0</span><span class='ind'>mv</span></td></tr>
          <tr><td class='title'>LAT:</td><td id='lat' class='value'><span class='v'>0</span><span class='ind'>&#176;</span></td></tr>
          <tr><td class='title'>LNG:</td><td id='lng' class='value'><span class='v'>0</span><span class='ind'>&#176;</span></td></tr>
          <tr><td class='title'>Idella Spawning Dist:</td><td id='ided' class='value'><span class='v'>0</span><span class='ind'>m</span></td></tr>
          <tr><td class='title'>Molitrix Spawning Dist:</td><td id='mold' class='value'><span class='v'>0</span><span class='ind'>m</span></td></tr>
          <tr><td class='title'>Piceus Spawning Dist:</td><td id='picd' class='value'><span class='v'>0</span><span class='ind'>m</span></td></tr>
        </table>
      </div>
      <div id='chart-frame'>
        <div id="chart-ctrl">
          <span style='margin-left:10px;' rel='0' id='TEMP' class='bt active'>TEMP</span>
          <span rel='1' id='SA' class='bt'>SALINITY</span>
          <span rel='2' id='PH' class='bt'>PH</span>
          <span rel='3' id='TDS' class='bt'>TDS</span>
          <span rel='4' id='FLOW' class='bt'>FLOW SPIKE</span>
          <span rel='5' id='DO' class='bt'>DO</span>
          <span rel='6' id='ORP' class='bt'>ORP</span>
          <span class='runingbt'>START CAPTURE</span>
        </div>
        <div style='height:300px;' class='plot'></div>
      </div>
      
      
    </div>
  </body>
</html>

