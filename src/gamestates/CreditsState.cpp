/**
 * FICHIER: CreditsState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *    État dans lequel l'utilisateur peut visualiser les crédits
 */

#include "CreditsState.h"
#include "Game.h"

namespace beat {
    CreditsState::CreditsState(Game &game) : GameState(game) {
        
    }
    
    CreditsState::~CreditsState() {
        
    }
    
    /**
     * Appelée à l'ouverture
     */
    void CreditsState::onStart() {
        _backMusic.openFromFile(resourcePath() + "sounds/music/epicSaxGuy.ogg");
        _backMusic.setLoop(true);
        _backMusic.setVolume(_game.config.volume);
        _backMusic.play();
    }
    
    /**
     * Appelée à chaque frame
     */
    void CreditsState::onUpdate(unsigned int delta) {
        
        if(_texts[_texts.getDim() - 1].getPosition().y >= -100) {
            for(int i = 0; i < _texts.getDim(); i++) {
                _texts[i].move(0, CREDIT_SCROLL_SPEED * delta);
            }
        }
        else {
            _game.stateManager.popState();
        }
    }
    
    /**
     * Appelée à l'affichage de l'état
     */
    void CreditsState::onDraw(sf::RenderTarget &target) {
        for(int i = 0; i < _texts.getDim(); i++) {
            target.draw(_texts[i]);
        }
    }
    
    /**
     * Appelé à la reception d'évènements
     */
    void CreditsState::onEvent(sf::Event const& event) {
        if(event.type == sf::Event::Closed) {
            _game.kill();
        }
        if(event.type == sf::Event::KeyPressed) {
			if(event.key.code == sf::Keyboard::Escape)
            _game.stateManager.popState();
        }
    }
    
    /**
     * Appelée à la fermeture
     */
    void CreditsState::onClose() {
        _backMusic.stop();
    }
    
    /**
     * Charge les crédits à partir d'un fichier texte
     */
    bool CreditsState::loadFromFile(std::string const& filepath) {
        
        _sectionFont.loadFromFile(resourcePath() + "graphics/fonts/RioGrande.ttf");
        _nameFont.loadFromFile(resourcePath() + "graphics/fonts/Moder DOS 437.ttf");
        
        int lastY = CREDIT_START_POSITION;
        
        std::ifstream istream;
        
        istream.open(filepath.c_str());
        
        if(!istream.is_open()) {
            return false;
        }
        
        std::string lastInserted;
        while(istream.good()) {
            std::string line;
            
            std::getline(istream, line);
            if(line.empty())
				continue;
            // S'il s'agit du nom d'une catégorie
            if(line[0] == '#') {
                std::string sectionName = line.substr(1);
                
                for(int i = 0; i < sectionName.size(); i++) {
                    sectionName[i] = tolower(sectionName[i]);
                }
                
                // Si le nom de la section essai d'atteindre les chaines multilingues
                if(sectionName[0] == '$') {
                    sectionName = sectionName.substr(1);
                    
                    sectionName = _game.getLocalizationStrings().get(sectionName, _game.getLanguage());
                }
            
                
                sf::Text text;
                text.setFont(_sectionFont);
                text.setString(sectionName);
                
                lastY+= CREDIT_SECTION_DISTANCE;
                text.setPosition(400 - text.getLocalBounds().width / 2, lastY);
                
                _texts.push_back(text);
                
            }
            // S'il s'agit d'un nom
            else if(line[0] == '-') {
                std::string name = line.substr(1);
                
                lastY += CREDIT_NAME_DISTANCE;
                
                sf::Text text;
                text.setFont(_nameFont);
                text.setString(name);
                text.setPosition(400 - text.getLocalBounds().width / 2, lastY);
                
                _texts.push_back(text);
            }
        }
        
        return true;
    }
}