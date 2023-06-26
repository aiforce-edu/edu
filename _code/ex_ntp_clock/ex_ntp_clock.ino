#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define STASSID "iot" //와이파이 검색했을때 뜨는 이름
#define STAPSK  "15151515" //패스워드
const char* ssid = STASSID;
const char* password = STAPSK;

const long utcOffsetInSeconds = 32400; // every UTC +1.00, +3600
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
}

void loop() {
  timeClient.update();
  
  Serial.print(Week[timeClient.getDay()]);
  Serial.print(" ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  delay(1000);
}
