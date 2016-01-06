/*
 *  FICHIER: CollisionManager.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-25
 *  DESCRIPTION:
 *  Un gestionnaire de collision
 */

#ifndef __TP3__CollisionManager__
#define __TP3__CollisionManager__

#include "Object.h"
#include "Collision.h"
#include <map>
#include <vector>

namespace beat {
    class ObjectManager;
    
    class CollisionManager {
    private:
        
        struct HitboxBuddy {
            bool inactive;
            sf::FloatRect hitbox;
            
            HitboxBuddy(sf::FloatRect hitbox) {
                this->hitbox = hitbox;
                inactive = false;
            }
            
            operator sf::FloatRect() {
                return hitbox;
            }
        };
        
        typedef std::map<ObjectUID, std::vector<HitboxBuddy> >::iterator HitboxBuddyIterator;
        
        /**
         * Une map de vecteur de boite de collision
         */
        std::map<ObjectUID, std::vector<HitboxBuddy> > _collisionBuddies;
        
        /**
         * Une référence vers le gestionnaire d'objet
         */
        ObjectManager& _objectManager;
        
    public:
        /**
         * Constructeur
         */
        CollisionManager(ObjectManager &objectManager);
        
        /**
         * Destructeur
         */
        ~CollisionManager();
        
        /**
         * Vérifie les collisions
         */
        void step(unsigned int delta);
        
        /**
         * Ajoute une boite de collision à un objet
         */
        unsigned int add(ObjectUID object, sf::FloatRect hitbox);
        
        /**
         * Modifie une boite de collision dans un objet
         */
        void alter(ObjectUID object, unsigned int index, sf::FloatRect hitbox);
        
        /**
         * Retourne la boite de collision à un index dans un objet
         */
        sf::FloatRect get(ObjectUID object, unsigned int index) const;
        
        /**
         * Informe si un objet existe dans l'arbre
         */
        bool exists(ObjectUID object, unsigned int index) const;
        
        /**
         * Retire un objet du système
         */
        void remove(ObjectUID object);
        
        /**
         * Retire une boite de collision
         */
        void remove(ObjectUID object, unsigned int index);
        
        /**
         * Retourne le nombre d'hitbox contenu par un objet
         */
        unsigned long getNbHitboxOf(ObjectUID object) const;
    };
}

#endif
