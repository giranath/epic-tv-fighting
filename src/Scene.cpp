/*
 *  FICHIER: Scene.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-29
 *
 */

#include "Scene.h"

namespace beat {
    
    Scene::Scene() {
        _musicPath = "";
        _floorHeight = 600;
    }
    
    Scene::Scene(Scene const& copy) {
        _musicPath = copy._musicPath;
        _ambiantMusic.openFromFile(_musicPath);
        _backPath = copy._backPath;
        //_middlePath = copy._middlePath;
        _width = copy._width;
        _floorHeight = copy._floorHeight;
    }
    
    Scene::~Scene() {
        _ambiantMusic.stop();
    }
    
    Scene& Scene::operator=(Scene const& other) {
        _musicPath = other._musicPath;
        
        _ambiantMusic.openFromFile(_musicPath);
        _backPath = other._backPath;
        //_middlePath = other._middlePath;
        
        _width = other._width;
        _floorHeight = other._floorHeight;
        
        return *this;
    }
    
    bool Scene::loadFromFile(const std::string &filepath) {
        std::ifstream istream;
        
        istream.open(filepath.c_str());
        
        if(!istream.is_open())
            return false;
        
        while(istream.good()) {
            std::string token;
            
            istream >> token;
            
            for(int i = 0; i < token.size(); i++) {
                token[i] = tolower(token[i]);
            }
            
            if(token == "ambiant-music:") {
                istream >> token;
                
                if(istream.fail())
                    return false;
                
                _musicPath = resourcePath() + "sounds/music/" + token;
                _ambiantMusic.openFromFile(_musicPath);
            }
            else if(token == "background:") {
                istream >> token;
                
                if(istream.fail()) {
                    return false;
                }
                
                _backPath = "graphics/scenes/" + token;
            }
            else if(token == "width:") {
                istream >> _width;
                
                if(istream.fail())
                    return false;
            }
            else if(token == "floor:") {
                istream >> _floorHeight;
                
                if(istream.fail())
                    return false;
            }
            
        }
        
        return true;
    }
    
    sf::Music& Scene::getAmbiantMusic() {
        return _ambiantMusic;
    }
    
    std::string Scene::getBackgroundTexture() {
        return _backPath;
    }
    
    void Scene::setWidth(unsigned int w) {
        _width = w;
    }
    
    unsigned int Scene::getWidth() const {
        return _width;
    }
    
    unsigned int Scene::getFloorHeight() const {
        return _floorHeight;
    }
}