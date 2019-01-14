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

*lates
1:ates
1:lats
1:late
2:alates
2:elates
2:plates
2:slates
2:lattes
2:lathes
2:latkes
2:lattes
2:latens
3:bates
3:cates
3:dates
3:fates
3:gates
3:hates
3:mates
3:nates
3:oates
3:pates
3:rates
3:sates
3:tates
3:vates
3:yates
3:lites
3:lotes
3:lutes
3:lytes
3:laces
3:lades
3:lakes
3:lames
3:lanes
3:lares
3:lases
3:laves
3:lawes
3:laxes
3:lazes
3:laths
3:latis
3:latus
3:lat's
3:latea
3:lated
3:laten
3:later
3:latex
4:altes
