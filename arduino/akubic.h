#ifndef __AKUBIC_H__
#define __AKUBIC_H__

#include "Arduino.h"
#define BIT0  0x01
#define BIT1  0x02
#define BIT2  0x04
#define BIT3  0x08
#define BIT4  0x10
#define BIT5  0x20
#define BIT6  0x40
#define BIT7  0x80


#define SW_VERSION  0x10
#define SLAVE_ID    0x73

#define BUFFER_SIZE 400
#define EEPROM_ADDRESS  0x100

#define I2C_READ_MODE      0x00
#define I2C_WRITE_MODE     0x01
#define WIFI_SSID     EEPROM_ADDRESS+0x11
#define WIFI_PWD      EEPROM_ADDRESS+0x31
#define SERVER_ACT1   EEPROM_ADDRESS+0x3B
#define SERVER_ACT2   EEPROM_ADDRESS+0x3C
#define FACILITY_ID   EEPROM_ADDRESS+0x3D
#define SERIAL_NUMBER EEPROM_ADDRESS+0x40
#define BASE_ID       EEPROM_ADDRESS+0x48
#define SAMPLE_RATE   EEPROM_ADDRESS+0x4A
#define CTIME_Y_H     EEPROM_ADDRESS+0x50
#define CTIME_Y_L     EEPROM_ADDRESS+0x51
#define CTIME_M       EEPROM_ADDRESS+0x52
#define CTIME_D       EEPROM_ADDRESS+0x53
#define CTIME_H       EEPROM_ADDRESS+0x54
#define CTIME_I       EEPROM_ADDRESS+0x55
#define CTIME_S       EEPROM_ADDRESS+0x56
#define MTIME_Y_H     EEPROM_ADDRESS+0x60
#define MTIME_Y_L     EEPROM_ADDRESS+0x61
#define MTIME_M       EEPROM_ADDRESS+0x62
#define MTIME_D       EEPROM_ADDRESS+0x63
#define MTIME_H       EEPROM_ADDRESS+0x64
#define MTIME_I       EEPROM_ADDRESS+0x65
#define MTIME_S       EEPROM_ADDRESS+0x66
#define SENSOR_VAL    EEPROM_ADDRESS+0x67
#define RSP           EEPROM_ADDRESS+0xA0
#define PIC_ACT       EEPROM_ADDRESS+0xA1
#define DEVICE_ID     EEPROM_ADDRESS+0xC0
#define SW_V          EEPROM_ADDRESS+0xC1
#define ERR_PIC1      EEPROM_ADDRESS+0xF0
#define ERR_PIC2      EEPROM_ADDRESS+0xF1

#define   RECV_SUCCESS    1
#define   RECV_FAIL       2
#define   RECV_TIMEOUT    0


#define MODE_REQUEST        1
#define MODE_INSTALL        2
#define MODE_ADJ_TIME       3

#define P(name) static const char name[] PROGMEM // declare a static string

struct SendObject{
  uint8_t sn[9];
  unsigned int parameter[8];
  unsigned char datetime[7];   
  unsigned int error;
};

struct ResObject{
  unsigned int status;
  unsigned int current_time[7];
  char sn[9];
  unsigned int sample_rate;
  unsigned int device_request;
  unsigned int request_detail;
};

// parameters

char recvBuffer[BUFFER_SIZE];
char dataBuffer[128];
const char OKrn[]  = "OK\r\n";

SendObject test_obj;
ResObject  res_obj;

uint8_t ssid_size,pwd_size;
char ssid[33];
char pwd[11];
char sn[9];

// function

byte recv(int timeout, const char* term=OKrn,bool debug = true);
byte send_data(byte mode = MODE_REQUEST);
void rx_empty(void);


int  getPosition(char* string,char search);
void getString(char * des,char *src,int startPos,int endPos);
char** str_split(char* a_str, const char a_delim);

void reset_wifi();
void Notify_host();

byte ATCIPSEND(int content_length);

template <class T> int EEPROM_readAnything(int ee, T& value,int length);
template <class T> int EEPROM_writeAnything(int ee, const T& value,int length);
void get_eeprom(int adr,char* buffer,int length);
void set_eeprom(int adr,char* buffer,int length);
#endif  // #ifndef __AKUBIC_H__
