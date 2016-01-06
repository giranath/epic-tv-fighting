/**
 * FICHIER: VersusState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 */

#include "VersusState.h"
#include "Game.h"

namespace beat {
    VersusState::VersusState(Game& game, Player& p1, Player& p2) : GameState(game), _p1(p1), _p2(p2) {
        this->_name1.setString(p1.getName());
        this->_name2.setString(p2.getName());
    }
    
    VersusState::~VersusState() {
        
    }
    
    void VersusState::onStart() {
        _font.loadFromFile(resourcePath() + "graphics/fonts/Moder DOS 437.ttf");
        _backHandler = &_game.textureManager.getHandler("graphics/backgrounds/versusScreenBack.png");
        _vsHandler = &_game.textureManager.getHandler("graphics/ui/VersusWord.png");
        
        _backSprite.setTexture(*_backHandler);
        _vsSprite.setTexture(*_vsHandler);
        _elapsedTime = 0;
        
        _seq1 = _p1.getAnimationSequence(0);
        _seq2 = _p2.getAnimationSequence(0);
        
        _name1.setFont(_font);
        _name2.setFont(_font);
        
        _p1NameSnd.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/" + _p1.getName() + ".wav"));
        _p2NameSnd.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/" + _p2.getName() + ".wav"));
        _versusSnd.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/vs.wav"));
        _p1NameSnd.setVolume(_game.config.volume);
        _p2NameSnd.setVolume(_game.config.volume);
        _versusSnd.setVolume(_game.config.volume);
        
        _f1 = _f2 = _f3 = false;
    }
    
    /**
     * Appelée lorsqu'on revient à cet état
     */
    void VersusState::onLoad() {
    
    }
    
    /**
     * Appelée à chaque frame
     */
    void VersusState::onUpdate(unsigned int delta) {
        _elapsedTime += delta;
        
        if(!_f1) {
            _p1NameSnd.play();
            _f1 = true;
        }
        else if(_f1 && _p1NameSnd.getStatus() == sf::Sound::Stopped && !_f2) {
            _versusSnd.play();
            _f2 = true;
        }
        else if(_f2 && _versusSnd.getStatus() == sf::Sound::Stopped && !_f3) {
            _p2NameSnd.play();
            _f3 = true;
        }
        
        if(_elapsedTime > VERSUS_STATE_DURATION && _f3) {
            _game.stateManager.popState();
        }
        
        _seq1.update(delta);
        _seq2.update(delta);
    }
    
    /**
     * Appelée à l'affichage de l'état
     */
    void VersusState::onDraw(sf::RenderTarget &target) {
        target.draw(_backSprite);
        
        sf::Sprite s1, s2;
        s1.setTexture(*_p1.getTextureHandler());
        s2.setTexture(*_p2.getTextureHandler());
        
        s1.setPosition(50, 100);
        s1.setScale(2, 2);
        _name1.setPosition(50, 50);
        
        s2.setPosition(750, 200);
        s2.setScale(-2, 2);
        _name2.setPosition(550, 150);
        
        FrameRect rect1, rect2;
        
        rect1 = _seq1.getFrameRect();
        rect2 = _seq2.getFrameRect();
        
        rect1.left *= (*_p1.getTextureHandler()).getWidth();
        rect1.top *= (*_p1.getTextureHandler()).getHeight();
        rect1.width *= (*_p1.getTextureHandler()).getWidth();
        rect1.height *= (*_p1.getTextureHandler()).getHeight();
        
        rect2.left *= (*_p2.getTextureHandler()).getWidth();
        rect2.top *= (*_p2.getTextureHandler()).getHeight();
        rect2.width *= (*_p2.getTextureHandler()).getWidth();
        rect2.height *= (*_p2.getTextureHandler()).getHeight();
        
        s1.setTextureRect(sf::IntRect(rect1));
        s2.setTextureRect(sf::IntRect(rect2));
        
        target.draw(s1);
        target.draw(s2);
        
        target.draw(_vsSprite);
    
        target.draw(_name1);
        target.draw(_name2);
    }
    
    /**
     * Appelé à la reception d'évènements
     */
    void VersusState::onEvent(sf::Event const& event) {
        if(event.type == sf::Event::Closed) {
            _game.kill();
        }
    }
    
    /**
     * Appelée lorsqu'on pousse un nouvel état dans la pile
     */
    void VersusState::onUnload() {
    
    }
    
    /**
     * Appelée à la fermeture
     */
    void VersusState::onClose() {
        _backHandler->release();
        _vsHandler->release();
    }
}