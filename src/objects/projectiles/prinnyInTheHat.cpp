#include "prinnyInTheHat.h"
#include "FXLoader.h"
#include "ObjectManager.h"

namespace beat {

	prinnyHat::prinnyHat(Object* sender) : PiouPiou(sender, 45) {
        _body = 0;
        _elapsedTime = 0;
    }

	void prinnyHat::onCreation() {
		_fx = FXLoader::createFromFile(resourcePath() + "datas/effects/dancingPrinny.fx");
		_body = sObjectManager->getWorld().createBoxBody(_Sender->getPosition().x, _Sender->getPosition().y,
			_fx->getAnimationSequence().getFrameRect().width, _fx->getAnimationSequence().getFrameRect().height);
		_body->setGravityAffected(true);
        _body->setPosition(_Position);
        _body->possessor = this;
        _fx->getAnimationSequence().play();
        
        _v = _Velocity.x;
	}

	void prinnyHat::onUpdate(int milliSec) {
		_elapsedTime += milliSec;
        _Position = _body->getPosition();
        
        if(_Position.y + _fx->getAnimationSequence().getFrameRect().height >= Object::sObjectManager->getWorld().getFloorHeight())
            _body->setVelocity(sf::Vector2f(_v * PRINNYHAT_SPEED, 0));
        
        if(_body->getPosition().x <= 0 ||
           _body->getPosition().x + 50 >= sObjectManager->getWorld().getWidth() ||
           _elapsedTime > 10000) {
            _Alive = false;
        }
		_fx->onUpdate(milliSec);
	}

	void prinnyHat::onDraw(sf::RenderTarget& target) {
		_fx->setPosition(_Position.x,_Position.y);
		_fx->onDraw(target);
	}

	void prinnyHat::onKill() {
		sObjectManager->getWorld().removeBody(_body);
	}
        
    void prinnyHat::onCollision(Collision const& collision) {
		if(collision.getObject()->getType() == OBJECT_PROJECTILE) {
            _Alive = false;
        }
	}
}