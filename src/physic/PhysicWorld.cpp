/*
 *  FICHIER: PhysicWorld.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *
 */

#include "PhysicWorld.h"
#include <iostream>


namespace beat {
    PhysicWorld::PhysicWorld(sf::Vector2f const& gravity) {
        _gravity = gravity;
        _elapsedTime = 0;
        _width = 800;
        _floor = FLOOR_HEIGHT;
		_ceiling = _floor - 450;
    }
    
    PhysicWorld::~PhysicWorld() {
        clear();
    }
    
    void PhysicWorld::clear() {
        for(cegep::list<PhysicBody*>::iterator it = _bodies.begin(); it != _bodies.end(); it++) {
            delete *it;
        }
        
        _bodies.clear();
    }
    
    /**
     * Crée un corps
     */
    BoxBody* PhysicWorld::createBoxBody(float posX, float posY, float width, float height, bool dynamic, bool gravity) {
        BoxBody* body = new BoxBody(sf::Vector2f(posX, posY), width, height, dynamic, gravity);
        
        _bodies.insert(_bodies.begin(), body);
        
        return body;
    }
    
    /**
     * Retire un corps
     */
    void PhysicWorld::removeBody(PhysicBody* body) {
        for(cegep::list<PhysicBody*>::iterator it = _bodies.begin(); it != _bodies.end(); it++) {
            if(*it == body) {
                delete *it;
                _bodies.erase(it);
                
                return;
            }
        }
    }
    
    /**
     * Met à jour le monde
     */
    void PhysicWorld::step(unsigned int deltaMs) {
        _elapsedTime += deltaMs;
        
        if(_elapsedTime < 35) {
            return;
        }
        
        for(cegep::list<PhysicBody*>::iterator it = _bodies.begin(); it != _bodies.end(); it++) {
            PhysicBody* body = *it;
            
            BoxBody *boxA;
            boxA = (BoxBody*)(*it);
            
            if(!boxA->isActivated())
                continue;
            
			BoxBody* rawr = (BoxBody*)(body);					//CAst
            if(body->isDynamic() && body->isAffectedByGravity()) {
				if(body->getPosition().y + rawr->getHeight() < _ceiling)			//plafond
					body->setVelocity(sf::Vector2f(body->getVelocity().x, 0));
                 body->setVelocity(body->getVelocity() + _gravity);
                
                if(body->possessor != 0)
                    body->possessor->setVelocity(0, 0);
            }
            
            // On deplace le corps en fonction de sa vélocité
            body->setPosition(body->getPosition() + (body->getVelocity() * (float)_elapsedTime));

            if(body->getType() == PhysicBody::BODY_BOX) {
                BoxBody* boxBody = (BoxBody*)(body);
                
                if(boxBody->getPosition().y + boxBody->getHeight() > _floor && body->isDynamic() && boxBody->isAffectedByGravity()) {
                    boxBody->setPosition(sf::Vector2f(boxBody->getPosition().x, _floor - boxBody->getHeight()));
                    boxBody->setVelocity(sf::Vector2f(0, 0));
                }
                
                if(boxBody->getPosition().x < 0 && body->isDynamic()) {
                    boxBody->setPosition(sf::Vector2f(0, boxBody->getPosition().y));
                }
                else if(boxBody->getPosition().x + boxBody->getWidth() > _width && body->isDynamic()) {
                    boxBody->setPosition(sf::Vector2f(_width - boxBody->getWidth(), boxBody->getPosition().y));
                }
            }
            else {
                if(body->getPosition().y > _floor && body->isDynamic() && body->isAffectedByGravity()) {
                    body->setPosition(sf::Vector2f(body->getPosition().x, _floor));
                    body->setVelocity(sf::Vector2f(0, 0));
                }
            }
            
            // On place un itérateur vers le prochain élément
            cegep::list<PhysicBody*>::iterator temp = it;
            temp++;
            
            // On test les collisions maintenant
            // Pour les tests, on commence au prochain élément jusqu'à la fin
			
            for(cegep::list<PhysicBody*>::iterator it2 = temp; it2 != _bodies.end(); it2++) {
                
                // S'il s'agit de deux boites
                if((*it)->getType() == PhysicBody::BODY_BOX && (*it2)->getType() == PhysicBody::BODY_BOX) {
                    // On les converti en boîtes
                    BoxBody *boxB;
                    boxB = (BoxBody*)(*it2);
                    
                    if(!boxB->isActivated())
                        continue;
                    
                    if(boxA->possessor == boxB->possessor)
                        continue;
                                        
                    sf::FloatRect rect, rectA, rectB;
                    rectA = boxA->getBoundingBox();
                    rectB = boxB->getBoundingBox();
                
                    // Si les deux rectangles se touchent
                    if(rectA.intersects(rectB, rect)) {
                        Object *A, *B;
                        
                        A = boxA->possessor;
                        B = boxB->possessor;
                        
                        /*
                         * Envoyé la collision
                         */
                        
                        Collision collisionA(B, boxA->getBoundingBox(), boxB->getBoundingBox(), rect);
                        collisionA.informations = boxB->collisionMask;
                        
                        Collision collisionB(A, boxB->getBoundingBox(), boxA->getBoundingBox(), rect);
                        collisionB.informations = boxA->collisionMask;
                        
                        if(A != 0) {
                            A->onCollision(collisionA);
                        }
                        
                        if(B != 0) {
                            B->onCollision(collisionB);
                        }
                        
                    }
                }
            }
        }
		_elapsedTime = 0;
    }
    
    void PhysicWorld::setGravity(sf::Vector2f const& gravity) {
        _gravity = gravity;
    }
    
    void PhysicWorld::debugDraw(sf::RenderTarget& target) {
        for(cegep::list<PhysicBody*>::iterator it = _bodies.begin(); it != _bodies.end(); it++) {
			//static int hauteurMax = 9999;
            switch((*it)->getType()) {
                case PhysicBody::BODY_BOX: {
                    BoxBody* box = (BoxBody*)(*it);
                    
                    sf::RectangleShape shape;
                    shape.setOrigin(0, 0);
                    shape.setPosition((*it)->getPosition());
                    shape.setSize(sf::Vector2f(box->getWidth(), box->getHeight()));
                    shape.setFillColor(sf::Color(255, 0, 255, 100));
                    shape.setOutlineColor(sf::Color::Magenta);
                    shape.setOutlineThickness(2.0f);

					/*
					if(hauteurMax > shape.getPosition().y + shape.getSize().y)
						hauteurMax = shape.getPosition().y + shape.getSize().y;
					std::cout << "hauteur max " << hauteurMax << std::endl;
                    */

                    target.draw(shape);
                    
                    shape.setSize(sf::Vector2f(_width, 0));
                    shape.setPosition(0, _floor);
                    shape.setOutlineColor(sf::Color::Green);
                    
                    target.draw(shape);
                }
                    break;
                default:
                    break;
            }
        }
    }
    
    void PhysicWorld::setWidth(unsigned int width) {
        _width = width;
    }
    
    unsigned int PhysicWorld::getWidth() const {
        return _width;
    }
    
    void PhysicWorld::setFloorHeight(unsigned int h) {
        _floor = h;
    }
    
    unsigned int PhysicWorld::getFloorHeight() const {
        return _floor;
    }

	void PhysicWorld::setCeilingHeight(unsigned int h) {
        _ceiling = h;
    }
    
    unsigned int PhysicWorld::getCeilingHeight() const {
        return _ceiling;
    }
}
