<?php
$table = "akubic_device_record.record_FID9_DID106";
class c_database {
  private $link = false;
  private $result = false;
  private $servername = "";
  private $serverport = "3306";
  private $username = "";
  private $password = "";
  private $database = "";
  
  public $debugmode = false;
  public $errormsg = false;
  public $querystring = false;
  
  function __set_configuration($servername,$serverport,$username,$password,$database) {
    $this->servername = $servername;
    $this->serverport = $serverport;
    $this->username = $username;
    $this->password = $password;
    $this->database = $database;
  }
  function __set_readonly()
  {
    $this->servername = "venus";
  }
  function __connect() 
  {
    @mysql_connect($this->servername,$this->username,$this->password,true,/*MYSQL_CLIENT_SSL|*/MYSQL_CLIENT_COMPRESS);
    $this->link = @mysql_select_db($this->database);
    if (!$this->link) { // database link error
      $this->errormsg[] = mysql_error();
      $this->__error_haddle();
    }
    else {
      mysql_query('set names utf8');
    }
    return $this->link ? true : false;
  }
  function __begin_transaction() 
  {
    mysql_query("set AUTOCOMMIT=0");
    mysql_query("begin");
   // unset($this->querystring);
   // unset($this->errormsg);
    $this->querystring = false;
    $this->errormsg = false;
  }
  function __end_transaction() 
  {
    if ($this->debugmode) {
      mysql_query("rollback");
    }
    else {
      if (!$this->errormsg)
        mysql_query("commit");
      else {
        mysql_query("rollback");
        $this->__error_haddle();
      }
    }
  }
  function __query($sql)
  {
    $this->querystring[] = $sql;
    $this->result = mysql_query($sql);
    $error = mysql_error();
    if ($error) {
      $this->errormsg[] = $error;
    }
  }
  function __get_row($mode="") {
    if ($mode=='num')
      return mysql_fetch_row($this->result);
    else if ($mode=='assoc')
      return mysql_fetch_assoc($this->result);
    else
      return mysql_fetch_array($this->result);
  }
  function __get_numberofrows() {return mysql_num_rows($this->result);}
  function __get_fieldname() {return mysql_fetch_field($this->result);}
  function __error_haddle()
  {
    $query_string = "";
    $error_string = "";
    if($this->querystring)
      foreach ($this->querystring as $value) {
        $query_string .= ($value."\n ");
      }
    if($this->errormsg)  
    foreach ($this->errormsg as $value) {
      $error_string .= ($value."\n ");
    }
    $query_string = str_replace("'","\'", $query_string);
    $error_string = str_replace("'","\'", $error_string);
    $today = date("Ymd",time());
    $createTable = "CREATE TABLE if not exists `errorlog`.`$today` (
    `index` BIGINT NOT NULL ,
    `query` BLOB NOT NULL ,
    `error` BLOB NOT NULL ,
    `time` DATETIME NOT NULL ,
    PRIMARY KEY (  `index` )
    ) ENGINE = INNODB CHARACTER SET utf8 COLLATE utf8_general_ci;";
    mysql_query($createTable);
    mysql_query("set AUTOCOMMIT=0");
    mysql_query("begin");
    $sql = "select max(`index`) from `errorlog`.`$today`;";
    $result = mysql_query($sql);
    $counter = mysql_fetch_row($result);
    $counter = $counter[0] + 1;
    $sql = "insert into `errorlog`.`$today` values('$counter','$query_string','$error_string',now());";
    mysql_query($sql);
    mysql_query("commit");
  }
  function __closelink()
  {
    if (isset($this->result)) mysql_free_result($this->result);
    if (isset($this->link)) mysql_close();
  }
  function Get_Value($sql,$mode="") 
  {
    $this->__query($sql);
    $result = $this->__get_row($mode);
    return $result;
  }
  function Get_Value_Array($sql,$mode="") 
  {
    $result = array();
    $this->__query($sql);
    for ($i=0;$i<$this->__get_numberofrows();$i++)
      $result[] = $this->__get_row($mode);
    return $result;
  }
  function Show_Query_String() 
  {
    foreach ($this->querystring as $value) {
      echo $value."<BR>";
    }
  }
  function Show_Error_Message() 
  {
    foreach ($this->errormsg as $value) {
      echo $value."<BR>";
    }
  }
}
?>
