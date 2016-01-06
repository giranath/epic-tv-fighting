/**
 * FICHIER: GameState.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *     Un gestionnaire d'états de jeu. C'est lui qui se charge de gérer la mémoires des états et
 *     de les manipuler en offrant une interface simple mais robuste
 */

#ifndef __TP3__GameStateManager__
#define __TP3__GameStateManager__

#include "Stack.h"
#include "GameState.h"

namespace beat {
    class GameStateManager {
    private:
        /**
         * Une pile d'état de jeu
         */
        cegep::Stack<GameState*> _stateStack;
        
        /**
         * On désactive la copie complètement
         */
        GameStateManager(GameStateManager const& copy);
        GameStateManager& operator=(GameStateManager const& copy);
        
    public:
        
        /**
         * Constructeur par défaut
         */
        GameStateManager();
        
        /**
         * Retire le dessus de la pile d'état
         */
        void popState();
        
        /**
         * Retire le dessus de la pile plusieurs fois
         */
        void popState(unsigned int time);
        
        /**
         * Retire les dessus de la pile jusqu'à un index ( 0 = premier placé, 1 = deuxième, 2 = troisième, etc...)
         */
        void popStateUntil(unsigned int index);
        
        /**
         * Ajoute un état sur la pile
         */
        void pushState(GameState* state);
        
        /**
         * Retourne l'état actuellement utilisé
         */
        GameState& getActualState() const;
        
        /**
         * Appel la méthode onUpdate de l'état actuel
         */
        void updateState(unsigned int deltaMs);
        
        /**
         * Appel la méthode onDraw de l'état actuel
         */
        void drawState(sf::RenderTarget& target);
        
        /**
         * Appel la méthode onEvent de l'état actuel
         */
        void manageEventOfState(sf::Event const& event);
        
        /**
         * Retourne la taille de la pile d'état
         */
        unsigned int getSize();
    };
}

#endif
