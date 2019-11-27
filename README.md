# Huffman_tree

## Description

*Création d'un programme qui construit un arbre de Huffman avec le mot ou la phrase entrée en argument.*

*Le codage d'Huffman est un algorithme de compression de données sans perte. Il a été inventé par David Albert Huffman, et publié en 1952. D. A. Huffman était un professeur et pionnier dans le domaine de l'informatique.*

*__Principe__ : On crée un arbre où chaque lettre est une feuille (voir exemple ci-dessous). On parcourt l'arbre depuis la racine afin de définir le code binaire de chaque lettre (à chaque déplacement vers la gauche on attribut un '0' et vers la droite un '1').*

![Alt Image Text](https://upload.wikimedia.org/wikipedia/commons/thumb/8/82/Huffman_tree_2.svg/350px-Huffman_tree_2.svg.png "Huffman")

*Exemple d'un arbre d'Huffman avec la phrase «this is an example of a huffman tree».*

*Ici, le code binaire de la lettre 'n' va être "0010".*

---

### Headers

Les headers sont disposés dans le dossier `inc/`.

Listes des headers :

	huffman.h

### Sources

Les sources sont disposés dans le dossier `src/`.

Listes des sources :

	main.c
	error_case.c
	tree.c
	huffman.c
	huffman_compress.c
	huffman_decompress.c
	utils.c

### Makefile

Le `Makefile` compile les sources afin de créer l'exécutable du serveur `huffman`. 

Pour compiler, voici la commande :

	make

La compilation est effectuée avec les flags `-O2 -W -Wall -Werror`.

---

Explication des flags :

`-O2` = génère le code de manière plus optimisé avec un temps de compilation plus faible.

`-W` = inhibe les messages d'avertissements.

`-Werror` = transforme les messages d'avertissements en erreurs.

`-Wall` = active les flags suivants :


	   -Waddress   
       -Warray-bounds=1 (only with -O2)  
       -Wc++11-compat  -Wc++14-compat
       -Wchar-subscripts  
       -Wenum-compare (in C/ObjC; this is on by default in C++) 
       -Wimplicit-int (C and Objective-C only) 
       -Wimplicit-function-declaration (C and Objective-C only) 
       -Wcomment  
       -Wformat   
       -Wmain (only for C/ObjC and unless -ffreestanding)  
       -Wmaybe-uninitialized 
       -Wmissing-braces (only for C/ObjC) 
       -Wnonnull  
       -Wopenmp-simd 
       -Wparentheses  
       -Wpointer-sign  
       -Wreorder   
       -Wreturn-type  
       -Wsequence-point  
       -Wsign-compare (only in C++)  
       -Wstrict-aliasing  
       -Wstrict-overflow=1  
       -Wswitch  
       -Wtrigraphs  
       -Wuninitialized  
       -Wunknown-pragmas  
       -Wunused-function  
       -Wunused-label     
       -Wunused-value     
       -Wunused-variable  
       -Wvolatile-register-var

---

`make clean` efface les fichiers `.o` créés dans le dossier `src/`.

`make distclean` supprime l'exécutable créer.

### Exécution

Le programme s'exécute de la sorte :

	./huffman MOT

ou :

	./huffman "PHRASE"

Il est possible de compresser plusieurs textes en même temps de la manière suivante :

	./huffman TEXTE TEXTE_2 ... TEXTE_N

###### Flags

Le programme possède trois flags :

- `-h` affiche l'aide et quitte le programme.
- `-v` affiche la version du programme et quitte le programme.
- `-d` afin de lancer le mode debug.
	
Extrait de la sortie du programme en mode debug :

On exécute le programme avec la commande suivante :

	./huffman titan -d

>![Alt Image Text](https://image.noelshack.com/fichiers/2019/44/4/1572534255-debug.png "Debug")

### Arbre de Huffman

__Structures de l'arbre :__

	struct node {
		struct data *data;
		struct node *left;
		struct node *right;
	};
	
	struct data {
		int occ;
		char letter;
		int size;
	};
	
	struct comp {
		int b;
		int *arr;
		int id;
		int size;
	};
---

__Étapes de création de l'arbre :__

1. Afin de créer l'arbre on commence par __compter le nombre d'occurence de chaque lettre__ présente dans le texte donné en argument avec la fonction `count_char()`. 

2. On __retire toutes les occurences__ du texte afin de ne garder qu'un exemplaire de chaque lettre avec `clean_str()`. 

3. Par la suite, on les __trie par ordre croissant en fonction de leur nombre d'occurence__ avec `order()`.

4. On peut maintenant __créer l'arbre__ en commencant par l'initialiser avec `tree_init()`.

5. Il faut maintenant __prendre les deux premières lettres et créer le parent qui contiendra la somme du nombre d'occurence des deux lettres__. Le parent prendra la place des deux lettres dans le texte que l'on retriera par ordre croissant. Tout ceci est effectué depuis la fonction `make_parent()`.

6. Enfin, il ne reste plus qu'a __réitérer l'étape au-dessus jusqu'à obtenir un seul et unique parent qui sera la racine__. Cela est effectué depuis la fonction `huffman_compress()` qui retournera l'arbre.

(cf. <http://projet.eu.org/pedago/sin/term/5-huffman.pdf>)

---
###### Encodage

Maintenant l'arbre crée, on récupère le code binaire de chaque lettre (voir __Principe__ dans __Description__) que l'on place dans un tableau. 

Une fois le tableau crée, on remplace chaque lettre du mot reçu par son code binaire. Pour terminer, on envoie le message encodé avec l'arbre binaire afin que le puisse décoder le message en se basant sur l'arbre.

###### Décodage

Afin de procéder au décodage, il faut parcourir le message encodé en même temps que l'arbre binaire receptionné. Lorsqu'une suite de bits entière est retrouvée on la remplace par le caractère correspondant. Pour retrouver une suite de bits, on parcourt l'arbre binaire depuis la racine en allant à gauche ou à droite suivant le bit (`0` = gauche, `1` = droite) rencontré jusqu'à trouver une feuille, la lettre qu'elle contient est celle qui correspond au code binaire utilisé.

(cf. <https://www.vincent-passau.be/dl/huffman.pdf>)

### Exemple

On exécute le programme avec la commande suivante :

	./huffman titan
	
>![Alt Image Text](https://image.noelshack.com/fichiers/2019/44/4/1572534258-huffman.png "Exemple")


Auteur : *César VENZAC*