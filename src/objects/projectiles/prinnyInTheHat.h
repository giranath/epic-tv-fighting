#ifndef __TP3__prinnyHat__
#define __TP3__prinnyHat__

#include "Projectile.h"
#include "PhysicWorld.h"
#include "CustomFX.h"

#define PRINNYHAT_SPEED 0.8f

namespace beat {
    class prinnyHat : public PiouPiou {
    private:
        BoxBody* _body;
        unsigned long _elapsedTime;
		CustomFX* _fx;
        
        float _v;
        
    public:
        prinnyHat(Object* sender);
        
        virtual void onCreation();
        virtual void onUpdate(int milliSec);
        virtual void onKill();
		virtual void onDraw(sf::RenderTarget& target);
        
        virtual void onCollision(Collision const& collision);
    };
}

#endif