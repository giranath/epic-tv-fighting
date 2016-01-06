/**
 * FICHIER: Object.cpp
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Classe de base pour tous les objets dynamique du jeu
 */

#include "Object.h"
#include <assert.h>

#include <iostream>

namespace beat {
    
    ObjectManager* Object::sObjectManager = 0;
    
    // On assigne automatiquement un identifiant qui sera assurément unique à partir de 1000
    static unsigned long autoID = 1000;
    
    Object::Object(int type, bool visible, bool alive) {
        _UID = ++autoID;
        
        _Alive = alive;
        _Visible = visible;
        _Type = type;
        _textureHandler = 0;
        
        _Rotation = 0;
        _ScaleX = 1;
        _ScaleY = 1;
    };
    
    Object::Object(Object const& other) {
        _UID = ++autoID;
        
        _Alive = other._Alive;
        _Visible = other._Visible;
        _Type = other._Type;
        
        _Sprite = other._Sprite;
        _textureHandler = other._textureHandler;
        
        if(_textureHandler != 0)
            _textureHandler->addRef();
        
        _Rotation = other._Rotation;
        _ScaleX = other._ScaleX;
        _ScaleY = other._ScaleY;
        _Position = other._Position;
    }
    
    Object::~Object() {
        if(_textureHandler != 0)
            _textureHandler->release();
    }
    
    void Object::onCollision(Collision const& collision) {
        /**
         * Ne fait rien par défaut
         */
        
        std::cout << "ON COLLISION!" << std::endl;
    }
    
    void Object::setAlive(bool a) {
		_Alive = a;
	}
    
	void Object::setVisible(bool v) {
		_Visible = v;
	}
    
	void Object::setUID(unsigned long id) {
		assert(id <= 1000);
		_UID = id;
	}
    
    
    void Object::setPosition(float x, float y) {
		_Position.x = x;
		_Position.y = y;
	}
    
	void Object::setVelocity(float x, float y) {
		_Velocity.x = x;
		_Velocity.y = y;
	}
    
    bool Object::isAlive() const {
        return _Alive;
    }
    
    bool Object::isVisible() const {
        return _Visible;
    }
    
    unsigned long Object::getUID() const {
        return _UID;
    }
    
    int Object::getType() const {
        return _Type;
    }
    
    sf::Vector2f Object::getPosition() const {
		return _Position;
	}
    
	sf::Vector2f Object::getVelocity() const {
		return _Velocity;
	}

	void Object::setTexture(sf::Texture& texture, sf::IntRect const& rect) {
		_Sprite.setTexture(texture);
		_Sprite.setTextureRect(rect);
	}
    
    void Object::setTextureHandler(TextureManager::TextureHandler& handler) {
        _textureHandler = &handler;
        
        _Sprite.setTexture(*_textureHandler);
    }
    
    void Object::setScale(float x, float y) {
        _ScaleX = x;
        _ScaleY = y;
        
        _Sprite.setScale(_ScaleX, _ScaleY);
    }
    
    void Object::setRotation(float rot) {
        _Rotation = rot;
        
        _Sprite.setRotation(rot);
    }
    
    float Object::getScaleX() const {
        return _ScaleX;
    }
    
    float Object::getScaleY() const {
        return _ScaleY;
    }
    
    float Object::getRotation() const {
        return _Rotation;
    }
    
    void Object::rotate(float theta) {
        setRotation(_Rotation + theta);
    }
    
    void Object::scale(float x, float y) {
        setScale(_ScaleX + x, _ScaleY + y);
    }
    
    void Object::setOrigin(float x, float y) {
        _Sprite.setOrigin(x, y);
    }
    
    TextureManager::TextureHandler* Object::getTextureHandler() const {
        return _textureHandler;
    }
}