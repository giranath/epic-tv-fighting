/**
 * FICHIER: VersusState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *    L'état dans lequel les joueurs voient les adversaires
 */

#ifndef __TP3__PlayerSelectionState__
#define __TP3__PlayerSelectionState__

#include "GameState.h"
#include "Player.h"
#include <SFML/Audio.hpp>

#define VERSUS_STATE_DURATION 4000

namespace beat {
    class VersusState : public GameState {
    public:
        VersusState(Game& game, Player& p1, Player& p2);
        virtual ~VersusState();
        
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
        
    private:
        sf::Sprite _backSprite;
        sf::Sprite _vsSprite;
        sf::Text _name1;
        sf::Text _name2;
        
        Player& _p1, &_p2;
        AnimationSequence _seq1, _seq2;
        
        TextureManager::TextureHandler* _backHandler, *_vsHandler;
        unsigned long _elapsedTime;
        
        sf::Font _font;
        sf::Sound _p1NameSnd, _p2NameSnd, _versusSnd;
        
        bool _f1, _f2, _f3;
    };
}

#endif
