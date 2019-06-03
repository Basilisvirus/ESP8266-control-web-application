#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

const char* ssid = "000000";
const char* password = "000000";

ESP8266WebServer server(80);

const int output1 = 4;
const int output2 = 5;
const int output3 = 12;
const int output4 = 14;

boolean device1 = false;
boolean device2 = false;
boolean device3 = false;
boolean device4 = false;
//===================================FUNCTIONS===============================================
void handleRoot() {

  String cmd;     
      cmd += "<!DOCTYPE HTML>\r\n";
      cmd += "<html>\r\n";
      //cmd += "<header><title>ESP8266 Webserver</title><h1>\"ESP8266 Web Server Control\"</h1></header>";
      cmd += "<head>";
      cmd += "<meta http-equiv='refresh' content='100'/>";
      cmd += "</head>";
      
    //<!--Toggle Device1 ON-->
      cmd+="<p>\r\n <form action=\"/status1=1\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device1 ON\">\r\n </form>\r\n </p>\r\n";
    
    //<!--Toggle Device1 OFF-->
      cmd+="<p>\r\n <form action=\"/status1=0\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device1 OFF\">\r\n </form>\r\n </p>\r\n";
   
    //<!--Toggle Device2 ON-->
      cmd+="<p>\r\n <form action=\"/status2=1\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device2 ON\">\r\n </form>\r\n </p>\r\n";

    //<!--Toggle Device2 OFF-->
      cmd+="<p>\r\n <form action=\"/status2=0\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device2 OFF\">\r\n </form>\r\n </p>\r\n";

    //<!--Toggle Device3 ON-->
      cmd+="<p>\r\n <form action=\"/status3=1\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device3 ON\">\r\n </form>\r\n </p>\r\n";

    //<!--Toggle Device3 OFF-->
      cmd+="<p>\r\n <form action=\"/status3=0\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device3 OFF\">\r\n </form>\r\n </p>\r\n";

    //<!--Toggle Device4 ON-->
      cmd+="<p>\r\n <form action=\"/status4=1\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device4 ON\">\r\n </form>\r\n </p>\r\n";

    //<!--Toggle Device4 OFF-->
      cmd+="<p>\r\n <form action=\"/status4=0\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle Device4 OFF\">\r\n </form>\r\n </p>\r\n";
      
      if(device1){
        cmd +=("<br/>Device1  : ON");
      }
      else{
        cmd +=("<br/>Device1  : OFF");
      }
      
      if(device2){
        cmd +=("<br/>Device2  : ON");
      }
      else{
        cmd +=("<br/>Device2  : OFF");
      }
           
       if(device3){
        cmd +=("<br/>Device3  : ON");
      }
      else{
        cmd +=("<br/>Device3  : OFF");
      }
      
      if(device4){
        cmd +=("<br/>Device4  : ON");
      }
      else{
        cmd +=("<br/>Device4  : OFF");
      }
           
      cmd += "</html>\r\n";
      server.send(200, "text/html", cmd);
}

//========================================SETUP=======================================
void setup(void){
  pinMode(output1, OUTPUT);
  pinMode(output2, OUTPUT);
  pinMode(output3, OUTPUT);
  pinMode(output4, OUTPUT);

  digitalWrite(output1, LOW); 
  digitalWrite(output2, LOW);
  digitalWrite(output3, LOW);
  digitalWrite(output4, LOW);
   
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("");



  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");

  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());


  

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  }
//============================================RIGHT FUNCTIONS==============================================
  server.on("/", handleRoot); //wont use HTTP_GET for now
  
  server.on("/status1=1", [](){
    server.send(200, "text/plain", "device1 = ON");
    digitalWrite(output1, HIGH); 
    device1 = true;
  });

  server.on("/status1=0", [](){
    server.send(200, "text/plain", "device1 = OFF");
    digitalWrite(output1, LOW); 
    device1 = false;
  });

  server.on("/status2=1", [](){
    server.send(200, "text/plain", "device2 = ON");
    digitalWrite(output2, HIGH); 
    device2 = true;
  });

  server.on("/status2=0", [](){
    server.send(200, "text/plain", "device2 = OFF");
    digitalWrite(output2, LOW); 
    device2 = false;
  });

  server.on("/status3=1", [](){
    server.send(200, "text/plain", "device3 = ON");
    digitalWrite(output3, HIGH); 
    device3 = true;
  });

  server.on("/status3=0", [](){
    server.send(200, "text/plain", "device3 = OFF");
    digitalWrite(output3, LOW); 
    device3 = false;
  });

  server.on("/status4=1", [](){
    server.send(200, "text/plain", "device4 = ON");
    digitalWrite(output4, HIGH); 
    device4 = true;
  });

  server.on("/status4=0", [](){
    server.send(200, "text/plain", "device4 = OFF");
    digitalWrite(output4, LOW); 
    device4 = false;
  });

  server.begin();
  Serial.println("HTTP server started");
}

//======================================================LOOP================================
void loop(void){
  server.handleClient();
}
