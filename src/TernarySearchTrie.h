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

template <typename Type>
class TernarySearchTrie {
private:
   // Élément (noeud) du Trie
   struct Node {
      bool value;     // TODO Valeur en cas de match
      char character; // Caractère que le noeud représente

      // Pointeurs vers les sous-arbres
      Node* left;   // Enfant de caractère plus petit
      Node* middle; // Enfant de caractère suivant
      Node* right;  // Enfant de caractère plus grand
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
   void deleteSubTree(Node* node) {
      if (node == nullptr)
         return;

      deleteSubTree(node->left);
      deleteSubTree(node->middle);
      deleteSubTree(node->right);

      delete node;
   }

public:
   void insert(std::string word) {
      root = put(root, word, 0);
   }

private:
   Node* put(Node* node, std::string word, size_t d) {
      char c = word.at(d);

      if (node == nullptr) {
         node = new Node();
         node->character = c;
      }

      if (c < node->character)
         node->left = put(node->left, word, d);
      else if (c > node->character)
         node->right = put(node->right, word, d);
      else if (d < word.length() - 1)
         node->middle = put(node->middle, word, d+1);
      else
         node->value = true;

      return node;
   }

public:
   bool contains(std::string word) const {
      return get(word);
   }

   bool get(std::string word) const {
      Node* node = get(root, word, 0);

      if (node == nullptr)
         return false;

      return node->value;
   }

private:
   Node* get(Node* node, std::string word, size_t d) const {
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
   void rotateRight(Node* root);
};

#endif
