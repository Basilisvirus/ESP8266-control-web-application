#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>

ESP8266WiFiMulti wifiMulti;     // Create an instance of the ESP8266WiFiMulti class, called 'wifiMulti'

ESP8266WebServer server(80);    // Create a webserver object that listens for HTTP request on port 80

const int led = 12;
const int led1= 14;

bool led_=false;
bool led1_=false;


void handleRoot();              // function prototypes for HTTP handlers
void handleLED();
void handleLED1();
void handleNotFound();

String cmd; //to store the html code before we send it
//========================================SETUP=======================================
void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  pinMode(led, OUTPUT);
   pinMode(led1, OUTPUT);

  wifiMulti.addAP("00000", "00000");   // add Wi-Fi networks you want to connect to
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());              // Tell us what network we're connected to
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());           // Send the IP address of the ESP8266 to the computer

  if (MDNS.begin("esp8266")) {              // Start the mDNS responder for esp8266.local
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }
//======================================RIGHT FUNCTIONS======================================================================
  server.on("/", HTTP_GET, handleRoot);   // Call the 'handleRoot' function when a client requests URI "/"
  server.on("/LED", HTTP_POST, handleLED);// Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.on("/LED1", HTTP_POST, handleLED1);// Call the 'handleLED' function when a POST request is made to URI "/LED"
  server.onNotFound(handleNotFound);      // When a client requests an unknown URI (i.e. something other than "/"), call function "handleNotFound"

  server.begin();                         // Actually start the server
  Serial.println("HTTP server started");
}
//==================================================================LOOP======================================================
void loop(void){
  server.handleClient();                    // Listen for HTTP requests from clients
}
//===================================FUNCTIONS===============================================
void handleRoot() { // When URI / is requested, send a web page with a button to toggle the LED
  cmd="";
 
 cmd+= "<!DOCTYPE HTML>\r\n <html>\r\n <header>\r\n <title>ESP8266 Webserver</title>\r\n <h1>\"ESP8266 Web Server Control\"</h1>\r\n </header>\r\n <p>\r\n <form action=\"/LED\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle LED\">\r\n </form>\r\n";
  if(led_){
    cmd += ("Led: ON \r\n </p>");
  }
  else{
    cmd +=("Led: OFF\r\n </p>");
  }
  
   cmd+="<p>\r\n <form action=\"/LED1\" method=\"POST\">\r\n <input type=\"submit\" value=\"Toggle LED1\">\r\n </form>\r\n ";
    if(led1_){
    cmd += ("Led1: ON \r\n </p>");
  }
  else{
    cmd +=("Led1: OFF\r\n </p>");
  }

  cmd+= "</html>\r\n";
  
  server.send(200, "text/html", cmd );
}

void handleLED() {                          // If a POST request is made to URI /LED
  digitalWrite(led,!digitalRead(led));      // Change the state of the LED
  led_=!led_;
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}
void handleLED1() {                          // If a POST request is made to URI /LED
  digitalWrite(led1,!digitalRead(led1));      // Change the state of the LED
    led1_=!led1_;  
  server.sendHeader("Location","/");        // Add a header to respond with a new location for the browser to go to the home page again
  server.send(303);                         // Send it back to the browser with an HTTP status 303 (See Other) to redirect
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); // Send HTTP status 404 (Not Found) when there's no handler for the URI in the request
}

