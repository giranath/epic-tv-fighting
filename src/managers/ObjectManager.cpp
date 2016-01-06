/**
 * FICHIER: ObjectManager.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Objet permmetant de gérer tous les objets dynamiques du jeu
 */

#include "ObjectManager.h"

namespace beat {
    ObjectManager::ObjectManager() {
        _world = new PhysicWorld(sf::Vector2f(0, 0.1));
    }
    
    ObjectManager::~ObjectManager() {
        clear();
        
        delete _world;
    }

    void ObjectManager::addObject(Object* object) {
        object->onCreation();
        
        _objectList.insert(_objectList.begin(), object);
    }

    void ObjectManager::removeObject(Object* object) {
        if(object != 0) {
            object->setAlive(false);
        }
    }
    
    void ObjectManager::removeObject(ObjectUID UID) {
        Object* obj = getObjectWithUID(UID);
        
        removeObject(obj);
    }
    
    void ObjectManager::step(int deltaMs) {
        // On crée un itérateur pointant sur le premier élément
        cegep::list<Object*>::iterator it = _objectList.begin();
        
        // Tant qu'on atteind pas la fin...
        while(it != _objectList.end()) {
            
            // On met à jour l'objet itéré
            (*it)->onUpdate(deltaMs);
            
            // S'il n'est plus en vie après la mise à jour, on l'efface de la liste
            if((*it)->isAlive() == false) {
                (*it)->onKill();
                
                delete *it;
                
                it = _objectList.erase(it);
            }
            else {
                it++;
            }
        }
    }
    
    void ObjectManager::drawVisibles(sf::RenderTarget& target) {
        // On parcourt tous les objets. S'il sont visibles, on les affichent
        for(cegep::list<Object*>::iterator it = _objectList.begin(); it != _objectList.end(); it++)  {
            if((*it)->isVisible())
                (*it)->onDraw(target);
            
        }
    }
    
    void ObjectManager::clear() {
        for(cegep::list<Object*>::iterator it = _objectList.begin(); it != _objectList.end(); it++) {
            delete *it;
        }
        
        _objectList.clear();
    }
    
    Object* ObjectManager::getObjectWithUID(ObjectUID UID) const {
        for(cegep::list<Object*>::iterator it = _objectList.begin(); it != _objectList.end(); ++it) {
            if((*it)->getUID() == UID) {
                return *it;
            }
        }
        
        return 0;
    }
    
    PhysicWorld& ObjectManager::getWorld() {
        return *_world;
    }
}