/**
 * FICHIER: ceciEstNotreMain.cpp
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *          Luc Bossé
 *
 * DESCRIPTION;
 *      Il s'agit d'un jeu de combat pour le travail pratique #3 du cours Structures de Donnée
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "ResourcePath.h"

#include "TextureManager.h"
#include "SoundBufferManager.h"
#include "GameStateManager.h"

#include "MenuState.h"

#include "Game.h"
#include "FXLoader.h"
#include "GenericPlayer.h"
#include "comboList.h"

#include <ctime>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

int main(int argc, const char * argv[]) {
    
    srand(time(NULL));
    
    // On instancie une fenêtre de taille 800 x 600 avec 16 bit par couleur ayant pour titre n'importe quoi
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), "Epic TV Fighting, the movie, the game, 2013"/*, sf::Style::Fullscreen*/);
    window.setFramerateLimit(60);
    
    // On désactive la répétition des touches pour rendre fonctionnel le système de combo
    window.setKeyRepeatEnabled(false);
    
    /**
     * Petit hack pour contourner un lag lorsque SFML crée son premier son
     * Probablement des initialisations internes
     */
    sf::Sound hackSound;
    
    // Il s'agit d'une classe représentant le jeu et ses systèmes principaux
    beat::Game game;
    
    // Si on arrive pas à lire les configurations du jeu, on assigne celles par défaut
    if(!game.loadConfig(resourcePath() + "game.settings")) {
        game.config.volume = 100;
        game.config.gravity = sf::Vector2f(0, 0.1);
    }
    
    // Ici on assigne les gestionnaires de ressource au chargeur d'effets
    beat::FXLoader::setSoundManager(&game.soundBufferManager);
    beat::FXLoader::setTextureManager(&game.textureManager);
    
    beat::SoundBufferManager::gSoundManager = &game.soundBufferManager;
    
    game.stateManager.pushState(new beat::MenuState(game));
    
    // Horloge centrale du programme, tout le programme se synchronise avec
    sf::Clock application_tick;
    
    // Ici on place l'icon de la fenêtre
    sf::Image image;
    image.loadFromFile(resourcePath() + "graphics/avatars/Nathan Giraldeau.png");
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    
    // Tant que le jeu est en cours...
    while(game.isPlaying()) {
        
        // On récupère le temps écoulé durant le tour de boucle
        unsigned int delta = application_tick.restart().asMilliseconds();
        
        // On ajoute ce temps au temps écoulée depuis le début du programme
        game.addTicks(delta);
        game.config.window_width = WINDOW_WIDTH;
        game.config.window_height = WINDOW_HEIGHT;
        
        /**
         * Petite sécurité pour empêcher que le programme plante si le jeu roule durant plusieurs jours d'affilé et que les ms atteigne la limite
         * du unsigned long
         */
		if(game.getTicks() > -100)
			game.resetTicks();

        sf::Event event;
        
        // On récupère tous les évènements du programme (clic souris, clavier, fenêtre, etc) et on les envois à l'état actuel
        while(window.pollEvent(event)) {
            game.stateManager.manageEventOfState(event);
        }
        
        // On met à jour l'état actuel
        game.stateManager.updateState(delta);
        
        // On replace la vue de la fenêtre à celle par défaut
        // Je n'ai pas vérifier avec SFML 2.1 mais avec les anciennes versions
        // Cela était nécessaire, la librairie ne s'en chargait pas seul
		window.setView(window.getDefaultView());
        
        // On efface le contenu de la fenêtre
        window.clear();
        
        // On affiche le contenu de l'état actuel
        game.stateManager.drawState(window);
        
        // On affiche le contenu
        window.display();
    }
    
    // Ici on vide la pile d'état pour s'assurer que le programme se ferme de manière élégante
    // Aussi, si on ajoute une fonctionnalité de sauvegarde dans le onClose, on est certain
    // quelle sera faite (sauf si le programme plante... mais cela ne devrait pas arriver)
    while(game.stateManager.getSize() > 0)
        game.stateManager.popState();
    
    return EXIT_SUCCESS;
}
