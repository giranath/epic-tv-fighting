/*
 *  FICHIER: Collision.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-25
 *  DESCRIPTION:
 */

#ifndef __TP3__Collision__
#define __TP3__Collision__

#include <SFML/Graphics.hpp>

namespace beat {
    class Object;
    
    /**
     * Rectangle représentant ce qui se touche entre deux rectangle
     */
    typedef sf::FloatRect Contact;
    
    class Collision {
    public:
        /**
         * Super constructeur
         */
        Collision(Object* object = 0, sf::FloatRect myHitbox = sf::FloatRect(), sf::FloatRect otherHitbox = sf::FloatRect(), Contact contact = Contact());
        
        /**
         * Retourne l'objet
         */
        Object* getObject() const;
        
        /**
         * Retourne la hitbox de celui qui est en collision
         */
        sf::FloatRect getMyHitbox() const;
        
        /**
         * Retourne la hitbox de l'autre
         */
        sf::FloatRect getOtherHitbox() const;
        
        /**
         * Retourne le point de contact avec l'objet
         */
        Contact getContact() const;
        
        /**
         * Informations sur la collision (le collisionMask pour le moment)
         */
        int informations;
        
    private:
        /**
         * L'objet avec lequel il y a collision
         */
        Object* _object;
        
        /**
         * La hitbox de l'objet en collision
         */
        sf::FloatRect  _hitBoxOther,
                        _hitboxMe;
        
        /**
         * Le point de contact sur la hitbox
         */
        Contact _contact;
    };
}

#endif
