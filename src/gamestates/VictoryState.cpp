//
//  VictoryState.cpp
//  TP3
//
//  Created by Nathan Giraldeau on 2013-12-17.
//  Copyright (c) 2013 Nathan Giraldeau. All rights reserved.
//

#include "VictoryState.h"

namespace beat {
    VictoryState::VictoryState(Game& game, Player* players[2], int victorious, Scene &scene) : GameState(game), _scene(scene) {
        for(int i = 0; i < 2; i++) {
            _players[i] = players[i];
        }
        _victoriousIndex = victorious;

		_victoryFont.loadFromFile(resourcePath() + "graphics/fonts/RioGrande.ttf");
		_victoryText.setFont(_victoryFont);
		_victoryText.setCharacterSize(60);
		if(victorious < 3)
			_victoryText.setString(players[victorious]->getName() + " Wins");
		else
			_victoryText.setString("DRAW");
        
        switch(_victoriousIndex) {
            case 0:
                _sequences[0] = _players[0]->getAnimationSequence(12);
                _sequences[1] = _players[1]->getAnimationSequence(11);
                break;
            case 1:
                _sequences[0] = _players[0]->getAnimationSequence(11);
                _sequences[1] = _players[1]->getAnimationSequence(12);
                break;
            default:
                _sequences[0] = _players[0]->getAnimationSequence(11);
                _sequences[1] = _players[1]->getAnimationSequence(11);
                break;
        }
        
        for(int i = 0; i < 2; i++) {
            _sequences[i].play();
        }
    }
    
    /**
     * Appelée à l'initialisation
     */
    void VictoryState::onStart() {
        if(_victoriousIndex != 3) {
             _sayWins = true;
            _wins.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/wins.wav"));
            _winner.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/" + _players[_victoriousIndex]->getName() + ".wav"));
        }
        
        _sayWins = true;
        _sayName = true;
    }
    
    /**
     * Appelée à chaque frame
     */
    void VictoryState::onUpdate(unsigned int delta) {
        for(int i = 0; i < 2; i++) {
            _sequences[i].update(delta);
            if(i != _victoriousIndex && _sequences[i].finished()) {
                _sequences[i].restart();
            }
        }
        
        if(_sayName) {
            _winner.play();
            _sayName = false;
        }
        
        if(_winner.getStatus() != sf::Sound::Playing && _sayWins) {
            _wins.play();
            _sayWins = false;
        }
    }
    
    /**
     * Appelée à l'affichage de l'état
     */
    void VictoryState::onDraw(sf::RenderTarget &target) {
    
        sf::Sprite sprite;
        sprite.setTexture(_game.textureManager.getTexture(_scene.getBackgroundTexture()));
        
         target.setView(sf::View(sf::FloatRect(0, 0, _game.textureManager.getTexture(_scene.getBackgroundTexture()).getSize().x, _game.textureManager.getTexture(_scene.getBackgroundTexture()).getSize().y)));
        target.draw(sprite);
        
        target.setView(sf::View(sf::FloatRect(0, 0, _scene.getWidth(), _scene.getFloorHeight())));
        for(int i = 0; i < 2; i++) {
            sf::Sprite p;
            p.setTexture(*_players[i]->getTextureHandler());
            p.setOrigin(_sequences[i].getActualOrigin().x * _players[i]->getTextureHandler()->getWidth(), 0);
            
            sf::FloatRect rect = _sequences[i].getFrameRect();
            
            rect.left *= _players[i]->getTextureHandler()->getWidth();
            rect.top *= _players[i]->getTextureHandler()->getHeight();
            rect.width *= _players[i]->getTextureHandler()->getWidth();
            rect.height *= _players[i]->getTextureHandler()->getHeight();
            
            p.setTextureRect((sf::IntRect)rect);

            p.setPosition(_players[i]->getPosition().x, _scene.getFloorHeight() - rect.height);
            
            target.draw(p);
        }
        
        target.setView(target.getDefaultView());
        _victoryText.setPosition(400-(_victoryText.getLocalBounds().width/2), 100);
		target.draw(_victoryText);
    }
    
    /**
     * Appelé à la reception d'évènements
     */
    void VictoryState::onEvent(sf::Event const& event) {
        if(event.type == sf::Event::Closed) {
            _game.kill();
        }
        
        if(event.type == sf::Event::KeyPressed) {
            if(event.key.code == sf::Keyboard::Return) {
                _game.stateManager.popState(2);
            }
            if(event.key.code == sf::Keyboard::Escape) {
                _game.stateManager.popState(3);
            }
        }
    }
    
    /**
     * Appelée à la fermeture
     */
    void VictoryState::onClose() {
        
    }
}