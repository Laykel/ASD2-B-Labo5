/*
 * File: SpellCheck.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 06.01.2019
 *
 * Description: Classe implémentant les méthodes nécessaires pour trouver les
 *              mots mal orthographiés dans un fichier de texte à l'aide d'un
 *              fichier dictionnaire, et pour écrire les variantes correctes
 *              de ces mots dans un fichier de sortie.
 */

#ifndef SPELLCHECK_H
#define SPELLCHECK_H

#include <iostream>
#include <list>
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
   SpellCheck(std::string dictionaryFile, std::string textFile, std::string outputFile) {
      // On construit le dictionnaire et on l'affecte par copie
      dict = Dictionary<Container>(dictionaryFile);

      // On enregistre tous les mots mal orthographiés
      findMisspelledWords(textFile);

      // On écrit les mots et toutes leurs variantes dans le fichier de sortie
      writeToFile(outputFile);
   }

private:
   /**
    * Lit le fichier de texte mot par mot et enregistre chaque mot non présent
    * dans le dictionnaire dans la liste misspelled
    *
    * @param textFile Le chemin vers le fichier de texte
    */
   void findMisspelledWords(std::string filename) {
      // On lit le fichier de texte et on insère chaque mot ne se trouvant pas
      // dans le dictionnaire dans la liste des mots mal orthographiés
      readFile(filename, [this](std::string word) {
                  // Si le mot ne se trouve pas dans le dictionnaire
                  if (!dict.contains(word)) {
                     // On insère le mot dans la liste de mots mal orthographiés
                     misspelled.push_back(word);
                  }
               });
   }

   /**
    * Génère toutes les variantes du mot donné selon les quatre règles et les
    * renvoie préfixées de leur numéro de règle
    *
    * @param word Le mot dont les variantes doivent être générées
    * @return un vecteur contenant toutes les variantes
    */
   std::list<std::string> generateAllVariants(std::string word) {
      const std::string characters = "abcdefghijklmnopqrstuvwxyz'";
      std::string variant;
      std::list<std::string> variants;

      // 1. L'utilisateur a tapé une lettre supplémentaire
      for (size_t i = 0; i < word.length(); ++i) {
         variant = word;
         variant.erase(i, 1);

         if (dict.contains(variant))
            variants.push_back("1:" + variant);
      }

      // 2. L'utilisateur a oublié de taper une lettre
      for (size_t i = 0; i < word.length(); ++i) {
         for(char c : characters) {
            variant = word;

            variant.insert(i, 1, c);

            if (dict.contains(variant))
               variants.push_back("2:" + variant);
         }
      }

      // 3. L'utilisateur a mal tapé une lettre
      for (size_t i = 0; i < word.length(); ++i) {
         variant = word;

         for(char c : characters) {
            variant.at(i) = c;

            if (dict.contains(variant))
               variants.push_back("3:" + variant);
         }
      }

      // 4. L'utilisateur a échangé deux lettres consécutives
      for (size_t i = 0; i < word.length() - 1; ++i) {
         variant = word;

         variant.at(i) = variant.at(i + 1);
         variant.at(i + 1) = word.at(i);

         if (dict.contains(variant))
            variants.push_back("4:" + variant);
      }

      return variants;
   }

   /**
    * Écrit les mots mal orthographiés et toutes leurs variantes correctes dans
    * le fichier donné en paramètre
    *
    * @param filename Le chemin vers le fichier de sortie
    */
   void writeToFile(std::string filename) {
      std::ofstream output(filename);

      if (output.is_open()) {
         std::list<std::string> variants; // Vecteur de variantes orthographiques
         // Pour chaque mot dans la liste de mots mal orthographiés
         for (std::string word : misspelled) {
            // On écrit le mot dans le fichier de sortie
            output << "*" << word << std::endl;

            // On génère toutes les variantes orthographiques de ce mot
            variants = generateAllVariants(word);

            // On écrit les variantes dans le fichier de sortie
            for (std::string variant : variants) {
               output << variant << std::endl;
            }
         }
      }
      else {
         // TODO Handle error
      }

      output.close();
   }

private:
   Dictionary<Container> dict;
   std::list<std::string> misspelled;
};

#endif
