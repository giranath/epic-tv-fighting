/*
 *  FICHIER: FXLoader.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *  DESCRIPTION:
 *  Class static permettant le chargement d'effet
 */

#ifndef __TP3__FXLoader__
#define __TP3__FXLoader__

#include "CustomFX.h"
#include "SoundBufferManager.h"
#include "TextureManager.h"
#include <fstream>

namespace beat {
    class FXLoader {
    public:
        /**
         * Crée une nouvelle instance de CustomFX à partir d'un fichier .fx
         */
        static CustomFX* createFromFile(std::string const& filepath);
        
        /**
         * Assigne le soundManager à utiliser
         */
        static void setSoundManager(SoundBufferManager* sndManager);
        
        /**
         * Assigne le textureManager à utiliser
         */
        static void setTextureManager(TextureManager* textureManager);
        
    private:
        /**
         * Pointeurs vers les différents gestionnaires de ressources
         */
        static SoundBufferManager* _sndManager;
        static TextureManager* _textureManager;
    };
}

#endif
