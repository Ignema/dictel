# Projet Compilation: Création d'un nouvelle langage de programmation

## Dictel: portabilité élevée et programmation memory-driven

### Objectifs

- Créer un langage qui brouille les frontiéres entre les variables et les fonctions et d'autres outils de codage en introduisant une structure unique qui stocke et suit tous les composants d'un programme.

- Définir un cadre général qui peut améliorer la façon dont nous échangeons des algorithmes et des scripts en tirant parti d'un middleware que tout autre langage peut interpréter facilement.

- Amélioration de la façon dont nous stockons les variables en mémoire en ajoutant de nouveaux paradigmes qui gèrent le *heap* et le *stack* d'une maniere plus efficace.

- Mettre l'accent sur la réutilisabilité du code en mettant à niveau les blocs conditionnels et itératifs en pseudo-fonctions pouvant être appelées plusieurs fois.

- Simplifier la concurrence et le threading en ajoutant l'option pour tout bloc donné à s'exécuter de manière asynchrone dans son propre thread géré par le langage. Cela rendra nécessaire d'introduire un type de données responsable du transfert des données via les *pipes*. Le langage utilisera les *pipes* de C pour introduire une approche plus intuitive pour son utilisation.

- Le but le plus ambitieux de ce projet et le plus intéressant est de créer des scripts simplement en spécifiant quelques variables. Puisque le langage est créé par une structure de données unique, cette dernière serait capable de construire des instructions de manière autonome.

### Motivation

De nombreux langages de programmation sont conçus d'une manière standard qui permet à l'utilisateur d'assumer la responsabilité de gérer ses variables manuellement. Dictel est un langage qui offrira des outils pour aider à faire les choses de manière plus sécurisée et concise. De plus, il n'existe pas de moyen standardisé pour traduire un langage à une autre. Dictel peut aussi fonctionner comme une couche intermédiaire afin que les programmes puissent devenir facilement portables puisque le langage ne stocke que des paires clé-valeur de variables qui composent le script. Cela peut également inclure des fonctions et bien sûr la fonction *main*.

### Bouts de code

#### Création d'un variable avec inference de type

    add(monVariable, 45)

#### Création d'un variable sans initialisation (null par defaut)

    add(monVariable)

#### Création d'un variable pour une seul utilisation avant d'etre liberer

    add(monVariable, 45, use=1)

#### Création d'un variable avec un type specifique pour eviter l'inference du type

    add(monVariable, 45, type="int")

#### Création d'un variable avec un allocation dynamique(en octet)

    add(monVariable, allocate="5*sizeof(int)")

#### Création d'un variable immutable(constante)

    add(monVariable, 45, state="immutable")

#### Création d'un variable non-nullable(raise error if monVariable is null)

    add(monVariable, 45, state="nonNullable")

#### Création d'un variable de type tableau

    add(monVariable, [45, 46, 47], type="int[]")

#### Création d'une fonction

    add(maFonction, kind="function", (monVariable) => {
        monVariable = monVariable + 1
    })

#### Création d'une fonction asynchrone

    add(maFonction, kind="function", (monVariable) => {
        monVariable = monVariable + 1
    }, run="asynchron")

#### Création d'un pipe

    add(monPipe, type="pipe")

#### Création d'un bloc conditionnel

    add(monIf, kind="if", (condition) ? {
        monVariable = monVariable + 1
    } : {
        monVariable = monVariable - 1
    })

#### Création d'un bloc itératif

    add(monFor, kind="for", (iterator) => {
        monVariable = monVariable + 1
    })

#### Création d'un bloc itératif conditionnel

    add(monWhile, kind="while", (condition) => {
        monVariable = monVariable + 1
    })

#### Remarque: On peut également utiliser le *for* et le *if* et le *while* traditionnel sans aucun problème

    while(condition){
        for(i=0, i<6, i=i+1){
            if(condition){
                monVariable = monVariable + 1
            }
            /*
            else {
                monVariable = monVariable + 1
            }
            */
        }
    }

#### Opérateur ternaire

    monVariable = true ? 1 : 0  // monVariable sera donc égale à 1

#### Création d'un range (interval)

    add(monRange, 1..100)

#### Création d'un switch

    add(monSwitch, kind="when", (monNombre) => {
        1 -> monVariable = 1
        2 -> monVariable = 2
        3 -> monVariable = 3
        _ -> monVariable = 0  // valeur par défaut 
    })

#### Création d'une structure

    add(maStructure, kind="struct", (monComposant1= 5, monComposant3= 65) => { // monComposant3= 6.5f
        monComposant1 -> int
        monComposant2 -> string
        monComposant3 -> float
        monComposant4 -> int[]
    })

#### Modification d'un variable

    monVariable = 500

#### Supprimer un variable de la mémoire

    del(monVariable)

#### Voir les paramètres d'une variable

    params(monVariable) // type, memoire, TTL, etc.

#### Afficher du texte sur la console

    log("Hello World")

#### Lire la saisie d'un utilisateur

    monNom = scan()

#### Afficher du texte sur la console avec interpolation

    log("Hello ${monNom}")

#### Le fichier qui stocke tout les variables quelque soit leur type

> dict.json

## Un exemple classique

    add(main, kind="function", ()=>{
        log("Hello Ensias!")
    })

`>>> dict main.dt`

`Hello Ensias!`

## Membres du groupe du projet

1. DOUSLIMI Yassir
2. EL BIACHE Houda
3. EDDAGHAL Mohammed
4. EL ARFAOUI Ikrame
5. El AZHAR Asmaa
6. EL FAKHORI Fouad
