/*
 *  FICHIER: SoundBufferManager.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-17
 *
 */

#include "SoundBufferManager.h"
#include <assert.h>

namespace beat {
    SoundBufferManager* SoundBufferManager::gSoundManager = 0;
    
    SoundBufferManager::SoundBufferManager() {
        
    }
    
    SoundBufferManager::~SoundBufferManager() {
        for(std::map<std::string, sf::SoundBuffer*>::iterator it = _Buffers.begin(); it != _Buffers.end(); ++it)
            delete it->second;
        
        _Buffers.clear();
    }
    
    bool SoundBufferManager::addBuffer(std::string const& filepath) {
        assert(!exists(getRealResPath(filepath)));
        
        sf::SoundBuffer* temp = new sf::SoundBuffer;
        
        if(!temp->loadFromFile(getRealResPath(filepath))) {
            return false;
        }
        
        _Buffers[getRealResPath(filepath)] = temp;
        
        return true;
    }
    
    sf::SoundBuffer& SoundBufferManager::getBuffer(std::string const& filepath) {
        
        if(!exists(filepath)) {
            addBuffer(filepath);
        }

        return *_Buffers.at(getRealResPath(filepath));
    }
    
    bool SoundBufferManager::exists(std::string const& filepath) const {
        return _Buffers.find(getRealResPath(filepath)) != _Buffers.end();
    }
    
    std::string SoundBufferManager::getRealResPath(std::string const& path) const {
        return resourcePath() + path;
    }
}