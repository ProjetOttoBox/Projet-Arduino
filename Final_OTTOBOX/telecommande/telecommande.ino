#include <IRremote.h>
#include <IRremoteInt.h>
 
IRsend ir_send; // crée une instance
 
void setup() 
{ 
  pinMode (3, OUTPUT);
}
 
void loop() 
{ 
   ir_send.sendNEC(0xE0E040BF, 32); // code télécommande et nombre de bits
   delay(10000); //On attends 10s avant de rejouer le code
}
