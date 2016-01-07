/**
 * FICHIER: TextureManager.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Objet permmetant de gérer les textures.
 */

#include "TextureManager.h"
#include <assert.h>

namespace beat {
    TextureManager::TextureManager() {
    }
    
    TextureManager::~TextureManager() {
        for(std::map<std::string, TextureHandler>::iterator it = _textures.begin(); it != _textures.end(); ++it)
            delete it->second.texture;
        
        _textures.clear();
    }
    
    bool TextureManager::addTexture(std::string const& filepath) {
        
        if(exists(getRealResPath(filepath)))
            return false;
        
        sf::Texture* temp = new sf::Texture;
        
        if(!temp->loadFromFile(getRealResPath(filepath))) {
            
            delete temp;
            
            createPlaceHolderFor(filepath);
            
            return false;
        }
        
        _textures[getRealResPath(filepath)] = temp;
        
        return true;
    }
    
    bool TextureManager::removeTexture(std::string const& filepath, bool forced) {
        if(!exists(filepath))
            return false;
        
        TextureHandler &handler = _textures[getRealResPath(filepath)];
        
        if(handler.refCount != 0)
            handler.refCount--;
        
        if(handler.refCount == 0 || forced)
            delete handler.texture;
        
        return true;
    }
    
    sf::Texture& TextureManager::getTexture(std::string const& filepath) {
        if(!exists(filepath)) {
            addTexture(filepath);
        }
        
        TextureHandler &handler = _textures[getRealResPath(filepath)];
        handler.refCount++;
        
        return *handler.texture;
    }
    
    TextureManager::TextureHandler& TextureManager::getHandler(std::string const& filepath) {
        if(!exists(filepath)) {
            addTexture(filepath);
        }
        
        TextureHandler &handler = _textures[getRealResPath(filepath)];
        handler.refCount++;
        
        return handler;
    }
    
    bool TextureManager::exists(std::string const& filepath) const {
        return _textures.find(getRealResPath(filepath)) != _textures.end();
    }
    
    std::string TextureManager::getRealResPath(std::string const& path) const {
        return resourcePath() + path;
    }
    
    void TextureManager::createPlaceHolderFor(std::string const& path) {
        TextureHandler placeholder(new sf::Texture());
        placeholder.refCount = 0;
        
        sf::Font font;
        font.loadFromFile(resourcePath() + "Courier New.ttf");
        
        sf::Text text;
        text.setFont(font);
        text.setColor(sf::Color::Cyan);
        text.setCharacterSize(18);
        text.setString(path);
        text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
        
        text.rotate(45);
        text.scale(1, -1);
        
        
        sf::RenderTexture texture;
        texture.create(text.getGlobalBounds().width + 30, text.getGlobalBounds().height + 30);
        
        text.setPosition(texture.getSize().x/2, texture.getSize().y/2);
        
        texture.clear(sf::Color::Magenta);
        
        texture.draw(text);
        
        *placeholder.texture = texture.getTexture();
        
        _textures[getRealResPath(path)] = placeholder;
    }
    
    unsigned int TextureManager::getRefCountOfTexture(std::string const& filepath) const {
        if(exists(filepath))
            return _textures.at(getRealResPath(filepath)).refCount;
        else
            return 0;
    }
    
    void TextureManager::releaseTexture(std::string const& path, bool immediateErase) {
        if(exists(path)) {
            TextureHandler& handler = _textures[getRealResPath(path)];
            
            if(handler.refCount != 0)
                handler.refCount--;
            
            if(handler.refCount == 0 && immediateErase) {
                removeTexture(path);
            }
        }
    }
    
    void TextureManager::clearUnusedTexture() {
        std::map<std::string, TextureHandler>::iterator it = _textures.begin();
        
        while(it != _textures.end()) {
            TextureHandler &handler = it->second;
            std::map<std::string, TextureHandler>::iterator current = it++;
            
            if(handler.refCount == 0) {
                delete it->second.texture;
                
                _textures.erase(current);
            }
            
        }
    }
}
