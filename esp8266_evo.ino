#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino

//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include "WiFiManager.h"         //https://github.com/tzapu/WiFiManager

std::unique_ptr<ESP8266WebServer> server;

const int flashButtonPin = 0;

#define d1 D1
#define d2 D2
#define d3 D3
#define d4 D4
#define d5 D5
#define d6 D6
#define d7 D7
#define d8 D8

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
  
  pinMode(d1, OUTPUT);
  digitalWrite(d1, LOW);

  pinMode(d2, OUTPUT);
  digitalWrite(d2, LOW);

  pinMode(d3, OUTPUT);
  digitalWrite(d3, LOW);
  
  pinMode(d4, OUTPUT);
  digitalWrite(d4, LOW);
  
  pinMode(d5, OUTPUT);
  digitalWrite(d5, LOW);
  
  pinMode(d6, OUTPUT);
  digitalWrite(d6, LOW);
  
  pinMode(d7, OUTPUT);
  digitalWrite(d7, LOW);
  
  pinMode(d8, OUTPUT);
  digitalWrite(d8, LOW);
  
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

  res = wifiManager.autoConnect("saepulfariz-device-lamps"); // anonymous ap
  // res = wifiManager.autoConnect("AutoConnectAP","password"); // password protected ap

  if(!res) {
      Serial.println("Failed to connect");
      // ESP.restart();
  } 
  else {
      //if you get here you have connected to the WiFi    
      Serial.println("connected...yeey :)");

      server.reset(new ESP8266WebServer(WiFi.localIP(), 80));

      // server.sendHeader("Access-Control-Allow-Origin", "*");
      // server.enableCORS(true);
      server->enableCORS(true);

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

      server->on("/d1/on", []() {
        digitalWrite(d1, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d1/off", []() {
        digitalWrite(d1, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d2/on", []() {
        digitalWrite(d2, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d2/off", []() {
        digitalWrite(d2, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d3/on", []() {
        digitalWrite(d3, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d3/off", []() {
        digitalWrite(d3, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d4/on", []() {
        digitalWrite(d4, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d4/off", []() {
        digitalWrite(d4, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d5/on", []() {
        digitalWrite(d5, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d5/off", []() {
        digitalWrite(d5, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d6/on", []() {
        digitalWrite(d6, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d6/off", []() {
        digitalWrite(d6, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d7/on", []() {
        digitalWrite(d7, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d7/off", []() {
        digitalWrite(d7, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d8/on", []() {
        digitalWrite(d8, LOW);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/d8/off", []() {
        digitalWrite(d8, HIGH);
        server->send(200, "text/html", SendHTML());
      });

      server->on("/api/lamps", []() {
        
        String json = "{";

        json += "\"success\" : true,";
        json += "\"message\" : \"List Data Lamps \",";
        json += "\"data\" : [";

        json += "{";
        json += "\"id\" : \"1\",";
        if(digitalRead(d1) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"2\",";
        if(digitalRead(d2) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"3\",";
        if(digitalRead(d3) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"4\",";
        if(digitalRead(d4) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"5\",";
        if(digitalRead(d5) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"6\",";
        if(digitalRead(d6) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"7\",";
        if(digitalRead(d7) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "},";

        json += "{";
        json += "\"id\" : \"8\",";
        if(digitalRead(d8) == LOW){
          json += "\"status\" : 1";
        }else{
          json += "\"status\" : 0";
        }
        json += "}]";

        json += "}";
        server->send(200, "text/plain", json);
      });

      // server->on("/api/lamps/{id}", handleLamp);

      server->on("/api/lamps/1", []() {
        handleLamp("1");
      });

      server->on("/api/lamps/2", []() {
        handleLamp("2");
      });

      server->on("/api/lamps/3", []() {
        handleLamp("3");
      });

      server->on("/api/lamps/4", []() {
        handleLamp("4");
      });

      server->on("/api/lamps/5", []() {
        handleLamp("5");
      });

      server->on("/api/lamps/6", []() {
        handleLamp("6");
      });

      server->on("/api/lamps/7", []() {
        handleLamp("7");
      });

      server->on("/api/lamps/8", []() {
        handleLamp("8");
      });

      // Error
      // server->on("/api/lamps/d1", handleLamp("D1"));
      // server->on("/api/lamps/d2", handleLamp("D2"));
      // server->on("/api/lamps/d3", handleLamp("D3"));
      // server->on("/api/lamps/d4", handleLamp("D4"));
      // server->on("/api/lamps/d5", handleLamp("D5"));
      // server->on("/api/lamps/d6", handleLamp("D6"));
      // server->on("/api/lamps/d7", handleLamp("D7"));
      // server->on("/api/lamps/d8", handleLamp("D8"));

      server->on("/api/status", []() {
        
        String json = "{";

        if(digitalRead(d1) == LOW){
          json += "\"1\" : 1,";
        }else{
          json += "\"1\" : 0,";
        }

        if(digitalRead(d2) == LOW){
          json += "\"2\" : 1,";
        }else{
          json += "\"2\" : 0,";
        }

        if(digitalRead(d3) == LOW){
          json += "\"3\" : 1,";
        }else{
          json += "\"3\" : 0,";
        }

        if(digitalRead(d4) == LOW){
          json += "\"4\" : 1,";
        }else{
          json += "\"4\" : 0,";
        }

        if(digitalRead(d5) == LOW){
          json += "\"5\" : 1,";
        }else{
          json += "\"5\" : 0,";
        }

        if(digitalRead(d6) == LOW){
          json += "\"6\" : 1,";
        }else{
          json += "\"6\" : 0,";
        }

        if(digitalRead(d7) == LOW){
          json += "\"7\" : 1,";
        }else{
          json += "\"7\" : 0,";
        }

        if(digitalRead(d8) == LOW){
          json += "\"8\" : 1";
        }else{
          json += "\"8\" : 0";
        }

        json += "}";
        server->send(200, "text/plain", json);
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

int getPinNumber(String pinName) {
  if (pinName == "0") return D0;
  if (pinName == "1") return D1;
  if (pinName == "2") return D2;
  if (pinName == "3") return D3;
  if (pinName == "4") return D4;
  if (pinName == "5") return D5;
  if (pinName == "6") return D6;
  if (pinName == "7") return D7;
  if (pinName == "8") return D8;
  return -1; // Invalid pin
}

void handleLamp(String lampId) {
  // Get the value of {id} parameter
  // String lampId = server->arg("id");

  // Convert lampId to pin number
  int pinNumber = getPinNumber(lampId);

  String json = "{";

  if(digitalRead(pinNumber) == LOW){
    digitalWrite(pinNumber, HIGH);
  }else{
    digitalWrite(pinNumber, LOW);
  }

  if (pinNumber != -1) {
    json += "\"success\" : true,";
    if(digitalRead(pinNumber) == LOW){
      json += "\"message\" : \"Status ON\",";
    }else{
      json += "\"message\" : \"Status OFF\",";
    }
    json += "\"data\" : {";
    json += "\"id\" : \""+lampId+"\",";
    if(digitalRead(pinNumber) == HIGH){
      json += "\"status\" : 1";
    }else{
      json += "\"status\" : 0";
    }
    json += "}";
    json += "}";
  }else{
    json += "\"success\" : false,";
    json += "\"message\" : \"Invalid ID\",";
    json += "\"data\" : {}";
    json += "}";
  }
  server->send(200, "text/plain", json);

}

void loop() {
  // put your main code here, to run repeatedly:
  // kalau pake LOW ketika konek wifi langsung ke reset
  // kalau pake HIGH ketika ada tombol D3 ke on off ikut ke reset juga
  /*
  if (digitalRead(flashButtonPin) == LOW) {
    WiFiManager wm;
    wm.resetSettings();
    ESP.reset();
    Serial.println("WiFi settings reset");
    delay(1000); 
  }
  */
  
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
  ptr += ".flex-container {display: flex;flex-wrap: wrap;justify-content: center;}\n";
  ptr += ".flex-container>div {flex: 20%; margin: 10px;text-align: center;font-size: 30px;}\n";
  ptr += "@media (max-width: 800px) {.flex-container>div {flex: 25%;}}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP8266 Web Server</h1>\n";
  
  if(digitalRead(LED_BUILTIN) == LOW)
  {
    ptr +="<p>LED Status: ON</p><a class=\"button button-on\" href=\"/led/off\">ON</a>\n";
  }else{
    ptr +="<p>LED Status: OFF</p><a class=\"button button-off\" href=\"/led/on\">OFF</a>\n";
  }

  ptr +="<div class='flex-container'>\n";
  ptr +="<div>\n";
  if(digitalRead(d1) == LOW)
  {
    ptr +="<p>D1 Status: ON</p><a class=\"button button-on\" href=\"/d1/off\">ON</a>\n";
  }else{
    ptr +="<p>D1 Status: OFF</p><a class=\"button button-off\" href=\"/d1/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="<div>\n";
  if(digitalRead(d2) == LOW)
  {
    ptr +="<p>D2 Status: ON</p><a class=\"button button-on\" href=\"/d2/off\">ON</a>\n";
  }else{
    ptr +="<p>D2 Status: OFF</p><a class=\"button button-off\" href=\"/d2/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="<div>\n";

  if(digitalRead(d3) == LOW)
  {
    ptr +="<p>D3 Status: ON</p><a class=\"button button-on\" href=\"/d3/off\">ON</a>\n";
  }else{
    ptr +="<p>D3 Status: OFF</p><a class=\"button button-off\" href=\"/d3/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="<div>\n";

  if(digitalRead(d4) == LOW)
  {
    ptr +="<p>D4 Status: ON</p><a class=\"button button-on\" href=\"/d4/off\">ON</a>\n";
  }else{
    ptr +="<p>D4 Status: OFF</p><a class=\"button button-off\" href=\"/d4/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="</div>\n"; // end flex-container

  ptr +="<div class='flex-container'>\n";


  ptr +="<div>\n";
  if(digitalRead(d5) == LOW)
  {
    ptr +="<p>D5 Status: ON</p><a class=\"button button-on\" href=\"/d5/off\">ON</a>\n";
  }else{
    ptr +="<p>D5 Status: OFF</p><a class=\"button button-off\" href=\"/d5/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="<div>\n";

  if(digitalRead(d6) == LOW)
  {
    ptr +="<p>D6 Status: ON</p><a class=\"button button-on\" href=\"/d6/off\">ON</a>\n";
  }else{
    ptr +="<p>D6 Status: OFF</p><a class=\"button button-off\" href=\"/d6/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="<div>\n";

  if(digitalRead(d7) == LOW)
  {
    ptr +="<p>D7 Status: ON</p><a class=\"button button-on\" href=\"/d7/off\">ON</a>\n";
  }else{
    ptr +="<p>D7 Status: OFF</p><a class=\"button button-off\" href=\"/d7/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="<div>\n";

  if(digitalRead(d8) == LOW)
  {
    ptr +="<p>D8 Status: ON</p><a class=\"button button-on\" href=\"/d8/off\">ON</a>\n";
  }else{
    ptr +="<p>D8 Status: OFF</p><a class=\"button button-off\" href=\"/d8/on\">OFF</a>\n";
  }

  ptr +="</div>\n";

  ptr +="</div>\n"; // end flex-container

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
