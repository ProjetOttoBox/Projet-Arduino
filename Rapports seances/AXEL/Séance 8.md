# // Déroulement de la séance 8 //

Durant cette séance nous avons décider avec Hugo d'abandonner le module Esp car la communication entre l'Esp et l'arduino était 
très complexe et emplie de bug et problèmes en tout genres.

Nous sommes donc directement passer par MIT App Inventor, le site qui nous a permis de coder l'application pour les commandes 
vocales sur le téléphone. Via MIT, nous avons à notre disposition un "lecteur" web qui permet de parcourir le fichier Json
fournit par l'API de OpenWeather grâce au lien suivant : 
<pre><code> http://api.openweathermap.org/data/2.5/weather?q=Antibes&APPID=1d7a7c2444395f0ea4f2064f4110dff9&units=metric </code></pre>

Le code MIT permet donc de vérifier si le temps est nuageux, pluvieux,... et d'envoyer cette information à la carte arduino
via Bluetooth.

Coté Arduino nous avons ajouter au code la partie suivante : 

![Image](https://raw.githubusercontent.com/ProjetOttoBox/Projet-Arduino/master/Ressources/54114892_2799100553647524_1761937361689640960_n.jpg)

Sur MIT en fonction de la météo on envoi des nombres et ces nombres correspondent aux différentes météo.
Ceci permet au module Mp3 de jouer les enregistrements qui correspondent à la météo.

A ce jour le projet est terminé il nous reste à installer la diode InfraRouge pour commander la télé et à faire les finitions 
des branchements et de la boite pour que le tout soit propre.
