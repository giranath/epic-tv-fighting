/*
 *  FICHIER: GameplayState.cpp
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *
 *  L'état dans lequel le jeu se déroule.
 *  C'est ici que le joueur évolue à travers les différents niveaux
 */

#ifndef __TP3__GameplayState__
#define __TP3__GameplayState__

#include "GameState.h"
#include "ObjectManager.h"
#include <SFML/Graphics.hpp>
#include "Projectile.h"
#include "FX.h"
#include <SFML/Audio.hpp>
#include "CollisionManager.h"
#include "Game.h"
#include "Player.h"
#include "CustomFX.h"
#include "FXLoader.h"
#include "PlayerGiranath.h"
#include "Scene.h"

#include "ProjectileFactory.h"
#include "GenericPlayer.h"
#include "Player.h"
#include "VictoryState.h"


#define LIFE_BAR_WIDTH 280
#define LIFE_BAR_HEIGHT 18

#define PLAYER_1 _players[0]
#define PLAYER_2 _players[1]

//#define BUILD_STUPID_AI

#define CAMERA_SPRING_CONSTANT 0.5
#define CAMERA_SPRING_DAMPING 0.25
#define CAMERA_DESIRED_DISTANCE 200
#define CAMERA_RELATIVE_VELOCITY 0.25

namespace beat {
    class GameplayState : public GameState {
    public:
        enum CombatMode {
            COMBAT_1_OF_2,
            COMBAT_2_OF_3,
            COMBAT_3_OF_4
        };
    private:
        CombatMode _combatMode;
        
        /**
         * Un gestionnaire d'image
         */
        ObjectManager _objManager;
        
        /**
         * Un flag permettant d'afficher des informations
         * spécifiques au debbugage
         */
        bool _debug;
        
        /**
         * Deux joueurs
         */
        GenericPlayer* _players[2];
        
        /**
         * Les barres de vie
         */
        sf::RectangleShape _lifeBars[2];
        sf::RectangleShape _bars[2];
        
        sf::Sprite _lifeBarContainer;
        
        // Le niveau
        Scene _scene;
        
        // Les sons
        sf::Font _font;
        sf::Sound _fight;
        sf::Sound _areYouReady;
        
        // Le temps écoulé
        unsigned long _elapsedTime;
        
        // Le temps écoulé depuis que le fight est affiché à l'écran
        unsigned long _fightElapsedTime;
        
        // Permet d'empêcher le mouvement des joueurs
        bool _freeze;
        
        // On affiche le mot draw, fight et gère leur transparence
        bool _displayDraw;
        bool _displayFight;
        float _fightAlpha;
        
        // Indique le rou
        unsigned short _round;
        
        unsigned int _roundDuration;
        unsigned int _roundTimer;
        
        // Le score des deux joueurs(le nombre de victoire)
        int _scores[2];
        int _scoreMax;
        int _maxRound;
        
        bool _roundOver;
        
        // On fait en sorte que les deux joueurs se regardent de face
        void facePlayers();
        
        // On replace les joueurs et réinitialise leurs vie
        void initPlayers();
        
        // Informe si le round est terminé
        bool roundIsOver() const;
        
        // On gère les entrées en temps réel (le clavier pour le déplacement)
        void manageFastInput();
        
        void manageRoundVictory();
        
    public:
        /**
         * Constructeur
         */
        GameplayState(Game& game, GenericPlayer* p1, GenericPlayer* p2, Scene const& scene);
        
        /**
         * Destructeur
         */
        virtual ~GameplayState();
        
        /**
         * Appelée pour l'initialisation de l'état
         */
        virtual void onStart();
        
        /**
         * Appelée pour mettre à jour l'état
         */
        virtual void onUpdate(unsigned int delta);
        
        /**
         * Appelée pour affiche l'état
         */
        virtual void onDraw(sf::RenderTarget &target);
        
        /**
         * Appelée pour gérer les évènements
         */
        virtual void onEvent(sf::Event const& event);
        
        /**
         * Appelé à la fermeture de l'état
         */
        virtual void onClose();
    };
}

#endif
