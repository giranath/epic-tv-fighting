/*
 *  FICHIER: CollisionManager.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-25
 *
 */

#include "CollisionManager.h"
#include <assert.h>
#include "ObjectManager.h"

namespace beat {
    CollisionManager::CollisionManager(ObjectManager &objectManager) : _objectManager(objectManager) {
        
    }

    CollisionManager::~CollisionManager() {
        
    }
    
    void CollisionManager::step(unsigned int delta) {
        if(_collisionBuddies.empty())
            return;
         
        // On parcourt chaque objet
        for(HitboxBuddyIterator it = _collisionBuddies.begin(); it != --_collisionBuddies.end(); ++it) {
            HitboxBuddyIterator tempIt = it;
            // Puis après tous les autres
            for(HitboxBuddyIterator it2 = ++tempIt; it2 != _collisionBuddies.end(); ++it2) {
                // Ici on a accédé au deux objets.
                // Il faut dorénavant tester tous leurs hitboxs entre eux
                
                // Tous les hitbox de A
                for(int hitba = 0; hitba < it->second.size(); hitba++) {
                    // Tous les hitbox de B
                    for(int hitbb = 0; hitbb < it2->second.size(); hitbb++) {
                        HitboxBuddy &A = it->second[hitba];
                        HitboxBuddy &B = it2->second[hitbb];
                        
                        // Si au moins une des deux hitbox est active, alors il est possible qu'il y est collision
                        if(!A.inactive || !B.inactive) {
                            Contact contact;
                            
                            // Si la boite A touche à B alors il y a collision
                            if(A.hitbox.intersects(B.hitbox, contact)) {
                                // On récupère les objets en contact dans le gestionnaire de collision
                                Object *objA, *objB;
                                
                                objA = _objectManager.getObjectWithUID(it->first);
                                objB = _objectManager.getObjectWithUID(it2->first);
                                
                                
                                /*
                                 * Ici on envoi le signale aux deux objets qu'une collision est survenue
                                 */
                                
                                if(objA != 0)
                                    objA->onCollision(Collision(objB, A.hitbox, B.hitbox, contact));
                                
                                if(objB != 0)
                                    objB->onCollision(Collision(objA, B.hitbox, A.hitbox, contact));
                            }
                        }
                    }
                }
            }
        }
    }
    
    unsigned int CollisionManager::add(ObjectUID object, sf::FloatRect hitbox) {
        _collisionBuddies[object].push_back(hitbox);
        
        return (unsigned int)_collisionBuddies[object].size() - 1;
    }
    
    void CollisionManager::alter(ObjectUID object, unsigned int index, sf::FloatRect hitbox) {
        assert(exists(object, index));
        
        _collisionBuddies[object][index].hitbox = hitbox;
        _collisionBuddies[object][index].inactive = false;
    }
    
    sf::FloatRect CollisionManager::get(ObjectUID object, unsigned int index) const {
        assert(exists(object, index));
        
        HitboxBuddy buddy = _collisionBuddies.at(object).at(index);
        
        return buddy.hitbox;
    }

    bool CollisionManager::exists(ObjectUID object, unsigned int index) const {
        return _collisionBuddies.find(object) != _collisionBuddies.end();
    }
    
    void CollisionManager::remove(ObjectUID object) {
        HitboxBuddyIterator it = _collisionBuddies.find(object);
        
        if(it != _collisionBuddies.end()) {
            _collisionBuddies.erase(it);
        }
    }
    
    void CollisionManager::remove(ObjectUID object, unsigned int index) {
        assert(exists(object, index));
        
        _collisionBuddies[object].erase(_collisionBuddies[object].begin() + index);
    }
    
    unsigned long CollisionManager::getNbHitboxOf(ObjectUID object) const {
        if(!exists(object, 0)) {
            return 0;
        }
        else {
            return _collisionBuddies.at(object).size();
        }
    }
}