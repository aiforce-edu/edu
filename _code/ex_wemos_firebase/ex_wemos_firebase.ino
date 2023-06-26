#include "FirebaseESP8266.h" 
#include <ESP8266WiFi.h>
 
#define FIREBASE_HOST "실시간 데이터베이스 주소 (http:// 빼고, 마지막 / 빼고)" 
#define FIREBASE_AUTH "실시간 데이터베이스 비밀번호"
#define WIFI_SSID "와이파이 SSID" // 연결 가능한 wifi의 ssid
#define WIFI_PASSWORD "와이파이비밀번호" // wifi 비밀번호

#define pinLED1 D4
#define pinLED2 D7
#define pinCDS  A0
 
FirebaseData firebaseData;
FirebaseJson json;
 
void printResult(FirebaseData &data);
void setup() // wifi 접속 과정.
{
  Serial.begin(9600);
 
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println();
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
 
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
 
  firebaseData.setBSSLBufferSize(1024, 1024);
  firebaseData.setResponseSize(1024);
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}

void loop()
{
 if(Firebase.getBool(firebaseData,"LED1")) {
  bool valLED1 = firebaseData.boolData();
  digitalWrite(pinLED1, valLED1);
 }

 if(Firebase.getBool(firebaseData, "LED2")) {
  bool valLED2 = firebaseData.boolData();
  digitalWrite(pinLED2, valLED2);
 } 
 
/* if(Firebase.getInt(firebaseData, "Int Data Tag")){
  int valInt = firebaseData.intData();
  // write Code...
 }
 if(Firebase.getFloat(firebaseData, "Float Data Tag")){
  float valFloat = firebaseData.floatData();
  // write Code...
 }
 if(Firebase.getString(firebaseData, "String Data Tag")){
  String valStr = firebaseData.stringData();
  // write Code...
 }*/

 //Firebase.setBool(firebaseData, "BoolData", /*Bool Data*/);
 Firebase.setInt(firebaseData, "Brightness", analogRead(pinCDS));
 //Firebase.setFloat(firebaseData, "FloatData", /*Float Data*/);
 //Firebase.setString(firebaseData, "StringData", /*String Data*/);
 delay(1000); // 1초마다 반복
}
