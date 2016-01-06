/*
 *  FICHIER: PlayerGiranath.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *
 */

#include "PlayerGiranath.h"
#include "Projectile.h"

namespace beat {
    PlayerGiranath::PlayerGiranath(unsigned int playerCount) : Player(playerCount) {
        _WalkingSpeed = 0.35f;
        _sequences.resize(7);
        
        _kickBox = 0;
        _punchBox = 0;
        
        _MaxHealth = _Health = 100;
        
        _JumpSpring = -1.7;
        
        _name = "Tralalathan";
        _actualSequence = &_sequences[GIRANATH_IDLE_SEQUENCE];
    }
    
    /**
     * Appelé la première itération
     */
    void PlayerGiranath::onCreation() {
        /**
         * On charge les ressources nécessaires au fonctionnement du joueur
         * Ici il s'agit des ses animations
         */
        if(!_sequences[GIRANATH_IDLE_SEQUENCE].loadFromFile(resourcePath() + "giranath_idle.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S IDLE SEQUENCE FILE!" << std::endl;
        }
        
        if(!_sequences[GIRANATH_WALKING_SEQUENCE].loadFromFile(resourcePath() + "giranath_walking.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S WALKING SEQUENCE FILE " << std::endl;
        }
        
        if(!_sequences[GIRANATH_LEFT_PUNCH_SEQUENCE].loadFromFile(resourcePath() + "giranath_left_punch.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S LPUNCH SEQUENCE FILE " << std::endl;
        }
        
        if(!_sequences[GIRANATH_RIGHT_PUNCH_SEQUENCE].loadFromFile(resourcePath() + "giranath_hadoken.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S RPUNCH SEQUENCE FILE!" << std::endl;
        }
        
        
        if(!_sequences[GIRANATH_RIGHT_KICK_SEQUENCE].loadFromFile(resourcePath() + "giranath_knee_kick.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S RKICK SEQUENCE FILE " << std::endl;
        }
        
        if(!_sequences[GIRANATH_JUMP_SEQUENCE].loadFromFile(resourcePath() + "giranath_jump.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S JUMP SEQUENCE FILE " << std::endl;
        }
        
        if(!_sequences[GIRANATH_HIT_SEQUENCE].loadFromFile(resourcePath() + "giranath_hit.seq")) {
            std::cerr << "CAN'T LOAD GIRANATH'S HIT SEQUENCE FILE " << std::endl;
        }
        
        /**
         * On crée le corps physique
         */
        _boundingBox = sObjectManager->getWorld().createBoxBody(_Position.x, _Position.y, 80, 300);
        
        _boundingBox->possessor = this;
        _boundingBox->collisionMask = _playerCount;
        
        _actualSequence->play();
    }
    
    /**
     * Appelée chaque frame
     */
    void PlayerGiranath::onUpdate(int milliSec) {
        if(_Health == 0) {
            _Visible = false;
        }
        
        // On met à jour la position
        _Position = _boundingBox->getPosition();
        _Position.x += 25;
        _Position.y += 160;
        
        // On syncronise la vélocité du corps physique à celle de l'objet
        _Velocity = _boundingBox->getVelocity();
        
        // On met à jours la séquence d'animation
        _actualSequence->update(milliSec);
        
        if(_actualSequence == &_sequences[GIRANATH_JUMP_SEQUENCE]) {
            if(_actualSequence->getFrameIndex() == 2) {
                _actualSequence->stop();
            }
        }
        
        // On set l'animation de saut si le personnage descend ou monte
        if(_Velocity.y > 0.1f || _Velocity.y < -0.1f) {
            if(_actualSequence != &_sequences[GIRANATH_RIGHT_KICK_SEQUENCE]) {
                _actualSequence = &_sequences[GIRANATH_JUMP_SEQUENCE];
                _actualSequence->setFrameIndex(2);
                _onFloor = false;
            }
        }
        else {
            _Velocity.y = 0;
            _onFloor = true;
        }
        
        // On boucle les animations
        if(_actualSequence->finished()) {
            
            // Si on est pas en train de faire un saut
            if(_actualSequence != &_sequences[GIRANATH_JUMP_SEQUENCE]) {
                // On ne répète pas la séquence de coups de poings
                if(_actualSequence == &_sequences[GIRANATH_IDLE_SEQUENCE] ||
                   _actualSequence == &_sequences[GIRANATH_WALKING_SEQUENCE]) {
                    _actualSequence->restart();
                }
                // Si le joueur donnait un coup, il revient à l'animation d'attente
                else {
                    _actualSequence = &_sequences[GIRANATH_IDLE_SEQUENCE];
                }
            }
            // Sinon on saute
            else {
                // Le saut est terminé on revient en idle
                if(_Position.y >= 400) {
                    _actualSequence = &_sequences[GIRANATH_IDLE_SEQUENCE];
                    _onFloor = true;
                }
            }
        }
        
        // Si le joueur n'a pas bougé, il devient en attente
        if(_Velocity == sf::Vector2f(0,0)) {
            // Par défaut, le joueur revient en idle
            if((_actualSequence == &_sequences[GIRANATH_WALKING_SEQUENCE] || _actualSequence == &_sequences[GIRANATH_JUMP_SEQUENCE]) &&
               !_actualSequence->finished()) {
                
                _actualSequence = &_sequences[GIRANATH_IDLE_SEQUENCE];
                _actualSequence->play();
                _onFloor = true;
            }
        }
        
        // On met à jour les attaques
        
        if(_actualSequence != &_sequences[GIRANATH_RIGHT_KICK_SEQUENCE] && _kickBox != 0) {
            sObjectManager->getWorld().removeBody(_kickBox);
            _kickBox = 0;
        }
        
        if(_actualSequence != &_sequences[GIRANATH_LEFT_PUNCH_SEQUENCE] &&
           _actualSequence != &_sequences[GIRANATH_RIGHT_PUNCH_SEQUENCE] &&
           _punchBox != 0) {
            sObjectManager->getWorld().removeBody(_punchBox);
            _punchBox = 0;
        }
        
        if(_kickBox != 0) {
            if(_direction == DIRECTION_RIGHT) {
                _kickBox->setPosition(sf::Vector2f(_Position.x - 25 + _Sprite.getGlobalBounds().width - 80,
                                                   _Sprite.getGlobalBounds().top + 170));
            }
            else {
                _kickBox->setPosition(sf::Vector2f(_Position.x - 25 - _Sprite.getGlobalBounds().width + 80,
                                                   _Sprite.getGlobalBounds().top + 170));
            }
        }
        
        if(_punchBox != 0) {
            if(_direction == DIRECTION_RIGHT)
                _punchBox->setPosition(sf::Vector2f(_Position.x - 25 + _Sprite.getGlobalBounds().width - 40,
                                                    _Sprite.getGlobalBounds().top + 60));
            else {
                _punchBox->setPosition(sf::Vector2f(_Position.x + 10 - _Sprite.getGlobalBounds().width + 40,
                                                    _Sprite.getGlobalBounds().top + 60));
            }
        }
        
        // On met à jour le Sprite
        if(_direction == DIRECTION_LEFT) {
            _Sprite.setScale(-1, 1);
        }
        else
            _Sprite.setScale(1, 1);
        
        _Sprite.setTextureRect(sf::IntRect(_actualSequence->getFrameRect(_textureHandler->getWidth(), _textureHandler->getHeight())));
        _Sprite.setOrigin((sf::Vector2f)_actualSequence->getActualOrigin(_textureHandler->getWidth(), _textureHandler->getHeight()));
    }
    
    /**
     * Appelé juste avant la destruction
     */
    void PlayerGiranath::onKill() {
        
    }
    
    /**
     * Définit une attaque de base
     */
    void PlayerGiranath::attackA() {
        if(_punchBox != 0) {
            sObjectManager->getWorld().removeBody(_punchBox);
            _punchBox = 0;
        }
        
        
        if(_actualSequence != &_sequences[GIRANATH_RIGHT_KICK_SEQUENCE]) {
            _actualSequence = &_sequences[GIRANATH_RIGHT_KICK_SEQUENCE];
            _sequences[GIRANATH_RIGHT_KICK_SEQUENCE].restart();
            
            _kickBox = sObjectManager->getWorld().createBoxBody(_Position.x - 25 + _Sprite.getGlobalBounds().width - 100,
                                                                _Sprite.getGlobalBounds().top + 170,
                                                                40, 80, false, false);
            
            _kickBox->possessor = this;
            _kickBox->collisionMask = RIGHT_KICK;
        }
    }
    
    /**
     * Définit une seconde attaque de base
     */
    void PlayerGiranath::attackB() {
        if(_kickBox != 0) {
            sObjectManager->getWorld().removeBody(_kickBox);
            _kickBox = 0;
        }
    
        if(_actualSequence != &_sequences[GIRANATH_LEFT_PUNCH_SEQUENCE] && _actualSequence != &_sequences[GIRANATH_RIGHT_PUNCH_SEQUENCE]) {
            _actualSequence = &_sequences[GIRANATH_LEFT_PUNCH_SEQUENCE];
            _sequences[GIRANATH_LEFT_PUNCH_SEQUENCE].restart();
            
            _punchBox = sObjectManager->getWorld().createBoxBody(_Position.x - 25 + _Sprite.getGlobalBounds().width - 50,
                                                                 _Sprite.getGlobalBounds().top + 60,
                                                                 20, 40, false, false);
            _punchBox->possessor = this;
            _punchBox->collisionMask = LEFT_PUNCH;
        }
        // Sinon si on donnait déjà un coup de poing, on passe au coup de droit
        else if(_actualSequence != &_sequences[GIRANATH_RIGHT_PUNCH_SEQUENCE]){
            _actualSequence = &_sequences[GIRANATH_RIGHT_PUNCH_SEQUENCE];
            _sequences[GIRANATH_RIGHT_PUNCH_SEQUENCE].restart();
            
            if(_punchBox != 0) {
                sObjectManager->getWorld().removeBody(_punchBox);
                _punchBox = 0;
                
                _punchBox = sObjectManager->getWorld().createBoxBody(_Position.x - 25 + _Sprite.getGlobalBounds().width - 50,
                                                                     _Sprite.getGlobalBounds().top + 60,
                                                                     20, 40, false, false);
                
                _punchBox->possessor = this;
                _punchBox->collisionMask = RIGHT_PUNCH;
            }
        }
    }
    
    void PlayerGiranath::jump() {
        // On fait faire un saut et on change la séquence d'animation
        if(_Velocity.y >= 0 && _boundingBox->getPosition().y + _boundingBox->getHeight() >= 600) {
            _boundingBox->setVelocity(sf::Vector2f(_boundingBox->getVelocity().x, _JumpSpring));
            _actualSequence = &_sequences[GIRANATH_JUMP_SEQUENCE];
            _sequences[GIRANATH_JUMP_SEQUENCE].restart();
            _onFloor = false;
        }
    }
    
    void PlayerGiranath::moveLeft() {
        // On assigne la séquence de marche comme celle à utiliser
        if(_actualSequence != &_sequences[GIRANATH_JUMP_SEQUENCE]) {
            _actualSequence = &_sequences[GIRANATH_WALKING_SEQUENCE];
            _actualSequence->play();
        }
        sideMove(-1);
    }
    
    void PlayerGiranath::moveRight() {
        // Même chose que moveLeft sauf que le déplacement se fait vers la droite
        if(_actualSequence != &_sequences[GIRANATH_JUMP_SEQUENCE]) {
            _actualSequence = &_sequences[GIRANATH_WALKING_SEQUENCE];
            _actualSequence->play();
        }
        sideMove(1);
    }
    
    void PlayerGiranath::onCollision(Collision const& collision) {
        if(collision.getMyHitbox() == _boundingBox->getBoundingBox() && collision.getObject()->getType() == OBJECT_ACTOR) {
            Actor* actor = (Actor*)(collision.getObject());
            
            if(actor->getActorType() == ACTOR_PLAYER) {
                Player* player = (Player*)actor;
                
                if(player != this) {

                    if(collision.informations >= LEFT_PUNCH) {
                        this->hit(5);
                        
                        // Si le cote gauche du rectangle de contact est à droite de mon coté gauche alors l'impact est à droite
                        if(_direction == DIRECTION_RIGHT) {
                            _boundingBox->setVelocity(sf::Vector2f(-1, -0.10));
                            _onFloor = false;
                        }
                        else {
                            _boundingBox->setVelocity(sf::Vector2f(1, -0.10));
                            _onFloor = false;
                        }
                    }
                }
            }
        }
    }
}