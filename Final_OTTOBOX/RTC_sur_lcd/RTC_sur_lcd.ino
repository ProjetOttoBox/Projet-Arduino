#include <Wire.h>    // Bibliothèque pour l'I2C
#include "RTClib.h"  // Bibliothèque pour le module RTC
#include <LiquidCrystal.h> // Bibliothèque pour l'écran

RTC_DS1307 RTC;      // Instance du module RTC de type DS1307
LiquidCrystal lcd(22,24,26,28,30,32);

void setup(void) {
  //Initialisation de l'éran
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 1);
  
  // Initialise la liaison I2C  
  Wire.begin();
  
  // Initialise le module RTC
  RTC.begin();
 
  //Initialise la date et le jour au moment de la compilation 
  // /!\ /!\ Les lignes qui suivent sert à définir la date et l'heure afin de régler le module, 
  // pour les montages suivant il ne faut surtout PAS la mettre, sans à chaque démarrage 
  // le module se réinitialisera à la date et heure de compilation
  
  DateTime dt = DateTime(__DATE__, __TIME__);
  RTC.adjust(dt);
  
}

void loop(){
  
  DateTime now=RTC.now(); //Récupère l'heure et le date courante
  
  affiche_date_heure(now);  //Converti la date en langue humaine
  
  delay(1000); // delais de 1 seconde
}

//Converti le numéro de jour en jour /!\ la semaine commence un dimanche
String donne_jour_semaine(uint8_t j){ 
  switch(j){
   case 0: return "DIM";
   case 1: return "LUN";
   case 2: return "MAR";
   case 3: return "MER";
   case 4: return "JEU";
   case 5: return "VEN";
   case 6: return "SAM";
   default: return "   ";
  }
}

// affiche la date et l'heure sur l'écran
void affiche_date_heure(DateTime datetime){
  
  // Date 
  String jour = donne_jour_semaine(datetime.dayOfWeek()) + " " + 
                Vers2Chiffres(datetime.day())+ "/" + 
                Vers2Chiffres(datetime.month())+ "/" + 
                String(datetime.year(),DEC);
  
  // heure
  String heure = "";
  heure  = Vers2Chiffres(datetime.hour())+ ":" + 
           Vers2Chiffres(datetime.minute())+ ":" + 
           Vers2Chiffres(datetime.second());

  //affichage sur l'écran
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(jour);
  lcd.setCursor(0, 1);
  lcd.print(heure);
}

//permet d'afficher les nombres sur deux chiffres
String Vers2Chiffres(byte nombre) {
  String resultat = "";
  if(nombre < 10)
    resultat = "0";
  return resultat += String(nombre,DEC);  
}
