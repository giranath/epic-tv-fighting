/*
 *  FICHIER: PhysicBody.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *
 */

#include "PhysicBody.h"
#include <iostream>

namespace beat {
    /**
     * Constructeur
     */
    PhysicBody::PhysicBody(sf::Vector2f const& position, bool dynamic, bool affectedByGravity) {
        _position = position;
        _useGravity = affectedByGravity;
        _dynamic = dynamic;
        _type = BODY_UNDEFINED;
        
        possessor = 0;
        collisionMask = 0;
    }
    
    /**
     * Informe si le corps est affecté par la gravité
     */
    bool PhysicBody::isAffectedByGravity() const {
        return _useGravity;
    }
    
    /**
     * Permet de modifier si l'objet est affecté par la gravité
     */
    void PhysicBody::setGravityAffected(bool affected) {
        _useGravity = affected;
    }
    
    /**
     * Retourne la position du corps
     */
    sf::Vector2f const& PhysicBody::getPosition() const {
        return _position;
    }
    
    /**
     * Assigne une position au corps
     */
    void PhysicBody::setPosition(sf::Vector2f const& position) {
        _position = position;
    }
    
    /**
     * Retourne une vélocité
     */
    sf::Vector2f const& PhysicBody::getVelocity() const {
        return _velocity;
    }
    
    /**
     * Assigne une vélocité
     */
    void PhysicBody::setVelocity(sf::Vector2f const& velocity) {
        _velocity = velocity;
    }
    
    bool PhysicBody::isDynamic() const {
        return _dynamic;
    }
    
    void PhysicBody::setDynamic(bool dynamic) {
        _dynamic = dynamic;
    }
    
    PhysicBody::BodyType PhysicBody::getType() const {
        return _type;
    }
    
    void PhysicBody::activate() {
        _activated = true;
    }
    
    void PhysicBody::desactivate() {
        _activated = false;
    }
    
    bool PhysicBody::isActivated() {
        return _activated;
    }
}