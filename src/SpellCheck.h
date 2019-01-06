/*
 * File: SpellCheck.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 06.01.2019
 *
 * Description:
 */

#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <vector>
#include "Dictionary.h"
#include "FileIO.h"

template <typename Container> // Container doit être un conteneur proposant des
                              // itérateurs (au moins Input Iterators) et une
                              // méthode insert() avec un seul argument
class SpellCheck {
public:
   /**
    * Constructeur pour l'objet correcteur orthographique : charge le dictionnaire,
    * trouve les mots mal orthographiés, génère les variantes et écrit le fichier
    * de sortie
    *
    * @param dictionaryFile Le chemin vers le fichier dictionnaire
    * @param textFile Le chemin vers le fichier de texte
    */
   SpellCheck(std::string dictionaryFile, std::string textFile) {
      dict = Dictionary<Container>(dictionaryFile);

      findMisspelledWords(textFile);

      for (std::string word : misspelled) {
         // On écrit le mot dans le fichier de sortie
         // On génère toutes les variantes
         generateAllVariants(word);
         // On écrit les variantes dans le fichier de sortie
      }
   }

   /**
    *
    */
   std::vector<std::string> generateAllVariants(std::string) {
      return {"", "2"};
   }

   // TOREMOVE
   void printMisspelled() {
      for (typename std::vector<std::string>::iterator it = misspelled.begin(); it != misspelled.end(); ++it)
         std::cout << *it << ", ";
   }

private:
   /**
    * Lit le fichier de texte mot par mot et enregistre chaque mot non présent
    * dans le dictionnaire dans la liste misspelled
    *
    * @param textFile Le chemin vers le fichier de texte
    */
   void findMisspelledWords(std::string textFile) {
      // File stream sur le fichier de texte
      std::ifstream df(textFile);

      // On vérifie si le file stream est bien lié à un fichier ouvert
      if (df.is_open()) {
         std::string word;

         // Tant que des mots nous sont retournés
         while (df >> word) {
            // On nettoie le mot
            word = sanitize(word);

            // On s'assure que le mot n'est pas vide
            if (!word.empty()) {
               // Si le mot ne se trouve pas dans le dictionnaire
               if (!dict.contains(word)) {
                  // On insère le mot dans la liste de mots mal orthographiés
                  misspelled.push_back(word);
               }
            }
         }

         // Fermeture du file stream
         df.close();
      } else {
         // TODO exception or something else ?
         std::cout << "Nom du fichier incorrect" << std::endl;
      }
   }

private:
   Dictionary<Container> dict;
   std::vector<std::string> misspelled;
};

#endif
