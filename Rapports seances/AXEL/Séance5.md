# // Déroulement de la séance 5 //

Durant cette séance nous avons avec Hugo effectuer les soudures des hauts parleurs .
Comme nous avons beaucoup de modules à brancher, les pins disponibles sur la carte Atmel Mini n'étaient pas suffisants
nous sommes donc passer sur une carte Atmel Mega 2560 qui comportent beaucoup plus de pin OUT. Il y a également sur la carte 8 
pin dédiés à la communication carte-modules.

[image1](https://raw.githubusercontent.com/ProjetOttoBox/Projet-Arduino/master/Ressources/51739620_319402441984273_8378919030521593856_n.jpg)


J'ai donc de mon coté brancher le module RTC ainsi que l'écran LCD. J'ai également branché le module ESP aux deux ports 
RX1 et TX1 de la carte Mega pour la communication ESP-Carte Arduino. Cette connexion permettra d'envoyer les données météo et 
de les exploiter ensuite.

[image2](https://raw.githubusercontent.com/ProjetOttoBox/Projet-Arduino/master/Ressources/51793331_528393944334002_3422025174591995904_n.jpg

L'ESP n'est toujours pas exploitable sur Mac OS, je n'ai donc pas pu tester la communication entre l'ESP et la carte Mega.
Cependant les données météo sont toujours récupérées correctement. J'utilisais Parallel Desktop mais la periode d'essai
est terminée.

J'ai donc installé via BootCamp un OS Windows afin de pouvoir programmer l'ESP. Je pensais pouvoior faire cela durant la 
séance, malheuresuement je me suis heurté a de nombreuses reprises à des problèmes de partition de mon disque.
Je vais devoir continuer à installer un OS Windows chez moi.
