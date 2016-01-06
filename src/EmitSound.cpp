/*
 *  FICHIER: EmitSound.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-12-14
 *
 */

#include "EmitSound.h"

namespace beat {
    EmitSound::EmitSound(unsigned int startFrame, std::string soundName, AnimationSequence &sequence) : _sequence(sequence) {
        _start = startFrame;
        
        _sound.setBuffer(SoundBufferManager::gSoundManager->getBuffer(soundName));
    }
    
    void EmitSound::onStart() {
        
    }
    
    void EmitSound::onUpdate(int delta, beat::Player* me) {
        if(_sequence.getFrameIndex() == _start) {
            if(_sound.getStatus() != sf::Sound::Playing)
                _sound.play();
        }
    }
    
    void EmitSound::onHit(beat::Player* enemy) {
        
    }
}