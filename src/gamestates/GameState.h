/**
 * FICHIER: GameState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *     Un état de jeu virtuel. Un état peut-être l'écran-titre, l'écran de jeu, gameover, etc.
 */

#ifndef __TP3__VGameState__
#define __TP3__VGameState__

#include <SFML/Graphics.hpp>
#include "State.h"
#include "TextureManager.h"

namespace beat {
    class Game;
    
    class GameState : public State {
        friend class GameStateManager;
    public:
        /**
         * Constructeur
         */
        GameState(Game& stateManager);
        
        /**
         * Destructeur
         */
        virtual ~GameState();
        
    protected:
        /**
         * Appelée à l'ouverture
         */
        virtual void onStart() = 0;
        
        virtual void onLoad();
        
        /**
         * Appelée à chaque frame
         */
        virtual void onUpdate(unsigned int delta) = 0;
        
        /**
         * Appelée à l'affichage de l'état
         */
        virtual void onDraw(sf::RenderTarget &target) = 0;
        
        /**
         * Appelé à la reception d'évènements
         */
        virtual void onEvent(sf::Event const& event) = 0;
        
        virtual void onUnload();
        
        /**
         * Appelée à la fermeture
         */
        virtual void onClose() = 0;
        
        Game& _game;
    };
}

#endif
