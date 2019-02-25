# // Déroulement de la séance 6 //

Durant cette séance nous avons avec Hugo décider de tester l'ensemble de nos fonctionnalitées afin de voir si tout fonctionne 
comme il faut. La commande vocale est opérationnelle pour les LED, la météo est correctement récupérée, les fichiers MP3 sont correctement lus et l'écran LCD ainsi que l'horloge également.
Hugo avait préenregistré les fichiers MP3 qui seront lus pour la météo (Pluie, soleil,...) à l'aide du synthétiseur de voix de google traduction.

J'ai de mon coté pu installer (enfin) l'ESP32 sur le mac d'Hugo ce qui m'as permi de modifier le programme de l'ESP afin de communiquer avec l'Arduino (connection Serial classique), cependant en feuilletant la doc sur internet, j'ai trouvé que l'esp n'utilise pas la même bibliothèque Serial, j'ai du donc la modifier afin qu'elle puisse prendre en compte la carte ESP32 (séléctionné FireBeetle ESP32 sur l'IDE Arduino). Cependant la communication n'est toujours pas opérationnelle. 

En parallèle Hugo pendant la semaine est allé voir Mr. Masson afin de confectionner un transformateur 220v-5v qui alimentera tout notre projet une fois les programmes implémentés dans la carte et l'ESP.

Autre problème qui lui est plus technique est que comme nous ne pouvons pas lancer deux programmes par IDE et que nous possèdons deux cartes différentes, nous ne pouvons pas upload tout le programme, c'est à dire les LED, l'écran, l'horloge, etc en plus de celui de la météo pour l'ESP. Les programmes doivent être upload séparémment.


Nous règlerons le problème de communication par la suite. Il s'agit d'ailleurs de la dernière étape pour que notre projet soit fonctionnel (qu'il réponde a nos attentes de début de projet) .
