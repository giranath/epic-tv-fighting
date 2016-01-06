/*
 *  FICHIER: Shoot.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-12-13
 *
 */

#include "Shoot.h"

namespace beat {
    Shoot::Shoot(unsigned int shootFrame, unsigned int startID, AnimationSequence& sequence, ShootType type) : _sequence(sequence) {
        _shootFrame = shootFrame;
        _shootStartLocID = startID;
        _type = type;
        _ready = false;
    }
    
    void Shoot::onStart() {
        _ready = true;
    }
    
    void Shoot::onUpdate(int delta, beat::Player* me) {
        // Si on est dans la séquence de tir
        if(_sequence.getFrameIndex() == _shootFrame) {
            Hitbox rect = _sequence.getHitboxWithID(_shootStartLocID);
            
            rect.box.left *= me->getTextureHandler()->getWidth();
            rect.box.top *= me->getTextureHandler()->getHeight();
            
            switch(_type) {
                case GUNTHERKEN: {
                    float velX = 1;
                    
                    if(me->getDirection() == Actor::DIRECTION_LEFT) {
                        velX *= -1;
                        rect.box.left *= -1;
                        rect.box.left -= 50;
                    }
                    
                    if(_ready == true)
                        Object::sObjectManager->addObject(ProjectileFactory::createGuntherKen(me, sf::Vector2f(rect.box.left, rect.box.top), sf::Vector2f(velX, 0)));
                }
                break;
				case PRINNYHAT: {
					float velX = 1;
                    
                    if(me->getDirection() == Actor::DIRECTION_LEFT) {
                        velX *= -1;
                        rect.box.left *= -1;
                        //rect.box.left -= 50;
                    }
                    
                    if(_ready == true)
                        Object::sObjectManager->addObject(ProjectileFactory::createPrinnyHat(me, sf::Vector2f(rect.box.left, rect.box.top), sf::Vector2f(velX, 0)));
					}

					break;
                default:
                    break;
            }
          
            _ready = false;
        }
    }
    
    void Shoot::onHit(beat::Player* enemy) {
        
    }
}