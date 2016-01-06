/*
Nom : Luc Bosse
Date : 2013-11-18
Description : State du menu

*/
#ifndef _MENU_STATE_
#define _MENU_STATE_

#include "GameState.h"
#include "GameplayState.h"
#include "OptionState.h"
#include "FXLoader.h"

#include "CustomFX.h"

#include "CreditsState.h"
#include "PlayerSelectionState.h"

namespace beat {
	class MenuState : public GameState {
	protected:
		sf::Sprite _tv;
        sf::Sprite _roulette;
		sf::Font _titreFont;
		sf::Text _pressAny;
        sf::Font _pressAnyFont;
		sf::Text _titre;
        sf::Text _hint;

		sf::View _vueMenu;

		int _status;
        int _selection;

        /**
         * C'est une blague
         */
        sf::Sprite _giranathou;
        
        /**
         * Ici, ce sont des objets permettant de manipuler sécuritairement des textures.
         * Pour leur conception, je me suis inspiré des itérateurs.
         * Prendre note qu'ils peuvent s'utiliser comme une sf::Texture. L'objet s'occupe
         * de se convertir aux moments appropriés
         */
        TextureManager::TextureHandler  *_rouletteHandler,
                                        *_tvHandler,
                                        *_giranHandler;
        
        bool _giranGoUp,
			_noisePlay;
        sf::Clock _giranTimer;
        
        CustomFX *_dancingPrinny,
                 *_tvNoise,
                 *_tvPlay,
                 *_tvOption,
                 *_tvExit,
                 *_tvCredits;
        
        CustomFX* _actualNoise;
        
        enum {
            PLAY_SELECTED = 0,
            OPTION_SELECTED,
            CREDITS_SELECTED,
            EXIT_SELECTED,
            NUM_SELECTED
        };
        
        
	public:
        /**
         * Constructeur
         */
		MenuState(Game& game);
        
        /**
         * Destructeur
         */
		virtual ~MenuState();

		/**
         * Appelée à l'ouverture
         */
        virtual void onStart();
        
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
         * Appelée à la fermeture
         */
        virtual void onClose();
	};
}

#endif