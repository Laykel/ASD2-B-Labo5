/*
 * File: FileIO.h
 * ASD 2 - Labo 5 - Mini projet
 * Authors: Loris Gilliand, Mateo Tutic, Luc Wachter
 * Created on 04.01.2019
 *
 * Description: Déclaration de fonctions pour la lecture et l'écriture de fichiers.
 */

#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <functional>

/**
 * Prédicat pour différencier les caractères appartenant à l'alphabet et
 * l'apostrophe de tous les autres caractères
 *
 * @param c Le caractère à tester
 * @return true si le caractère n'est pas alphabétique minuscule ou apostrophe
 */
bool isNotAlphabeticOrApostrophe(char c);

/**
 * Permet de nettoyer une string en la convertissant en minuscules et en lui
 * retirant les caractères non autorisés (voir isNotAlphabetic)
 *
 * @param line Le mot à nettoyer
 * @return le mot sans les caractères non autorisés
 */
std::string sanitize(std::string line);

/**
 * Fonction de lecture de fichier mot par mot qui effectue l'opération de la
 * fonction passée en paramètre
 *
 * @param filename Le chemin du fichier à lire
 * @param function L'opération à effectuer sur les mots lus
 */
void readFile(std::string filename, std::function<void(std::string)> function);

#endif
