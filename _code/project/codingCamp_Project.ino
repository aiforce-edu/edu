#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "FirebaseESP8266.h" 

#define swL D2
#define swR D3
#define sensor A0

#define DISP_INIT    0
#define DISP_CLOCK   1
#define DISP_MESSAGE 2

#define FIREBASE_HOST "skku-iotcodingcamp-default-rtdb.firebaseio.com" 
#define FIREBASE_AUTH "y1Svf6gXlZvOoRmGuDSb0zrE0qnL5lvUhpMfBzyS"
#define WIFI_SSID "iot" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "12345678" // wifi 비밀번호

const long utcOffsetInSeconds = 9*3600; // every UTC +1.00, +3600
String Week[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
LiquidCrystal_I2C lcd(0x3F, 16, 2); 
FirebaseData firebaseData;
FirebaseJson json;

bool valSWL = false;
bool valSWR = false;
bool prev_valSWL = false;
bool prev_valSWR = false;
int dispMode = 0; // 0 : default, 1 : Clock, 2 : display Message

void setup() {
  Serial.begin(9600);

  pinMode(swL, INPUT);
  pinMode(swR, INPUT);
   
  lcd.init();
  lcd.backlight();
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay (500);
    Serial.print(".");
  }
  Serial.print("WiFi connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  // Initialize NTP  
  timeClient.begin();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop() {
  prev_valSWL = valSWL;
  prev_valSWR = valSWR;
  valSWL = digitalRead(swL);
  valSWR = digitalRead(swR);

  float valADC = analogRead(sensor);
  float t = valADC * 320.0/1024.0 - 50;
  
  if(valSWL < prev_valSWL)
  {
    dispMode++; 
    if (dispMode > 2) dispMode = 0;
  }
  if(valSWR < prev_valSWR)
  {
    dispMode--; 
    if (dispMode < 0) dispMode = 2;
  }

  if(dispMode == DISP_INIT)
  {
    String strT = String(t);
    lcd.setCursor(0,0);
    lcd.print(" IoT CodingCamp ");
    lcd.setCursor(0,1);
    lcd.print("* Temp :       *");
    lcd.setCursor(9,1);
    lcd.print("     ");
    lcd.setCursor(9,1);
    lcd.print(strT);
  }
  else if(dispMode == DISP_CLOCK)
  {
    int srartPos = 2;
    timeClient.update();
    String strHour = String(timeClient.getHours());
    String strMin  = String(timeClient.getMinutes());
    String strSec  = String(timeClient.getSeconds());
    lcd.setCursor(0,0);
    lcd.print("*** NTP Clock **");
    lcd.setCursor(0,1);
    lcd.print("                ");
    lcd.setCursor(srartPos,1);
    lcd.print(Week[timeClient.getDay()]);
    lcd.setCursor(srartPos+4,1);
    lcd.print(strHour); lcd.print(":");
    lcd.print(strMin); lcd.print(":");
    lcd.print(strSec); 
  }
  else if(dispMode == DISP_MESSAGE)
  {
    if(Firebase.getString(firebaseData, "SendMessage"))
    {
      String valStr = firebaseData.stringData();
      lcd.setCursor(0,0);
      lcd.print("*** Message  ***");
      lcd.setCursor(0,1);
      lcd.print("                ");
      lcd.setCursor(0,1);
      lcd.print(valStr.substring(2,valStr.length()-2));
    }
  }
  Firebase.setFloat(firebaseData, "Temperature", t);
  delay(1000);
}
