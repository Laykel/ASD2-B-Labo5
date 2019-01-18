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

#include <iostream>
#include <chrono>

#include "StringHashTable.h"
#include "TernarySearchTrie.h"
#include "Dictionary.h"
#include "SpellCheck.h"

using namespace std;

// Définition de la structure de données à utiliser pour le dictionnaire
//using dictionaryType = StringHashTable;
using dictionaryType = TernarySearchTrie;

// Teste le temps de chargement du dictionnaire
// Affiche le temps de chargement en microsecondes
Dictionary<dictionaryType> testDictionary(string dictionaryFile) {
   chrono::high_resolution_clock::time_point t1, t2;

   // Moment avant lecture
   t1 = chrono::high_resolution_clock::now();
   // Lecture du dictionnaire et chargement en mémoire
   Dictionary<dictionaryType> dict(dictionaryFile);
   // Moment après lecture
   t2 = chrono::high_resolution_clock::now();

   // Affichage du temps de lecture en millisecondes
   cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "ms"
        << endl;

   return dict;
}

// Utilise les classes mises en place pour tester correcteur orthographique
// Affiche le temps de correction en microsecondes
void testSpellCheck(Dictionary<dictionaryType> dict, string textFile, string outputFile) {
   chrono::high_resolution_clock::time_point t1, t2;

   // Moment avant correction
   t1 = chrono::high_resolution_clock::now();
   // Application de la correction orthographique
   SpellCheck<dictionaryType> sc(dict, textFile);
   sc.writeToFile(outputFile); // Écriture des variantes dans le fichier
   // Moment après correction
   t2 = chrono::high_resolution_clock::now();

   // Affichage du temps de correction en millisecondes
   cout << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
        << "ms" << endl
        << sc.getMisspelledWords().size() << " mots mal orthographiés." << endl;
}

int main() {
   // Test du dictionnaire
   cout << "Temps de chargement du dictionnaire en mémoire" << endl;
   cout << "==============================================" << endl;
   cout << "Dictionnaire (706824 mots) : ";
   // Afficher le temps de chargement du dictionnaire et le retourner
   Dictionary<dictionaryType> dict = testDictionary("data/dictionary.txt");
   cout << endl;

   // Test de la correction orthographique
   cout << "Temps d'exécution du correcteur orthographique" << endl;
   cout << "==============================================" << endl;
   cout << "Petit texte (Lates) : ";
   testSpellCheck(dict, "data/input_lates.txt", "output/output_lates.txt");
   cout << endl;

   cout << "Petit texte (Simple) : ";
   testSpellCheck(dict, "data/input_simple.txt", "output/output_simple.txt");
   cout << endl;

   cout << "Wikipedia : ";
   testSpellCheck(dict, "data/input_wikipedia.txt", "output/output_wiki.txt");
   cout << endl;

   cout << "Sherlock Holmes : ";
   testSpellCheck(dict, "data/input_sh.txt", "output/output_sh.txt");

   return EXIT_SUCCESS;
}
