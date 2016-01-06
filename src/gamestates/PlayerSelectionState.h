/**
 * FICHIER: PlayerSelectionState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *    L'état dans lequel les joueurs choisisent les personnages qu'ils incarneront
 */

#ifndef __TP3__PlayerSelectionState__
#define __TP3__PlayerSelectionState__

#include "GameState.h"
#include "GameplayState.h"
#include "GenericPlayer.h"

namespace beat {
    class PlayerSelectionState : public GameState {
    private:
        sf::Sprite _back;
        
        sf::Sprite _players_sprt[2];
        sf::Font _font;
        sf::Text _hint;
        
        sf::Sprite _cursors[2];
        
        int _choice[2];
        int _playerSelectionTurn;
        unsigned long _elapsedTime;
        
        std::string _players[2];
        
    public:
        PlayerSelectionState(Game& game);
        virtual ~PlayerSelectionState();
        
        virtual void onStart();
        
        /**
         * Appelée lorsqu'on revient à cet état
         */
        virtual void onLoad();
        
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
         * Appelée lorsqu'on pousse un nouvel état dans la pile
         */
        virtual void onUnload();
        
        /**
         * Appelée à la fermeture
         */
        virtual void onClose();
    };
}

#endif
