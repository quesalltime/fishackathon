function GetLineChart(data,parent)
{
  var profile = {};
  profile.v = [];
  profile.v[0] = "TEMP";
  profile.v[1] = "SA";
  profile.v[2] = "PH";
  profile.v[3] = "TDS";
  profile.v[4] = "FLOW SPIKE";
  profile.v[5] = "DO";
  profile.v[6] = "ORP";
  
  var color_map = [];
  color_map[0] = "#7cb5ec";
  color_map[1] = "#90ed7d";
  color_map[2] = "#2b908f";
  color_map[3] = "#f45b5b";
  color_map[4] = "#91e8e1";
  color_map[5] = "#79b018";
  color_map[6] = "#f5e425";
  var range_map = [];
  range_map[0] = {min:15,max:30};
  range_map[1] = {min:0,max:15};
  range_map[2] = {min:0,max:14};
  range_map[3] = {min:0,max:200};
  range_map[4] = {min:0,max:2};
  range_map[5] = {min:0,max:100};
  range_map[6] = {min:0,max:500};
  
  var series = [];
//  for(var i in profile.v){
//    series.push({
//      name : profile.v[i],
//      data : data[i],
//      tooltip: {
//          valueDecimals: 1
//      }
//    })
////    break;
//  }
//  
  
  series[0] = {
    name : profile.v[0],
    data : data[0],
    tooltip: {
        valueDecimals: 1
    },
    color: color_map[0],
    point: {
        events: {
            click: chart_point_click
        }
    }
  }

  
  parent.highcharts('StockChart', {
    
    chart: {
      events: {
        load: function () {
//          var series = this.series[0];
        //    window.clearInterval(chart_timer);chart_timer = null;
          //  chart_timer = setInterval(function () {chart_timer_proc(parent.highcharts());},1000);
        },
        redraw:function(e){
//          console.log(e,this)
        }
      }
    },
    credits: {
      enabled: false
    },
    
    
    
    rangeSelector : {
        selected : 1
    },

    title : {
        text : ''
    },
    series : series,
    yAxis:range_map[0],
    
  })
  $(".bt").bind("click",function(){
    if($(this).hasClass("active"))return false;
    var id = $(this).attr("rel");
    $(this).parent().find(".bt.active").removeClass("active")
    $(this).addClass("active");
//     parent.highcharts().destroy();
    parent.highcharts('StockChart', {
    
    chart: {
      events: {
        load: function () {
          //window.clearInterval(chart_timer);chart_timer = null;
          //chart_timer = setInterval(function () {chart_timer_proc(parent.highcharts());},1000);
        },
        redraw:function(e){
//          console.log(e,this)
        }
      }
    },
    credits: {
      enabled: false
    },
    
    
    
    rangeSelector : {
        selected : 1
    },

    title : {
        text : ''
    },
    //yAxis:range_map[id],
    
  })
    
  parent.highcharts().addSeries({
      name : profile.v[id],
      data : data[id],
      tooltip: {
          valueDecimals: 1
      },
      color: color_map[id],
      point: {
        events: {
            click: chart_point_click
        }
      }
    });  
    
    
//    while(chart.series.length){
//      for(var i in chart.series)chart.series[i].remove();
//    }
    
    
//    chart.addSeries({
//      name : profile.v[id],
//      data : data[id],
//      tooltip: {
//          valueDecimals: 1
//      },
//      color: color_map[id],
//    });
//    chart.yAxis[0].update(range_map[id]); 

//    chart.yAxis[0].setExtremes(range_map[id].min,range_map[id].max);
  })
  
}

get_marker_detail = function(e)
{
  var m_id = this.metadata_id;
  $(".bt").eq(0).trigger("click");
//  console.log(akubic_sensor[this.metadata_id],this)
//  this.setIcon("image/b_pin_alert.png");
//   myMarkers[destinationID].setIcon(otherIcon)

  for(var i in akubic_sensor){
    markers[i].setIcon(marker_color_map[akubic_sensor[i].level]);
  }
  for(var i in akubic_sensor[this.metadata_id]){
    $("#sensor_detail td.value#"+i+" span.v").text(akubic_sensor[this.metadata_id][i]);
  }
  pre_select = this.metadata_id;
  
  if(akubic_sensor[pre_select].TEMP>17&&akubic_sensor[pre_select].FLOW>0.7)level = 3;
  else if(akubic_sensor[pre_select].TEMP>17&&akubic_sensor[pre_select].FLOW<=0.7)level = 2;
  else if(akubic_sensor[pre_select].TEMP<=17&&akubic_sensor[pre_select].FLOW>0.7)level = 1;
  else if(akubic_sensor[pre_select].TEMP<=17&&akubic_sensor[pre_select].FLOW<=0.7)level = 0;
  akubic_sensor[pre_select].level = level;
  $("#ctrl_window .level").attr("id","_"+akubic_sensor[pre_select].level);
  $("#ctrl_window").attr("level",akubic_sensor[pre_select].level);
  markers[pre_select].setIcon("image/b_pin_select.png");


}
chart_point_click = function(e)
{
//  console.log(this)
}
function chart_timer_proc(chart)
{
  server_exchange("get_last_chart_data.php",{index:chart.series[0].data[chart.series[0].data.length-1].id,s_type:$("#chart-ctrl .bt.active").attr("id")},function(){
    if(this.series){
      chart.series[0].addPoint(this.series, true, true);
      chart.series[1].addPoint(this.series, true, true);
    }
  },function(){
//          window.location = "";
  })
}