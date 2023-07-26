#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 
//Input I2C address after check address at the first parameter

#define STASSID "iot" //와이파이 검색했을때 뜨는 이름
#define STAPSK  "12345678" //패스워드
const char* ssid = STASSID;
const char* password = STAPSK;

const long utcOffsetInSeconds = 9*3600; // every UTC +1.00, +3600
String Week[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

void setup() {
  Serial.begin(9600);
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay (500);
    Serial.print(".");
  }
  Serial.print("WiFi connected");
  Serial.print("IP address : ");
  Serial.println(WiFi.localIP());

  // Initialize NTP  
  timeClient.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("NTP Clock");
}

void loop() {
  timeClient.update();
  String strHour = String(timeClient.getHours());
  String strMin  = String(timeClient.getMinutes());
  String strSec  = String(timeClient.getSeconds());
  lcd.setCursor(0,1);
  lcd.print("                ");
  lcd.setCursor(0,1);
  lcd.print(Week[timeClient.getDay()]);
  lcd.print(" ");
  lcd.print(strHour); lcd.print(":");
  lcd.print(strMin); lcd.print(":");
  lcd.print(strSec); 
  delay(1000);
}
