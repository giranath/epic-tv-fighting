/**
 * FICHIER: ProjectileFactory
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DATE: 13 décembre 2013
 *
 * DESCRIPTION;
 *      Légendaire projectile de Tralalathan
 */

// Ajout d'un commentaire pour luc

#ifndef __TP3__ProjectileFactory__
#define __TP3__ProjectileFactory__

#include "Guntherken.h"
#include "prinnyInTheHat.h"

namespace beat {
    class ProjectileFactory {
    public:
        static Guntherken* createGuntherKen(Object* sender, sf::Vector2f relativePosition, sf::Vector2f initialVelocity);
        
		static prinnyHat*  createPrinnyHat(Object* sender, sf::Vector2f relativePosition, sf::Vector2f initialVelocity);

        static void setTextureManager(TextureManager* textureManager);
    private:
        static TextureManager* _textureManager;
    };
}


#endif
