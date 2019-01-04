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

/**
 * Prédicat pour différencier les caractères appartenant à l'alphabet et
 * l'apostrophe de tous les autres caractères
 *
 * @param c Le caractère à tester
 * @return true si le caractère n'est pas alphabétique minuscule ou apostrophe
 */
bool isNotAlphabetic(char c);

/**
 * Permet de nettoyer une string en la convertissant en minuscules et en lui
 * retirant les caractères non autorisés (voir isNotAlphabetic)
 *
 * @param line Le mot à nettoyer
 * @return le mot sans les caractères non autorisés
 */
std::string sanitize(std::string line);

#endif
