/**
 * FICHIER: CreditsState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *    État dans lequel l'utilisateur peut visualiser les crédits
 */

#ifndef __TP3__CreditsState__
#define __TP3__CreditsState__

#include "GameState.h"
#include <map>
#include <string>
#include "vector.h"
#include <queue>
#include <SFML/Audio.hpp>

#include <fstream>

#define CREDIT_SCROLL_SPEED -0.064f
#define CREDIT_FIXED_Y_POSITION 75
#define CREDIT_SECTION_DISTANCE 150
#define CREDIT_NAME_DISTANCE 30
#define CREDIT_START_POSITION 500

namespace beat {
    class CreditsState : public GameState {
    private:
        
        sf::Font _sectionFont, _nameFont;
        
        vecteur<sf::Text> _texts;
        
        sf::Music _backMusic;
        
    public:
        CreditsState(Game &game);
        virtual ~CreditsState();
        
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
        
        /**
         * Charge les crédits à partir d'un fichier texte
         */
        bool loadFromFile(std::string const& filepath);
    };
}

#endif 
