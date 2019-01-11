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
   struct Node {
      Type value;
      char character;

      Node* left,  middle, right;
   };

public:
   TernarySearchTrie();
   ~TernarySearchTrie();

   void insert(std::string word);

   bool find(std::string word);

private:
   void rotateRight(Node* root);
};

#endif
