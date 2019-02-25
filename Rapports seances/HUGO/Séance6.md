# // Compte rendue de la séance 6 + vacances //

Durant la séance numéro 6 nous avons avec axel mit en commun nos travaux , d'un coté l'api méteo et l'esp32 et de l'autre l'application pour smartphone et les codes en blocs pour s'occupé de relié les deux de manière a avoir une méteo fonctinnant en controle vocale. Cependant nous avons rencontré de nombreux problème. Notament le fait que la carte Esp32 ou est positionner la méteo est difficile d'accès avec notre a applications et ils nous étaient donc compliqué de récuperer la méteo pour la mettre dans notre projet. Après une heure de rechercher nous avons décider de nous en occupper plutard et de finaliser la totalité de notre projet pour ensuite rajouter cette partie.

Ainsi avec l'aide de Mr Masson j'ai refait les soudure des LED. Mr Masson ma permi d'apprendre a faire des soudures bien plus propres que celle que j'ai pu faire auparavant. Après avoir souder les LED entres elles. Voici le résultat de la soudure.

![Images](https://github.com/ProjetOttoBox/Projet-Arduino/blob/master/Ressources/52713787_243406123277956_7484131507150258176_n.jpg).

De plus avant cette séance et pendant la semaine de pause j'ai rajouté une nouvelle fonctionalité sous les conseils de axel. Notre boite en plus de nous repondre la méteo pourra aussi nous donner de la musique et nous indiquer qu'elle piece est allumer grace au enceinte et au code que voici .


<pre><code>#include <SoftwareSerial.h>;
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
void sendCommand(int8_t command, int16_t dat) { 
  delay(20); 
  Send_buf[0] = 0x7e; //starting byte 
  Send_buf[1] = 0xff; //version 
  Send_buf[2] = 0x06; //the number of bytes of the command without starting byte and ending byte 
  Send_buf[3] = command; // 
  Send_buf[4] = 0x00;//0x00 = no feedback, 0x01 = feedback 
  Send_buf[5] = (int8_t)(dat >> 8);//datah 
  Send_buf[6] = (int8_t)(dat); //datal 
  Send_buf[7] = 0xef; //ending byte 
  for(uint8_t i=0; i<8; i++){ 
    mySerial.write(Send_buf[i]) ; 
  } 
} 
void setup() {
  mySerial.begin(9600);//Start our Serial coms for our serial monitor! 
  delay(500);//Wait chip initialization is complete 
  sendCommand(CMD_SEL_DEV, DEV_TF);//select the TF card   
  delay(200);
}

void loop() {
  sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00201);//play the first song with volume 15 class 
  delay(2000);
  sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00301);
  delay(1200);
  sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00601);
  delay(2000);
  sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00203);
  delay(3000);
  sendCommand(CMD_PLAY_WITHFOLDER, 0X0F00204);
  delay(100000);
}
</code></pre>

Ce programme par exemple vas dans la carte micro sd cherche le dossier numero 00X et joue le fichier son 0X.

De plus j'ai également regardé la possibilté d'une diode ir pour allumer et eteindre un televiseur. 
A l'aide d'un capteur j'ai récuperé le code hexa du signal envoyé par la télecommande pour allumé et j'ai éffectué ce code qui pour l'instant ne fonctionne pas parfaitement 

<pre><code>/* 
  Emission infrarouge 
*/

#include <IRremote.h>

IRsend emission_ir; // crée une instance

void setup() 
{ 
}

void loop() 
{ 
   emission_ir.sendNEC(0xE0E0F00F, 32); // code télécommande CGV on/off 
   delay(10000); 
}
</code></pre>

ET pour finir avec l'aide d'un ancien peip2 ayant une imprimmante 3D nous avons revue le design de notre boite. 

