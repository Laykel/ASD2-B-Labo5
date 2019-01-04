/*
 * File: FileIO.cpp
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 04.01.2019
 *
 * Description: Définition de fonctions pour la lecture et l'écriture de fichiers.
 */

#include "FileIO.h"

#include <fstream>
#include <iostream>
#include <algorithm>

using namespace std;

// Prédicat pour différencier les caractères appartenant à l'alphabet et
// l'apostrophe de tous les autres caractères
bool isNotAlphabetic(char c) {
   // Code ASCII des lettres minuscules : 97-122
   // Code ASCII de l'apostrophe : 39
   if (((int) c >= 97 && (int) c <= 122) || (int) c == 39)
      return false;
   else
      return true;
}

// Permet de nettoyer une string en la convertissant en minuscules et en lui
// retirant les caractères non autorisés (voir isNotAlphabetic)
string sanitize(string line) {
   // On convertit le mot en minuscules
   for(size_t i = 0; i < line.length(); ++i) {
       line[i] = (char) tolower(line[i]);
   }

   // On retire tous les caractères qui ne sont pas alphabétiques ou un apostrophe
   line.erase(remove_if(line.begin(), line.end(), isNotAlphabetic), line.end());

   return line;
}
