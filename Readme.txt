Antoine PETIT & Honore NINTUNZE

Pour nettoyer le dossier:
	make realclean

Pour compiler:
	make

Ceci créera le fichier executable pingpong

En lançant ./pingpong on constate que à chaque intérruption du timer on switch entre les fonctions ping, pong et pang. 
Au bout d'un certain temps la fonction pang se termine et on switch uniquement entre ping et pong.
