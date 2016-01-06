#include "MenuState.h"
#include "TextureManager.h"

#include "Game.h"

#include "PlayerGiranath.h"
#include "GenericPlayer.h"

#define _ANCIENX 100.0f		//Ancienne positione de la tv
#define _ANCIENY 350.0f

#define _NOUVEAUTVX -200.0f	//Nouvelle position de la tv et de la vue
#define _NOUVEAUTVY 600.0f
#define _NOUVEAUVUEX -50.0f
#define _NOUVEAUVUEY 700.0f

#define _VITTVX ((_NOUVEAUTVX - _ANCIENX) / 1000.0f)	//Calcul pour trouver la vitesse de transition
#define _VITTVY ((_NOUVEAUTVY - _ANCIENY) / 1000.0f)
#define _VITVUEX ((_NOUVEAUVUEX - 400.0f) / 1000.0f)
#define _VITVUEY ((_NOUVEAUVUEY - 300.0f) / 1000.0f)


namespace beat {
    MenuState::MenuState(Game &game) : GameState(game) {
        _rouletteHandler = 0;
        _tvHandler = 0;
        _giranGoUp = true;
    }

    MenuState::~MenuState() {
    }

    void MenuState::onStart() {
		_status = 0;
		_vueMenu.setSize(800, 600);
		_vueMenu.setCenter(400, 300);

		_noisePlay = true;

		_titreFont.loadFromFile(resourcePath() + "graphics/fonts/RioGrande.ttf");
		_titre.setFont(_titreFont);
		_titre.setString("    Epic TV Fighting\nthe Movie The GAME");
		_titre.setCharacterSize(60);
		_titre.setPosition(400-(_titre.getLocalBounds().width/2), 10);

		_pressAnyFont.loadFromFile(resourcePath() + "graphics/fonts/Moder DOS 437.ttf");
		_pressAny.setFont(_pressAnyFont);
		_pressAny.setString(_game.getLocalizationStrings().get("press_start", _game.getLanguage()));
		_pressAny.setCharacterSize(24);
		_pressAny.setPosition(400-(_pressAny.getLocalBounds().width/2),200);

        _hint.setFont(_pressAnyFont);
        _hint.setColor(sf::Color::White);
        _hint.setString(_game.getLocalizationStrings().get("menu_hint", _game.getLanguage()));
        _hint.setPosition(-145-(_pressAny.getLocalBounds().width/2), 500);
        _hint.setCharacterSize(18);
        
        _rouletteHandler = &_game.textureManager.getHandler("graphics/ui/tv_roulette.png");
        _tvHandler = &_game.textureManager.getHandler("graphics/ui/TV_ancienne.png");
        _giranHandler = &_game.textureManager.getHandler("graphics/avatars/Nathan Giraldeau.png");

        _tv.setTexture(*_tvHandler);
        
        _roulette.setTexture(*_rouletteHandler);
        
        _giranathou.setTexture(*_giranHandler);
        _giranathou.setColor(sf::Color(255, 255, 255, 100));
        
        _roulette.setOrigin(_roulette.getLocalBounds().width / 2, _roulette.getLocalBounds().height/2);
        
        _tv.setPosition(100, 350);
        _roulette.setPosition(_tv.getPosition().x + 325, _tv.getPosition().y + 58);
        _giranathou.setPosition(145, 600);
        _giranathou.scale(2, 2);
        
        _dancingPrinny = FXLoader::createFromFile(resourcePath() + "datas/effects/dancingPrinny.fx");
        
        _dancingPrinny->setPosition(640, 445);
        
        _dancingPrinny->setScale(2.75, 2.75);
        _dancingPrinny->getAnimationSequence().play();
        
        _tvNoise = FXLoader::createFromFile(resourcePath() + "datas/effects/TVNoise.fx");
        _tvPlay = FXLoader::createFromFile(resourcePath() + "datas/effects/TVPlay.fx");
        _tvOption = FXLoader::createFromFile(resourcePath() + "datas/effects/TVOption.fx");
        _tvExit = FXLoader::createFromFile(resourcePath() + "datas/effects/TVExit.fx");
        _tvCredits = FXLoader::createFromFile(resourcePath() + "datas/effects/TVCredits.fx");
        
        _tvNoise->getAnimationSequence().play();
        _tvPlay->getAnimationSequence().play();
        
        _actualNoise = _tvNoise;
        _actualNoise->setScale(1.5, 1.1);
    }

    void MenuState::onLoad() {
        _pressAny.setString(_game.getLocalizationStrings().get("press_start", _game.getLanguage()));
        _pressAny.setPosition(400-(_pressAny.getLocalBounds().width/2),200);
        
        _hint.setString(_game.getLocalizationStrings().get("menu_hint", _game.getLanguage()));
        _hint.setPosition(-145-(_pressAny.getLocalBounds().width/2), 500);
    }
    
    void MenuState::onUpdate(unsigned int delta) {
        _actualNoise->onUpdate(delta);
        if(_status == 0) {		//Press anybutton menu
			_dancingPrinny->onUpdate(delta);

			if(_game.getTicks()%2000 > 1750)
				_pressAny.setColor(sf::Color::Transparent);
			else
				_pressAny.setColor(sf::Color::White);

			if(_giranathou.getPosition().y > 400 && _giranGoUp) {
				_giranathou.move(0, -0.05f * delta);
				_giranTimer.restart();
			}
        
			if(_giranathou.getPosition().y <= 400 && _giranGoUp && _giranTimer.getElapsedTime().asSeconds() > 2)
				_giranGoUp = false;
        
			if(_giranathou.getPosition().y < 600 && !_giranGoUp) {
				_giranathou.move(0, 0.15f * delta);
				_giranTimer.restart();
			}
        
			if(_giranathou.getPosition().y >= 600 && !_giranGoUp && _giranTimer.getElapsedTime().asSeconds() > 10)
				_giranGoUp = true;
     
        
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				_dancingPrinny->setPosition(_dancingPrinny->getPosition().x - (delta * 0.1f), _dancingPrinny->getPosition().y);
        
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				_dancingPrinny->setPosition(_dancingPrinny->getPosition().x + (delta * 0.1f), _dancingPrinny->getPosition().y);

		} else if(_status == 1) {		//Animation de transition entre press any et menu
			_vueMenu.setCenter(_vueMenu.getCenter().x + (_VITVUEX * delta), _vueMenu.getCenter().y+(_VITVUEY * delta));
			_tv.setPosition(_tv.getPosition().x+(_VITTVX * delta), _tv.getPosition().y+(_VITTVY * delta));
            _roulette.setPosition(_tv.getPosition().x + 325, _tv.getPosition().y + 58);
			_tv.setScale(_tv.getScale().x + ((0.5/1000)*delta),_tv.getScale().x + ((0.5/1000)*delta));
			_roulette.setScale(_tv.getScale().x, _tv.getScale().x);
			_actualNoise->setScale(_actualNoise->getScaleX() + ((0.5/1000)*delta),
				_actualNoise->getScaleY() + ((0.5/1000)*delta));
            
			if(_tv.getPosition().x < _NOUVEAUTVX || _tv.getPosition().y > _NOUVEAUTVY) {
				_status = 2;
				_tv.setScale(1.5 , 1.5);
				_vueMenu.setCenter(_NOUVEAUVUEX,_NOUVEAUVUEY);
				_tv.setPosition(_NOUVEAUTVX, _NOUVEAUTVY);
                _roulette.setPosition(286, 687);
                _roulette.setScale(_tv.getScale().x, _tv.getScale().x);
				_roulette.setRotation(-20);
				_actualNoise->setScale(2, 1.6);
            }
		} else if (_status == 2) {
            switch(_selection) {
                case PLAY_SELECTED:
                    _actualNoise = _tvPlay;
                    _roulette.setRotation(0);
                    _actualNoise->getAnimationSequence().play();
                    break;
                case OPTION_SELECTED:
                    _actualNoise = _tvOption;
                    _roulette.setRotation(45);
                    _actualNoise->setPosition(_tv.getPosition().x, _tv.getPosition().y);
                    _actualNoise->getAnimationSequence().play();
                    break;
                case EXIT_SELECTED:
                    _actualNoise = _tvExit;
                    _roulette.setRotation(135);
                    _actualNoise->setPosition(_tv.getPosition().x, _tv.getPosition().y);
                    _actualNoise->getAnimationSequence().play();
                    break;
                case CREDITS_SELECTED:
                    _actualNoise = _tvCredits;
                    _roulette.setRotation(90);
                    _actualNoise->setPosition(_tv.getPosition().x, _tv.getPosition().y);
                    _actualNoise->getAnimationSequence().play();
                    break;
                default:
                    break;
            }
            
            _actualNoise->setScale(2, 1.6);

		} else if(_status == 3) {		//Animation de transition entre le menu et le press any
            _actualNoise = _tvNoise;
			_vueMenu.setCenter(_vueMenu.getCenter().x - (_VITVUEX * delta),
				_vueMenu.getCenter().y-(_VITVUEY * delta));
			_tv.setPosition(_tv.getPosition().x-(_VITTVX * delta), 
				_tv.getPosition().y-(_VITTVY * delta));
			_tv.setScale(_tv.getScale().x - ((0.5/1000)*delta),
				_tv.getScale().x - ((0.5/1000)*delta));
			_roulette.setScale(_tv.getScale().x, 
				_tv.getScale().x);
			_actualNoise->setScale(_actualNoise->getScaleX() - ((0.5/1000)*delta),
				_actualNoise->getScaleY() - ((0.5/1000)*delta));
            
			if(_tv.getPosition().x > _ANCIENX || _tv.getPosition().y < _ANCIENY) {
				_status = 0;
				_tv.setScale(1 , 1);
				_vueMenu.setCenter(400,300);
				_tv.setPosition(_ANCIENX, _ANCIENY);
				_roulette.setPosition(_tv.getPosition().x + 325, _tv.getPosition().y + 58);
                _roulette.setScale(1, 1);
				_giranathou.setPosition(145, 600);
				_roulette.setRotation(-20);
				_actualNoise->setScale(1.5, 1.1);
            }
		}
    }

    void MenuState::onEvent(sf::Event const& event) {
        // Pour tous les états, on quitte le programme en appuyant sur le x de la fenêtre
        if(event.type == sf::Event::Closed) {
            _game.kill();
        }
        
        switch(_status) {
            // Si on est à l'état press start...
            case 0:
                if((event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) &&
					!(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && !(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))) {
                    if(event.key.code == sf::Keyboard::Escape || event.joystickButton.button == 1) {
                        _game.kill();
                    }
                    else {
                        _status = 1;
                        _selection = 0;
                    }
                }
                
                break;
            // Sinon si on est à la selection d'un option dans le menu (zoom sur la tv)
            case 2:
                if(event.type == sf::Event::KeyPressed || event.type == sf::Event::JoystickButtonPressed) {
                    if(event.key.code == sf::Keyboard::Escape || event.joystickButton.button == 1) {
                        _status = 3;
                    }
                    else if(event.key.code == sf::Keyboard::Return || event.joystickButton.button == 8) {
						if(_selection == PLAY_SELECTED) {
                            _game.stateManager.pushState(new PlayerSelectionState(_game));
                        }
                        else if(_selection == OPTION_SELECTED) {
                            _game.stateManager.pushState(new OptionState(_game));
                        }
                        else if(_selection == CREDITS_SELECTED) {
                            CreditsState* creditState = new CreditsState(_game);
                            
                            if(creditState->loadFromFile(resourcePath() + "credits.cred") == false) {
                                delete creditState;
                                _game.kill();
                            }
                            else {
                                _game.stateManager.pushState(creditState);
                            }
                            
                        }
                        else if(_selection == EXIT_SELECTED) {
                            _game.kill();
                        }
                    }
                    else if(event.key.code == sf::Keyboard::Space) {
                        _selection++;
                    }
                    else if(event.key.code == sf::Keyboard::Left) {
                        _selection--;
                    }
                    else if(event.key.code == sf::Keyboard::Right) {
                        _selection++;
                    }
                    
                    if(_selection >= NUM_SELECTED) {
                        _selection = PLAY_SELECTED;
                    }
                    
                    if(_selection < 0) {
                        _selection = NUM_SELECTED - 1;
                    }
                }
                break;
            // Sinon par défaut on ne fait rien de plus
            default:
                break;
        }
    }

    void MenuState::onDraw(sf::RenderTarget& target) {
        _actualNoise->setPosition(_tv.getPosition().x + 10, _tv.getPosition().y);
        
        if(_status != 2) {
            _roulette.setRotation(-20);
        }
        
		target.setView(_vueMenu);
		if(_status == 0 || _status == 1 || _status == 2 || _status == 3) {
			if(_noisePlay)
				_actualNoise->onDraw(target);
            if(_status == 0) {
                target.draw(_giranathou);
				_dancingPrinny->onDraw(target);
			}
			target.draw(_tv);
			if(_status == 2 || _status == 0)
				target.draw(_roulette);
            
			target.draw(_titre);
			target.draw(_pressAny);
            
            if(_status == 2) {
                target.draw(_hint);
            }
		}
    }

    void MenuState::onClose() {
        delete _dancingPrinny;
        
        _tvHandler->release();
        _rouletteHandler->release();
        
        _game.textureManager.clearUnusedTexture();
    }
}