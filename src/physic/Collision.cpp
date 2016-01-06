/*
 *  FICHIER: Collision.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-25
 *
 */

#include "Collision.h"

namespace beat  {
    /**
     * Super constructeur
     */
    Collision::Collision(Object* object, sf::FloatRect myHitbox, sf::FloatRect otherHitbox, Contact contact) {
        _object = object;
        _hitboxMe = myHitbox;
        _hitBoxOther = otherHitbox;
        _contact = contact;
    }
    
    /**
     * Retourne l'objet
     */
    Object* Collision::getObject() const {
        return _object;
    }
    
    /**
     * Retourne ma hitbox
     */
    sf::FloatRect Collision::getMyHitbox() const {
        return _hitboxMe;
    }
    
    /**
     * Retourne la hitbox de l'autre
     */
    sf::FloatRect Collision::getOtherHitbox() const {
        return _hitBoxOther;
    }
    
    /**
     * Retourne le point de contact avec l'objet
     */
    Contact Collision::getContact() const {
        return _contact;
    }
}