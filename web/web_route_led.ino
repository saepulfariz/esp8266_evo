/*
 * This ESP8266 NodeMCU code was developed by newbiely.com
 *
 * This ESP8266 NodeMCU code is made available for public use without any restriction
 *
 * For comprehensive instructions and wiring diagrams, please visit:
 * https://newbiely.com/tutorials/esp8266/esp8266-controls-led-via-web
 */
// https://newbiely.com/tutorials/esp8266/esp8266-controls-led-via-web

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define LED_PIN D6  // The ESP8266 pin connected to LED

const char *ssid = "YOUR_WIFI_SSID";     // CHANGE IT
const char *password = "YOUR_WIFI_PASSWORD";  // CHANGE IT

ESP8266WebServer server(80); // Web server on port 80

int LED_state = LOW;

String getHTML() {
  String html = "<!DOCTYPE HTML>";
  html += "<html>";
  html += "<head>";
  html += "<link rel='icon' href='data:,'>";
  html += "</head>";
  html += "<p>LED state: <span style='color: red;'>";

  if (LED_state == LOW)
    html += "OFF";
  else
    html += "ON";

  html += "</span></p>";
  html += "<a href='/led1/on'>Turn ON</a>";
  html += "<br><br>";
  html += "<a href='/led1/off'>Turn OFF</a>";
  html += "</html>";

  return html;
}

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LED_state);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Print the ESP8266's IP address
  Serial.print("ESP8266 Web Server's IP address: ");
  Serial.println(WiFi.localIP());

  // home page
  server.on("/", HTTP_GET, []() {
    Serial.println("ESP8266 Web Server: New request received:");
    Serial.println("GET /");
    server.send(200, "text/html", getHTML());
  });

  // Route to control the LED
  server.on("/led1/on", HTTP_GET, []() {
    Serial.println("ESP8266 Web Server: New request received:");
    Serial.println("GET /led1/on");
    LED_state = HIGH;
    digitalWrite(LED_PIN, LED_state);
    server.send(200, "text/html", getHTML());
  });
  server.on("/led1/off", HTTP_GET, []() {
    Serial.println("ESP8266 Web Server: New request received:");
    Serial.println("GET /led1/off");
    LED_state = LOW;
    digitalWrite(LED_PIN, LED_state);
    server.send(200, "text/html", getHTML());
  });

  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.handleClient();

  // Your code here
}
