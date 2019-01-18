/*
 * File: TernarySearchTrie.cpp
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 18.01.2019
 *
 * Description: Classe implémentant les tries ternaires de recherche. Ce fichier
 *              contient la définition des méthodes.
 *              - En pratique, les TST vont nous permettre d'améliorer les temps de
 *              recherche de mots, mais le chargement d'un dictionnaire dans la
 *              structure va prendre un peu plus de temps.
 *              - En effet, une recherche non fructueuse peut être plus rapide car
 *              il suffit de comparer les quelques premiers caractères, alors qu'une
 *              table de hachage doit comparer toute la string.
 *              - En outre, les tables de hachage utilisent souvent plus d'espace
 *              que les TST.
 */

#include "TernarySearchTrie.h"

// Destructeur
TernarySearchTrie::~TernarySearchTrie() {
   deleteSubTree(root);
}

// Suppression récursive de sous-arbre
void TernarySearchTrie::deleteSubTree(Node* node) {
   // Si le noeud n'existe pas, on retourne (cas trivial)
   if (node == nullptr)
      return;

   // Appel récursif pour chaque sous-arbre
   deleteSubTree(node->left);
   deleteSubTree(node->middle);
   deleteSubTree(node->right);

   // On libère la mémoire
   delete node;
}

// Insertion de mot
void TernarySearchTrie::insert(const std::string& word) {
   root = put(root, word, 0);
}

// Insertion récursive de mot
TernarySearchTrie::Node* TernarySearchTrie::put(TernarySearchTrie::Node* node,
                                                const std::string& word, size_t idx) {
   // On récupère le caractère à insérer
   char c = word.at(idx);

   // Si le noeud n'existe pas, on le crée avec le caractère courant
   if (node == nullptr)
      node = new Node(c);

   // Si le caractère est plus petit que le caractère du noeud courant (ASCII)
   if (c < node->character)
      // On continue l'insertion du mot dans le noeud de gauche
      node->left = put(node->left, word, idx);
   // Si le caractère est plus grand que le caractère du noeud courant (ASCII)
   else if (c > node->character)
      // On continue l'insertion du mot dans le noeud de droite
      node->right = put(node->right, word, idx);
   // Si on n'est pas encore au dernier caractère
   else if (idx < word.length() - 1)
      // On continue l'insertion dans le noeud du milieu
      node->middle = put(node->middle, word, idx+1);
   else
      // Sinon, c'est le dernier caractère, et on indique alors qu'il est
      // présent à l'aide de l'attribut value
      node->value = true;

   // On ré-équilibre le TST, puis on retourne la nouvelle racine
   return restoreBalance(node);
}

// Permet de vérifier si un mot se trouve dans le TST
bool TernarySearchTrie::contains(const std::string& word) const {
   // On récupère le premier noeud du mot, s'il se trouve dans l'arbre
   Node* node = get(root, word, 0);

   // Si ce noeud est inexistant, on retourne false
   if (node == nullptr)
      return false;

   // Sinon, on retourne sa valeur (true)
   return node->value;
}

// Permet de chercher un mot dans le TST
TernarySearchTrie::Node* TernarySearchTrie::get(TernarySearchTrie::Node* node,
                                                const std::string& word, size_t idx) const {
   // Si le noeud n'existe pas, on renvoie le pointeur null
   if (node == nullptr)
      return nullptr;

   // On récupère le caractère à insérer
   char c = word.at(idx);

   // Si le caractère est plus petit que le caractère du noeud courant (ASCII)
   if (c < node->character)
      // On continue la recherche du mot dans le noeud de gauche
      return get(node->left, word, idx);
   // Si le caractère est plus grand que le caractère du noeud courant (ASCII)
   else if (c > node->character)
      // On continue la recherche du mot dans le noeud de droite
      return get(node->right, word, idx);
   // Si on n'est pas encore au dernier caractère
   else if (idx < word.length() - 1)
      // On continue la recherche du mot dans le noeud du milieu
      return get(node->middle, word, idx+1);
   else
      // Sinon, c'est le dernier caractère, et on retourne le noeud
      return node;
}

// Permet de récupérer la hauteur du noeud node
int TernarySearchTrie::height(Node* node) {
   // Si le noeud est inexistant, sa hauteur est de -1
   if (node == nullptr)
      return -1;

   // Sinon, on retourne sa hauteur
   return node->nodeHeight;
}

// Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
void TernarySearchTrie::updateNodeHeight(Node* node) {
   // La hauteur d'un noeud est la plus grande des hauteurs de ses enfants + 1
   node->nodeHeight = std::max(height(node->right), height(node->left)) + 1;
}

// Permet de calculer l'équilibre d'un noeud avec les hauteurs de ses enfants
int TernarySearchTrie::balance(Node* node) {
   // Si le noeud est inexistant, il est équilibré
   if(node == nullptr)
      return 0;

   // Sinon, son équilibre est égal à la hauteur du sous-arbre gauche moins celle
   // du sous-arbre droit
   return height(node->left) - height(node->right);
}

// Permet de ré-équilibrer le sous-arbre de racine node
TernarySearchTrie::Node* TernarySearchTrie::restoreBalance(TernarySearchTrie::Node* node) {
   // Si le déséquilibre est inférieur à -1 (gauche < droite - 1)
   if(balance(node) < -1) {
      // Si le sous-arbre droit n'est pas équilibré
      if (balance(node->right) > 0)
         // On effectue une rotation à droite du sous-arbre droit
         node->right = rotateRight(node->right);
      // On effectue une rotation à gauche
      node = rotateLeft(node);
   }
   // Si le déséquilibre est supérieur à 1 (gauche > droite + 1)
   else if(balance(node) > 1) {
      // Si le sous-arbre gauche n'est pas équilibré
      if (balance(node->left) < 0)
         // On effectue une rotation à gauche du sous-arbre gauche
         node->left = rotateLeft(node->left);
      // On effectue une rotation à droite
      node = rotateRight(node);
   }
   else {
      // On met à jour la hauteur du noeud
      updateNodeHeight(node);
   }

   return node;
}

// Rotation droite avec mise à jour des hauteurs
TernarySearchTrie::Node* TernarySearchTrie::rotateRight(TernarySearchTrie::Node* x) {
   Node* y = x->left;
   x->left = y->right;
   y->right = x;

   updateNodeHeight(x);
   updateNodeHeight(y);

   return y;
}

// Rotation gauche avec mise à jour des hauteurs
TernarySearchTrie::Node* TernarySearchTrie::rotateLeft(TernarySearchTrie::Node* x) {
   Node* y = x->right;
   x->right = y->left;
   y->left = x;

   updateNodeHeight(x);
   updateNodeHeight(y);

   return y;
}
