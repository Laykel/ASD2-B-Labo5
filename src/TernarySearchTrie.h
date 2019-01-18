/*
 * File: TernarySearchTrie.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 03.01.2019
 *
 * Description: Classe implémentant les tries ternaires de recherche. Ce fichier
 *              contient les déclarations de méthodes.
 *              - Les méthodes d'insertion et de recherche sont fortement inspirée des
 *              slides de Robert Sedgewick et Kevin Wayne sur les Ternary Search
 *              Tries.
 *              - Les méthodes d'équilibrage sont fortement inspirée du fichier
 *              AVLTree.h de M. Cuisenaire.
 */

#ifndef TERNARYSEARCHTRIE_H
#define TERNARYSEARCHTRIE_H

#include <string>

class TernarySearchTrie {
private:
   // Élément (noeud) du Trie
   struct Node {
      char character; // Caractère que le noeud représente
      bool value;     // Valeur du noeud (true si fin de mot, false sinon)

      // Pointeurs vers les sous-arbres
      Node* left;   // Enfant de caractère plus petit
      Node* right;  // Enfant de caractère plus grand
      Node* middle; // Enfant de caractère suivant

      int nodeHeight; // Hauteur du sous-arbre dont ce noeud est la racine

      // Constructeur du noeud
      Node(char c) : character(c), value(false), left(nullptr), right(nullptr),
                     middle(nullptr), nodeHeight(0) {}
   };

   // Racine du Trie
   Node* root;

public:
   /**
    * Constructeur
    */
   TernarySearchTrie()
   : root(nullptr) {};

   /**
    * Destructeur
    */
   ~TernarySearchTrie();

private:
   /**
    * Suppression récursive de sous-arbre
    *
    * @param node Le noeud à supprimer avec ses sous-arbres
    * @see inspiré de AVLTree.h
    */
   void deleteSubTree(Node* node);

public:
   /**
    * Insertion de mot
    *
    * @param word Le mot à insérer
    * @see inspiré des slides de Robert Sedgewick
    */
   void insert(const std::string& word);

private:
   /*
    * Insertion récursive de mot
    *
    * @param node Le noeud sur lequel on commence l'insertion
    * @param word Le mot à insérer
    * @param idx  L'index de la lettre du mot en train d'être insérée
    * @returns la nouvelle racine de l'arbre, après ré-équilibrage
    * @see inspiré des slides de Robert Sedgewick
    */
   Node* put(Node* node, const std::string& word, size_t idx);

public:
   /**
    * Permet de vérifier si un mot se trouve dans le TST
    *
    * @param word Le mot à chercher dans le TST
    * @returns true si le mot se trouve dans le TST, false sinon
    * @see inspiré des slides de Robert Sedgewick
    */
   bool contains(const std::string& word) const;

private:
   /**
    * Permet de chercher un mot dans le TST
    *
    * @param node Le noeud sur lequel commencer la recherche
    * @param word Le mot à trouver dans le TST
    * @param idx L'index de la lettre du mot en train d'être insérée
    * @returns le premier noeud faisant partie du mot
    * @see inspiré des slides de Robert Sedgewick
    */
   Node* get(Node* node, const std::string& word, size_t idx) const;

private:
   // Helpers

   /**
    * Permet de récupérer la hauteur du noeud node
    *
    * @param node Le noeud duquel on veut savoir la hauteur
    * @returns la hauteur du sous-arbre de racine node
    * @see inspiré de AVLTree.h
    */
   int height(Node* node);

   /**
    * Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    *
    * @param node Le noeud duquel on veut mettre à jour la hauteur
    * @see inspiré de AVLTree.h
    */
   void updateNodeHeight(Node* node);

   /**
    * Permet de calculer l'équilibre d'un noeud avec les hauteurs de ses enfants
    *
    * @param node Le noeud duquel on veut connaître l'équilibre
    * @returns l'équilibre du noeud
    * @see inspiré de AVLTree.h
    */
   int balance(Node* node);

   /**
    * Permet de ré-équilibrer le sous-arbre de racine node
    *
    * @param node Le noeud à ré-équilibrer
    * @returns la nouvelle racine de ce sous-arbre
    * @see inspiré de AVLTree.h
    */
   Node* restoreBalance(Node* node);

   /**
    * Rotation droite avec mise à jour des hauteurs
    *
    * @param x Le noeud sur lequel effectuer la rotation
    * @returns la nouvelle racine du sous-arbre
    * @see inspiré de AVLTree.h
    */
   Node* rotateRight(Node* x);

   /**
    * Rotation gauche avec mise à jour des hauteurs
    *
    * @param x Le noeud sur lequel effectuer la rotation
    * @returns la nouvelle racine du sous-arbre
    * @see inspiré de AVLTree.h
    */
   Node* rotateLeft(Node* x);
};

#endif
