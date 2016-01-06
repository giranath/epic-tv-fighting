/*
 *  FICHIER: EmitSound.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-12-14
 *
 *  DESCRIPTION:
 *  Permet au joueur d'émettre un bruit
 *
 */

#ifndef __TP3__EmitSound__
#define __TP3__EmitSound__

#include "attack_effect.h"
#include "SoundBufferManager.h"

namespace beat {
    class EmitSound : public attack_effect {
    private:
        sf::Sound _sound;
        unsigned int _start;
        AnimationSequence &_sequence;
        
    public:
        EmitSound(unsigned int startFrame, std::string soundName, AnimationSequence &sequence);
        
        virtual void onStart();
        virtual void onUpdate(int delta, beat::Player* me);
		virtual void onHit(beat::Player* enemy);
    };
}

#endif
