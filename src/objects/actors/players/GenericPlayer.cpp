/*
 *  FICHIER: GenericPlayer.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *  DESCRIPTION:
 *  Un joueur définissable par un fichier externe
 */

#include "GenericPlayer.h"

namespace beat {
    /**
     * Le constructeur
     */
    GenericPlayer::GenericPlayer(unsigned int playerCount) : Player(playerCount) {
        _boundingBox = 0;
        _elapsedTime = 0;
        _hit = false;
    }
    
    /**
     * Le destructeur
     */
    GenericPlayer::~GenericPlayer() {
    }
    
    /**
     * Charge le joueur à partir d'un fichier
     */
	void GenericPlayer::setIsWalking(bool i)
	{
		if(i == false && i != _isWalking)
			_walk->restart();
		_isWalking = i;
	}

    bool GenericPlayer::loadFromFile(std::string const& path) {
        std::ifstream stream;
        
        stream.open(path.c_str());
        
        // Si l'ouverture échoue
        if(!stream.is_open()) {
            std::cerr << "Impossible to load '" << path << "'!" << std::endl;
            return false;
        }
        
        while(stream.good()) {
            std::string token;
            
            stream >> token;
            
            if(token == "name:") {
                stream >> _name;
            }
            else if(token == "health:") {
                stream >> _Health;
                
                if(stream.fail()) {
                    return false;
                }
                
                _MaxHealth = _Health;
            }
            else if(token == "sequences{") {
                // On lit jusqu'au }
                do {
                    
                    if(token == "file:") {
                        stream >> token;
                        
                        AnimationSequence sequence;
                        if(!sequence.loadFromFile(resourcePath() + token)) {
                            std::cerr << "Can't load '" << resourcePath() + token << "'!" << std::endl;
                            return false;
                        }
                        
                        _sequences.push_back(sequence);
                    }
                    
                    stream >> token;
                }while(token != "}");
            }
            else if(token == "combotree:") {
                stream >> token;
                _comboTree.loadFromFile(resourcePath() + token, *this);
            }
            else if(token == "walkingspeed:") {
                stream >> _WalkingSpeed;
                
                if(stream.fail())
                    return false;
            }
            else if(token == "jumpspring:") {
                stream >> _JumpSpring;
                
                if(stream.fail())
                    return false;
            }
            else if(token == "texture:") {
                stream >> _textureName;
                
                if(stream.fail())
                    return false;
            }
            
        }
		_comboTimer = 0;
		_comboBlock = false;
		_comboStart = false;
        _comboIterator = _comboTree.begin();
        _actualSequence = &(*_comboIterator);

		_walk = &(getAnimationSequence(1));

		_isWalking = false;

        
        return true;
    }
    
    void GenericPlayer::syncHitboxes(AnimationSequence &sequence) {
        // On parcourt toutes les boites d'une frame
        for(int i = 0; i < sequence.getNbHitbox(); i++) {
            cegep::list<BoxBody*>::iterator it;
            Hitbox hitbox = sequence.getHitboxAt(i);
            
            if(hitbox.informations == 0) {
                _bodyHitbox = hitbox;
            }
            
            // Ensuite on regarde toutes les boîtes de l'objet
            for(it = _hitboxes.begin(); it != _hitboxes.end(); it++) {
                BoxBody* body = (BoxBody*)(*it);
                body->possessor = this;
                
                if(body->collisionMask != 0) {
                    body->setPosition(sf::Vector2f(-1000, 0));
                    body->desactivate();
                }
                
                if(hitbox.informations == (*it)->collisionMask) {
                    body->setDimensions(hitbox.box.width * (*_textureHandler).getWidth(),
                                        hitbox.box.height * (*_textureHandler).getHeight());
                    body->activate();
                    
                    // Si c'est pas le corps de l'objet on le place à sa position dans le fichier de séquence + celle du joueur
                    if(body != _boundingBox) {
                        float mod = 1.0f;
                        
                        if(_direction == DIRECTION_LEFT)
                            mod = -1.0f;
                        
                        if(_direction == DIRECTION_RIGHT)
                            body->setPosition(sf::Vector2f(_Position.x  + hitbox.box.left * (*_textureHandler).getWidth(),
                                                           _Position.y + hitbox.box.top * (*_textureHandler).getHeight()));
                        else {
                            body->setPosition(sf::Vector2f(_Position.x - (hitbox.box.left + hitbox.box.width) * (*_textureHandler).getWidth(),
                                                           _Position.y + hitbox.box.top * (*_textureHandler).getHeight()));
                        }
                    }
                    
                    break;
                }
            }
            
            // Si on c'est rendu à la fin de l'itération alors il manque cette boite
            if(it == _hitboxes.end()) {
                BoxBody* newBody = sObjectManager->getWorld().createBoxBody(_Position.x - hitbox.box.left * (*_textureHandler).getWidth(),
                                                                            _Position.y - hitbox.box.top * (*_textureHandler).getHeight(),
                                                                            hitbox.box.width * (*_textureHandler).getWidth(),
                                                                            hitbox.box.height * (*_textureHandler).getHeight());
                newBody->collisionMask = hitbox.informations;
                newBody->possessor = this;
                
                if(newBody->collisionMask == 0) {
                    newBody->setGravityAffected(true);
                    _boundingBox = newBody;
                    _bodyHitbox = hitbox;
                }
                else
                    newBody->setGravityAffected(false);
                
                _hitboxes.insert(_hitboxes.begin(), newBody);
            }
        }
    }
    
    /**
     * Appelée chaque frame
     */
    void GenericPlayer::onUpdate(int milliSec) {
        _elapsedTime += milliSec;
		if(_isWalking == true)
			_actualSequence = _walk;
        
        if(_elapsedTime - _hitE >= 1000 && _hit == true) {
            _hit = false;
        }
        
        _Sprite.setColor(sf::Color::White);
        
        if((_elapsedTime - _hitE) % 300 <= 150 && _hit) {
            _Sprite.setColor(sf::Color(255, 255, 255, 100));
        }
        
        if(_boundingBox != 0) {
            _Position = sf::Vector2f(_boundingBox->getPosition().x, _boundingBox->getPosition().y);
            
            _Position.y += (((*_comboIterator).getActualOrigin().y - ((*_comboIterator).getHitboxAt(0).box.top  -
                                                                     ((*_comboIterator).getFrameRect().top)))) * (*_textureHandler).getHeight();
        
            _Position.x += (((*_comboIterator).getActualOrigin().x - ((*_comboIterator).getHitboxAt(0).box.left -
                                                                     ((*_comboIterator).getFrameRect().left)))) * (*_textureHandler).getWidth();
        }
        
        if(_Velocity.y < 0.01f || _Velocity.y > -0.01f) {
            _Velocity.y = 0.0f;
            _onFloor = true;
        }
        
        (*_comboIterator).play();
		(*_comboIterator).update(milliSec);
        
		if(_comboStart == true) {
			_comboTimer += milliSec;
			if(_comboTimer > 200 && !_comboBlock) {
				_comboBlock = true;
				_comboStart = false;
				(*_comboIterator).restart();
			}
		}
		else if((*_comboIterator).finished()) {
            _comboIterator = _comboTree.begin();
            _comboBlock = false;
            (*_comboIterator).restart();
        }
		else if(_comboIterator == _comboTree.begin() && (*_comboIterator).finished())
			(*_comboIterator).restart();

		//Si il marche pas
        if(_isWalking == false || (_comboStart || _comboBlock))
			_actualSequence = &(*_comboIterator);
		else {
			_actualSequence = _walk;
			_actualSequence->play();
			_actualSequence->update(milliSec);
			if(_actualSequence->finished())
				_actualSequence->restart();
		}
        AnimationSequence &sequence = *_actualSequence;

        sf::FloatRect rect = sequence.getFrameRect();
        sf::Vector2f origin = sequence.getActualOrigin();

        // Mise à jour du sprite
        _Sprite.setOrigin(origin.x * (*_textureHandler).getWidth(), origin.y * (*_textureHandler).getHeight());
        _Sprite.setTextureRect(sf::IntRect(rect.left * (*_textureHandler).getWidth(),
                                           rect.top * (*_textureHandler).getHeight(),
                                           rect.width * (*_textureHandler).getWidth(),
                                           rect.height * (*_textureHandler).getHeight()));
        
        if(_direction == DIRECTION_LEFT) {
            _Sprite.setScale(-1, 1);
        }
        else
            _Sprite.setScale(1, 1);
        
        syncHitboxes(sequence);
        
		_comboIterator.onUpdate(milliSec, this);
    }
    
    /**
     * Appelé juste avant la destruction
     */
    void GenericPlayer::onKill() {
    }
    
    /**
     * Appelé la première itération
     */
    void GenericPlayer::onCreation() {
        this->syncHitboxes(*_actualSequence);
    }
    
    /**
     * Définit une attaque de base
     */
    void GenericPlayer::attackA() {
		if(!_comboBlock) {
			_comboStart = true;
			if(_comboIterator.goa1())
				_comboTimer = 0;
		}
    }
    
    /**
     * Définit une seconde attaque de base
     */
    void GenericPlayer::attackB() {
		if(!_comboBlock) {
			_comboStart = true;
			if(_comboIterator.goa2())
				_comboTimer = 0;
		}
    }
    
    /**
     * Execute un saut au personnage
     */
    void GenericPlayer::jump() {
        if(_Velocity.y >= 0 && _boundingBox->getPosition().y + _boundingBox->getHeight() >= sObjectManager->getWorld().getFloorHeight()) {
            _boundingBox->setVelocity(sf::Vector2f(_boundingBox->getVelocity().x, _JumpSpring));
            
            _onFloor = false;
        }
    }
    
    /**
     * Déplace le joueur vers la gauche
     */
    void GenericPlayer::moveLeft() {
        
		if(_comboIterator == _comboTree.begin()) {
			sideMove(-1);
			_isWalking = true;
        }
		else if(!_comboBlock) {
			if(_direction == DIRECTION_RIGHT) {	//Check side
				if(_comboIterator.gog())
					_comboTimer = 0;
			}
			else {
				if(_comboIterator.god())
					_comboTimer = 0;
			}
			_comboStart = true;
            
            //_actualSequence = &_sequences[1];
		}
    }
    
    /**
     * Déplace le joueur vers la droite
     */
    void GenericPlayer::moveRight() {
		if(_comboIterator == _comboTree.begin()) {
			sideMove(1);
			_isWalking = true;
        }
		else if(!_comboBlock) {
			if(_direction == DIRECTION_LEFT) {	//Check side
				if(_comboIterator.gog())
					_comboTimer = 0;
			}
			else {
				if(_comboIterator.god())
					_comboTimer = 0;
			}
			_comboStart = true;
            
           //_actualSequence = &_sequences[1];
		} 
    }
    
    /**
     * Que faire en cas de collision avec un autre
     */
    void GenericPlayer::onCollision(Collision const& collision) {
        
        if(_hit) return;
        
        if(collision.getObject() == 0) return;
        
        switch(collision.getObject()->getType()) {
            case OBJECT_ACTOR: {
                Actor* actor = (Actor*)collision.getObject();
                
                switch(actor->getActorType()) {
                    case Actor::ACTOR_PLAYER: {
                        if(collision.informations != 0) {
                            float velX = 1.5;
                            
                            if(_direction == DIRECTION_RIGHT)
                                velX *= -1;
                            
                            _boundingBox->setVelocity(sf::Vector2f(velX, -0.7));
                            this->hit(10);
                            _hit = true;
                            _hitE = _elapsedTime;
                        }
                        
                    }
                    default:
                        break;
                }
                
            }
                break;
            case OBJECT_PROJECTILE: {
                PiouPiou* projectile = (PiouPiou*)collision.getObject();
                
                if(projectile->getSenderUID() != this->getUID()) {
                    this->hit(projectile->getDamage());
                    _hit = true;
                    _hitE = _elapsedTime;
                    
                    projectile->setAlive(false);
                }
            }
                break;
                default:
                break;
        }
    }
    
    void GenericPlayer::clearHitboxes() {
        cegep::list<BoxBody*>::iterator it = _hitboxes.begin();
        
        while(it != _hitboxes.end()) {
            sObjectManager->getWorld().removeBody(*it);
            
            it = _hitboxes.erase(it);
        }
    }
}