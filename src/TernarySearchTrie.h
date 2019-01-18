/*
 * File: TernarySearchTrie.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 03.01.2019
 *
 * Description: Classe implémentant les tries ternaires de recherche.
 */

#ifndef TERNARYSEARCHTRIE_H
#define TERNARYSEARCHTRIE_H

#include <string>

/* template <typename Type> */
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
   ~TernarySearchTrie() {
      deleteSubTree(root);
   }

private:
   /**
    * Méthode récursive de suppression de sous-arbres
    *
    * @param node Le noeud à supprimer avec ses sous-arbres
    */
   void deleteSubTree(Node* node) {
      if (node == nullptr)
         return;

      deleteSubTree(node->left);
      deleteSubTree(node->middle);
      deleteSubTree(node->right);

      delete node;
   }

public:
   /**
    * Méthode d'insertion du mot donné
    *
    * @param word Le mot à insérer
    */
   void insert(const std::string& word) {
      root = put(root, word, 0);
   }

private:
   /*
    * Méthode récursive d'ajout de symbole
    *
    * @param node
    * @param word
    * @param d
    * @returns ...
    */
   Node* put(Node* node, const std::string& word, size_t d) {
      char c = word.at(d);

      if (node == nullptr) {
         node = new Node(c);
      }

      if (c < node->character)
         node->left = put(node->left, word, d);
      else if (c > node->character)
         node->right = put(node->right, word, d);
      else if (d < word.length() - 1)
         node->middle = put(node->middle, word, d+1);
      else
         node->value = true;

      return restoreBalance(node);
   }

   // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
   void updateNodeHeight(Node* node) {
      node->nodeHeight = std::max(height(node->right), height(node->left)) + 1;
   }

   int balance(Node* x) {
      if(x == nullptr)
         return 0;

      return height(x->left) - height(x->right);
   }

   Node* restoreBalance(Node* x) {
      if(balance(x) < -1) // left < right-1
      {
         if (balance(x->right)>0)
            x->right = rotateRight( x->right );
         x = rotateLeft(x);
      }
      else if( balance(x) > 1) // left > right+1
      {
         if ( balance(x->left) < 0 )
            x->left = rotateLeft( x->left );
         x = rotateRight(x);
      }
      else
         updateNodeHeight(x);

      return x;
   }

   int height(Node* x) {
      if (x == nullptr)
         return -1;
      return x->nodeHeight;
   }

public:
   bool contains(const std::string& word) const {
      Node* node = get(root, word, 0);

      if (node == nullptr)
         return false;

      return node->value;
   }

private:
   Node* get(Node* node, const std::string& word, size_t d) const {
      if (node == nullptr)
         return nullptr;

      char c = word.at(d);

      if (c < node->character)
         return get(node->left, word, d);
      else if (c > node->character)
         return get(node->right, word, d);
      else if (d < word.length() - 1)
         return get(node->middle, word, d+1);
      else
         return node;
   }

private:
   //
   // AVL: rotation droite avec mise à jour des tailles et hauteurs
   //
   Node* rotateRight(Node* x) {
      Node* y = x->left;
      x->left = y->right;
      y->right = x;

      updateNodeHeight(x);
      updateNodeHeight(y);

      return y;
   }

   //
   // AVL: rotation gauche avec mise à jour des tailles et hauteurs
   //
   Node* rotateLeft(Node* x) {
      Node* y = x->right;
      x->right = y->left;
      y->left = x;

      updateNodeHeight(x);
      updateNodeHeight(y);

      return y;
   }
};

#endif
