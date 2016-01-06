/**
 * FICHIER: PlayerSelectionState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 */

#include "PlayerSelectionState.h"
#include "Game.h"

namespace beat {
    PlayerSelectionState::PlayerSelectionState(Game& game) : GameState(game) {
        
    }
    
    PlayerSelectionState::~PlayerSelectionState() {
        
    }
    
    void PlayerSelectionState::onStart() {
        _back.setTexture(_game.textureManager.getTexture("graphics/backgrounds/charselect_background.png"));
        
        _players_sprt[0].setTexture(_game.textureManager.getTexture("graphics/ui/tralalathan_select.png"));
        _players_sprt[1].setTexture(_game.textureManager.getTexture("graphics/ui/rukusan_select.png"));
        
        _players[0] = "tralalathan";
        _players[1] = "rukusan";
        
        for(int i = 0; i < 2; i++) {
            //std::string path;
            char path[100];
            _players_sprt[i].setPosition(500 * i + 50, 150);
            sprintf(path, "graphics/ui/p%d_cursor.png", i + 1);
            
            _cursors[i].setTexture(_game.textureManager.getTexture(std::string(path)));
            _choice[i] = i;
        }
        
        _font.loadFromFile(resourcePath() + "graphics/fonts/RioGrande.ttf");
        _hint.setFont(_font);
        _hint.setString(_game.getLocalizationStrings().get("choose_your_fighter", _game.getLanguage()));
        _hint.setCharacterSize(48);
        
        _hint.setPosition(400 - _hint.getLocalBounds().width / 2, 50);
        
        _playerSelectionTurn = 0;
    }
    
    /**
     * Appelée lorsqu'on revient à cet état
     */
    void PlayerSelectionState::onLoad() {
        _playerSelectionTurn = 0;
    }
    
    /**
     * Appelée à chaque frame
     */
    void PlayerSelectionState::onUpdate(unsigned int delta) {
        _elapsedTime += delta;
        
        for(int i = 0; i < 2; i++) {
            _cursors[i].setColor(sf::Color::White);
            _cursors[i].setPosition(_choice[i] * 500 + 50, 450);
        }
        _cursors[1].setPosition(_cursors[1].getPosition().x + 140, _cursors[1].getPosition().y);
        
        if(_elapsedTime % 500 < 250) {
            _cursors[_playerSelectionTurn].setColor(sf::Color::Transparent);
        }
    }
    
    /**
     * Appelée à l'affichage de l'état
     */
    void PlayerSelectionState::onDraw(sf::RenderTarget &target) {
        target.draw(_back);
        
        for(int i = 0; i < 2; i++) {
            target.draw(_players_sprt[i]);
            target.draw(_cursors[i]);
        }
        
        target.draw(_hint);
    }
    
    /**
     * Appelé à la reception d'évènements
     */
    void PlayerSelectionState::onEvent(sf::Event const& event) {
        switch(event.type) {
            case sf::Event::Closed:
                _game.kill();
                break;
            case sf::Event::KeyPressed: {
                switch(event.key.code) {
                    case sf::Keyboard::Return:
                    {
                        if(_playerSelectionTurn == 1) {
                            
                            std::string files[2];
                            
                            for(int i = 0; i < 2; i++) {
                                
                                files[i] = "datas/players/" + _players[_choice[i]] + "/";
                                
                                files[i] += _players[_choice[i]];
                                
                                for(int j = 0; j < files[i].size(); j++) {
                                    files[i][j] = tolower(files[i][j]);
                                }
                                
                                files[i] += ".player";
                                
                            }
                            
                            GenericPlayer* p = new GenericPlayer(1);
                            GenericPlayer* p2 = new GenericPlayer(2);
                            if(!p->loadFromFile(resourcePath() + files[0])) {
                                std::cerr << "Impossible to load: " + resourcePath() + files[0] << std::endl;
                                _game.kill();
                                
                                _game.stateManager.popStateUntil(0);
                            }
                            else if(!p2->loadFromFile(resourcePath() + files[1])) {
                                std::cerr << "Impossible to load: " + resourcePath() + files[1] << std::endl;
                                _game.kill();
                                
                                _game.stateManager.popStateUntil(0);
                            }
                            else {
                                p->setTextureHandler(_game.textureManager.getHandler(p->getTextureName()));
                                p2->setTextureHandler(_game.textureManager.getHandler(p2->getTextureName()));
                                
                                Scene scene;
                                
                                int random = rand() % 5;
                                
                                switch(random) {
                                    case 0:
                                        scene.loadFromFile(resourcePath() + "datas/scenes/bathHouse.scene");
                                        break;
                                    case 1:
                                        scene.loadFromFile(resourcePath() + "datas/scenes/deathStar.scene");
                                        break;
                                    case 2:
                                        scene.loadFromFile(resourcePath() + "datas/scenes/dojo.scene");
                                        break;
                                    case 3:
                                        scene.loadFromFile(resourcePath() + "datas/scenes/hell.scene");
                                        break;
                                    default:
                                        scene.loadFromFile(resourcePath() + "datas/scenes/stonehenge.scene");
                                        break;
                                }
                                
                                _game.stateManager.pushState(new GameplayState(_game,
                                                                               p,
                                                                               p2,
                                                                               scene));
                            }
                        }
                        else {
                            _playerSelectionTurn++;
                        }
                    }
                        break;
                    case sf::Keyboard::Escape:
                        if(_playerSelectionTurn == 0)
                            _game.stateManager.popState();
                        else
                            _playerSelectionTurn--;
                        
                        break;
                    case sf::Keyboard::BackSpace:
                        if(_playerSelectionTurn == 1)
                            _playerSelectionTurn = 0;
                        break;
                    case sf::Keyboard::Right:
                        _choice[_playerSelectionTurn]++;
                        if(_choice[_playerSelectionTurn] > 1) {
                            _choice[_playerSelectionTurn] = 1;
                        }
                        break;
                    case sf::Keyboard::Left:
                        _choice[_playerSelectionTurn]--;
                        if(_choice[_playerSelectionTurn] < 0) {
                            _choice[_playerSelectionTurn] = 0;
                        }
                        break;
                    default:
                        break;
                }
            }
                break;
            default:
                break;
        }
    }
    
    /**
     * Appelée lorsqu'on pousse un nouvel état dans la pile
     */
    void PlayerSelectionState::onUnload() {
    
    }
    
    /**
     * Appelée à la fermeture
     */
    void PlayerSelectionState::onClose() {
    
    }
}