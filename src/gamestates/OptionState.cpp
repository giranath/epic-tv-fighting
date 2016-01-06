//
//  OptionState.cpp
//  TP3
//
//  Created by Nathan Giraldeau on 2013-12-06.
//  Copyright (c) 2013 Nathan Giraldeau. All rights reserved.
//

#include "OptionState.h"
#include <sstream>

namespace beat {
    /**
     * Constructeur
     */
    OptionState::OptionState(Game& game) : GameState(game) {
        
    }
    
    /**
     * Destructeur
     */
    OptionState::~OptionState() {
        
    }
    
    /**
     * Appelée à l'ouverture
     */
    void OptionState::onStart() {
        _game.textureManager.addTexture("graphics/ui/language_buttons.png");
        _button_english.setTexture(_game.textureManager.getTexture("graphics/ui/language_buttons.png"));
        _button_french.setTexture(_game.textureManager.getTexture("graphics/ui/language_buttons.png"));
        
        _button_french.setTextureRect(sf::IntRect(50, 0, 50, 50));
        _button_english.setTextureRect(sf::IntRect(50, 50, 50, 50));
        
        _button_french.setPosition(75, 100);
        _button_english.setPosition(75, 175);
        
        _font.loadFromFile(resourcePath() + "graphics/fonts/Moder DOS 437.ttf");
        _languageTitle.setFont(_font);
        _languageTitle.setString(_game.getLocalizationStrings().get("language_title", _game.getLanguage()));
        _languageTitle.setPosition(15, 50);
        _languageTitle.setColor(sf::Color::White);
        
        _actualLanguage.setFont(_font);
        _actualLanguage.setPosition(30, 250);
        _actualLanguage.setColor(sf::Color::White);
        
        _volumeTitle.setFont(_font);
        _volumeTitle.setString("Volume");
        _volumeTitle.setPosition(30, 325);
        
        _volumeSlider.setTexture(_game.textureManager.getTexture("graphics/ui/volumeSlider.png"));
        _volumeSlider.setOrigin(6, 6);
        
        // Il s'agit de la position minimale du curseur ([32, 390], 433)
        _volumeSlider.setPosition((_game.config.volume / 100) * 352 + 32, 433);
        
        _selectSound.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/select.wav"));
        _selectSound.setVolume(50);
        
        _hint.setFont(_font);
        _hint.setColor(sf::Color::White);
        _hint.setCharacterSize(18);
        
        _backSprite.setTexture(_game.textureManager.getTexture("graphics/backgrounds/option_background.png"));
        
        _dragVolumeSlider = false;
        
        _volumeValue.setFont(_font);
        _volumeValue.setPosition(340, 325);
        
        _backupConfig = _game.config;
        
        _apply = false;
        
        for(int i = 0; i < 3; i++) {
            _roundButton[i].setTexture(_game.textureManager.getTexture("graphics/ui/roundNumberButtons.png"));
            _roundButton[i].setTextureRect(sf::IntRect(0, i * 50, 100, 50));
            _roundButton[i].setPosition(440 + (i * 110), 110);
            
            _roundDuration[i].setTexture(_game.textureManager.getTexture("graphics/ui/roundDurationButtons.png"));
            _roundDuration[i].setTextureRect(sf::IntRect(0, i * 50, 100, 50));
            _roundDuration[i].setPosition(440 + (i * 110), 230);
        }
        
        _nbRoundText.setFont(_font);
        _nbRoundText.setString("Rounds");
        _nbRoundText.setPosition(440, 50);
        
        _roundDurationText.setFont(_font);
        _roundDurationText.setPosition(440, 180);
    }
    
    /**
     * Appelée à chaque frame
     */
    void OptionState::onUpdate(unsigned int delta) {
        _languageTitle.setString(_game.getLocalizationStrings().get("language_title", _game.getLanguage()));
        _actualLanguage.setString(_game.getLanguage());
        
        _roundDurationText.setString(_game.getLocalizationStrings().get("time_title", _game.getLanguage()));
        
        _hint.setString(_game.getLocalizationStrings().get("option_hint", _game.getLanguage()));
        _hint.setPosition(400 - _hint.getLocalBounds().width/2, 535);
        
        std::stringstream stream;
        stream << (int)_game.config.volume;
        
        _volumeValue.setString(stream.str());
        
        _selectSound.setVolume(_game.config.volume);
        
        for(int i = 0; i < 3; i++) {
            _roundButton[i].setPosition(440 + (i * 110), 110);
            _roundDuration[i].setPosition(440 + (i * 110), 230);
        }
        
        _roundDuration[_game.config.roundDuration].setTextureRect(sf::IntRect(100, _game.config.roundDuration * 50, 100, 50));
        _roundButton[_game.config.combatMode].setTextureRect(sf::IntRect(100, _game.config.combatMode * 50, 100, 50));
    }
    
    /**
     * Appelée à l'affichage de l'état
     */
    void OptionState::onDraw(sf::RenderTarget &target) {
        target.setView(sf::View(sf::FloatRect(0, 0, 768, 512)));
        target.draw(_backSprite);
        
        target.setView(target.getDefaultView());
        target.draw(_languageTitle);
        
        target.draw(_button_french);
        target.draw(_button_english);
        
        target.draw(_volumeTitle);
        target.draw(_volumeSlider);
        target.draw(_volumeValue);
        
        for(int i = 0; i < 3; i++) {
            target.draw(_roundButton[i]);
            target.draw(_roundDuration[i]);
        }
        
        target.draw(_nbRoundText);
        target.draw(_roundDurationText);
        
        target.draw(_actualLanguage);
        target.draw(_hint);
    }
    
    /**
     * Appelé à la reception d'évènements
     */
    void OptionState::onEvent(sf::Event const& event) {
        sf::Vector2f mousePosition;
        
        switch(event.type) {
            case sf::Event::Closed:
                _game.kill();
                break;
            case sf::Event::KeyPressed:
                switch(event.key.code) {
                    case sf::Keyboard::Escape:
                        _game.stateManager.popState();
                        break;
                    case sf::Keyboard::Return:
                        _apply = true;
                        _game.stateManager.popState();
                        break;
                    case sf::Keyboard::F:
                        _game.setLanguage("francais");
                        break;
                    case sf::Keyboard::E:
                        _game.setLanguage("english");
                        break;
                    case sf::Keyboard::L:
                        _game.setLanguage("latin");
                        break;
                    case sf::Keyboard::I:
                        _game.setLanguage("italian");
                        break;
                    case sf::Keyboard::S:
                        _game.setLanguage("spanish");
                        break;
                    case sf::Keyboard::G:
                        _game.setLanguage("german");
                        break;
                    case sf::Keyboard::C:
                        _game.setLanguage("creol");
                        break;
                    default:
                        break;
                }
                break;
            case sf::Event::MouseMoved:
                
                mousePosition.x = event.mouseMove.x;
                mousePosition.y = event.mouseMove.y;
                
                // Si on est en train de déplacer le curseur du volume...
                if(_dragVolumeSlider) {
                    _volumeSlider.setPosition(mousePosition.x, 433);
                    
                    if(_volumeSlider.getPosition().x < 32) {
                        _volumeSlider.setPosition(32, 433);
                    }
                    else if(_volumeSlider.getPosition().x > 390) {
                        _volumeSlider.setPosition(390, 433);
                    }
                    
                    _game.config.volume = ((_volumeSlider.getPosition().x - 32) / 358) * 100;
                }
                else if(_button_english.getGlobalBounds().contains(mousePosition)) {
                    _button_english.setTextureRect(sf::IntRect(0, 50, 50, 50));
                }
                else if(_button_french.getGlobalBounds().contains(mousePosition)) {
                    _button_french.setTextureRect(sf::IntRect(0, 0, 50, 50));
                }
                else {
                    _button_french.setTextureRect(sf::IntRect(50, 0, 50, 50));
                    _button_english.setTextureRect(sf::IntRect(50, 50, 50, 50));
                }
                
                for(int i = 0; i < 3; i++) {
                    _roundButton[i].setTextureRect(sf::IntRect(0, i * 50, 100, 50));
                    _roundDuration[i].setTextureRect(sf::IntRect(0, i * 50, 100, 50));
                    
                    if(_roundButton[i].getGlobalBounds().contains(mousePosition)) {
                        _roundButton[i].setTextureRect(sf::IntRect(100, i * 50, 100, 50));
                    }
                    else if(_roundDuration[i].getGlobalBounds().contains(mousePosition)) {
                        _roundDuration[i].setTextureRect(sf::IntRect(100, i * 50, 100, 50));
                    }
                }
                
                
                break;
            case sf::Event::MouseButtonPressed:
                
                mousePosition.x = event.mouseButton.x;
                mousePosition.y = event.mouseButton.y;
                
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(_button_english.getGlobalBounds().contains(mousePosition)) {
                        _game.setLanguage("english");
                        _selectSound.play();
                    }
                    else if(_button_french.getGlobalBounds().contains(mousePosition)) {
                        _game.setLanguage("francais");
                        _selectSound.play();
                    }
                    else if(_volumeSlider.getGlobalBounds().contains(mousePosition)) {
                        _dragVolumeSlider = true;
                    }
                    
                    for(int i = 0; i < 3; i++) {
                        
                        if(_roundButton[i].getGlobalBounds().contains(mousePosition)) {
                            _game.config.combatMode = i;
                            _selectSound.play();
                        }
                        else if(_roundDuration[i].getGlobalBounds().contains(mousePosition)) {
                            _game.config.roundDuration = i;
                            _selectSound.play();
                        }
                    }
                }
                break;
            case sf::Event::MouseButtonReleased:
                if(event.mouseButton.button == sf::Mouse::Left && _dragVolumeSlider) {
                    _dragVolumeSlider = false;
                    _selectSound.play();
                }
                break;
            default:
                break;
        }
    }
    
    /**
     * Appelée à la fermeture
     */
    void OptionState::onClose() {
        if(!_apply)
            _game.config = _backupConfig;
        
        _game.saveConfig( resourcePath() + "game.settings");
        
        _game.textureManager.removeTexture("graphics/ui/language_buttons.png");
    }
}