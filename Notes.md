## Notes sur l'implémentation

- StringHashTable sans optimisations
```
Temps de chargement du dictionnaire en mémoire
==============================================
Dictionnaire (706824 mots) : 644ms

Temps d'exécution du correcteur orthographique
==============================================
Sherlock Holmes : 212586us ~= 212ms
1016 mots mal orthographiés.
```

- TernarySearchTrie sans optimisations
```
Temps de chargement du dictionnaire en mémoire
==============================================
Dictionnaire (706824 mots) : 872ms

Temps d'exécution du correcteur orthographique
==============================================
Sherlock Holmes : 152423us ~= 152ms
1016 mots mal orthographiés.
```

- StringHashTable avec optimisations
```
Temps de chargement du dictionnaire en mémoire
==============================================
Dictionnaire (706824 mots) : 317ms

Temps d'exécution du correcteur orthographique
==============================================
Sherlock Holmes : 127536us ~= 127ms
1016 mots mal orthographiés.
```

- TernarySearchTrie avec optimisations
```
Temps de chargement du dictionnaire en mémoire
==============================================
Dictionnaire (706824 mots) : 275ms

Temps d'exécution du correcteur orthographique
==============================================
Sherlock Holmes : 80972us ~= 80ms
1016 mots mal orthographiés.
```

- Taille des fichiers en entrée :
```
>> du data/
4.0K    input_lates.txt
4.0K    input_simple.txt
60K     input_wikipedia.txt
584K    input_sh.txt
7.8M    dictionary.txt
```

- Nombre de lignes du dictionnaire :
```
>> wc -l data/dictionary.txt
706824 data/dictionary.txt
```

- Nombre de lignes des fichiers en sortie :
```
>> wc -l output/*
   53 output/output_lates.txt
 1719 output/output_sh.txt
    0 output/output_simple.txt
  428 output/output_wiki.txt
 2200 total
```

- Avec toutes les optimisations, le TST est aussi plus rapide en insertion que les hash tables !!

- Choix de `unordered_set` : nous avions besoin d'une table de symboles avec de très bonnes performances en insertion et en recherche. Les tables de hachage nous permettent de faire ces opérations en temps constant (amorti). C'est meilleur que ce que `set` peut nous proposer avec ses arbres binaires équilibrés.

- On lit le dictionnaire de la même manière que le fichier d'entrée, pour prévoir le cas où un dictionnaire différent serait utilisé, avec des majuscules ou d'autres caractères.

- Cette manière, c'est de lire mot par mot, convertir en minuscule, retirer les caractères non autorisés, puis retirer tout apostrophe en première ou dernière position du mot. Nous ne nous occupons pas des traits d'union, qui seront supprimés à la fois dans le dictionnaire et dans les mots du texte.

- Dans le set, il n’y a que 637’850 entrées, alors que le dictionnaire contient 706’823 mots. Cela est dû aux doublons qui résultent de notre méthode de nettoyage. (J’ai vérifié et il y a bien le bon nombre de doublons.)

- Nous n'enregistrons pas les variantes, parce que ce serait lent et peu utile. En revanche, nous avons séparé les différentes règles de génération de variantes en autant de méthodes pour permettre à une application implémentant notre correcteur (haha) de récupérer les variantes précises.

- En outre, nous avons fait en sorte que l'ajout d'autres fonctions de génération de variantes plus avancées soit extrêmement simple. (Création de la méthode, incrémentation de `NBR_VARIANT_FUNCTIONS`, ajout de la méthode dans le tableau `variantFunc`.)

- Implémentation du TST

- Hashtables can also be used in place of ternary search trees for mapping strings to values. However, hash maps also frequently use more memory than ternary search trees (but not as much as tries). Additionally, hash maps are typically slower at reporting a string that is not in the same data structure, because it must compare the entire string rather than just the first few characters. There is some evidence that shows ternary search trees running faster than hash maps.[1] Additionally, hash maps do not allow for many of the uses of ternary search trees, such as near-neighbor lookups. 

- Complexités, UML ??
- Pourquoi on utilise une string avec les caractères autorisés dans generateAllVariants, mais pas dans FileIO.cpp.

- Lire texte et comparer chaque mot avec dictionnaire (FileIO.h, SpellCheck.h)

  - Si le mot est dans le dictionnaire, ne rien faire
  - Sinon, stocker le mot dans une liste de mots incorrects (SpellCheck.h)

- Parcourir la liste de mots incorrects et effectuer les 4 modifications
- pour chaque caractère, comparer le mot modifié avec dictionnaire et stocker
- dans fichier toutes les corrections possibles (SpellCheck.h, FileIO.h)

Petit texte (Lates) : 332us ~= 0ms
1 mots mal orthographiés.

Petit texte (Simple) : 70us ~= 0ms
0 mots mal orthographiés.

Wikipedia : 37523us ~= 37ms
169 mots mal orthographiés.

Petit texte (Lates) : 337us ~= 0ms
1 mots mal orthographiés.

Petit texte (Simple) : 34us ~= 0ms
0 mots mal orthographiés.

Wikipedia : 23502us ~= 23ms
169 mots mal orthographiés.

Petit texte (Lates) : 313us ~= 0ms
1 mots mal orthographiés.

Petit texte (Simple) : 35us ~= 0ms
0 mots mal orthographiés.

Wikipedia : 22839us ~= 22ms
169 mots mal orthographiés.

Petit texte (Lates) : 256us ~= 0ms
1 mots mal orthographiés.

Petit texte (Simple) : 25us ~= 0ms
0 mots mal orthographiés.

Wikipedia : 10959us ~= 10ms
169 mots mal orthographiés.

