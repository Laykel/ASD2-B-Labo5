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
      bool value = false;     // Valeur du noeud (true si fin de mot, false sinon)
      char character; // Caractère que le noeud représente

      // Pointeurs vers les sous-arbres
      Node* left;   // Enfant de caractère plus petit
      Node* middle; // Enfant de caractère suivant
      Node* right;  // Enfant de caractère plus grand
      
      int nodeSize; // taille du sous-arbre dont ce noeud est la racine.
      int nodeHeight; // hauteur du sous-arbre dont ce noeud est la racine.
      Node() : right(nullptr), left(nullptr), nodeSize(1), nodeHeight(0) { }
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
   void insert(std::string word) {
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

      updateNodeSize(node);
      
      node = restoreBalance(node);
      
      return node;
   }
   
   // HELPER: Mise à jour de la taille d'un sous-arbre à partir des taille de ses enfants
   void updateNodeSize(Node* x) {
      x->nodeSize = size(x->right) + size(x->left) + 1;
   }
   // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
   void updateNodeHeight(Node* x) {
      x->nodeHeight = std::max(height(x->right),height(x->left)) + 1;
   }
   
private:
   int balance(Node* x) {
      if(x==nullptr) return 0;
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
      else updateNodeHeight(x);
      return x;
   }
   
   int size(Node* x) {
      return ( x == nullptr ) ? 0 : x->nodeSize;
   }
   
   int height(Node* x) {
      if ( x == nullptr )
         return -1;
      return x->nodeHeight;
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
   //void rotateRight(Node* root);
   //
   // AVL: rotation droite avec mise à jour des tailles et hauteurs
   //
   Node* rotateRight(Node* x) {
      Node* y = x->left;
      x->left = y->right;
      y->right = x;

      y->nodeSize = x->nodeSize;
      updateNodeSize(x);

      updateNodeHeight(x);
      updateNodeHeight(y);
      std::cout << "rot droite effectuee" << std::endl;
      return y;
   }

   //
   // AVL: rotation gauche avec mise à jour des tailles et hauteurs
   //
   Node* rotateLeft(Node* x) {
      std::cout << "rot gauche effectuee" << std::endl;
      Node* y = x->right;
      x->right = y->left;
      y->left = x;

      y->nodeSize = x->nodeSize;
      updateNodeSize(x);

      updateNodeHeight(x);
      updateNodeHeight(y);
      
      return y;
   }
};

#endif
