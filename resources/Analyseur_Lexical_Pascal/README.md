# Mini-Compilateur Pascal en C

## Désambiguïsation

Il s'agit d'une implémentation d'un compilateur de Pascal en C réalisé pendant les TP de compilation

## Exécution

Pour exécuter le compilateur, taper les commandes suivantes:

    gcc compilateur.c -o compilateur
    ./compilateur test01.pas 

*Remarque: Vous pouvez tester votre propre fichier en l'ajoutant au répertoire "samples" et en changeant test01.pas dans la commande ci-dessus par le nom de votre fichier.*

## Contenu

Ce projet contient un fichier main appelé "compilateur.c" et trois sous-dossiers.

### Dossier 1: analyseurs

Ce dossier contient les différents analyseurs dont nous avons besoin pour notre compilateur:

    analyseur_lexical.c
    analyseur_syntaxique.c
    analyseur_semantique.c

### Dossier 2: headers

Ce dossier contient les variables globales et les instanciations nécessaires à l'exécution de nos programmes

    globals.h

### Dossier 3: samples

Ce dossier contient des programmes pascal qu'on peut tester

    *.pas
