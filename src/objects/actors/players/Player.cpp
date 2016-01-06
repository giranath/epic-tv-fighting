/*
 *  FICHIER: Player.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *
 */

#include "Player.h"

namespace beat {
    /**
     * Constructeur
     */
    Player::Player(unsigned int playerCount) : Actor(ACTOR_PLAYER) {
        _playerCount = playerCount;
		_boundingBox = 0;
        _actualSequence = 0;
    }
    
    /**
     * Destructeur
     */
    Player::~Player() {
        
    }
    
    /**
     * Appelée chaque frame
     */
    void Player::onUpdate(int milliSec) {
    }
    
    /**
     * Appelé juste avant la destruction
     */
    void Player::onKill() {
        
    }
    
    /**
     * Appelé la première itération
     */
    void Player::onCreation() {
    
    }
    
    /**
     * Retourne le nombre du joueur
     * NOTE: 1 = joueur 1 , 2 = joueur 2
     */
    unsigned int Player::getPlayerCount() const {
        return _playerCount;
    }
    
    std::string Player::getName() const {
        return _name;
    }
    
    void Player::setName(std::string const& name) {
        _name = name;
    }
    
    AnimationSequence& Player::getAnimationSequence(unsigned int index) {
        assert(index < _sequences.getDim());
        return _sequences[index];
    }
    
    std::string Player::getTextureName() const {
        return _textureName;
    }
}