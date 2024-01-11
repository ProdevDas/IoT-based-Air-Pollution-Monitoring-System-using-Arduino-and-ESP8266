#include <ESP8266WiFi.h>
#include "secrets.h"
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#define DEBUG true

char ssid[] = "realme_9_Pro_5G";   // your network SSID (name) 
char pass[] = "8472037351";   // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
// WiFiClient  client;
ESP8266WebServer server(80);
// Initialize our values
float air_quality=0;
String page = "";


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, pass);
  
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nConnected.");
  Serial.print("Server begin at IP ");

  Serial.println(WiFi.localIP());  // Print IP address of NodeMCU

  server.on("/",[](){
     page = "<h1>IOT Air Pollution Monitoring System</h1>"; //string named page and stored the output in it

    page += "<p><h2>";   

    page+= " Air Quality is ";

    page+= air_quality;

    page+= " PPM";

    page += "<p>";

    if (air_quality<=1000)

    {

      page+= "Fresh Air";

    }

      else if(air_quality<=2000 && air_quality>=1000)

    {

      page+= "Poor Air";

    }


      else if (air_quality>=2000 )

    {

      page+= "Danger! Move to Fresh Air";

    }


    page += "</h2></p></BODY></HTML>";

    server.send(200, "text/html", page);

  });

  server.begin(); // Start the server
  Serial.println("Web server started!");
}
  


void loop() {
  if (Serial.available() > 0)
    {
    String data = Serial.readStringUntil('\n'); //  it will read untill \n 
    air_quality=data.toFloat();
    Serial.println(air_quality);
    }
  delay(1000);
  server.handleClient();
  
} 