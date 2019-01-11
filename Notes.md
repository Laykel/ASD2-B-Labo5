## Notes sur l'implémentation

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
