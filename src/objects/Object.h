/**
 * FICHIER: Object.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Classe de base pour tous les objets dynamique du jeu
 */

#ifndef __TP3__Object__
#define __TP3__Object__

#define OBJECT_UNDEFINED 0

#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include "Collision.h"

namespace beat {
    class ObjectManager;
    
    typedef unsigned long ObjectUID;
    
    class Object {
    private:
        /**
         * L'identifiant de l'object
         */
        unsigned long _UID;
        
        /**
         * Le type principal de l'objet
         */
        int _Type;
        
        /**
         * Assigne un identifiant unique de manière automatique(s'incrémente à chaque assignement)
         */
        static unsigned long autoUID;
        
    protected:
        /**
         * Flag sur la visibilité de l'objet
         */
        bool _Visible;
        
        /**
         * Flag sur
         */
        bool _Alive;
        
        /**
         * La position de l'objet
         */
        sf::Vector2f _Position;
        
        /**
         * La vélocité de l'objet
         */
        sf::Vector2f _Velocity;

        /**
         * Le sprite de l'objet
         */
		sf::Sprite _Sprite;
        
        /**
         * Un texture handler
         */
        TextureManager::TextureHandler* _textureHandler;
        
        /**
         * Un facteur de redimensionnement
         */
        float _ScaleX, _ScaleY;
        
        /**
         * Une rotation
         */
        float _Rotation;
        
    public:
        /**
         * Constructeur
         */
        Object(int type = OBJECT_UNDEFINED, bool visible = true, bool alive = true);
        
        /**
         * Constructeur de copie
         */
        Object(Object const& other);
        
        /**
         * Destructeur
         */
        virtual ~Object();
        
        /**
         * Appelé à chaque frame
         */
        virtual void onUpdate(int milliSec) = 0;
        
        /**
         * Appelé juste avant la destruction
         */
		virtual void onKill() = 0;
        
        /**
         * Appelé la première itération
         */
		virtual void onCreation() = 0;
        
        /**
         * Appelé pour l'affichage
         */
        virtual void onDraw(sf::RenderTarget& target) = 0;
        
        /**
         * Quoi faire en cas de collision
         */
        virtual void onCollision(Collision const& collision);
        
        /**
         * Permet d'assigner un identifiant entre [0 et 100]
         */
		void setUID(unsigned long id);
        
        /**
         * Permet de modifier la visibilité
         */
		void setVisible(bool v);
        
        /**
         * Permet d'indiquer si l'objet doit être détruit
         */
		void setAlive(bool a);
        
        /**
         * Permet de changer la position
         */
		void setPosition(float x, float y);
        
		/**
         * Permet de changer la velocitÈ
         */
		void setVelocity(float x, float y);
        
        /**
         * Informe si l'objet est toujours utilisé
         */
        bool isAlive() const;
        
        /**
         * Informe si l'objet est visible
         */
        bool isVisible() const;
        
        /**
         * Retourne l'identifiant unique de l'objet
         */
        unsigned long getUID() const;
        
        /**
         * Retourne le type de l'objet
         */
        int getType() const;
        
		/**
         * Retourne la position de l'objet
         */
		sf::Vector2f getPosition() const;
        
		/**
         * Retourne la VelocitÈ de l'objet
         */
		sf::Vector2f getVelocity() const;

        /**
         * Assigne une texture à un objet
         */
		void setTexture(sf::Texture& texture, sf::IntRect const& rect);
        
        /**
         * Assigne un texture handler à l'objet
         */
        void setTextureHandler(TextureManager::TextureHandler& handler);
        
        /**
         * Assigne un redimensionnement
         */
        void setScale(float x, float y);
        
        /**
         * Assigne une rotation
         */
        void setRotation(float rot);
        
        /**
         * Retourne l'orientation en degrés
         */
        float getRotation() const;
        
        /**
         * Retourne le facteur de redimensionnement en X
         */
        float getScaleX() const;
        
        /**
         * Retourne le facteur de redimensionnement en Y
         */
        float getScaleY() const;
        
        /**
         * Tourne un objet
         */
        void rotate(float theta);
        
        /**
         * Redimenssionne un objet
         */
        void scale(float x, float y);
        
        /**
         * Modifie le point d'ancrage
         */
        void setOrigin(float x, float y);
        
        /**
         * Retourne le texture handler
         */
        TextureManager::TextureHandler* getTextureHandler() const;
        
        /**
         * Un object Manager static
         */
        static ObjectManager* sObjectManager;
    };
}

#endif
