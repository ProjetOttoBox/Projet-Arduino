#include <WiFi.h>
#include <ArduinoJson.h>

const char* ssid     = "SFR_DC78";      // SSID of local network
const char* password = "67heyt5wvn44vitt5wtp";   // Password on network
String APIKEY = "232cf000a68e5902c6a783b0d12b4985";
String CityID = "253394"; //Sparta, Greece

int  counter = 60;

String weatherDescription ="";
String weatherLocation = "";
String Country;
float Temperature;
float Humidity;
float Pressure;

void setup() {
  Serial.begin(115200);
  Serial.println("...Connecting");  
  Serial.println("Connecting");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Connected");
  delay(1000);

}
