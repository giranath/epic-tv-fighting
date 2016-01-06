/**
 * FICHIER: Projectile.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Classe héritant d'Object qui représente un projectile
 */

#include "Projectile.h"
#include "CustomFX.h"
#include "FXLoader.h"
#include "ObjectManager.h"

namespace beat {
    PiouPiou::PiouPiou(Object* sender, int damage) : Object(OBJECT_PROJECTILE) {
        _Sender = sender;
        _Damage = damage;
    }
    
    PiouPiou::~PiouPiou() {
        
    }
    
    void PiouPiou::onCreation() {
        if(_Sender)
            _Position = _Sender->getPosition();
        
        _el = 0;
    }
    
    void PiouPiou::onUpdate(int milliSec) {
        _Position += _Velocity * (float)milliSec;
        _el += milliSec;
        
        if(_el > 2000) {
            this->setAlive(false);
        }
    }
    
    void PiouPiou::onDraw(sf::RenderTarget& target) {
        _Sprite.setOrigin(_Sprite.getTexture()->getSize().x/2, _Sprite.getTexture()->getSize().y/2);

        _Sprite.setPosition(_Position);
        
        target.draw(_Sprite);
    }
    
    void PiouPiou::onKill() {
    }
    
    void PiouPiou::setDamage(int value) {
        _Damage = value;
    }
    
    ObjectUID PiouPiou::getSenderUID() const {
        return _Sender->getUID();
    }

    int PiouPiou::getDamage() const {
        return _Damage;
    }
}