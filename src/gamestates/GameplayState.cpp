/*
 *  FICHIER: GameplayState.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *
 *  L'état dans lequel le jeu se déroule.
 *  C'est ici que le joueur évolue à travers les différents niveaux
 */

#include "GameplayState.h"
#include <math.h>
#include "VersusState.h"

#include "Guntherken.h"
#include <sstream>

namespace beat {
    GameplayState::GameplayState(Game& game, GenericPlayer* p1, GenericPlayer* p2, Scene const& scene) : GameState(game){
        Object::sObjectManager = &_objManager;
        
        _combatMode = (CombatMode)_game.config.combatMode;
        _debug = false;
        
        PLAYER_1 = p1;
        PLAYER_2 = p2;
        _scene = scene;
        _objManager.getWorld().setWidth(_scene.getWidth());
        _displayFight = false;
        
        switch(_game.config.roundDuration) {
            case 0:
                _roundDuration = 30000;
                break;
            case 1:
                _roundDuration = 60000;
                break;
            default:
                _roundDuration = 99000;
                break;
        }
        
        
        _roundTimer = _roundDuration;
    }
    
    GameplayState::~GameplayState() {
        Object::sObjectManager = 0;
    }
    
    void GameplayState::onStart() {
        
        ProjectileFactory::setTextureManager(&_game.textureManager);
        
        for(int i = 0; i < 2; i++) {
            _players[i]->setPosition(i * (_scene.getWidth() - 150) + 50, 200);
            _objManager.addObject(_players[i]);
            
            _bars[i].setPosition(i * 450 + 36, 10);
            _bars[i].setSize(sf::Vector2f(LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT));
            _bars[i].setFillColor(sf::Color::Red);
            
            _lifeBars[i].setPosition(i * 450 + 36, 10);
            _lifeBars[i].setSize(sf::Vector2f(LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT));
            _lifeBars[i].setFillColor(sf::Color::Green);
            
            _scores[i] = 0;
        }
        
        switch(_combatMode) {
            case COMBAT_1_OF_2:
                _scoreMax = 1;
                _maxRound = 1;
                break;
            case COMBAT_2_OF_3:
                _scoreMax = 2;
                _maxRound = 3;
                break;
            case COMBAT_3_OF_4:
                _scoreMax = 3;
                _maxRound = 5;
                break;
        }
        
        PLAYER_2->setFacingDirection(Actor::DIRECTION_LEFT);
        
        switch(_combatMode) {
            case COMBAT_1_OF_2:
                _lifeBarContainer.setTexture(_game.textureManager.getTexture("graphics/ui/uibar1of2.png"));
                break;
            case COMBAT_2_OF_3:
                _lifeBarContainer.setTexture(_game.textureManager.getTexture("graphics/ui/uibar2of3.png"));
                break;
            case COMBAT_3_OF_4:
                _lifeBarContainer.setTexture(_game.textureManager.getTexture("graphics/ui/uibar3of4.png"));
                break;
        }
        
        _scene.getAmbiantMusic().setVolume(_game.config.volume);
        _scene.getAmbiantMusic().setLoop(true);
        
        _objManager.getWorld().setGravity(_game.config.gravity);
        _objManager.getWorld().setFloorHeight(_scene.getFloorHeight());
        
        _font.loadFromFile(resourcePath() + "graphics/fonts/Crimes Times Six.ttf");
        
        _game.stateManager.pushState(new VersusState(_game, *PLAYER_1, *PLAYER_2));
        
        _fight.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/fight.wav"));
        _fight.setVolume(_game.config.volume);
        
        _areYouReady.setBuffer(_game.soundBufferManager.getBuffer("sounds/sfx/areyouready.wav"));
        _areYouReady.setVolume(_game.config.volume);
        
        _elapsedTime = 0;
        _freeze = true;
        
        _round = 0;
        _displayDraw = false;
    }
    
    void GameplayState::initPlayers() {
        for(int i = 0; i < 2; i++) {
            Player* p = (Player*)_players[i];
            p->setPosition(i * (_scene.getWidth() - 150) + 50, 200);
            p->getBoxBody()->setPosition(p->getPosition());
            p->getBoxBody()->setVelocity(sf::Vector2f(0, 0));
            p->setLife(p->getMaxHealth());
            _freeze = true;
        }
        
        PLAYER_2->setFacingDirection(Actor::DIRECTION_LEFT);
    }
    
    void GameplayState::onUpdate(unsigned int delta) {
        
        // Ici on fait jouer le son du commentateur pour laisser le temps au joueur de se préparer au combat
        if(_elapsedTime == 0) {
            _areYouReady.play();
            if(_scene.getAmbiantMusic().getStatus() != sf::Music::Playing)
                _scene.getAmbiantMusic().play();
            initPlayers();
        }
        
        // Ici on annonce le début du combat, les joueurs peuvent maintenant commencer
        if(_areYouReady.getStatus() == sf::Sound::Stopped && _fight.getStatus() != sf::Sound::Playing && _elapsedTime < 2000) {
            _fight.play();
            _freeze = false;
            _displayFight = true;
            _fightElapsedTime = 0;
            _fightAlpha = 255;
            _roundTimer = _roundDuration;
        }
        
        // On récupère le temps écoulé dans le rounds
        _elapsedTime += delta;
        
        if(!_freeze) {
            _roundTimer -= delta;
            if(_roundTimer > _roundDuration)
                _roundTimer = 0;
        }
        
        // Ici on gère le sprite qui affiche le mot Fight
        if(_displayFight || _displayDraw) {
            _fightElapsedTime += delta;
            
            if(_fightElapsedTime > 2000) {
                _displayFight = false;
                
                if(_displayDraw) {
                    _displayDraw = false;
                    _elapsedTime = 0;
                }
            }
            
            if(_fightElapsedTime > 1000) {
                float v = (float)delta * (255.0f / 1000.0f);
                
                if(v > _fightAlpha)
                    _fightAlpha = 0;
                else
                    _fightAlpha -= v;
            }
        }
        
        
        // Ici on met fin à la manche
        // Pour le moment ça met fin à la phase de jeu et retourne à l'écran titre
        if(PLAYER_1->getHealth() == 0 || PLAYER_2->getHealth() == 0 || _roundTimer <= 0) {
            _roundTimer = _roundDuration;
            
            _round++;
            
            if(PLAYER_1->getHealth() == 0)
                _scores[1]++;
            
            if(PLAYER_2->getHealth() == 0)
                _scores[0]++;
            
            if(PLAYER_1->getHealth() > 0 && PLAYER_2->getHealth() > 0) {
                _displayDraw = true;
                _fightElapsedTime = 0;
                _fightAlpha = 255;
                _freeze = true;

            }
            
            if(_round >= _maxRound ||
               _scores[0] >= _scoreMax ||
               _scores[1] >= _scoreMax) {
                Player* temp[2];
                
                for(int i = 0; i < 2; i++) {
                    temp[i] = _players[i];
                }
                
                int victorious = 0;
                
                if(_scores[0] == _scores[1])
                    victorious = 3;
                else if(_scores[0] > _scores[1])
                    victorious = 0;
                else
                    victorious = 1;
                
                _game.stateManager.pushState(new VictoryState(_game, temp, victorious, _scene));
            }
            
            _elapsedTime = 0;
        }
        
        _objManager.getWorld().step(delta);
        
        // Ici on fait en sorte que les joueurs soient de face
        if(PLAYER_1->getPosition().x < PLAYER_2->getPosition().x) {
            if(PLAYER_1->onFloor()) {
                PLAYER_1->setFacingDirection(Actor::DIRECTION_RIGHT);
            }
            
            if(PLAYER_2->onFloor()) {
                PLAYER_2->setFacingDirection(Actor::DIRECTION_LEFT);
            }
        }
        else {
            if(PLAYER_1->onFloor()) {
                PLAYER_1->setFacingDirection(Actor::DIRECTION_LEFT);
            }
            
            if(PLAYER_2->onFloor()) {
                PLAYER_2->setFacingDirection(Actor::DIRECTION_RIGHT);
            }
        }
        
        PLAYER_1->wait();
        PLAYER_2->wait();
        
        /*
         * On gère les contrôles des joueurs
         */
        // Le joueur 1
        
        if(!_freeze) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
					PLAYER_1->moveLeft();
				}
				else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
					PLAYER_1->moveRight();
				}
			} else {
				PLAYER_1->setIsWalking(false);
			}
            
            // Le joueur 2
			if(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis(0)) > 25 || sf::Keyboard::isKeyPressed(sf::Keyboard::D) 
				|| sf::Joystick::getAxisPosition(0, sf::Joystick::Axis(0)) < -25 || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
				if(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis(0)) > 25 || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
					PLAYER_2->moveRight();
				}
				else if(sf::Joystick::getAxisPosition(0, sf::Joystick::Axis(0)) < -25 || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
					PLAYER_2->moveLeft();
				}
			} else {
				PLAYER_2->setIsWalking(false);
			}
        }
        
        _objManager.step(delta);
        
        for(int i = 0; i < 2; i++) {
            _lifeBars[i].setSize(sf::Vector2f(((float)_players[i]->getHealth() / (float)_players[i]->getMaxHealth()) * LIFE_BAR_WIDTH, LIFE_BAR_HEIGHT));
        }
    }
    
    void GameplayState::onDraw(sf::RenderTarget &target) {
        
        sf::Sprite sprite;
        sprite.setTexture(_game.textureManager.getTexture(_scene.getBackgroundTexture()));
        
        target.setView(sf::View(sf::FloatRect(0, 0, _game.textureManager.getTexture(_scene.getBackgroundTexture()).getSize().x, _game.textureManager.getTexture(_scene.getBackgroundTexture()).getSize().y)));
        
        target.draw(sprite);
        
        target.setView(sf::View(sf::FloatRect(0, 0, _scene.getWidth(), _scene.getFloorHeight())));
        
        _objManager.drawVisibles(target);
        
        target.setView(target.getDefaultView());
        
        // On affiche les barres de vie
        for(int i = 0; i < 2; i++) {
            target.draw(_bars[i]);
            target.draw(_lifeBars[i]);
        }
        target.draw(_lifeBarContainer);
        
        // Les points de victoire du premier joueur
        for(int i = 0; i < _scores[0]; i++) {
            sf::Sprite dot;
            dot.setTexture(_game.textureManager.getTexture("graphics/ui/victoryDot.png"));
            
            dot.setPosition(300 - (i * 18 + 3), 32);
            dot.setPosition(dot.getPosition().x - i * 3, dot.getPosition().y);
            
            target.draw(dot);
        }
        
        // Les points de victoire du deuxième joueur
        for(int i = 0; i < _scores[1]; i++) {
            sf::Sprite dot;
            dot.setTexture(_game.textureManager.getTexture("graphics/ui/victoryDot.png"));
            
            dot.setPosition(482 + (i * 18 + 3), 32);
            dot.setPosition(dot.getPosition().x + i * 3, dot.getPosition().y);
            
            target.draw(dot);
        }
        
        // On affiche les noms des joueurs
        sf::Text name;
        name.setFont(_font);
        name.setString(_players[0]->getName());
        name.setPosition(35, 30);
        name.setCharacterSize(18);
        name.setColor(sf::Color::Yellow);
        target.draw(name);
        
        name.setString(_players[1]->getName());
        name.setPosition(765 - name.getLocalBounds().width, 30);
        target.draw(name);
        
        // On affiche le temps restant au round
        
        sf::Text timeRound;
        sf::Font t;
        t.loadFromFile(resourcePath() + "graphics/fonts/ka1.ttf");
        timeRound.setFont(t);
        
        std::stringstream stream;
        stream << _roundTimer / 1000;
        
        timeRound.setString(stream.str());
        timeRound.setCharacterSize(64);
        timeRound.setPosition(400 - timeRound.getLocalBounds().width/2, 10);
        timeRound.setColor(sf::Color::Yellow);
        
        target.draw(timeRound);
        
        if(_displayFight || _displayDraw) {
            sf::Sprite fightSprite;
            
            if(_displayFight) {
                fightSprite.setTexture(_game.textureManager.getTexture("graphics/ui/Fight_screen.png"));
            }
            else if(_displayDraw) {
                fightSprite.setTexture(_game.textureManager.getTexture("graphics/ui/draw.png"));
            }
            fightSprite.setPosition(400 - fightSprite.getLocalBounds().width/2, 300 - fightSprite.getLocalBounds().height/2);
            fightSprite.setColor(sf::Color(255, 255, 255, _fightAlpha));
            
            target.draw(fightSprite);
        }
        
        //target.setView(_gameView);
        target.setView(sf::View(sf::FloatRect(0, 0, _scene.getWidth(), _scene.getFloorHeight())));
        if(_debug)
            _objManager.getWorld().debugDraw(target);
    }
    
    void GameplayState::onEvent(sf::Event const& event) {        
        if(event.type == sf::Event::Closed)
            _game.kill();
        
        // Le premier joueur ne se joues qu'avec le clavier
        if(event.type == sf::Event::KeyPressed) {
            switch(event.key.code) {
                case sf::Keyboard::P:
                    _debug = !_debug;
                    break;
                case sf::Keyboard::Escape:
                    _game.stateManager.popState(2);
                    break;
                    
                // Ici les contrôles du joueur 1
                case sf::Keyboard::M:
                    if(!_freeze)
                        PLAYER_1->attackA();
                    break;
				case sf::Keyboard::Comma:
                    if(!_freeze)
                        PLAYER_1->attackB();
                    break;
				case sf::Keyboard::Up:
                    if(!_freeze)
                        PLAYER_1->jump();
                    break;
				case sf::Keyboard::R:
					if(!_freeze)
                        PLAYER_2->attackA();
                    break;
				case sf::Keyboard::T:
					if(!_freeze)
                        PLAYER_2->attackB();
                    break;
				case sf::Keyboard::W:
					if(!_freeze)
                        PLAYER_2->jump();
                    break;
                default:
                    break;
                
            }
        }
        // Pour le moment le deuxième joueur ne se joues qu'à la manette
        else if(event.type == sf::Event::JoystickButtonPressed) {
            switch(event.joystickButton.button) {
                case 0:
                    if(!_freeze)
                        PLAYER_2->jump();
                    break;
                case 2:
                    if(!_freeze)
                        PLAYER_2->attackA();
                    break;
                case 3:
                    if(!_freeze)
                        PLAYER_2->attackB();
                    break;
                default:
                    break;
            }
        }
    }

    
    void GameplayState::onClose() {
        _scene.getAmbiantMusic().stop();
        ProjectileFactory::setTextureManager(0);
    }
}
