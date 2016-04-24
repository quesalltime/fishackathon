/*
  Software serial multple serial test

 Receives from the hardware serial, sends to software serial.
 Receives from software serial, sends to hardware serial.

 The circuit:
 * RX is digital pin 10 (connect to TX of other device)
 * TX is digital pin 11 (connect to RX of other device)

 Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).

 created back in the mists of time
 modified 25 May 2012
 by Tom Igoe
 based on Mikal Hart's example

 This example code is in the public domain.

 */
#include <avr/pgmspace.h> 
#include <EEPROM.h>
#include <Wire.h>
#include <assert.h>
#include <SoftwareSerial.h>
#include "akubic.h"




#define __SHOW_LOG__  1

SoftwareSerial mySerial(4, 5); // RX, TX

#define esp mySerial
#define dbg Serial

#if  __SHOW_LOG__
long int  total = 0,lSuccess=0;
#endif//  


uint8_t Timer_count = 0;
uint8_t min_count = 0;

const uint8_t ledPin =  13;         // LED pin
const uint8_t RST_PIN = 3;      // Reset pin
const uint8_t INT_PIN = 2;

boolean Serial_in_loop = false;
boolean bRouting = false;
uint8_t bSendData = 0;
unsigned int sample_rate;


boolean input_mode = false;




void setup() {
  esp.begin(9600); //RX1 TX1，即 Pin18 及 Pin19
  dbg.begin(9600);
  dbg.println(F("Arduino START"));
  pinMode(ledPin, OUTPUT);      // 把 ledPin 設置成 output pin
 
  // init esp8266 reset pin
  pinMode(RST_PIN,OUTPUT);
  digitalWrite(RST_PIN,HIGH);

  pinMode(INT_PIN,OUTPUT);
  digitalWrite(INT_PIN,HIGH);
   
  parameter_init();  
  get_base_id();
  dbg.println(F("BASE ID"));
  dbg_eeprom(BASE_ID,2);
  
  timer_init();
  i2c_init();
  reset_wifi();  
  
  
}

void get_base_id(){
  //char base_id[2];
  //base_id[0] = 0x08;  
  //base_id[1] = 0xDA;
  unsigned int base_id = 0x2200;
  EEPROM.put(BASE_ID,base_id);
  
}



void parameter_init(){
  uint16_t i;
  ssid_size = 0;
  pwd_size = 0;
  
  EEPROM.write(RSP,0);
  EEPROM.write(PIC_ACT,0);
  EEPROM.write(DEVICE_ID,SLAVE_ID); 
  EEPROM.write(SW_V,SW_VERSION);
  EEPROM_readAnything(SERIAL_NUMBER,sn,8);
  


#if  __SHOW_LOG__
  dbg.print(EEPROM.read(DEVICE_ID),HEX);
  dbg.println(F(""));
  dbg.print(EEPROM.read(SW_V),HEX);
  dbg.println("");  
#endif
}
void timer_init(){
  TCCR1A = 0x00;                // Normal mode, just as a Timer
  TCCR1B &= ~_BV(CS12);         // no prescaling
  TCCR1B &= ~_BV(CS11);      
  TCCR1B |= _BV(CS10);    
  TIMSK1 |= _BV(TOIE1);         // enable timer overflow interrupt
  TCNT1 = 0;  
}
void i2c_init(){
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event  
}

void loop() {


  if(bSendData > 0){
    if(bSendData == BIT0){
      dbg.println(F("Send Data MODE_REQUEST"));
      send_data(MODE_REQUEST);  
    }else if(bSendData == BIT1){   // PIC_ACT
      dbg.println(F("goto BIT2"));
      dbg.println(EEPROM.read(PIC_ACT) );
      dbg.println(F("----"));
      
      if(EEPROM.read(PIC_ACT) == BIT0){
        dbg.println(F("GOTO PIC_ACT SETAP"));  
        memset(ssid,0,32);
        memset(pwd,0,10);
        EEPROM_readAnything(WIFI_SSID,ssid,ssid_size);
        EEPROM_readAnything(WIFI_PWD,pwd,pwd_size);
        dbg.println(ssid);
        dbg.println(pwd);
        dbg.println(F("--------------"));
        if(connectWifi(ssid,pwd) != RECV_SUCCESS){
          dbg.println(F("RESET FAIL"));  
          setBit(RSP,BIT4);
        }
        EEPROM.write(PIC_ACT,0);
        Notify_host();  
      }else if(EEPROM.read(PIC_ACT) == BIT1){
        dbg.println(F("GOTO PIC_ACT CNCT"));  
        EEPROM.write(PIC_ACT,0);
        connection_check();
      }else if(EEPROM.read(PIC_ACT) == BIT2){
        dbg.println(F("GOTO PIC_ACT REG")); 
        EEPROM.write(PIC_ACT,0);  
        send_data(MODE_INSTALL);  
      }else if(EEPROM.read(PIC_ACT) == BIT3){
          dbg.println(F("GOTO PIC_ACT Adjust Time")); 
          EEPROM.write(PIC_ACT,0x01);
          send_data(MODE_ADJ_TIME);  
      }else if(EEPROM.read(PIC_ACT) == BIT4){
        dbg.println(F("GOTO PIC_ACT reset ESP8266"));   
        EEPROM.write(PIC_ACT,0);
        reset_wifi(); 
      }else{
        
      }
     
    }
    
    bSendData  = 0;  
  }
  if( min_count >= 4 && bRouting){
    //routing();
    send_data();
#if  __SHOW_LOG__
  total++;
  dbg.print(F("total = "));
  dbg.print(total);
  dbg.print(F(" ,success = "));
  dbg.print(lSuccess);
  
#endif
    min_count = 0;  
  }

  
  if (esp.available() && Serial_in_loop)
  {
    char cc = esp.read();

    dbg.write(cc);
    
  }

  if(input_mode){
    if (dbg.available() ) 
    {
      char chars = dbg.read();
      dbg.write(chars);    
      if(chars == 'z'){
        input_mode = false;
        dbg.println(F("return switch case"));  
      }
    }
  }else{
  
    if (dbg.available() ) 
    {
      char chars = dbg.read();
      Serial_in_loop = false;
      memset(recvBuffer,0,sizeof(recvBuffer));
      switch(chars){
        case 'z':
         input_mode = true;
        break;
        case 't':
          AT();
        break;
        case 'x':
          Serial_in_loop = true;
          strcpy(recvBuffer,"AT+CWLAP\r\n");
        break;
        case 'm':
          esp.print(F("AT+CWMODE=1\r\n"));
          dbg.println(F("Wait AT+CWMODE"));
          recv(10000);
        break;
        case 'e': // HW RST
          reset_wifi();
        break;
       
        case '1': // RST
          ATRST();
        break;      
        case '2':  //ip
          esp.print(F("AT+CIFSR\r\n"));
          dbg.println(F("Wait AT+CIFSR"));
          recv(10000,"OK\r\n");
          dbg.println(F("Finish AT+CIFSR"));
        break;
        case '3':
          bRouting = !bRouting;
          if(bRouting){
            min_count = 5;
            total = lSuccess = 0;
           // dbg.println("Start Testing .. ");
            dbg.println(F("-------------------------------------"));
            dbg.println(F("-  start Testing                    -"));
            dbg.println(F("-------------------------------------"));
          }else{
            dbg.println(F("Finish Testing .. "));
          }
          break;
         case 'v':
          dbg.println(F("GET REQUEST"));
          send_data(MODE_REQUEST); 
          break;
         case 'u':  // install
         dbg.println(F("INSTALL process"));
         send_data(MODE_INSTALL);
         break;
         case 'w':
          dbg.println(F("ADJ TIME"));
          send_data(MODE_ADJ_TIME);
          dbg.println(F("--------"));
          dbg.println(F("READ Current Time"));
          for(int k = 0; k < 7 ; k++){
              dbg.print(F(" -> 0x")); 
              dbg.print(EEPROM.read(CTIME_Y_H+k),HEX);
              dbg.println(F(""));
          }
         break;
         case '6':
          dbg.println(F("start AT+CWJAP test"));
          esp.print(F("AT+CWJAP?\r\n"));
          recv(5000);
         break;
         case '7':
          dbg.println(F("start Connection test"));
          if(ATCIPSTART("discover.r3dstar.com",80) == RECV_SUCCESS){
            ATCIPCLOSE(); 
          }else{
            dbg.println(F("NONO Connection"));  
          }
         
          dbg.println(F("Finish Connection test"));
         break;
         case '8':
          dbg.println(F("start CIPSTATUS test"));
          esp.print(F("AT+CIPSTATUS\r\n"));
          recv(10000);
         break;
         case '9':
          Notify_host();
         break;

        case 'p':
          dbg.println(F("connect to Make11F"));
          connectWifi("Make11F","synMakeEl");
          recv(5000);
         break;
        
      }
      if(strlen(recvBuffer) > 0 && Serial_in_loop){
        dbg.println(F("Start send command ... "));
        esp.print(recvBuffer);
      }
      
     
    }
  }
}

ISR (TIMER1_OVF_vect)
{ 
  Timer_count++;
  if (Timer_count == 244) {             // overflow frequency = 16 MHz/65536 = 244Hz
    PORTB ^= _BV(5);              // Toggle LED, PB5 = Arduino pin 13
    Timer_count = 0;
    min_count++;
    
  } 
}


void reset_wifi(){
  digitalWrite(RST_PIN,LOW);
  delay(2000);
  digitalWrite(RST_PIN,HIGH);
  if(recv(5000,"ready") == RECV_SUCCESS){
    dbg.println(F("RESET FINISH!!"));
  }else{
    dbg.println(F("RESET FAIL"));  
    setBit(RSP,BIT6);
    
  }
   Notify_host();
}

void Notify_host(){
  dbg.println(F("NOTIFY HOST"));
  dbg.print(F("RSP 0x"));
  dbg.println(EEPROM.read(RSP),HEX);
  dbg.print(F("PIC_ACT 0x"));
  dbg.println(EEPROM.read(PIC_ACT),HEX);
  dbg.println(F("----"));
  digitalWrite(INT_PIN,LOW);
  delay(1);
  digitalWrite(INT_PIN,HIGH);
  
}

byte send_data(byte mode){
  unsigned long t=millis();
  uint8_t result;
  unsigned char adj_time = 0 ;
  int cnt;
  Serial_in_loop = false;
  int content_length;
  memset(recvBuffer,0,sizeof(recvBuffer));
  if(mode == MODE_ADJ_TIME)
    adj_time = 1;
  dbg.println(F("----------------"));
  result = ATCIPSTART("discover.r3dstar.com",80);
  dbg.println(result);

  if(result != RECV_SUCCESS){
    dbg.println(F("fail"));
    setBit(RSP,BIT5);
    Notify_host();
    return false;    
  }

  dbg.println(F("----------------"));


  EEPROM_readAnything(SERIAL_NUMBER,test_obj.sn,8);
  //memcpy(test_obj.sn,sn,8);
  test_obj.sn[8] = '\0';
// parameter[8]
  for(cnt = 0;cnt < 8;cnt++){
    test_obj.parameter[cnt] = (EEPROM.read(SENSOR_VAL+cnt*2) << 8) + EEPROM.read(SENSOR_VAL+cnt*2+1);
  }
  // datetime[7]
  for(cnt = 0;cnt < 7;cnt++){
    test_obj.datetime[cnt] = ((EEPROM.read(MTIME_Y_H+cnt) >> 4) *10) + ( EEPROM.read(MTIME_Y_H+cnt) % 16) ;
  }

  test_obj.error = (EEPROM.read(ERR_PIC1)<<8) + EEPROM.read(ERR_PIC1+1);

  memset(dataBuffer,0,sizeof(dataBuffer));
  memset(recvBuffer,0,sizeof(recvBuffer));
   if(mode == MODE_INSTALL){
  
  unsigned long facility_id = ((unsigned long)EEPROM.read(FACILITY_ID) << 16) + ((unsigned long)EEPROM.read(FACILITY_ID+1)<<8) + EEPROM.read(FACILITY_ID+2);
  
  unsigned int base_id  = (EEPROM.read(BASE_ID)<<8) + EEPROM.read(BASE_ID+1);
  sprintf(dataBuffer,"data={\"facility_id\":\"%lu\",\"base_id\":%d}\r\n\r\n",facility_id,base_id);


    sprintf(recvBuffer,"%d\r\n\r\n%s",strlen(dataBuffer),dataBuffer);
    P(install) = "POST /akubic/api/1.00/Install.php HTTP/1.1\r\nHost: discover.r3dstar.com\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";
  
    printP(install);
    for (cnt =0;cnt < strlen(recvBuffer);cnt++){
      EEPROM.write(0x200+strlen_P(install)+cnt,recvBuffer[cnt]);      
    }  
    content_length = strlen_P(install) + strlen(recvBuffer);
    
  }
  else{
    // if(mode == MODE_REQUEST){
  sprintf(dataBuffer,"data={\"sn\":\"%s\",\"d\":[%d,%d,%d,%d,%d,%d,%d,%d],\"t\":[%d,%d,%d,%d,%d,%d,%d],\"e\":%d,\"r\":%d}\r\n\r\n",
  test_obj.sn,
  test_obj.parameter[0],test_obj.parameter[1],test_obj.parameter[2],test_obj.parameter[3],
  test_obj.parameter[4],test_obj.parameter[5],test_obj.parameter[6],test_obj.parameter[7],
  test_obj.datetime[0],test_obj.datetime[1],test_obj.datetime[2],test_obj.datetime[3],
  test_obj.datetime[4],test_obj.datetime[5],test_obj.datetime[6],test_obj.error,
  adj_time);

  sprintf(recvBuffer,"%d\r\n\r\n%s",strlen(dataBuffer),dataBuffer);
  P(request) = "POST /akubic/api/1.00/GetRequest.php HTTP/1.1\r\nHost: discover.r3dstar.com\r\nContent-Type: application/x-www-form-urlencoded\r\nContent-Length: ";

  printP(request);
  for (cnt =0;cnt < strlen(recvBuffer);cnt++){
    EEPROM.write(0x200+strlen_P(request)+cnt,recvBuffer[cnt]);      
  }  
  content_length = strlen_P(request) + strlen(recvBuffer);
  }

  
  
  if(ATCIPSEND(content_length) != RECV_SUCCESS){
    dbg.println(F("\r\nATCIPSEND FAIL"));
    ATCIPCLOSE();
    setBit(RSP,BIT5);
    Notify_host();
    return false;  
  }
  
  

  
    memset(dataBuffer,0,sizeof(dataBuffer));
    

    getString(dataBuffer,recvBuffer,getPosition(recvBuffer,'{')+1,getPosition(recvBuffer,'}')-1);
    dbg.println(F("String split"));
    dbg.println(dataBuffer);
    char** tokens;
    char ** numbers;
    uint8_t i;
    tokens = str_split(dataBuffer, '#');

    if (tokens)
    {
      dbg.println(F("GET INTO TOKENS"));
      res_obj.status = atoi(*(tokens));

      EEPROM.write(RSP,res_obj.status);
      dbg.println(F("\r\nGET status"));
      dbg_eeprom(RSP,BIT0);
      
      memcpy(res_obj.sn,*(tokens+2),8);
      res_obj.sample_rate = atoi(*(tokens+3));
      
      EEPROM.get(SAMPLE_RATE,sample_rate);
      dbg.println(F("OLD sample rate"));
      dbg.println(sample_rate);
      if(sample_rate != res_obj.sample_rate && res_obj.status == 0){
        dbg.println(F("change SAMPLE_RATE"));
        EEPROM.put(SAMPLE_RATE,res_obj.sample_rate);  
        setBit(PIC_ACT,BIT1);
      }
      
      dbg.println(F("\r\nGET SAMPLE_RATE"));
      dbg_eeprom(SAMPLE_RATE,2);
      res_obj.device_request = atoi(*(tokens+4));
      res_obj.request_detail = atoi(*(tokens+5));

      if(mode == MODE_INSTALL){
        if( res_obj.status == 0){
          set_eeprom(SERIAL_NUMBER,res_obj.sn,8);
          dbg.println(F("-----"));
          dbg.println(F("SN"));
          for (i = 0; i < 8; i++){
            dbg.write(EEPROM.read(SERIAL_NUMBER+i));  
          }
          dbg.println(F("\r\n-----"));  
          EEPROM.put(SAMPLE_RATE,res_obj.sample_rate);  
        }
        //setRSP(BIT1);
        
        setBit(PIC_ACT,BIT1);
      }

      
      dbg.println(F("---------------"));
      dbg.println(res_obj.status);
      dbg.println(res_obj.sample_rate);
      dbg.println(res_obj.sn);
      dbg.println(res_obj.device_request);
      dbg.println(res_obj.request_detail);
      dbg.println(F("---------------"));
        
        for (i = 0; *(tokens + i); i++)
        {

            dbg.print(i);
            dbg.print(F(" : "));
            if(i==1){
                
              dbg.println(*(tokens + i));
              dbg.println(F("Split detail"));
              numbers  = str_split(*(tokens + i), ','); 
               if(numbers){
                int j;
                for (j = 0; *(numbers + j); j++)
                {  
                  uint8_t cc = atoi(*(numbers + j));
                  res_obj.current_time[j] = cc/10*16+cc%10;
                  dbg.print(*(numbers + j)); 
                  dbg.print(F(" -> 0x")); 
                  dbg.print(res_obj.current_time[j],HEX);
                  EEPROM.write(CTIME_Y_H+j,res_obj.current_time[j]);
                  dbg.println(F(""));  
                  free(*(numbers + j));
                }
                 free(numbers);
              }
                dbg.println(F("Finish sub split"));
            }else if(i != 2){
              int ccc = atoi(*(tokens + i));
              dbg.print(F("<number> "));
              dbg.println(ccc);
            }else{
              dbg.print(F("<string> "));
              dbg.println(*(tokens + i));  
            }
            
            free(*(tokens + i));
        }
        
        free(tokens);
    }
    
   
  ATCIPCLOSE();
  lSuccess++;
  t=millis() - t;
  dbg.print(F(" cost time = "));
  dbg.println(t);
  setBit(PIC_ACT,BIT0);
  //EEPROM.write(PIC_ACT,0x01);
  Notify_host();
}

byte recv(int timeout, const char* term,bool debug ) {
  unsigned long t=millis();
  byte found=RECV_TIMEOUT;
  uint16_t i=0;
  int len=strlen(term);
  memset(recvBuffer, 0, BUFFER_SIZE);

  rx_empty();
  // wait for at most timeout milliseconds
  // or if OK\r\n is found
  while(millis()<t+timeout) {
    if(esp.available()) {
      char tmp = esp.read();
      dbg.write(tmp);
      if(i < BUFFER_SIZE-1){
        recvBuffer[i++]=tmp;
        if(i>=len) {
          if(strncmp(recvBuffer+i-len, term, len)==0) {
            found = RECV_SUCCESS;
            dbg.print(F("[DBG]find "));
            dbg.println(term);
            break;
          }else if(strncmp(recvBuffer+i-5, "ERROR", 5)==0) {
            found = RECV_FAIL;
            dbg.println(F("[DBG]find Error"));
            break;
          }
        }
      }else{
          dbg.println(F("\r\nBUFFER FAIL"));
          rx_empty();
          dbg.println(F("run rx_empty"));
          return RECV_FAIL;  
        }
      
    }
  }
  
  recvBuffer[i]='\0';
  if(debug)
    {
      dbg.print(recvBuffer);
    } 
  if(found == RECV_TIMEOUT){
    dbg.println(F("[DBG]Recv Timeout!!")); 
   }  
  return found;
}

void rx_empty(void) 
{
    while(esp.available() > 0) {
        esp.read();
    }
}



int  getPosition(char* string,char search){
  const char *moved_string = strchr(string, search);
  /* If not null, return the difference. */
  if (moved_string) {
    return moved_string - string;
  }
  /* Character not found. */
  return -1;
}
void getString(char * des,char *src,int startPos,int endPos){
  memset(des,0,sizeof(des));
  memcpy(des,src+startPos,endPos-startPos+1);
  
}

char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    
    int count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;
    
    // Count how many elements will be extracted. 
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }

    // Add space for trailing token. 
    count += last_comma < (a_str + strlen(a_str) - 1);

    // Add space for terminating null string so caller
    //   knows where the list of returned strings ends. 
    count++;

    result = (char**)malloc(sizeof(char*) * count);

    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);

        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}


// I2C event

void i2c_process(){
  uint16_t i,i2c_mode,i2c_length,address;
  i2c_mode = EEPROM.read(0x00);
  if(i2c_mode == I2C_WRITE_MODE){
    dbg.println(F("GET into I2C WRITE"));
    address = EEPROM.read(0x01);
    i2c_length = EEPROM.read(0x02);
    
    for(i=0;i<i2c_length;i++){
      EEPROM.write(EEPROM_ADDRESS+address+i,EEPROM.read(0x03+i));
    }

    switch(address+EEPROM_ADDRESS){
      case MTIME_Y_H:
        //if(!bSendData)  bSendData = true;  
        bSendData = BIT0;
      break;  
      
      case WIFI_SSID:
      dbg.println(F("GET SSID"));
      ssid_size  = i2c_length;
      
      
      for (i=i2c_length;i<32;i++){
        EEPROM.write(WIFI_SSID+i,0);
      }
      for (i=0;i<32;i++){
        dbg.write(EEPROM.read(WIFI_SSID+i));
      }
      dbg.println(F("-------------"));
      break;
      case WIFI_PWD:
      dbg.println(F("GET PWD"));
      pwd_size = i2c_length;
      
      for (i=i2c_length;i<10;i++){
        EEPROM.write(WIFI_PWD+i,0);
      }
      
      for (i=0;i<10;i++){
        dbg.write(EEPROM.read(WIFI_PWD+i));
      }
      break;
      case PIC_ACT:
      bSendData = BIT1;
      dbg.println(F("GET 0xA1 data"));
      dbg.println(EEPROM.read(PIC_ACT));
      break;
    }
    
    
  }

  /*
    if(i2c_mode == I2C_READ_MODE){
     dbg.println(F("GET into I2C READ"));
     i2c_length = EEPROM.read(0x01);
      address = EEPROM.read(0x02);
    }else 
   * 
   */
  
}
     
void receiveEvent(int howMany) {
  
  int x=0;
  unsigned char c;
  dbg.println(F("receiveEvent"));
  while (1 < Wire.available()) { // loop through all but the last
    c = Wire.read(); // receive byte as a character
    EEPROM.write(x,c);
    dbg.print(F("0x"));         // print the character
    dbg.print(c,HEX);
    dbg.print(F(","));
    x++;
  }
  dbg.println("");
  Wire.read();    // receive byte as an integer
  dbg.println(F("Test EEPROM"));
  for( x = 0 ; x < EEPROM.read(0x02);x++){
    dbg.print(F("0x"));         // print the character
    dbg.print(EEPROM.read(x+3),HEX);
    dbg.print(F(","));    
  }
  dbg.println(F("I2C_PROCESS ... "));
  i2c_process();
}


void requestEvent() {
  uint8_t i,i2c_length,address,i2c_mode;
  dbg.println(F("RequestEvent"));
  i2c_mode = EEPROM.read(0x00);
  address = EEPROM.read(0x01);  
  i2c_length = EEPROM.read(0x02);

  dbg.println(i2c_mode);
  dbg.println(address);
  dbg.println(i2c_length);
  dbg.println(F("------"));
  
  char * req = (char*)malloc(i2c_length+1);
  for(i=0;i<i2c_length;i++){
    req[i] = EEPROM.read(EEPROM_ADDRESS+address+i);
    dbg.print(i);
    dbg.print(" : 0x");
    dbg.println(req[i],HEX);
   
  }
  dbg.println(F("------"));
  req[i2c_length] = '\0';
  
  Wire.write(req,i2c_length);
  if( address == 0xA0){
    dbg.println(F("CLEAR A0 A1"));
    EEPROM.write(RSP,0);  
    EEPROM.write(PIC_ACT,0);  
  }
  
#ifdef  __DEBUG_MODE__
  dbg.print(F("Send i2c: "));
  for(i=0;i<i2c_length;i++){
    dbg.print(req[i],HEX);
  }
#endif
  free(req);
  // as expected by master
}

byte ATCIPSTART(char* addr,uint32_t port){
  uint8_t result;
  esp.print(F("AT+CIPSTART=\"TCP\",\""));  
  esp.print(addr);
  esp.print(F("\","));
  esp.print(port);
  esp.print(F("\r\n\r\n"));
  result = recv(5000);
  
  return result;
}

byte ATCIPCLOSE(){
  uint8_t result;
  esp.print(F("AT+CIPCLOSE\r\n"));  
  result = recv(5000); 
  return result;
}

byte ATRST(){
  uint8_t result;
  esp.print(F("AT+RST\r\n"));  
  result = recv(10000,"ready");
  
  return result;
}
byte AT(){
  uint8_t result;
  esp.print(F("AT\r\n"));  
  result = recv(1000);
  
  return result;
}

byte connectWifi(char* ssid,char*pwd){
  uint8_t result;
#ifdef __DBUG_MODE__
  dbg.print(F("connect wifi : "));
  dbg.println(ssid);
#endif

  esp.print(F("AT+CWJAP=\""));
  esp.print(ssid);
//  esp.print("MAKE11F");
  esp.print(F("\",\""));
//  esp.print("synMakeEl");
  esp.print(pwd);
  esp.println(F("\"\r\n"));

  result = recv(10000,OKrn);
  return result;

}
void setBit(const int adr,const byte cmd){
  EEPROM.write(adr,EEPROM.read(adr)|cmd);
  dbg.print(F("setBit 0x"));
  dbg.print(EEPROM.read(adr),HEX);
  
}
byte connection_check(){
  dbg.println(F("start Connection test"));
  if(ATCIPSTART("discover.r3dstar.com",80) == RECV_SUCCESS){
    ATCIPCLOSE();
  }else{
    setBit(RSP,BIT5); 
    dbg.println(F("NONO Connection"));  
    
  }
 
  dbg.println(F("Finish Connection test"));
  Notify_host();  
}
byte ATCIPSEND(int content_length){
  uint8_t result;
  int cnt;
  dbg.println(F("Send DATA(ATCIPSEND)"));
//  dbg.println(buf);
  
  esp.print(F("AT+CIPSEND="));
  esp.print(content_length);
  esp.print(F("\r\n"));
  
  result = recv(10000,">");



  
  if(result == RECV_SUCCESS){
    dbg.println(F("RECV_SUCCESS"));
    for ( cnt =0; cnt < content_length;cnt++){
      char c = EEPROM.read(0x200+cnt);
      esp.write(c);
      dbg.write(c);
    }
//   

    dbg.println(F("------"));

#if   0
    recv(1000,"SEND OK");

    result = recv(10000,"\r\n\r\n");
    while(esp.available()) {
    
      char tmp = esp.read();
      dbg.write(tmp);
     }
    dbg.println(F("\r\n+IPD Finish!!!\r\n------"));
  
    return RECV_FAIL;
#else     
    
    
    result = recv(10000,"}"); 

    dbg.println(F("ATCIPSEND subrutine finish"));

#endif
    
  }else{
    return result;
  }
  return result;
    
}


void set_eeprom(int adr,char* buffer,int length){
  uint16_t i;
  for( i =0; i < length ; i++){
    EEPROM.write(adr+i,buffer[i]);  
  }  
}
void get_eeprom(int adr,char* buffer,int length){
  uint16_t i;
  memset(buffer,0,sizeof(buffer));
  for( i =0; i < length ; i++){
    buffer[i] = EEPROM.read(adr+i);  
  }
}

void dbg_eeprom(int adr,int length){

  uint16_t i;
  dbg.println(F("-----")); 
  for( i =0; i < length ; i++){
    dbg.print(F("0x"));
    dbg.print(EEPROM.read(adr+i),HEX);  
    dbg.println(F(""));
  }
  dbg.println(F("\r\n-----")); 
  
}

template <class T> int EEPROM_writeAnything(int ee, const T& value,int length)
{
   const byte* p = (const byte*)(const void*)&value;
   uint16_t i;
   for (i = 0; i < length; i++)
       EEPROM.write(ee++, *p++);
   return i;
}

template <class T> int EEPROM_readAnything(int ee, T& value,int length)
{
   byte* p = (byte*)(void*)&value;
   uint16_t i;
   for (i = 0; i < length; i++)
       *p++ = EEPROM.read(ee++);
   return i;
}

void printP(const char *str PROGMEM)
{
  char c;
  int i =0;
  while((c = pgm_read_byte(str++))){
    EEPROM.write(0x200+i,c);
    i++;
  }
}

