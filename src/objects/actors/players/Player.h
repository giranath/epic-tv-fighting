/*
 *  FICHIER: Player.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *  DESCRIPTION:
 *  Correspond à l'interface de base d'un joueur
 */

#ifndef __TP3__Player__
#define __TP3__Player__

#include "Actor.h"
#include "AnimationSequence.h"
#include <iostream>
#include "vector.h"

namespace beat {
    class Player : public Actor {
    protected:
        unsigned int _playerCount;
        std::string _name;
        std::string _textureName;
        
        vecteur<AnimationSequence> _sequences;
        AnimationSequence* _actualSequence;
        
    public:
        /**
         * Constructeur
         */
        Player(unsigned int playerCount = 1);
        
        /**
         * Destructeur
         */
        virtual ~Player();
        
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
         * Retourne le nombre du joueur
         * NOTE: 1 = joueur 1 , 2 = joueur 2
         */
        unsigned int getPlayerCount() const;
        
        /**
         * Définit une attaque de base
         */
        virtual void attackA() = 0;
        
        /**
         * Définit une seconde attaque de base
         */
        virtual void attackB() = 0;
        
        std::string getName() const;
        void setName(std::string const& name);
        
        AnimationSequence& getAnimationSequence(unsigned int index);
        
        std::string getTextureName() const;
    };
}

#endif
