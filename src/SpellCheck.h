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

// On définit ici le nombre de fonctions à appliquer sur les mots mal
// orthographiés pour générer leurs variantes
#define NBR_VARIANT_FUNCTIONS 4

template <typename Container> // Container doit être un conteneur proposant une
                              // méthode insert(string) et une méthode
                              // bool contains(string)
class SpellCheck {
public:
   /**
    * Constructeur pour l'objet correcteur orthographique : charge le dictionnaire,
    * trouve les mots mal orthographiés, génère les variantes et écrit le fichier
    * de sortie
    *
    * @param dict Une référence constante vers le dictionnaire
    * @param textFile Le chemin vers le fichier de texte
    */
   SpellCheck(const Dictionary<Container>& dict, const std::string& textFile)
   : dict(dict) {
      // On enregistre tous les mots mal orthographiés
      findMisspelledWords(textFile);
   }

   /**
    * Getter : permet de récupérer la liste de mots mal orthographiés
    *
    * @return la liste de mots mal orthographiés
    */
   std::list<std::string> getMisspelledWords() {
      return misspelled;
   }

   /**
    * Variante orthographique 1 : L'utilisateur a tapé une lettre supplémentaire
    *
    * @param word Le mot dont les variantes doivent être générées
    * @return la liste des variantes correctes du mot
    */
   // O(N) dans la taille du mot jusqu'à O(N^2) (en fonction de erase)
   std::list<std::string> oneLetterLessVariants(std::string word) {
      std::string variant;
      std::list<std::string> variants;

      // Pour chaque caractère du mot
      for (size_t i = 0; i < word.length(); ++i) {
         variant = word;
         // On efface ce caractère
         variant.erase(i, 1);

         // Et si le mot résultant est dans le dictionnaire
         if (dict.contains(variant))
            // On l'ajoute aux variantes correctes
            variants.push_back(variant);
      }

      return variants;
   }

   /**
    * Variante orthographique 2 : L'utilisateur a oublié de taper une lettre
    *
    * @param word Le mot dont les variantes doivent être générées
    * @return la liste des variantes correctes du mot
    */
   // O(N * 27) dans la longueur du mot jusqu'à O(N * 27N) (en fonction de insert)
   std::list<std::string> oneLetterMoreVariants(std::string word) {
      std::string variant;
      std::list<std::string> variants;

      // Pour chaque position dans le mot
      for (size_t i = 0; i < word.length(); ++i) {
         // Pour chaque caractère autorisé
         for(char c : allowedCharacters) {
            variant = word;

            // On insère ce caractère à la position courante
            variant.insert(i, 1, c);

            // Et si le mot résultant est dans le dictionnaire
            if (dict.contains(variant))
               // On l'ajoute aux variantes correctes
               variants.push_back(variant);
         }
      }

      return variants;
   }

   /**
    * Variante orthographique 3 : L'utilisateur a mal tapé une lettre
    *
    * @param word Le mot dont les variantes doivent être générées
    * @return la liste des variantes correctes du mot
    */
   // O(N * 27) dans la longueur du mot
   std::list<std::string> oneLetterChangedVariants(std::string word) {
      std::string variant;
      std::list<std::string> variants;

      // Pour chaque caractère du mot
      for (size_t i = 0; i < word.length(); ++i) {
         variant = word;

         // Pour chaque caractère autorisé
         for(char c : allowedCharacters) {
            // On remplace le caractère à la position par ce caractère
            variant.at(i) = c;

            // Et si le mot résultant est dans le dictionnaire
            if (dict.contains(variant))
               // On l'ajoute aux variantes correctes
               variants.push_back(variant);
         }
      }

      return variants;
   }

   /**
    * Variante orthographique 4 : L'utilisateur a échangé deux lettres consécutives
    *
    * @param word Le mot dont les variantes doivent être générées
    * @return la liste des variantes correctes du mot
    */
   // O(N) dans la taille du mot
   std::list<std::string> twoLettersSwappedVariants(std::string word) {
      std::string variant;
      std::list<std::string> variants;

      // Pour chaque position dans le mot
      for (size_t i = 0; i < word.length() - 1; ++i) {
         variant = word;

         // On échange le caractère à la position courante avec le suivant
         variant.at(i) = variant.at(i + 1);
         variant.at(i + 1) = word.at(i);

         // Et si le mot résultant est dans le dictionnaire
         if (dict.contains(variant))
            // On l'ajoute aux variantes correctes
            variants.push_back(variant);
      }

      return variants;
   }

   /**
    * Écrit les mots mal orthographiés et toutes leurs variantes correctes dans
    * le fichier donné en paramètre
    *
    * @param filename Le chemin vers le fichier de sortie
    */
   void writeToFile(const std::string& filename) {
      // File stream d'écriture
      std::ofstream output(filename);

      // On vérifie si le file stream est bien lié à un fichier ouvert
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
         std::cerr << std::endl
                   << "Erreur lors de l'écriture dans le fichier '"
                   << filename << "'." << std::endl;
      }

      output.close();
   }

private:
   /**
    * Lit le fichier de texte mot par mot et enregistre chaque mot non présent
    * dans le dictionnaire dans la liste misspelled
    *
    * @param filename Le chemin vers le fichier de texte
    */
   void findMisspelledWords(const std::string& filename) {
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
    * @return un vecteur contenant toutes les variantes préfixées de leur numéro
    */
   // O(4 * (complexité des 4 fonctions + N)) dans le nombre de variantes
   std::list<std::string> generateAllVariants(const std::string& word) {
      std::list<std::string> variants;

      // On itère sur le nombre de fonction génératrices de variantes
      for (int i = 0; i < NBR_VARIANT_FUNCTIONS; ++i) {
         // Pour chaque variante générée par la fonction
         for (std::string variant : variantFunc[i](word)) {
            // On ajoute la variante avec son numéro de variante dans
            // la liste de variantes
            variants.push_back(std::to_string(i + 1) + ":" + variant);
         }
      }

      return variants;
   }

private:
   const Dictionary<Container>& dict;
   std::list<std::string> misspelled;
   const std::string allowedCharacters = "abcdefghijklmnopqrstuvwxyz'";

   // Tableau de fonctions génératrices de variantes orthographiques
   // Ajouter ici, et modifier la constante NBR_VARIANT_FUNCTIONS
   std::function<std::list<std::string>(std::string)> variantFunc[NBR_VARIANT_FUNCTIONS] = {
      std::bind(&SpellCheck::oneLetterLessVariants,     this, std::placeholders::_1),
      std::bind(&SpellCheck::oneLetterMoreVariants,     this, std::placeholders::_1),
      std::bind(&SpellCheck::oneLetterChangedVariants,  this, std::placeholders::_1),
      std::bind(&SpellCheck::twoLettersSwappedVariants, this, std::placeholders::_1)
   };
};

#endif
