/*
 *  FICHIER: GenericPlayer.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *  DESCRIPTION:
 *  Un joueur définissable par un fichier externe
 */

#ifndef __TP3__GenericPlayer__
#define __TP3__GenericPlayer__

#include "Player.h"
#include "comboList.h"
#include "List.h"
#include "AnimationSequence.h"

namespace beat {
    class GenericPlayer : public Player {
    private:
        comboTree _comboTree;
        comboTree::iterator _comboIterator;
		int _comboTimer;
		bool _comboStart;
		bool _comboBlock;
		AnimationSequence* _walk;

        
        // Une liste des différentes boites de collision d'un personnage
        // Une liste me semble pertinente du aux nombreuses suppressions et ajouts
        cegep::list<BoxBody*> _hitboxes;
        Hitbox _bodyHitbox;
        
        bool _hit;
        unsigned int _hitE;
        unsigned int _elapsedTime;
        
        void syncHitboxes(AnimationSequence &sequence);
        
        bool _isWalking;
        
    public:
        /**
         * Le constructeur
         */
        GenericPlayer(unsigned int playerCount = 0);
        
        /**
         * Le destructeur
         */
        virtual ~GenericPlayer();
        /**
		* Setteur de is walking
		*/
		void setIsWalking(bool i);

        /**
         * Charge le joueur à partir d'un fichier
         */
        bool loadFromFile(std::string const& path);
        
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
        
        /**
         * Supprime toutes les boites de collision d'un joueur
         */
        void clearHitboxes();
    };
}

#endif
