#include <SoftwareSerial.h>
#include <WiFi.h>
#include <IRremote.h>
#include <Wire.h>    // Bibliothèque pour l'I2C
#include "RTClib.h"  // Bibliothèque pour le module RTC
#include <LiquidCrystal.h> // Bibliothèque pour l'écran

RTC_DS1307 RTC;      // Instance du module RTC de type DS1307
LiquidCrystal lcd(22,24,26,28,30,32);
IRsend ir_send;

//#include <HTTPClient.h>
//#include <ArduinoJson.h>
//#include <SoftwareSerialEsp32.h>
#define RXa 10
#define TXa 11
#define led1 2 //Cuisine
#define led2 3 //salle de bain 
#define led3 4 //salle a manger
#define led4 5 //toilettes
#define led5 6 //chambre
#define led6 7 //garage
#define led7 8 //Salon
#define led8 9 //Couloir
#define char* weather0_description;
SoftwareSerial BlueT(RXa,TXa);
//SoftwareSerialEsp32 Esp32(17,16); // RX,TX
// MP3// 
#define RX 12
#define TX 13
SoftwareSerial mySerial(RX,TX);
//////////////////////////////////////////////////////////////////////////////////// 
//all the commands needed in the datasheet(http://geekmatic.in.ua/pdf/Catalex_MP3_board.pdf) 
static int8_t Send_buf[8] = {0} ;//The MP3 player undestands orders in a 8 int string 
                                 //0X7E FF 06 command 00 00 00 EF;(if command =01 next song order)  
#define NEXT_SONG 0X01  
#define PREV_SONG 0X02  
#define CMD_PLAY_W_INDEX 0X03 //DATA IS REQUIRED (number of song) 
#define VOLUME_UP_ONE 0X04 
#define VOLUME_DOWN_ONE 0X05 
#define CMD_SET_VOLUME 0X06//DATA IS REQUIRED (number of volume from 0 up to 30(0x1E)) 
#define SET_DAC 0X17 
#define CMD_PLAY_WITHVOLUME 0X22 //data is needed  0x7E 06 22 00 xx yy EF;(xx volume)(yy number of song) 
#define CMD_SEL_DEV 0X09 //SELECT STORAGE DEVICE, DATA IS REQUIRED 
#define DEV_TF 0X02 //HELLO,IM THE DATA REQUIRED 
#define SLEEP_MODE_START 0X0A 
#define SLEEP_MODE_WAKEUP 0X0B 
#define CMD_RESET 0X0C//CHIP RESET 
#define CMD_PLAY 0X0D //RESUME PLAYBACK 
#define CMD_PAUSE 0X0E //PLAYBACK IS PAUSED 
#define CMD_PLAY_WITHFOLDER 0X0F//DATA IS NEEDED, 0x7E 06 0F 00 01 02 EF;(play the song with the directory \01\002xxxxxx.mp3 
#define STOP_PLAY 0X16 
#define PLAY_FOLDER 0X17// data is needed 0x7E 06 17 00 01 XX EF;(play the 01 folder)(value xx we dont care) 
#define SET_CYCLEPLAY 0X19//data is needed 00 start; 01 close 
#define SET_DAC 0X17//data is needed 00 start DAC OUTPUT;01 DAC no output 
////////////////////////////////////////////////////////////////////////////////////  
void sendCommand(int8_t command, int16_t dat) 
{ 
delay(20); 
Send_buf[0] = 0x7e; //starting byte 
Send_buf[1] = 0xff; //version 
Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte 
Send_buf[3] = command; // 
Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback 
Send_buf[5] = (int8_t)(dat >> 8);//datah 
Send_buf[6] = (int8_t)(dat); //datal 
Send_buf[7] = 0xef; //ending byte 
for(uint8_t i=0; i<8; i++)// 
{ 
  mySerial.write(Send_buf[i]) ; 
} 
} 
// FIN MP3//

void setup() {  
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
  
  mySerial.begin(9600);//Start our Serial coms for our serial monitor! 
  delay(500);//Wait chip initialization is complete 
  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card   
  delay(200);
  Serial.begin(9600);
  pinMode(RXa,INPUT);
  pinMode(TXa,OUTPUT);
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  pinMode(led5,OUTPUT);
  pinMode(led6,OUTPUT);
  pinMode(led7,OUTPUT);
  pinMode(led8,OUTPUT);
  digitalWrite(led1,HIGH);
  digitalWrite(led2,HIGH);
  digitalWrite(led3,HIGH);
  digitalWrite(led4,HIGH);
  digitalWrite(led5,HIGH);
  digitalWrite(led6,HIGH);
  digitalWrite(led7,HIGH);
  digitalWrite(led8,HIGH);
  BlueT.begin(9600);
  
}
void loop(){
  DateTime now=RTC.now(); //Récupère l'heure et le date courante
  
  affiche_date_heure(now);  //Converti la date en langue humaine
  
  delay(1000); // delais de 1 seconde
  int recvChar;
  while(true){
    if(BlueT.available()){
      recvChar = BlueT.read();
      Serial.print(recvChar);
      if(recvChar==1){
        digitalWrite(led1,LOW);
      }
      else if (recvChar == 0){
        digitalWrite(led1,HIGH);
      }
      else if(recvChar==2){
        digitalWrite(led2,LOW);
      }
      else if (recvChar == 3){
        digitalWrite(led2,HIGH);
      }
      else if(recvChar==4){
        digitalWrite(led3,LOW);
      }
      else if (recvChar == 5){
        digitalWrite(led3,HIGH);
      }
      else if(recvChar==6){
        digitalWrite(led4,LOW);
      }
      else if (recvChar == 7){
        digitalWrite(led4,HIGH);
      }
      else if(recvChar==8){
        digitalWrite(led5,LOW);
      }
      else if (recvChar == 9){
        digitalWrite(led5,HIGH);
      }
      else if(recvChar==10){
        digitalWrite(led6,LOW);
      }
      else if (recvChar == 11){
        digitalWrite(led6,HIGH);
      }
      else if(recvChar==12){
        digitalWrite(led7,LOW);
      }
      else if (recvChar == 13){
        digitalWrite(led7,HIGH);
      }
      else if(recvChar==14){
        digitalWrite(led8,LOW);
      }
      else if (recvChar == 15){
        digitalWrite(led8,HIGH);
      }
      else if (recvChar == 16){
        digitalWrite(led1,LOW);
        digitalWrite(led2,LOW); 
        digitalWrite(led3,LOW); 
        digitalWrite(led4,LOW); 
        digitalWrite(led5,LOW); 
        digitalWrite(led6,LOW); 
        digitalWrite(led7,LOW); 
        digitalWrite(led8,LOW);          
      }
      else if (recvChar == 17){
        digitalWrite(led1,HIGH);
        digitalWrite(led2,HIGH); 
        digitalWrite(led3,HIGH); 
        digitalWrite(led4,HIGH); 
        digitalWrite(led5,HIGH); 
        digitalWrite(led6,HIGH); 
        digitalWrite(led7,HIGH); 
        digitalWrite(led8,HIGH);
      }
     else if (recvChar == 18){
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00203);
      delay(3500);
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00204);
     }
     else if (recvChar == 19){
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00203);
      delay(3500);
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00202);
     }
     else if (recvChar == 20){
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00205);
      delay(3500);
     }
     else if (recvChar == 21){
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00203);
      delay(3500);
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00208);
     }
     else if (recvChar == 23){
      sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00103);
     }
     else if (recvChar == 24){
      sendCommand(CMD_PAUSE, 0X0E001);
     }
    }
  }
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
