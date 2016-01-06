/*
 *  FICHIER: FX.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-17
 *  DESCRIPTION:
 *  Classe représentant un effet visuelle
 *  Cela peut aller de l'explosion nucléaire au petit chat en arrière de scène
 */

#ifndef __TP3__FX__
#define __TP3__FX__

#include "Object.h"
#include "vector.h"
#include <SFML/Audio.hpp>
#include "AnimationSequence.h"

#define OBJECT_FX 6512

namespace beat {
    
    typedef vecteur<sf::IntRect> Sequence;
    
    class FX : public Object {
    protected:
        /**
         * Une séquence de frame pour l'animation
         */
        AnimationSequence _AnimationSequence;
        
        /**
         * L'animation doit elle se répeter
         */
        bool _Looped;
        
        /**
         * La durée de vie de l'effet
         */
        DurationMs _Lifetime;
        
        /**
         * Le temps écoulé
         */
        unsigned int _ElapsedTime;
        
    public:
        /**
         * Constructeur
         */
        FX(AnimationSequence const& animationSequence = AnimationSequence(), DurationMs lifetime = 0, bool looped = false);
        
        /**
         * Copieur
         */
        FX(const FX& copy);
        
        /**
         * Destructeur
         */
        virtual ~FX();
    
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
        
        /**
         * Appelé pour l'affichage
         */
        virtual void onDraw(sf::RenderTarget& target);
        
        /**
         * Assigne une durée de vie en milisecondes (0 = infinie)
         */
        void setLifetime(DurationMs lifetime);
        
        /**
         * Retourne la durée de vie de l'effet en milisecondes
         */
        DurationMs getLifetime() const;
        
        AnimationSequence& getAnimationSequence();
    };
}

#endif
