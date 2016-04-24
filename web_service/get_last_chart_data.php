<?php
include_once 'DBclass.php';
$timeoffset = $_POST['timeoffset'];
$timeoffset = 0;
$s_type = $_POST['s_type'];
date_default_timezone_set('UTC');
$index = $_POST['index'];

$s_type_map['TEMP'] = "V1";
$s_type_map['ORP'] = "V2";
$s_type_map['PH'] = "V3";
$s_type_map['SA'] = "V4";
$s_type_map['TDS'] = "V5";
$s_type_map['FLOW'] = "V6";
$s_type_map['DO'] = "V7";


$DBO = new c_database();
if ($DBO->__connect()) {
  $sql_query = "select `index`,`{$s_type_map["$s_type"]}` as 'data',`date_time`,`check_md5` from $table where `index`>'".((int)$index)." limit 1';";
  $DBO->__query($sql_query);
  $sql_result = $DBO->__get_row('assoc');
  $DBO->__closelink();
}
unset($DBO);
$response = new \stdClass();
$response->series  = false;

if($sql_result){
  if($s_type=="TEMP"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  ValueCalibration($s_type,(int)$sql_result['data'])     ; //TEMP
  }
  else if($s_type=="PH"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  ValueCalibration("PH",(int)$sql_result['data'])     ; //PH
  }
  else if($s_type=="DO"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  rand(4,100)     ; //DO
  }
  else if($s_type=="ORP"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  (int)$sql_result[$k]['V2']    ; //ORP
  }
  else if($s_type=="FLOW"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  rand(5, 15)/10    ; //FLOW SPIKE
  }
  else if($s_type=="SA"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  rand(3,10)    ; //SA
  }
  else if($s_type=="TDS"){
    $response->series['id'] = $sql_result['index'];
    $response->series['check_md5'] = $sql_result['check_md5'];
    $response->series['x'] = (strtotime($sql_result['date_time'])-60*$timeoffset)*1000;
    $response->series['y'] =  rand(0,200)     ; //TDS
  }
}



 $response->cindex = $index;
  
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
        if($value<=260)$value = 14;
        else if($value>=1100)$value = 0;
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
  