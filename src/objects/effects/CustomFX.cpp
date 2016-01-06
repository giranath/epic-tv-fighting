/*
 *  FICHIER: CustomFX.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-17
 *
 */

#include "CustomFX.h"
#include <fstream>
#include "TextureManager.h"
#include "SoundBufferManager.h"

namespace beat {
    CustomFX::CustomFX() : FX() {
        
    }
    
    CustomFX::CustomFX(CustomFX const& copy) : FX(copy) {
        _startSnd = copy._startSnd;
        _updateSnd = copy._updateSnd;
        _endSnd = copy._endSnd;
    }
    
    CustomFX::~CustomFX() {
        
    }
    
    void CustomFX::onUpdate(int milliSec) {
        if(_updateSnd.getStatus() != sf::Sound::Playing)
            _updateSnd.play();
        FX::onUpdate(milliSec);
    }
    
    void CustomFX::onKill() {
        _endSnd.play();
        FX::onKill();
    }
    
    void CustomFX::onCreation() {
        _startSnd.play();
        FX::onCreation();
    }
}