#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"         //https://github.com/tzapu/WiFiManager

std::unique_ptr<ESP8266WebServer> server;

const int flashButtonPin = 0;

void handleRoot() {
  server->send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server->uri();
  message += "\nMethod: ";
  message += (server->method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server->args();
  message += "\n";
  for (uint8_t i = 0; i < server->args(); i++) {
    message += " " + server->argName(i) + ": " + server->arg(i) + "\n";
  }
  server->send(404, "text/plain", message);
}

void setup() {
  // put your setup code here, to run once:
  
	
  // Inisialisasi PIN lampu 
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
  
  Serial.begin(115200);
  //Serial.setDebugOutput(true);
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;
  //reset saved settings
  // wifiManager.resetSettings();

  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  // wifiManager.autoConnect("AutoConnectAP");
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();


  //if you get here you have connected to the WiFi
  // Serial.println("connected...yeey :)");

  bool res;

  res = wifiManager.autoConnect("AutoConnectAP"); // anonymous ap
  // res = wifiManager.autoConnect("AutoConnectAP","password"); // password protected ap

  if(!res) {
      Serial.println("Failed to connect");
      // ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected...yeey :)");

      server.reset(new ESP8266WebServer(WiFi.localIP(), 80));

      server->on("/", []() {
        server->send(200, "text/html", SendHTML()); 
      });

    
      server->on("/led/on", []() {
        digitalWrite(LED_BUILTIN, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/led/off", []() {
        digitalWrite(LED_BUILTIN, HIGH);
        server->send(200, "text/html", SendHTML());
      });


      server->on("/reset", []() {
        Serial.println("WiFi settings reset");
        server->send(200, "text/plain", "WiFi settings reset, reconnect wifi");
        WiFiManager wifiManager;
        wifiManager.resetSettings();
        ESP.reset();
      });
    
      server->onNotFound(handleNotFound);
    
      server->begin();
      Serial.println("HTTP server started");
      Serial.println(WiFi.localIP());
  }
  
 
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(flashButtonPin) == LOW) {
    WiFiManager wm;
    wm.resetSettings();
    ESP.reset();
    Serial.println("WiFi settings reset");
    delay(1000); 
  }
  
  server->handleClient();
}

String SendHTML(){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #1abc9c;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #1abc9c;}\n";
  ptr +=".button-on:active {background-color: #16a085;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  
  if(digitalRead(LED_BUILTIN) == LOW)
  {
    ptr +="<p>LED Status: ON</p><a class=\"button button-off\" href=\"/led/off\">OFF</a>\n";
  }else{
    ptr +="<p>LED Status: OFF</p><a class=\"button button-on\" href=\"/led/on\">ON</a>\n";
  }

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}