/*
 *  FICHIER: Shoot.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-12-13
 *
 *  DESCRIPTION:
 *  Permet au joueur de lancer des projectiles
 *
 */


#ifndef __TP3__ShootEffect__
#define __TP3__ShootEffect__

#include "attack_effect.h"
#include "Projectile.h"
#include "ProjectileFactory.h"

namespace beat {
    class Shoot : public attack_effect {
    public:
        enum ShootType {
            GUNTHERKEN,
			PRINNYHAT
        };
    private:
        unsigned int _shootFrame;       // À quel frame le projectile doit-il partir?
        unsigned int _shootStartLocID;  // Dans quelle boite de collision le projectile doit-il démarrer sa course?

        ShootType _type;
        AnimationSequence &_sequence;
        bool _ready;
        
    public:
        Shoot(unsigned int shootFrame, unsigned int startID, AnimationSequence& sequence, ShootType type);
        
        virtual void onUpdate(int delta, beat::Player* me);
		virtual void onHit(beat::Player* enemy);
		virtual void onStart();
    };
}

#endif
