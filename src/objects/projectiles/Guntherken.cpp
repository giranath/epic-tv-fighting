/**
 * FICHIER: Guntherken
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Légendaire projectile de Tralalathan
 */

#include "Guntherken.h"
#include "ObjectManager.h"
#include <iostream>

namespace beat {
    Guntherken::Guntherken(Object* sender) : PiouPiou(sender, 10) {
        _body = 0;
        _elapsedTime = 0;
    }
    
    void Guntherken::onCreation() {
        _body = sObjectManager->getWorld().createBoxBody(_Sender->getPosition().x, _Sender->getPosition().y, 50, 50);
        _body->setGravityAffected(false);
        _body->setPosition(_Position);
        _body->possessor = this;
        
        _Sprite.setOrigin(25, 25);
        
    }

    void Guntherken::onUpdate(int milliSec) {
        _elapsedTime += milliSec;
        
        _Position = _body->getPosition();
        _Position.x += 25;
        _Position.y += 25;
        _Sprite.rotate(0.56 * milliSec);
        
        _body->setVelocity(_Velocity * GUNTHERKEN_SPEED);
        
        if(_body->getPosition().x <= 0 ||
           _body->getPosition().x + 50 >= sObjectManager->getWorld().getWidth() ||
           _elapsedTime > 10000) {
            _Alive = false;
        }
    }
    
    void Guntherken::onKill() {
        sObjectManager->getWorld().removeBody(_body);
    }
    
    void Guntherken::onCollision(Collision const& collision) {
        if(collision.getObject()->getType() == OBJECT_PROJECTILE) {
            _Alive = false;
        }
    }
}