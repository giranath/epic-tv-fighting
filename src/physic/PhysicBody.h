/*
 *  FICHIER: PhysicBody.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *  DESCRIPTION:
 */

#ifndef __TP3__PhysicBody__
#define __TP3__PhysicBody__

#include <SFML/Graphics.hpp>

namespace beat {
    class Object;
    
    class PhysicBody {
    public:
        enum BodyType {
            BODY_BOX,
            BODY_UNDEFINED
        };
        
        /**
         * Constructeur
         */
        PhysicBody(sf::Vector2f const& position = sf::Vector2f(), bool dynamic = true, bool affectedByGravity = true);
        
        /**
         * Informe si le corps est affecté par la gravité
         */
        bool isAffectedByGravity() const;
        
        /**
         * Permet de modifier si l'objet est affecté par la gravité
         */
        void setGravityAffected(bool affected);
        
        /**
         * Retourne la position du corps
         */
        sf::Vector2f const& getPosition() const;
        
        /**
         * Assigne une position au corps
         */
        void setPosition(sf::Vector2f const& position);
        
        /**
         * Retourne une vélocité
         */
        sf::Vector2f const& getVelocity() const;
        
        /**
         * Assigne une vélocité
         */
        void setVelocity(sf::Vector2f const& velocity);
        
        /**
         * Le corps est-il dynamic?
         */
        bool isDynamic() const;
        
        void setDynamic(bool dynamic);
        
        BodyType getType() const;
        
        Object* possessor;
        
        int collisionMask;
        
        void activate();
        void desactivate();
        
        bool isActivated();
        
    protected:
        BodyType _type;
        
        /**
         * Le corps est-il affecté par la gravité?
         */
        bool _useGravity;
        
        /**
         * Le corps peut-il bouger?
         */
        bool _dynamic;
        
        /**
         * La vélocité du corps
         */
        sf::Vector2f _velocity;
        
        /**
         * La position du corps
         */
        sf::Vector2f _position;
        
        /**
         * L'UID de l'objet représenté par ce corps
         */
        unsigned long _represents;
        
        bool _activated;
        
    };
}

#endif
