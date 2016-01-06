/*
 *  FICHIER: PhysicWorld.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *  DESCRIPTION:
 */

#ifndef __TP3__PhysicWorld__
#define __TP3__PhysicWorld__

#include "PhysicBody.h"
#include "BoxBody.h"
#include "List.h"
#include "Object.h"

namespace beat {
    class PhysicWorld {
    public:
        PhysicWorld(sf::Vector2f const& gravity = sf::Vector2f(0, 0.1f));
        ~PhysicWorld();
        
        void clear();
        
        /**
         * Crée un corps
         */
        BoxBody* createBoxBody(float posX, float posY, float width, float height, bool dynamic = true, bool gravity = true);
        
        /**
         * Retire un corps
         */
        void removeBody(PhysicBody* body);
        
        /**
         * Met à jour le monde
         */
        void step(unsigned int deltaMs);
        
        /**
         * Assigne une gravité en cours d'execution
         */
        void setGravity(sf::Vector2f const& gravity);
        
        /**
         * Affiche des infos de debuggage
         */
        void debugDraw(sf::RenderTarget& target);
        
        void setWidth(unsigned int width);
        unsigned int getWidth() const;
        
        static const unsigned int FLOOR_HEIGHT = 600;
        
        void setFloorHeight(unsigned int h);
        
        unsigned int getFloorHeight() const;
        
		void setCeilingHeight(unsigned int h);
        
        unsigned int getCeilingHeight() const;

    private:
        /**
         * Un vecteur représentant la gravité
         */
        sf::Vector2f _gravity;
        
        /**
         * Une liste de corps physique
         */
        cegep::list<PhysicBody*> _bodies;
        
        /**
         * Le temps écoulé
         */
        unsigned long _elapsedTime;
        
        /**
         * La largeur du monde en pixels (oui le monde se mesure en pixel et il est plat aussi :) )
         */
        unsigned int _width,
                     _floor,
					 _ceiling;
    };
}

#endif
