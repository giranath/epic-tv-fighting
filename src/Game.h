/*
 *  FICHIER: Game.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-18
 *  DESCRIPTION:
 *  Classe représentant le jeu
 */

#ifndef __TP3__Game__
#define __TP3__Game__

#include "TextureManager.h"
#include "SoundBufferManager.h"
#include "GameStateManager.h"
#include <fstream>
#include "LocalizationStrings.h"

namespace beat {
    class Game {
    public:
        
        struct GameConfig {
            // Le volume des sons
            float volume;
            
            // La gravité
            sf::Vector2f gravity;
            
            // Les dimension de la fenêtre
            unsigned int window_width, window_height;
            
            // Le langage actuel
            std::string language;
            
            // La durée d'un round
            unsigned int roundDuration;
            
            // Le mode de combat (1 round, 3 rounds ou 5 rounds)
            unsigned int combatMode;
        };
        
        /**
         * Constructeur
         */
        Game();
        
        // Le gestionnaire de texture
        TextureManager textureManager;
        
        // Le gestionnaire de sons
        SoundBufferManager soundBufferManager;
        
        // Le gestionnaire d'état
        GameStateManager stateManager;
        
        /**
         * Informe si le jeu est en cours d'execution
         */
        bool isPlaying() const;
        
        /**
         * Met fin à l'execution du jeu
         */
        void kill();
        
        /**
         * Retourne le nombre de ms écoulés depuis le début du programme
         */
		unsigned long getTicks() const;
        
        /**
         * Réinitialise les ticks à 0
         */
		void resetTicks();
        
        /**
         * Ajoute des ticks au compteur
         */
		void addTicks(unsigned long t);

        /**
         * Configurations du jeu
         */
        GameConfig config;
        
        /**
         * Charge un fichier de configuration
         */
        bool loadConfig(std::string const& filepath);
        
        /**
         * Sauvegarde les configurations dans un fichier
         */
        bool saveConfig(std::string const& filepath);
        
        /**
         * Retourne le gestionnaire de chaines localisées
         */
        LocalizationString& getLocalizationStrings();
        
        /**
         * Retourne le langage utilisé durant la session de jeu
         */
        std::string getLanguage();
        
        /**
         * Modifie le langage utilisé durant la session de jeu
         */
        void setLanguage(std::string const& name);
        
        /**
         * Retourne la fenêtre Je vais probablement la retirer
         */
        //sf::RenderWindow& getRenderWindow();
        
    private:
        /**
         * Booléenne sur l'état du jeu
         */
        bool _playing;
        
        /**
         * Le nombre de ms écoulées depuis le début du programme
         */
		unsigned long _ticks;
        
        /**
         * Le gestionnaire de chaines
         */
        LocalizationString _localizationStrings;
        
        /**
         * Le fichier d'accès au chaines localisées
         */
        std::string _localizationStr;

    };
}

#endif
