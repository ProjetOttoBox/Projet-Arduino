

// CODE POUR L'ESP//


// Importation des librairies
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <SoftwareSerialEsp32.h>

// Définition des constantes
const char* SSID     = "Mieux que SFR"; // Le nom de votre réseau Wifi
const char* SSID_MDP = "beuteu235"; // Le mot de passe de vôtre réseau Wifi
const char* LANGUE = "fr"; // Langue (ar,bg,ca,cz,de,el,en,fa,fi,fr,gl,hr,hu,it,ja,kr,la,lt,mk,nl,pl,pt,ro,ru,se,sk,sl,es,tr,ua,vi,zh_cn,zh_tw)
const char* EMPLACEMENT = "Antibes"; // Le nom de votre ville
const char* API = "1d7a7c2444395f0ea4f2064f4110dff9"; // Votre numéro d'API pour OpenWeatherMap

// Déclaration des objets
HTTPClient http;
StaticJsonBuffer<1000> jsonBuffer;

//Communications RX TX
SoftwareSerialEsp32 Esp32(9,10); // RX,TX

void setup()
{
  Serial.begin(9600);
  Esp32.begin(9600);
  //Serial.println();

  WiFi.begin(SSID,SSID_MDP);

  //Serial.print("Connection");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
   // Serial.print(".");
  }
  //Serial.println();

  //Serial.print("Connecté, adresse IP: ");
  //Serial.println(WiFi.localIP());
}

void loop() 
{


  if(WiFi.status() != WL_CONNECTED) {
     // Serial.println("WiFi non connecté !");
  }
  else {  
      //Serial.println("Envoi de la requête");
      String url = "http://api.openweathermap.org/data/2.5/weather?q=";
      url+=EMPLACEMENT;
      url+="&APPID=";
      url+=API;
      url+="&units=metric";
      http.begin(url);
      int httpCode = http.GET();
      if (httpCode == 200) {
        String reponse = http.getString();
        
        JsonObject& root = jsonBuffer.parseObject(reponse);

        long id = root["id"]; // 2950159
        const char* name = root["name"]; // "Berlin"
        int cod = root["cod"]; // 200       

        const size_t capacity = JSON_ARRAY_SIZE(1) + JSON_OBJECT_SIZE(1) + 2*JSON_OBJECT_SIZE(2) + JSON_OBJECT_SIZE(4) + JSON_OBJECT_SIZE(5) + JSON_OBJECT_SIZE(6) + JSON_OBJECT_SIZE(12) + 390;
        DynamicJsonBuffer jsonBuffer(capacity);

        const char* json = "{\"coord\":{\"lon\":13.39,\"lat\":52.52},\"weather\":[{\"id\":600,\"main\":\"Snow\",\"description\":\"light snow\",\"icon\":\"13n\"}],\"base\":\"stations\",\"main\":{\"temp\":273.66,\"pressure\":1023,\"humidity\":90,\"temp_min\":273.15,\"temp_max\":274.15},\"visibility\":10000,\"wind\":{\"speed\":1,\"deg\":270},\"clouds\":{\"all\":75},\"dt\":1547140800,\"sys\":{\"type\":1,\"id\":1275,\"message\":0.0027,\"country\":\"DE\",\"sunrise\":1547104409,\"sunset\":1547133307},\"id\":2950159,\"name\":\"Berlin\",\"cod\":200}";

        float coord_lon = root["coord"]["lon"]; // 13.39
        float coord_lat = root["coord"]["lat"]; // 52.52

        JsonObject& weather0 = root["weather"][0];
        int weather0_id = weather0["id"]; // 600
        const char* weather0_main = weather0["main"]; // "Snow"
        const char* weather0_description = weather0["description"]; // "light snow"
        const char* weather0_icon = weather0["icon"]; // "13n"

         
        const char* base = root["base"]; // "stations"

        JsonObject& main = root["main"];
        int main_temp = main["temp"]; // 273.66
        int main_pressure = main["pressure"]; // 1023
        int main_humidity = main["humidity"]; // 90
        float main_temp_min = main["temp_min"]; // 273.15
        float main_temp_max = main["temp_max"]; // 274.15

        int visibility = root["visibility"]; // 10000

        int wind_speed = root["wind"]["speed"]; // 1
        int wind_deg = root["wind"]["deg"]; // 270

        int clouds_all = root["clouds"]["all"]; // 75

        long dt = root["dt"]; // 1547140800

        JsonObject& sys = root["sys"];
        int sys_type = sys["type"]; // 1
        int sys_id = sys["id"]; // 1275
        float sys_message = sys["message"]; // 0.0027
        const char* sys_country = sys["country"]; // "DE"
        long sys_sunrise = sys["sunrise"]; // 1547104409
        long sys_sunset = sys["sunset"]; // 1547133307

        Serial.println(weather0_description);
        Serial.println(main_temp);
        Esp32.write(weather0_description);
        Esp32.write(main_temp);
        
        
      }
      else {
        Serial.print("Erreur HTTP: ");
        Serial.println(httpCode);
        }
      
      http.end();
      
    }
  
  delay (1000);
}
