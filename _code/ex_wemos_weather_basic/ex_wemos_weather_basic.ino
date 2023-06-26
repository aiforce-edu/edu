#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "YangJipsa" //와이파이 검색했을때 뜨는 이름
#define STAPSK  "15151515" //패스워드
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

//http://www.kma.go.kr/wid/queryDFSRSS.jsp?zone=4159025300
const char* host = "www.kma.go.kr";
const int httpsPort = 80;
 
String url = "/wid/queryDFSRSS.jsp?zone=4159025300";

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.print("connecting to ");

  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.print("connecting to ");
  Serial.println(host);
  Serial.print("requesting URL: ");
  Serial.println(url);
}

void loop() {
  delay(10000);
  
  String strHOUR,strTEMP,strPOP;
  bool checkHOUR = false;
  bool checkTEMP = false;
  bool checkPOP  = false;

  WiFiClient client;
  
  if (!client.connect(host, httpsPort)) 
  {
    Serial.println("connection failed");
    return;
  }

  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");

  unsigned long t = millis(); //생존시간
  while(1){
    if(client.available()) break;
    if(millis() - t > 10000) break;
  }

  //Serial.println("request sent");

  while(client.available())
  {
    String data = client.readStringUntil('\n'); //readline();
    Serial.print("data : ");
    Serial.println(data);
    delay(1);

// <hour> 쪽 데이터 파싱
    String temp = "<hour>";
    
    int s = data.indexOf(temp) + temp.length(); // 길이 = 6
    int e = data.indexOf("</hour>");
    if(s != -1 && e != -1 && !checkHOUR)
    {
      strHOUR = data.substring(s,e);
      //Serial.println("시간=" + strHOUR);
      checkHOUR = true;
    }
// <temp> 쪽 데이터 파싱
    temp = "<temp>";
    s = data.indexOf(temp) + temp.length();
    e = data.indexOf("</temp>");
    if(s != -1 && e != -1 && !checkTEMP)
    {
      strTEMP = data.substring(s,e);
      //Serial.println("온도=" + strTEMP);
      checkTEMP = true;
    }
// <pop> 쪽 데이터 파싱
    temp = "<pop>";
    s = data.indexOf(temp) + temp.length();
    e = data.indexOf("</pop>");
    if(s != -1 && e != -1 && !checkPOP)
    {
      strPOP = data.substring(s,e);
      //Serial.println("강수확률 =" + strPOP);
      checkPOP = true;
    }
  
  }
  Serial.print("Time : "); Serial.print(strHOUR); Serial.print("h");
  Serial.print(" ,Temp : "); Serial.print(strTEMP); Serial.print("C");
  Serial.print(" ,POP : "); Serial.print(strPOP); Serial.println("%");
 
  Serial.println("DONE");
}
