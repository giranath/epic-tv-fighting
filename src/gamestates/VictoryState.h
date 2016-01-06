/**
 * FICHIER: VictoryState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *    État dans lequel on dévoile le vainqueur du combat
 */

#ifndef __TP3__VictoryState__
#define __TP3__VictoryState__

#include "GameState.h"
#include "Player.h"
#include "Scene.h"
#include "Game.h"

namespace beat {
    class VictoryState : public GameState {
    public:
        VictoryState(Game &game, Player* players[2], int victorious, Scene &scene);
        
        virtual void onStart();
        /**
         * Appelée à chaque frame
         */
        virtual void onUpdate(unsigned int delta);
        
        /**
         * Appelée à l'affichage de l'état
         */
        virtual void onDraw(sf::RenderTarget &target);
        
        /**
         * Appelé à la reception d'évènements
         */
        virtual void onEvent(sf::Event const& event);
        
        /**
         * Appelée à la fermeture
         */
        virtual void onClose();
    private:
        Player* _players[2];
        Scene &_scene;
        
        AnimationSequence _sequences[2];
        
        // L'index du vainqueur
        int _victoriousIndex;
        
		sf::Font _victoryFont;
		sf::Text _victoryText;

        sf::Sound _winner;
        sf::Sound _wins;
        
        bool _sayWins;
        bool _sayName;
    };
}

#endif
