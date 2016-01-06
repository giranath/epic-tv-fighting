/**
 * FICHIER: Projectile.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Classe héritant d'Object qui représente un projectile
 */

#ifndef __TP3__Projectile__
#define __TP3__Projectile__

#include "Object.h"

#define OBJECT_PROJECTILE 666

namespace beat {
    class PiouPiou : public Object {
    protected:
        /**
         * Pointeur vers l'objet qui à envoyé l'objet
         */
        Object* _Sender;
        
        /**
         * Le nombre de point de dégats au contact
         */
        int _Damage;
        
        unsigned long _el;
        
    public:
        /**
         * Constructeur
         */
        PiouPiou(Object* sender, int damage = 1);
        
        /**
         * Destructeur
         */
        virtual ~PiouPiou();
        
        /**
         * Appelé à chaque frame
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
         * Appelé pour l'affichage
         */
        virtual void onDraw(sf::RenderTarget& target);
        
        /**
         * Permet de modifier le nombre de dommage causé par l'impact d'un projectile
         */
        void setDamage(int value);
        
        /**
         * retourne l'identifiant de celui qui tire le projectile
         */
        ObjectUID getSenderUID() const;
        
        /**
         * Retourne les dommages causés par un projectile
         */
        int getDamage() const;
    };
}

#endif
