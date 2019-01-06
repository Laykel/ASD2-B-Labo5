/*
 * File: main.cpp
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 03.01.2019
 *
 * Description: Fichier d'entrée du programme, permet de tester le correcteur
 *              orthographique avec les deux structures de données proposées à
 *              l'aide des arguments à main().
 */

#include <cstdlib>
#include <iostream>
#include <set>
#include <chrono>

#include "Dictionary.h"
#include "SpellCheck.h"

using namespace std;

// Teste le temps de chargement du dictionnaire
// Affiche le temps de chargement en microsecondes
void testDictionary(string dictionaryFile) {
   chrono::high_resolution_clock::time_point t1, t2;

   // Moment avant lecture
   t1 = chrono::high_resolution_clock::now();
   // Lecture du dictionnaire et chargement en mémoire
   Dictionary<set<string>> dict(dictionaryFile);
   // Moment après lecture
   t2 = chrono::high_resolution_clock::now();

   // Affichage du temps de lecture en microsecondes et en millisecondes
   cout << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << "us"
        << " ~= "
        << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms"
        << endl;
}

// Utilise les classes mises en place pour tester correcteur orthographique
// Affiche le temps de correction en microsecondes
void testSpellCheck(string dictionaryFile, string textFile) {
   chrono::high_resolution_clock::time_point t1, t2;

   // Moment avant correction
   t1 = chrono::high_resolution_clock::now();
   SpellCheck<set<string>> sc(dictionaryFile, textFile);
   // Moment après correction
   t2 = chrono::high_resolution_clock::now();

   // Affichage du temps de correction en secondes
   cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() / 1000
        << "s" << endl;

   sc.printMisspelled();
   cout << endl;
}

int main(/*int argc, const char* argv[]*/) {
   // TODO argument du programme pour le lancer avec une structure de données ou une autre
   // Aucun argument lance les deux programmes.

   // Test du dictionnaire
   cout << "Temps de chargement du dictionnaire en mémoire :" << endl;
   cout << "Dictionnaire (6 mots) :" << endl;
   testDictionary("../data/dictionary_lates.txt");
   cout << "Dictionnaire (706824 mots) :" << endl;;
   testDictionary("../data/dictionary.txt");
   cout << endl;

   // Test de la correction orthographique
   cout << "Temps d'exécution du correcteur orthographique :" << endl;
   /* testSpellCheck("../data/dictionary.txt", "../data/input_lates.txt"); */
   testSpellCheck("../data/dictionary.txt", "../data/input_sh.txt");

   return EXIT_SUCCESS;
}
