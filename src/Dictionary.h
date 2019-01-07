/*
 * File: Dictionary.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 04.01.2019
 *
 * Description: Classe implémentant un dictionnaire dont le conteneur est générique
 *              Le type 'Container' doit implémenter la fonction insert() avec un
 *              seul paramètre.
 */

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <string>
#include <fstream>

#include "FileIO.h"

template <typename Container> // Container doit être un conteneur proposant des
                              // itérateurs (au moins Input Iterators) et une
                              // méthode insert() avec un seul argument
class Dictionary {
public:
   // On garde le constructeur par défaut fourni
   Dictionary() = default;

   /**
    * Constructeur du dictionnaire, à partir du fichier en paramètre
    *
    * @param filename Le chemin vers le fichier contenant les mots du dictionnaire
    */
   Dictionary(std::string filename) {
      // File stream sur le fichier dictionnaire
      std::ifstream df(filename);

      // On vérifie si le file stream est bien lié à un fichier ouvert
      if (df.is_open()) {
         std::string line;

         // Tant que des lignes nous sont retournées
         while (getline(df, line)) {
            // On nettoie le mot
            line = sanitize(line);

            // On s'assure que la ligne n'est pas vide
            if (!line.empty()) {
               // On insère la ligne dans notre dictionnaire après l'avoir nettoyée
               dict.insert(line);
            }
         }

         // Fermeture du file stream
         df.close();
      } else {
         // TODO exception or something else ?
         std::cout << "Nom du fichier incorrect" << std::endl;
      }
   }

   /**
    * Vérifie si le mot donné se trouve dans le dictionnaire
    *
    * @param word Le mot que l'on cherche
    * @return true si le dictionnaire contient le mot, false sinon
    */
   bool contains(std::string word) {
      return dict.find(word) != dict.end();
   }

private:
   // Structure de données contenant les entrées du dictionnaire
   Container dict;
};

#endif
