/*
 *  FICHIER: Scene.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-29
 *
 *  DESCRIPTION:
 *  Représente une scène dans laquelle les joueurs meneront leur combat
 *
 */

#ifndef __TP3__Scene__
#define __TP3__Scene__

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <fstream>
#include "ResourcePath.h"

namespace beat {
    class Scene {
    private:
        std::string _musicPath;
        std::string _backPath;
        
        sf::Music _ambiantMusic;
        unsigned int _width;
        unsigned int _floorHeight;
    public:
        Scene();
        Scene(Scene const& copy);
        ~Scene();
        
        Scene& operator=(Scene const& other);
        
        /**
         * Charge une scene à partir d'un fichier .scene
         */
        bool loadFromFile(std::string const& filepath);
        
        /**
         * Retourne la musique d'ambiance de la scene
         */
        sf::Music& getAmbiantMusic();
        
        /**
         * Retourne la texture de fond de la scene
         */
        std::string getBackgroundTexture();
        
        /**
         * Assigne une largeur
         */
        void setWidth(unsigned int w);
        
        /**
         * Retourne la largeur de la scène
         */
        unsigned int getWidth() const;
        
        unsigned int getFloorHeight() const;
    };
}

#endif
