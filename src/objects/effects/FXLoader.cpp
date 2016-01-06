/*
 *  FICHIER: FXLoader.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *
 */

#include "FXLoader.h"
#include <assert.h>

namespace beat {
    TextureManager* FXLoader::_textureManager = 0;
    SoundBufferManager* FXLoader::_sndManager = 0;
    
    CustomFX* FXLoader::createFromFile(std::string const& filepath) {
        CustomFX* fx = new CustomFX;
        
        std::ifstream file;
        
        file.open(filepath.c_str());
        
        if(!file.is_open()) {
            delete fx;
            return 0;
        }
        
        std::string token;
        while(file.good()) {
            file >> token;
            
            for(int i = 0; i < token.size(); i++) {
                token[i] = tolower(token[i]);
            }
            
            if(token == "duration:") {
                DurationMs duration;
                file >> duration;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                fx->_AnimationSequence.setDuration(duration);
            }
            else if(token == "lifetime:") {
                file >> token;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                for(int i = 0; i < token.size(); i++) {
                    token[i] = tolower(token[i]);
                }
                
                if(token == "immortal") {
                    fx->_Lifetime = 0;
                }
                else {
                    fx->_Lifetime = atoi(token.c_str());
                }
            }
            else if(token == "frames{") {
                do {
                    file >> token;
                    
                    if(file.fail()) {
                        delete fx;
                        return 0;
                    }
                    
                    if(token == "frame:") {
                        sf::FloatRect rect;
                        
                        file >> rect.left >> rect.top >> rect.width >> rect.height;
                        
                        fx->_AnimationSequence.appendFrame(rect, FrameOrigin(0,0));
                    }
                    
                }while(token != "}");
            }
            else if(token == "loop:") {
                std::string temp;
                file >> temp;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                for(int i = 0; i < temp.size(); i++)
                    temp[i] = tolower(temp[i]);
                
                if(temp == "yes" || temp == "1" || temp == "true")
                    fx->_Looped = true;
                else
                    fx->_Looped = false;
            }
            else if(token == "spritesheet:") {
                file >> token;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                fx->setTextureHandler(_textureManager->getHandler(token));
            }
            else if(token == "start_sound:") {
                file >> token;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                if(!_sndManager->exists(token))
                    _sndManager->addBuffer(token);
                
                fx->_startSnd.setBuffer(_sndManager->getBuffer(token));
            }
            else if(token == "update_sound:") {
                file >> token;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                if(!_sndManager->exists(token))
                    _sndManager->addBuffer(token);
                
                fx->_updateSnd.setBuffer(_sndManager->getBuffer(token));
            }
            else if(token == "end_sound:") {
                file >> token;
                
                if(file.fail()) {
                    delete fx;
                    return 0;
                }
                
                if(!_sndManager->exists(token))
                    _sndManager->addBuffer(token);
                
                fx->_endSnd.setBuffer(_sndManager->getBuffer(token));
            }
        }
        
        return fx;
    }
    
    void FXLoader::setSoundManager(SoundBufferManager* sndManager) {
        assert(sndManager != 0);
        
        _sndManager = sndManager;
    }
    
    void FXLoader::setTextureManager(TextureManager* textureManager) {
        assert(textureManager != 0);
        
        _textureManager = textureManager;
    }
}