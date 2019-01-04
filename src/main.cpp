/*
 * File: main.cpp
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 03.01.2019
 *
 * Description: Fichier d'entrée du programme, permet de tester le correcteur
 *              orthographique avec les deux structures de données proposées à
 *              l'aide de la constante DATA_STRUCTURE.
 */

#include <cstdlib>
#include <iostream>
#include <set>

#include "Dictionary.h"

using namespace std;

// Utilise les classes mises en place pour le correcteur orthographique
void test(string dictionaryFile, string textFile) {
   // Lire dictionary et le stocker (FileIO.h, Dictionary.h)
   Dictionary<set<string>> dict(dictionaryFile);
   dict.print();

   // Lire texte et comparer chaque mot avec dictionnaire (FileIO.h, main.cpp)

      // Si le mot est dans le dictionnaire, ne rien faire
      // Sinon, stocker le mot dans une liste de mots incorrects (SpellCheck.h)

   // Parcourir la liste de mots incorrects et effectuer les 4 modifications
   // pour chaque caractère, comparer le mot modifié avec dictionnaire et stocker
   // dans fichier toutes les corrections possibles (SpellCheck.h, FileIO.h)
}

int main() {
   // TODO argument du programme pour le lancer avec une structure de données ou une autre
   // Aucun argument lance les deux programmes.
   test("../data/dictionary_lates.txt", "../data/input_lates.txt");

   return EXIT_SUCCESS;
}
