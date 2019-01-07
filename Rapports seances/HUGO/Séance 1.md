# //Déroulement de la séance//

La séance d'aujourd'hui a était principalement concue autour de deux points de notre projet. 

Le premier était une préréalisation de la boîte finale (support physique).
  Pour ce faire une maquette papiers à etais réalisé. Ensuite j'ai décidé d'utiliser pour la réalisation de l'objet final le logiciel Inventor.
  Cependant étant donné que celui-ci n'existe pas sur Mac, j'ai dû télécharger un émulateur de Windows qui a pris du temps et je n'ai donc pas pue aller au bout de la réalisation de la boîte. 
  Objectif que je mettais fixer pour aujourd'hui. La réalisation de celle-ci devra être faite avant la semaine prochaine pour 
  permettre l'impression en 3D au fab lab avant la fin de semaine prochaine.
  
Le second était l'utilisation d'un nouveau logiciel.
  Ainsi a l'aide de MIT A2P qui est un site tous public permettant la creation de code de type bloc pour des applications sur smartphone
  j'ai réalisé une premiere application basique permettant d'activer et d'ettiendre une led avec un bouton tactile, et j'ai également ajouté 
  une connection bluetooth.
  
 # //Code//
 Voici le code permettant de faire le liens avec arduino, MIT et le telephone:
 
 
 <pre><code>#include <SoftwareSerial.h>
#define RX 10
#define TX 11
#define led 9
SoftwareSerial BlueT(RX,TX);

void setup() {
  Serial.begin(9600);
  pinMode(RX,INPUT);
  pinMode(TX,OUTPUT);
  pinMode(led,OUTPUT);
  digitalWrite(led,HIGH);
  BlueT.begin(9600);
}
void loop(){
  int recvChar;
  while(1){
    if(BlueT.available()){
      recvChar = BlueT.read();
      Serial.print(recvChar);
      if(recvChar==1){
        digitalWrite(led,LOW);
      }
      else if (recvChar == 0){
        digitalWrite(led,HIGH);
      }
    }
  }
}
</code></pre>
![image](https://raw.githubusercontent.com/ProjetOttoBox/Projet-Arduino/master/Ressources/code.jpg)
