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
   Node* put(Node* node, const std::string& word, size_t idx) {
      char c = word.at(idx);

      if (node == nullptr)
         node = new Node(c);

      if (c < node->character)
         node->left = put(node->left, word, idx);
      else if (c > node->character)
         node->right = put(node->right, word, idx);
      else if (idx < word.length() - 1)
         node->middle = put(node->middle, word, idx+1);
      else
         node->value = true;

      return restoreBalance(node);
   }

   // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
   void updateNodeHeight(Node* node) {
      node->nodeHeight = std::max(height(node->right), height(node->left)) + 1;
   }

   int balance(Node* node) {
      if(node == nullptr)
         return 0;

      return height(node->left) - height(node->right);
   }

   Node* restoreBalance(Node* node) {
      if(balance(node) < -1) {                  // left < right-1
         if (balance(node->right) > 0)
            node->right = rotateRight(node->right);
         node = rotateLeft(node);
      }
      else if(balance(node) > 1) {              // left > right+1
         if (balance(node->left) < 0)
            node->left = rotateLeft(node->left);
         node = rotateRight(node);
      }
      else {
         updateNodeHeight(node);
      }

      return node;
   }

   int height(Node* node) {
      if (node == nullptr)
         return -1;

      return node->nodeHeight;
   }

public:
   bool contains(const std::string& word) const {
      Node* node = get(root, word, 0);

      if (node == nullptr)
         return false;

      return node->value;
   }

private:
   Node* get(Node* node, const std::string& word, size_t idx) const {
      if (node == nullptr)
         return nullptr;

      char c = word.at(idx);

      if (c < node->character)
         return get(node->left, word, idx);
      else if (c > node->character)
         return get(node->right, word, idx);
      else if (idx < word.length() - 1)
         return get(node->middle, word, idx+1);
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
