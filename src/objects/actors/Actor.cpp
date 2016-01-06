/**
 * FICHIER: Actor.cpp
 * PROJET:  TP3
 * AUTHEUR: Rukusan aka Luc Bossé
 *
 * DESCRIPTION;
 *      Classe de base pour tous les acteurs du jeu, dérive d'Object
 */

#include "Actor.h"

namespace beat {
	Actor::Actor(ActorType const& type) : Object(OBJECT_ACTOR) {
		_Health = 100;
		_MaxHealth = 100;
		_WalkingSpeed = 4;
        _actorType = type;
        
        _direction = DIRECTION_RIGHT;
        
        _JumpSpring = -1.6;
        
        _onFloor = true;
	}

	void Actor::sideMove(int direction) {
		if(_boundingBox != 0) {
            _Velocity = sf::Vector2f(_WalkingSpeed * direction, _boundingBox->getVelocity().y);
			_boundingBox->setVelocity(_Velocity);
	
        }
    }

	Actor::~Actor() {
		_Health = 0;
		_MaxHealth = 0;
		_WalkingSpeed = 0;
	}

	Actor::Direction Actor::getDirection() const {
		return _direction;
	}

	void Actor::jump() {
        if(_boundingBox != 0) {
            _Velocity = sf::Vector2f(_boundingBox->getVelocity().x, _JumpSpring);
            _boundingBox->setVelocity(_Velocity);
        }
    }
    
    void Actor::moveLeft() {
        sideMove(-1);
    }
    
    void Actor::moveRight() {
        sideMove(1);
    }
    
    void Actor::wait() {
        sideMove(0);
    }

	void Actor::onDraw(sf::RenderTarget& target) {
		_Sprite.setPosition(_Position);
		target.draw(_Sprite);
	}
    
    Actor::ActorType Actor::getActorType() const {
        return _actorType;
    }
    
    int Actor::getMaxHealth() const {
        return _MaxHealth;
    }
    
    int Actor::getHealth() const {
        return _Health;
    }
    
    void Actor::hit(unsigned int damage) {
        _Health -= damage;
        
        if(_Health <= 0)
            _Health = 0;
    }
    
    void Actor::setFacingDirection(Direction direction) {
        _direction = direction;
    }
    
    bool Actor::onFloor() const {
        return _onFloor;
    }
    
    BoxBody* Actor::getBoxBody() const {
        return _boundingBox;
    }
    
    void Actor::setLife(int health) {
        _Health = health;
        
        if(_Health > _MaxHealth)
            _Health = _MaxHealth;
    }
}