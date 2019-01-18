/*
 * File: Dictionary.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 04.01.2019
 *
 * Description: Classe implémentant un dictionnaire dont le conteneur est générique.
 *              - Le type 'Container' doit implémenter les fonctions insert() et
 *              contains() avec un seul paramètre de type string.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <fstream>

#include "FileIO.h"

template <typename Container> // Container doit être un conteneur proposant une
                              // méthode insert(string) et une méthode
                              // bool contains(string)
class Dictionary {
public:
   /**
    * Constructeur du dictionnaire, à partir du fichier en paramètre
    *
    * @param filename Le chemin vers le fichier contenant les mots du dictionnaire
    */
   Dictionary(const std::string& filename) {
      // On lit le fichier dictionnaire et on insère chaque mot lu dans dict
      readFile(filename, [this](const std::string& word) {
                  dict.insert(word);
               });
   }

   /**
    * Vérifie si le mot donné se trouve dans le dictionnaire
    *
    * @param word Le mot que l'on cherche
    * @return true si le dictionnaire contient le mot, false sinon
    */
   bool contains(const std::string& word) const {
      return dict.contains(word);
   }

private:
   // Structure de données contenant les entrées du dictionnaire
   Container dict;
};

#endif
