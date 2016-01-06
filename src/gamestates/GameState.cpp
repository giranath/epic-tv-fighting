/**
 * FICHIER: GameState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *     Un état de jeu virtuel. Un état peut-être l'écran-titre, l'écran de jeu, gameover, etc.
 */

#include "GameState.h"

namespace beat {
    GameState::GameState(Game& manager) : _game(manager) {

    }
    
    GameState::~GameState() {
        
    }
    
    void GameState::onLoad() {
    }
    
    void GameState::onUnload() {
    }
}
