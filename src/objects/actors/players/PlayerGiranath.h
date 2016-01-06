/*
 *  FICHIER: PlayerGiranath.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *  DESCRIPTION:
 *  Correspond au Joueur #2 Giranath (Nathan Giraldeau)
 */

#ifndef __TP3__PlayerGiranath__
#define __TP3__PlayerGiranath__

#include "Player.h"

#define LEFT_PUNCH 100
#define RIGHT_PUNCH 101

#define RIGHT_KICK 102

#define GIRANATH_IDLE_SEQUENCE 0
#define GIRANATH_WALKING_SEQUENCE 1
#define GIRANATH_LEFT_PUNCH_SEQUENCE 2
#define GIRANATH_RIGHT_PUNCH_SEQUENCE 3
#define GIRANATH_RIGHT_KICK_SEQUENCE 4
#define GIRANATH_JUMP_SEQUENCE 5
#define GIRANATH_HIT_SEQUENCE 6

namespace beat {
    class PlayerGiranath : public Player {
    public:
        /**
         * Constructeur
         */
        PlayerGiranath(unsigned int playerCount);
        
        /**
         * Appelée chaque frame
         */
        virtual void onUpdate(int milliSec);
        
        /**
         * Appelé juste avant la destruction
         */
        virtual void onKill();
        
        /**
         * Appelé la première itération
         */
        virtual void onCreation();
        
        /**
         * Définit une attaque de base
         */
        virtual void attackA();
        
        /**
         * Définit une seconde attaque de base
         */
        virtual void attackB();
        
        /**
         * Execute un saut au personnage
         */
        virtual void jump();
        
        /**
         * Déplace le joueur vers la gauche
         */
        virtual void moveLeft();
        
        /**
         * Déplace le joueur vers la droite
         */
        virtual void moveRight();
        
        /**
         * Que faire en cas de collision avec un autre
         */
        virtual void onCollision(Collision const& collision);
        
    private:
        //AnimationSequence _sequences[7];
                
        /**
         * La séquence actuelle
         */
        AnimationSequence* _actualSequence;
        
        /**
         * La corps physique du coup de pied
         */
        BoxBody* _kickBox;
        
        /**
         * Le corps physique du coup de poing
         */
        BoxBody* _punchBox;
    };
}

#endif
