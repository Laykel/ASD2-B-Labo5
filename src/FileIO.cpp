/*
 * File: FileIO.cpp
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 04.01.2019
 *
 * Description: Définition de fonctions pour la lecture et l'écriture de fichiers.
 *              - Pour chaque mot, nous le lisons, convertissons en minuscule,
 *              retirons les caractères non autorisés, puis retirons tout apostrophe
 *              en première ou dernière position du mot. Nous ne nous occupons pas
 *              des traits d'union, qui seront supprimés à la fois dans le
 *              dictionnaire et dans les mots du texte, pour garantir la cohérence.
 */

#include "FileIO.h"

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Prédicat pour différencier les caractères appartenant à l'alphabet et
// l'apostrophe de tous les autres caractères
bool isNotAlphabeticOrApostrophe(char c) {
   // Code ASCII des lettres minuscules : 97-122
   // Code ASCII de l'apostrophe : 39
   if (((int) c >= 97 && (int) c <= 122) || (int) c == 39)
      return false;
   else
      return true;
}

// Permet de nettoyer une string en la convertissant en minuscules et en lui
// retirant les caractères non autorisés (voir isNotAlphabetic)
string sanitize(string word) {
   // On convertit le mot en minuscules
   for (size_t i = 0; i < word.length(); ++i) {
       word[i] = (char) tolower(word[i]);
   }

   // On retire tous les caractères qui ne sont pas alphabétiques ou un apostrophe
   word.erase(remove_if(word.begin(), word.end(), isNotAlphabeticOrApostrophe), word.end());

   // On retire les apostrophes avant et après le mot
   if (!word.empty() and word.at(0) == '\'')
      word.erase(0, 1);
   if (!word.empty() and word.at(word.length() - 1) == '\'')
      word.erase(word.length() - 1, 1);

   return word;
}

// Fonction de lecture de fichier mot par mot qui effectue l'opération de la
// fonction passée en paramètre
void readFile(const string& filename, function<void(std::string)> function) {
   // File stream sur le fichier
   ifstream df(filename);

   // On vérifie si le file stream est bien lié à un fichier ouvert
   if (df.is_open()) {
      string word;

      // Tant que des mots nous sont retournés
      while (df >> word) {
         // On nettoie le mot
         word = sanitize(word);

         // On s'assure que la ligne n'est pas vide
         if (!word.empty()) {
            // On applique la fonction passée en paramètre
            function(word);
         }
      }

      // Fermeture du file stream
      df.close();
   } else {
      cerr << std::endl
           << "Erreur lors de la lecture du fichier '"
           << filename << "'." << std::endl;
   }
}
