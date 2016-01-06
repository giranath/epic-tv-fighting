/*
 *  FICHIER: BoxBody.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *
 */

#include "BoxBody.h"

namespace beat {
    BoxBody::BoxBody(sf::Vector2f const& position, float width, float height, bool dynamic, bool affected) : PhysicBody(position, dynamic, affected) {
        _width = width;
        _height = height;
        
        _type = BODY_BOX;
        activate();
    }
    
    float BoxBody::getWidth() const {
        return _width;
    }
    
    float BoxBody::getHeight() const {
        return _height;
    }
    
    sf::FloatRect BoxBody::getBoundingBox() const {
        return sf::FloatRect(_position.x, _position.y, _width, _height);
    }
    
    void BoxBody::setWidth(float w) {
        _width = w;
    }
    
    void BoxBody::setHeight(float h) {
        _height = h;
    }
    
    void BoxBody::setDimensions(float w, float h) {
        setWidth(w);
        setHeight(h);
    }
}