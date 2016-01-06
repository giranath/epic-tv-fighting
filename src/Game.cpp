/*
 *  FICHIER: Game.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-18
 *
 */

#include "Game.h"

namespace beat {
    Game::Game() {
        _playing = true;
		_ticks = 0;
        
        config.volume = 10;
        config.roundDuration = 2;
        
        // 0 = 1 de 2, 1 = 2 de 3 et 2 = 3 de 4
        config.combatMode = 0;
    }
    
    bool Game::isPlaying() const {
        return _playing;
    }
    
    void Game::kill() {
        _playing = false;
    }

	unsigned long Game::getTicks() const {
		return _ticks;
	}
	
    void Game::resetTicks() {
		_ticks = 0;
	}
    
	void Game::addTicks(unsigned long t) {
		_ticks += t;
	}
    
    bool Game::loadConfig(std::string const& filepath) {
        std::ifstream istream;
        
        istream.open(filepath.c_str());
        
        if(!istream.is_open()) {
            std::cerr << "[" << filepath << "] do not exists" << std::endl;
            return false;
        }
        
        while(istream.good()) {
            std::string token;
            
            istream >> token;
            
            for(int i = 0; i < token.size(); i++) {
                token[i] = tolower(token[i]);
            }
            
            if(token == "volume:") {
                float temp;
                istream >> temp;
                
                if(istream.fail()) {
                    std::cerr << "[" << filepath << "]" << " volume option needs a float value!" << std::endl;
                    return false;
                }
                
                config.volume = temp;
            }
            else if(token == "gravity:") {
                float x, y;
                istream >> x >> y;
                
                if(istream.fail()) {
                    std::cerr << "[" << filepath << "]" << "gravity needs two float values!" << std::endl;
                    return false;
                }
                
                config.gravity = sf::Vector2f(x, y);
            }
            else if(token == "strings:") {
                istream >> _localizationStr;
                
                if(!_localizationStrings.loadFromFile(resourcePath() + _localizationStr)) {
                    return false;
                }
            }
            else if(token == "language:") {
                istream >> config.language;
            }
        }
        
        return true;
    }
    
    bool Game::saveConfig(std::string const& filepath) {
        std::ofstream ostream;
        
        ostream.open(filepath.c_str());
        
        if(!ostream.is_open()) {
            std::cerr << "Can't save config in '" << filepath << "'" << std::endl;
            return false;
        }
        
        ostream << "volume: " << config.volume << std::endl;
        ostream << "gravity: " << config.gravity.x << " " << config.gravity.y << std::endl;
        ostream << "strings: " << _localizationStr << std::endl;
        ostream << "language: " << config.language;
        
        return true;
    }
    
    LocalizationString& Game::getLocalizationStrings() {
        return _localizationStrings;
    }
    
    std::string Game::getLanguage() {
        return config.language;
    }
    
    void Game::setLanguage(std::string const& name) {
        config.language = name;
    }
    
}