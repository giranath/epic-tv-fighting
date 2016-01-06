/**
 * FICHIER: GameState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *     Un gestionnaire d'états de jeu. C'est lui qui se charge de gérer la mémoires des états et
 *     de les manipuler en offrant une interface simple mais robuste
 */

#include "GameStateManager.h"

namespace beat {
    GameStateManager::GameStateManager() {
        
    }
    
    void GameStateManager::popState() {
        // On ferme le dessus de la pile
        _stateStack.top()->onClose();
        
        // On retire le dessus
        _stateStack.pop();
        
        // On charge le nouvel élément du dessus
        if(_stateStack.getSize() > 0)
            _stateStack.top()->onLoad();
    }
    
    void GameStateManager::popState(unsigned int time) {
        for(int i = 0; i < time && _stateStack.getSize() > 0; i++) {
            popState();
        }
    }
    
    void GameStateManager::popStateUntil(unsigned int index) {
        while(_stateStack.getSize() > 0 && _stateStack.getSize() != index) {
            popState();
        }
    }
    
    void GameStateManager::pushState(GameState* state) {
        if(_stateStack.getSize() > 0)
            _stateStack.top()->onUnload();
        
        _stateStack.push(state);
        
        _stateStack.top()->onStart();
    }
    
    GameState& GameStateManager::getActualState() const {
        assert(!_stateStack.isEmpty());
        
        return *_stateStack.top();
    }
    
    void GameStateManager::updateState(unsigned int deltaMs) {
        if(_stateStack.getSize() > 0)
            getActualState().onUpdate(deltaMs);
    }
    
    void GameStateManager::drawState(sf::RenderTarget& target) {
        if(_stateStack.getSize() > 0)
            getActualState().onDraw(target);
    }
    
    void GameStateManager::manageEventOfState(sf::Event const& event) {
        if(_stateStack.getSize() > 0)
            getActualState().onEvent(event);
    }
    
    unsigned int GameStateManager::getSize() {
        return _stateStack.getSize();
    }
}