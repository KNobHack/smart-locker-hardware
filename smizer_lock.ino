#include <Keypad_I2C.h>
#include <Keypad.h>
#include <Wire.h>
#include <HX711.h>
#define I2CADDR 0x20

int i =0;
int no_lock = 123;
int lampu = 0;
int kunci = 0;
int status_lock= 0;
int status_lamp = 0;
int status_packet= 0;
int webpass = 1234;


// KEYPAD=================================================================
const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
// Digitran keypad, bit numbers of PCF8574 i/o port
byte rowPins[ROWS] = {0, 1, 2, 3}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {4, 5, 6,7}; //connect to the column pinouts of the keypad

Keypad_I2C kpd( makeKeymap(keys), rowPins, colPins, ROWS, COLS, I2CADDR, PCF8574 );

// KEYPAD=================================================================


// RELAY==================================================================
  const int relay1 = 8;
  const int relay2 = 9;
// RELAY==================================================================


// LOADCELL===============================================================
// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = A1;
const int LOADCELL_SCK_PIN = A0;  
HX711 scale;
// LOADCELL===============================================================

// ESP8266================================================================
// ESP8266================================================================




void setup() {
Serial.begin(9600);
// KEYPAD=================================================================
  Wire.begin( );
  kpd.begin( makeKeymap(keys) );
  Serial.begin(9600);
  Serial.println( "start" );
// KEYPAD================================================================

// RELAY=================================================================
  unsigned long timeawal = 0;
  pinMode (relay1, OUTPUT);
  pinMode (relay2, OUTPUT);
// RELAY=================================================================


// LOADCELL===============================================================
  Serial.println("Pastikan Tidak Ada Beban");
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(1005.0);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare(50);                // reset the scale to 0
  Serial.println("Silahkan Untuk Menimbang");*/
// LOADCELL===============================================================

// ESP8266================================================================
// ESP8266================================================================
}
/*
void connectAP(String SSID, String Pass){                     // fungsi koneksi ke AP
  //bila ESP baru harus set Mode ke station (AT+CWMODE=1) terlebih dahulu
  //Serial.println("Connecting...");
  wifi.print("AT+CWJAP=\"");
  wifi.print(SSID);
  wifi.print("\",\"");
  wifi.print(Pass);
  wifi.println("\"");
  ShowResponse(5000);
  wifi.println("AT+CIFSR");
  ShowResponse(5000);
  
}
*/

void loop() {
  digitalWrite (relay1, LOW);
// KEYPAD=================================================================
  int pass = password ();
  Serial.print ("Password = ");
  Serial.println (pass); 
  delay (2000);
// KEYPAD=================================================================

      
// RELAY=================================================================

  
  if (lampu == 1){
  digitalWrite (relay2, HIGH);
  status_lamp = 1;
  delay (900000);
  digitalWrite (relay2, LOW);
  status_lamp = 2;
  }

  if (kunci == 1){
  digitalWrite (relay1, HIGH);
  status_lock = 1;
  status_lamp = 0 ;
  delay (30000);
  digitalWrite (relay1, LOW);
  status_lock = 0;
  }
  
  if (pass == webpass){
  digitalWrite (relay1, HIGH);
  status_lock = 1;
  status_lamp = 0;
  delay (30000);
  digitalWrite (relay1, LOW);
  status_lock = 0;
  }
 // RELAY=================================================================


// LOADCELL===============================================================
  Serial.print("Berat = ");
  float status_berat= scale.get_units(25);
  if(status_berat<=1){
    status_berat=0.0;
    status_packet = 0;
  }
  if (status_berat > 1){
    status_packet=1;
  }
  
  Serial.println(status_berat,1);
  
  scale.power_down();
  delay(2000);
  scale.power_up();

// LOADCELL===============================================================


// ESP8266=================================================================
/*  data2server = url;
  data2server += " HTTP/1.1";
  
  send_data();
  //Serial.println(ShowResponseServer(5000));
  wifi.println("AT+CIPCLOSE=4");

  delay(5000);
  */
// ESP8266=================================================================
}

int password (){
Serial.println ("Start..."); 
bool flag = 0;
char key [4] ;

while (flag==0){
  key [i] = kpd.getKey();
  if (key [i]){
  if ((key [i] == 'A') || (key [i] == 'B') || (key [i] == 'C') || (key [i] == 'D')|| (key [i] == '#') || (key [i] == '*')){ }
  else {
    Serial.print ("key ");
    Serial.print (i);
    Serial.print (" = ");
    Serial.println(key[i]);
    i++;
    if (i==4){
      i=0;
      flag = 1;
     // Serial.println (key);
    }
   }
  }
}
int x  = atoi (key);
 return x;
}
/*
void ShowResponse(int wait){
  //Serial.print("response ESP : ");
  long timeNOW = millis();
  String hasilread;
  while(millis()-timeNOW < wait){
    while(wifi.available()){
      hasilread = wifi.readString();
      //Serial.println(hasilread);
      delay(10);
      return;
    }
  }
}

void send_data(){
 wifi.println("AT+CIPMUX=1");
  ShowResponse(2000);
  
  wifi.print("AT+CIPSTART=4,\"TCP\",\"");
  wifi.print(ServerIP);
  wifi.println("\",80");
  ShowResponse(2000);

  wifi.print("AT+CIPSEND=4,");
  wifi.println(data2server.length()+host.length()+6);  //6 for \r\n
  
  //Serial.println(data2server);
  //Serial.println(host);
  //Serial.println();
  delay(100);
  
  wifi.println(data2server);
  wifi.println(host);
  wifi.println();
}

String ShowResponseServer(int wait){      // baca data dari server
  //Serial.print("response FROM SERVER : ");
  long timeNOW = millis();
  String hasilread;
  while(millis()-timeNOW < wait){
    while(wifi.available()){
      hasilread = wifi.readString();
    }
    return hasilread;
  }
  return "Time out - no data";
  
}
*/
