/*
 *  FICHIER: AnimationSequence.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *
 */

#include "AnimationSequence.h"

#include <assert.h>

namespace beat {
    AnimationSequence::AnimationSequence() {
        _frameIndex = 0;
        
        _playing = false;
        _elapsedTime = 0;
        _durationMS = 0;
    }
    
    AnimationSequence::AnimationSequence(vecteur<FrameRect> const& frames, DurationMs duration) {
        
        _durationMS = duration;
        
        _elapsedTime = 0;
        _frameIndex = 0;
        
        _playing = false;
    }
    
    AnimationSequence::AnimationSequence(AnimationSequence const& other) {
        _rects = other._rects;
        
        _durationMS = other._durationMS;
        _elapsedTime = 0;
        _frameIndex = 0;
        
        _playing = false;
    }
	
	void AnimationSequence::appendFrame(FrameRect const& rect, FrameOrigin const& origin) {
		Frame temp(rect, origin);
		_rects.push_back(temp);
	}

    void AnimationSequence::setFrameOriginAt(unsigned int index, FrameOrigin const& origin) {
        _rects[index]._o = origin;
    }
    
    FrameRect AnimationSequence::getFrameRect(unsigned int valX, unsigned int valY) const {
        assert(_rects.getDim() > 0);
        
        sf::FloatRect rect = _rects[_frameIndex]._r;
        
        rect.left *= valX;
        rect.width *= valX;
        rect.top *= valY;
        rect.height *= valY;
        
        return rect;
    }
    
    void AnimationSequence::update(unsigned int elapsedMs) {
        
        // Si l'animation est en cours...
        if(_playing) {
            
            // On ajoute le temps écoulé durant la frame au compteur _elapsedTime
            _elapsedTime = (_elapsedTime + elapsedMs);
            
            // On recupère le ratio entre temps écoulé et durée d'une animation
            float ratio = (float)_elapsedTime / (float)_durationMS;
            
            // Si la séquence n'est pas vide, on place le curseur de l'animation à une position selon le ratio
            if(_rects.getDim() != 0)
                _frameIndex = ratio * (_rects.getDim() - 1);
        }
        
        // Ici on s'assure que l'index ne dépasse pas la taille d'une séquence et si c'est le cas, la séquence à terminée
        if(_frameIndex > _rects.getDim() - 1) {
            _frameIndex = (unsigned int)_rects.getDim() - 1;
            _playing = false;
        }
    }
    
    DurationMs AnimationSequence::getDuration() const {
        return _durationMS;
    }
    
    void AnimationSequence::setDuration(DurationMs duration) {
        _durationMS = duration;
    }
    
    void AnimationSequence::play() {
        _playing = true;
    }
    
    void AnimationSequence::restart() {
        _playing = true;
        _frameIndex = 0;
        _elapsedTime = 0;
    }
    
    void AnimationSequence::stop() {
        _playing = false;
    }
    
    AnimationSequence const& AnimationSequence::operator=(AnimationSequence const& other) {
        _rects = other._rects;
        
        _durationMS = other._durationMS;
        _elapsedTime = 0;
        _frameIndex = 0;
        _playing = false;
        
        return *this;
    }
    
    bool AnimationSequence::isPlaying() const {
        return _playing;
    }
    
    bool AnimationSequence::finished() const {
        // Si l'index se retrouve à la fin de la séquence, il a fini
        return _frameIndex == _rects.getDim() - 1;
    }
    
    bool AnimationSequence::loadFromFile(std::string const& filepath) {
        std::ifstream stream;
        
        stream.open(filepath.c_str());
        
        if(stream.is_open() == false)
            return false;
        
        // On lit tout le fichier
        while(stream.good()) {
            std::string token;
            
            stream >> token;
            
            if(stream.fail()) {
                return false;
            }
            
            for(int i = 0; i < token.size(); i++) {
                token[i] = tolower(token[i]);
            }
            
            if(token == "duration:") {
                stream >> _durationMS;
            }
            else if(token == "frames{") {
                while(token != "}") {
                    stream >> token;
                    
                    if(token == "frame:") {
                        FrameRect rect;
                        FrameOrigin origin;
                        
                        stream >> rect.left >> rect.top >> rect.width >> rect.height;
                        stream >> origin.x >> origin.y;
                        Frame temp(rect, origin);
                        _rects.push_back(temp);
						
                    }
                    else if (token == "hitbox{") {
						_rects[_rects.getDim()-1]._h.resize(1);
						stream >> token;
						while(token != "}") {
							if(token == "body:") {
								sf::FloatRect frect;
								stream >> frect.left >> frect.top >> frect.width >> frect.height;
								_rects[_rects.getDim()-1]._h[0] = frect;
							} else if(token == "hitbox:") {
                                Hitbox box;
								stream >> box.box.left >> box.box.top >> box.box.width >> box.box.height >> box.informations;
								_rects[_rects.getDim()-1]._h.push_back(box);
							}
							stream >> token;
						}
						token.clear();
					}
                }
            }
            // Si un autre token est lue, il y a erreur dans le format du fichier on retourne false
            else {
                return false;
            }
            
        }
        
        return true;
    }
    
    unsigned int AnimationSequence::getFrameIndex() const {
        return _frameIndex;
    }
    
    void AnimationSequence::setFrameIndex(unsigned int index) {
        _frameIndex = index;
    }
    
    FrameOrigin AnimationSequence::getActualOrigin(unsigned int valX, unsigned int valY) {
        assert(_rects.getDim() > 0);
        
        FrameOrigin origin = _rects[_frameIndex]._o;
        origin.x *= valX;
        origin.y *= valY;
        
        return origin;
    }
    
    unsigned int AnimationSequence::getNbHitbox() const {
        return _rects[_frameIndex]._h.getDim();
    }
    
    Hitbox AnimationSequence::getHitboxAt(unsigned int index) {
        return _rects[_frameIndex]._h[index];
    }
    
    Hitbox AnimationSequence::getHitboxWithID(unsigned int ID) {
        for(int i = 0; i < _rects[_frameIndex]._h.getDim(); i++) {
            if(_rects[_frameIndex]._h[i].informations == ID) {
                return _rects[_frameIndex]._h[i];
            }
        }
        
        return Hitbox();
    }
}