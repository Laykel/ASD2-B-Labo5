## Notes sur l'implémentation

- Choix de `unordered_set` :

- On lit le dictionnaire de la même manière que le fichier d'entrée, pour prévoir le cas où un dictionnaire différent serait utilisé, avec des majuscules ou d'autres caractères.

- Dans le set, il n’y a que 637’850 entrées, alors que le dictionnaire contient 706’824 mots. Cela est dû aux doublons qui résultent de notre méthode de nettoyage. (J’ai vérifié et il y a bien le bon nombre de doublons.)

- Implémentation du TST

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
706823 data/dictionary.txt
```

- Nombre de lignes des fichiers en sortie :
```
>> wc -l output/*
   53 output/output_lates.txt
 1719 output/output_sh.txt
  428 output/output_wiki.txt
 2200 total
```

- Complexités, UML ??
- Nous n'enregistrons pas les variantes, parce que ce serait lent et peu utile.
- Pourquoi on utilise une string avec les caractères autorisés dans generateAllVariants, mais pas dans FileIO.cpp.

   // Lire texte et comparer chaque mot avec dictionnaire (FileIO.h, SpellCheck.h)

      // Si le mot est dans le dictionnaire, ne rien faire
      // Sinon, stocker le mot dans une liste de mots incorrects (SpellCheck.h)

   // Parcourir la liste de mots incorrects et effectuer les 4 modifications
   // pour chaque caractère, comparer le mot modifié avec dictionnaire et stocker
   // dans fichier toutes les corrections possibles (SpellCheck.h, FileIO.h)
