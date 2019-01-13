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
#include <chrono>
#include <unordered_set>

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
   Dictionary<unordered_set<string>> dict(dictionaryFile);
   // Moment après lecture
   t2 = chrono::high_resolution_clock::now();

   // Affichage du temps de lecture en microsecondes et en millisecondes
   cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms"
        << endl;
}

// Utilise les classes mises en place pour tester correcteur orthographique
// Affiche le temps de correction en microsecondes
void testSpellCheck(Dictionary<unordered_set<string>> dict, string textFile, string outputFile) {
   chrono::high_resolution_clock::time_point t1, t2;

   // Moment avant correction
   t1 = chrono::high_resolution_clock::now();
   // Application de la correction orthographique
   SpellCheck<unordered_set<string>> sc(dict, textFile, outputFile);
   // Moment après correction
   t2 = chrono::high_resolution_clock::now();

   // Affichage du temps de correction en millisecondes
   cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
        << "ms" << endl;
}

int main(/*int argc, const char* argv[]*/) {
   // TODO argument du programme pour le lancer avec une structure de données ou une autre
   // Aucun argument lance les deux programmes.

   // Test du dictionnaire
   cout << "Temps de chargement du dictionnaire en mémoire" << endl;
   cout << "==============================================" << endl;
   cout << "Dictionnaire (706824 mots) : ";
   testDictionary("data/dictionary.txt");
   cout << endl;

   // Test de la correction orthographique
   Dictionary<unordered_set<string>> dict("data/dictionary.txt");
   cout << "Temps d'exécution du correcteur orthographique" << endl;
   cout << "==============================================" << endl;
   cout << "Petit texte (Lates) : ";
   testSpellCheck(dict, "data/input_lates.txt", "output/output_lates.txt");
   cout << "Wikipedia : ";
   testSpellCheck(dict, "data/input_wikipedia.txt", "output/output_wiki.txt");
   cout << "Sherlock Holmes : ";
   testSpellCheck(dict, "data/input_sh.txt", "output/output_sh.txt");

   return EXIT_SUCCESS;
}
