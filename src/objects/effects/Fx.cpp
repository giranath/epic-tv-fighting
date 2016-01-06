/*
 *  FICHIER: FX.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-17
 *
 */

#include "FX.h"
#include <iostream>

namespace beat {
    FX::FX(AnimationSequence const& animationSequence, DurationMs lifetime, bool looped) : Object(OBJECT_FX) {
        _AnimationSequence = animationSequence;
        _Looped = looped;
        
        _ElapsedTime = 0;
        
        _Lifetime = lifetime;
    }
    
    FX::FX(const FX& copy) : Object(copy) {
        _AnimationSequence = copy._AnimationSequence;
        _Looped = copy._Looped;
        
        _Lifetime = copy._Lifetime;
        
        _ElapsedTime = 0;
    }
    
    FX::~FX() {
        
    }
    
    void FX::onUpdate(int milliSec) {
        if(_Looped && _AnimationSequence.finished()) {
            _AnimationSequence.restart();
        }
        
        _AnimationSequence.update(milliSec);
    }
    
    void FX::onKill() {
        
    }

    void FX::onCreation() {
        _ElapsedTime = 0;
        _AnimationSequence.play();
    }

    void FX::onDraw(sf::RenderTarget& target) {
        _Sprite.setPosition(_Position);
        
        _Sprite.setTextureRect(sf::IntRect(_AnimationSequence.getFrameRect()));
        
        target.draw(_Sprite);
    }
    
    void FX::setLifetime(DurationMs lifetime) {
        _Lifetime = lifetime;
    }
    
    DurationMs FX::getLifetime() const {
        return _Lifetime;
    }
    
    AnimationSequence& FX::getAnimationSequence() {
        return _AnimationSequence;
    }
}