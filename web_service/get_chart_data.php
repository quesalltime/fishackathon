<?php
include_once 'DBclass.php';
$timeoffset = $_POST['timeoffset'];
date_default_timezone_set('UTC');
$timeoffset = 0;

$DBO = new c_database();
if ($DBO->__connect()) {
  $sql_query = "select a.*,b.bias_value from $table a left join akubic_device_record.bias_info b on a.bias_id=b.bias_id order by a.date_time;";
  $DBO->__query($sql_query);
  $cnt = $DBO->__get_numberofrows();
  for($i=0;$i<$cnt;$i++){
    $sql_result[] = $DBO->__get_row('assoc');
  }
  $DBO->__closelink();
}

unset($DBO);
$response = new \stdClass();

$response->series[0] = array();
$response->series[1] = array();
$response->series[2] = array();
$response->series[3] = array();
$response->series[4] = array();
$response->series[5] = array();
$response->series[6] = array();
$response->series[7] = array();

//"v":["TEMP","NH3","PH","TDS","GHca","GHmg","DO","ORP","ENVT","ENVH"]
foreach($sql_result as $k=>$v){
//  if($k==25)break;
  
  $response->series[0][$k]['id'] = $sql_result[$k]['index'];
  $response->series[0][$k]['check_md5'] = $sql_result[$k]['check_md5'];
  $response->series[0][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[0][$k]['y'] =  ValueCalibration("TEMP",(int)$sql_result[$k]['V1'])     ; //TEMP
  
  $response->series[1][$k]['id'] = $sql_result[$k]['index'];
  $response->series[1][$k]['check_md5'] = $sql_result[$k]['check_md5'];
  $response->series[1][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[1][$k]['y'] = rand(3,10)    ; //SA

  $response->series[2][$k]['id'] = $sql_result[$k]['index'];
  $response->series[2][$k]['check_md5'] = $sql_result[$k]['check_md5'];
  $response->series[2][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[2][$k]['y'] =  ValueCalibration("PH",(int)$sql_result[$k]['V3'])     ; //PH

  $response->series[3][$k]['id'] = $sql_result[$k]['index'];
  $response->series[3][$k]['check_md5'] = $sql_result[$k]['check_md5'];
  $response->series[3][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[3][$k]['y'] = rand(0,200)     ; //TDS
  
  $response->series[4][$k]['id'] = $sql_result[$k]['index'];
  $response->series[4][$k]['check_md5'] = $sql_result[$k]['check_md5'];
  $response->series[4][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[4][$k]['y'] = rand(5, 15)/10    ; //FLOW SPIKE

  $response->series[5][$k]['id'] = $sql_result[$k]['index'];
  $response->series[5][$k]['check_md5'] = $sql_result[$k]['check_md5'];  
  $response->series[5][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[5][$k]['y'] = rand(4,100)     ; //DO
  
  $response->series[6][$k]['id'] = $sql_result[$k]['index'];
  $response->series[6][$k]['check_md5'] = $sql_result[$k]['check_md5'];
  $response->series[6][$k]['x'] = (strtotime($sql_result[$k]['date_time'])-60*$timeoffset)*1000;
  $response->series[6][$k]['y'] = (int)$sql_result[$k]['V2']    ; //ORP
}


$response->sql = $sql_result;

echo json_encode($response);



function ValueCalibration($type,$value)
  {
    switch ($type) 
    {
      case "TEMP":
        $value = round((float)$value/16,2);
      break;
      case "PH":
        if($value<=645)$value = 14;
        else if($value>=1485)$value = 0;
//        else $value = round(($value*(-1/60) + (55/6)),1) + 1;
        else $value = round((-$value/60 + 24.75),1)-1;
        
        
//        if($value>180){
//          $value = ((float)$value-180)/1.5; //round(((float)$value-180)/1.5,2);
//        }
//        else{
//          $value = 0;
//        }
      break;  
      default:
      break;
    }
    return $value;
  }