/**
 * FICHIER: Guntherken
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Légendaire projectile de Tralalathan
 */

#ifndef __TP3__Guntherken__
#define __TP3__Guntherken__

#include "Projectile.h"
#include "PhysicWorld.h"

#define GUNTHERKEN_SPEED 0.6f

namespace beat {
    class Guntherken : public PiouPiou {
    private:
        BoxBody* _body;
        unsigned long _elapsedTime;
        
    public:
        Guntherken(Object* sender);
        
        virtual void onCreation();
        virtual void onUpdate(int milliSec);
        virtual void onKill();
        
        virtual void onCollision(Collision const& collision);
    };
}

#endif
