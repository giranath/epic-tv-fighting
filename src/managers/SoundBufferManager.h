/*
 *  FICHIER: SoundBufferManager.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-17
 *  DESCRIPTION:
 *  Un gestionnaire de son courts, s'occupe de les garder en vie
 *  et facilite leurs utilisations
 */

#ifndef __TP3__SoundBufferManager__
#define __TP3__SoundBufferManager__

#include <SFML/Audio.hpp>
#include <string>
#include <map>
#include "ResourcePath.h"

namespace beat {
    class SoundBufferManager {
    private:
        std::map<std::string, sf::SoundBuffer*> _Buffers;
        
        std::string getRealResPath(std::string const& path) const;
        
    public:
        /**
         * Constructeur
         */
        SoundBufferManager();
        
        /**
         * Destructeur
         */
        ~SoundBufferManager();
        
        /**
         * Ajoute un son au gestionnaire
         */
        bool addBuffer(std::string const& filepath);
        
        /**
         * Retourne un son du gestionnaire
         */
        sf::SoundBuffer& getBuffer(std::string const& filepath);
        
        /**
         * Informe si un son existe dans le gestionnaire
         */
        bool exists(std::string const& filepath) const;
        
        static SoundBufferManager* gSoundManager;
    };
}

#endif
