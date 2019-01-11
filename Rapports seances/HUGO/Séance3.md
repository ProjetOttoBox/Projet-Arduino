# // Compte rendue de la séance 3//

Durant les deux semaines de pose pédagogique, mon objectif a été:
De finaliser la conception de L’OTTO BOX, a l’aide d’un nouveau logiciel: 
Fusion, un logiciel de conception 3D disponible sous Mac. 
Ainsi notre projet est constitué de deux parties: 
Un socle de 15 cm*15 cm et une boîte de 15 cm*15 cm*12 cm. 
Nous avons écrit sur le devant de la boîte le nom de celle-ci en braille pour permettre une compréhension du nom même pour les
personnes possédant un handicap de vision. 
Cependant durant la conception j’ai rencontré de nombreux problèmes.
Notamment quant à la dimension et aux symétries des différents éléments ai placé. 
De plus j’ai dû mesurer précisément l’ensemble des éléments que nous allons intégrer dans la boîte 
(LED, capteur de mouvement etc.) pour concevoir la boîte en conséquence. 
Une fois la conception terminée nous nous sommes rendue au fab lab pour démarrer l’impression. 
Actuellement l’impression est en cours et nous espérons pouvoir vous la présenter la semaine prochaine.

Cette semaine je me suis intéressé à la commande vocale avec l’application mit compagnon. 
Ainsi j’ai conçu une application disponible sur android pour notre projet. 
Cette application permet pour l’instant de se connecter en bluetooth à la carte arduino et d’allumer par commande vocale 
`différente pièce d’une maison qui est prête enregistrer, celles-ci sont schématisé par des LED incluses dans notre boîte 
qui s’allumera si la commande vocale est activée. Par exemple si l’utilisateur dit allume le salon>> la LED correspondant 
au salon sur la boîte va s’activer ainsi que la pièce correspondante.

Aujourd’hui j’ai finalisé le design de notre application celle-ci est maintenant fonctionnelle et active.
Par la suite je me suis occupé de faire fonctionner le capteur de mouvement PIR pour arduino, 
celui-ci envoi un message au terminale a chaque fois qu’un mouvement est détecté. 
Dans la semaine je m’occuperais de connecter ce PIR à une succession de LED qui s’allumera en conséquence.

 # //Code//
 Voici le code permettant de faire le liens avec arduino, MIT et le telephone:
 
 
 <pre><code>#include <SoftwareSerial.h>
#define RX 10
#define TX 11
#define led1 2 //Cuisine
#define led2 3 //salle de bain 
#define led3 4 //salle a manger
#define led4 5 //toilettes
#define led5 6 //chambre
#define led6 7 //garage
#define led7 8 //Salon
#define led8 9 //Couloir
SoftwareSerial BlueT(RX,TX);

void setup() {
  Serial.begin(9600);
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
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
    }
  }
}
</pre></code>
