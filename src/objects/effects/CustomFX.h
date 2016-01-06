/*
 *  FICHIER: CustomFX.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-17
 *  DESCRIPTION:
 *  Il s'agit d'un effet qui peut être défini dans un fichier .fx
 */

#ifndef __TP3__CustomFX__
#define __TP3__CustomFX__

#include "FX.h"

namespace beat {
    class TextureManager;
    class SoundBufferManager;
    class FXLoader;
    
    class CustomFX : public FX {
        friend class FXLoader;
    private:
        sf::Sound   _startSnd,
                    _endSnd,
                    _updateSnd;
         
    public:
        /**
         * Constructeur
         */
        CustomFX();
        
        /**
         * Copieur
         */
        CustomFX(CustomFX const& copy);
        
        /**
         * Destructeur
         */
        virtual ~CustomFX();
        
        /**
         * Appelé à chaque frame
         */
        virtual void onUpdate(int milliSec);
        
        /**
         * Appelé juste avant la destruction
         */
		virtual void onKill();
        
        /**
         * Appelé la première itération
         */
		virtual void onCreation();
    };
}


#endif
