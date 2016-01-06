/**
 * FICHIER: OptionState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *    État dans lequel l'utilisateur peut configurer son jeu
 */

#ifndef __TP3__OptionState__
#define __TP3__OptionState__

#include "GameState.h"
#include <SFML/Audio.hpp>
#include "Game.h"

namespace beat {
    class OptionState : public GameState {
    private:
        sf::Sprite  _button_french,
                    _button_english;
        
        sf::Font _font;
        sf::Text _languageTitle;
        sf::Text _actualLanguage;
        sf::Text _hint;
        sf::Text _volumeTitle;
        sf::Text _volumeValue;
        
        sf::Text _nbRoundText,
                 _roundDurationText;
        
        sf::Sound _selectSound;
        sf::Sprite _backSprite;
        sf::Sprite _volumeSlider;
        
        sf::Sprite _roundButton[3];
        sf::Sprite _roundDuration[3];
        
        bool _dragVolumeSlider;
        
        Game::GameConfig _backupConfig;
        
        bool _apply;
        
    public:
        /**
         * Constructeur
         */
        OptionState(Game& game);
        
        /**
         * Destructeur
         */
        virtual ~OptionState();
        
        /**
         * Appelée à l'ouverture
         */
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
    };
}

#endif
