/*
 * File: StringHashTable.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 14.01.2019
 *
 * Description: Extension de la classe unordered_set pour nous permettre d'utiliser
 *              la même méthode contains() que sur notre TernarySearchTrie.
 */

#ifndef STRINGHASHTABLE_H
#define STRINGHASHTABLE_H

#include <unordered_set>

class StringHashTable : public std::unordered_set<std::string> {
public:
   bool contains(const std::string& word) const {
      return find(word) != end();
   }
};

#endif
