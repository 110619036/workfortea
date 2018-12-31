#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`


const char* ssid = "Darkkiller";
const char* password = "0971093999";


SSD1306Wire  display(0x3c, 21, 22);
int freq = 5000;
int ledchannel = 0;
int resolution = 8;


const int buttonPin = 33;
float sensor = 25;                     
float gas_value;
int money = 0;
int buttonState = 0;


WebServer server(80);
char website[3000];


void handleSensorData(){
  String json = "{\"vr\":";
  json += money;
  json += "}";
  server.send(200,"application/json", json);
}


void handleRoot() {
  snprintf(website,1000,"<!DOCTYPE html><html lang=\"en\"><head> <meta charset=\"UTF-8\"> <script src=\"https://code.jquery.com/jquery-2.2.4.min.js\"></script> <script>setInterval(requestData, 500); function requestData(){$.get(\"/sensors\") .done(function(data){if(data){$(\"#resis\").text(data.vr);}else{$(\"#resis\").text(\"?\");}}) .fail(function(){console.log(\"fail\");});}</script> <title>Money counter</title></head><body> <div class=\"container\"style=\"text-align:center;background-color: rgb(255, 248, 235);\"><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br> <h1>目前金額總數為<span id=\"resis\"></span></h1><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br></div></body></html>");
  server.send(200, "text/html", website);
  
}


void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}


void setup(void) {
  ledcSetup(ledchannel,freq,resolution);
  ledcAttachPin(LED_BUILTIN,ledchannel);

  display.init();

  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);
  
  pinMode(buttonPin, INPUT);
  pinMode(sensor,INPUT);
  
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
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

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/sensors", handleSensorData);
  server.onNotFound(handleNotFound);

  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

    display.setTextAlignment(TEXT_ALIGN_RIGHT);

}


void loop(void) {
    gas_value=analogRead(sensor);
    buttonState = digitalRead(buttonPin);

    Serial.println(gas_value);
    display.clear();
    delay(7);
    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 10, "This is a person");
    display.display();

    if(money < 10){
   display.clear();
    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He is thin");
        display.display();
      }

      
    else if(money >= 10 && money < 20){
    display.clear();
    
    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He fat a little");
        display.display();
      }

    else if(money >= 20 && money < 30){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He is medium build");
        display.display();
      }

    else if(money >= 30 && money < 40){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He can study");
        display.display();
      }

      else if(money >= 40 && money < 50){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He get papper");
        display.display();
      }

      else if(money >= 50 && money < 60){
    display.clear();
    
    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "");
        display.display();
      }

      else if(money >= 60 && money < 70){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He have friends");
        display.display();
      }

      else if(money >= 70 && money < 80){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He have a good job");
        display.display();
      }

      else if(money >= 80 && money < 90){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He get marry");
        display.display();
      }

      else if(money >= 40 && money < 50){
    display.clear();

    delay(7);

    display.setTextAlignment(TEXT_ALIGN_LEFT);
    display.setFont(ArialMT_Plain_16);
    display.drawString(0, 40, "He have happy life");
        display.display();
      }
   
    if(gas_value < 2000){
    money++;
    }

    if (buttonState == HIGH) {
    money = 0;
  } 
  
  server.handleClient();
}
