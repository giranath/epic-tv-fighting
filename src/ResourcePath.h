/**
 * FICHIER: ResourcePath.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Fonction permettant de rendre compatible le chemin d'accès des resources sur mac et windows
 */

#ifndef __TP3__ResourcePath__
#define __TP3__ResourcePath__

#include <string>

typedef std::string ResourcePath;

/**
 * Retourne le chemin d'accès des ressources.
 * Sur mac, cela correspond à 'application.app/Contents/Resources/'
 * et sur Windows à rien du tout.
 * 
 * Return: le chemin d'accès se terminant par '/'
 */
ResourcePath resourcePath();

#endif
