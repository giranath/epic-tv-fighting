/**
 * FICHIER: Actor.h
 * PROJET:  TP3
 * AUTHEUR: Rukusan aka Luc Boss�
 *
 * DESCRIPTION;
 *      Classe de base pour tous les acteurs du jeu, d�rive d'Object
 */

#include "Object.h"
#include "BoxBody.h"
#include "ObjectManager.h"

#ifndef _ACTOR_
#define _ACTOR_

#define OBJECT_ACTOR 123

namespace beat {
class Actor : public Object {
public:
    enum ActorType {
        ACTOR_PLAYER = 0,
        ACTOR_ENNEMY,
        ACTOR_UNDEFINED
    };
    
    enum Direction {
        DIRECTION_LEFT,
        DIRECTION_RIGHT
    };
protected:
    /**
     * Point de vie actuellement
     */
	int _Health;
    
    /**
     * Vie maximale
     */
	int _MaxHealth;
    
    /**
     * La force du saut
     */
    float _JumpSpring;
    
    /**
     * Vitesse de d�placement en pixel/millisecondes
     */
	float _WalkingSpeed;

    /**
     * D�placement de l'acteur sur l'axe horizontale
     */
	void sideMove(int direction);

    /**
     * Le type d'acteur
     */
    ActorType _actorType;
    
    /**
     * La direction vers laquelle l'acteur fait face
     */
    Direction _direction;
    
    BoxBody* _boundingBox;
    
    bool _onFloor;
    
public:
    /**
     * Constructeur
     */
	Actor(ActorType const& type = ACTOR_UNDEFINED);
    
    /**
     * Destructeur
     */
	virtual ~Actor();
    
    /**
     * Appel� � chaque frame
     */
	virtual void onUpdate(int milliSec) = 0;
        
    /**
     * Appel� juste avant la destruction
     */
	virtual void onKill() = 0;
        
    /**
     * Appel� la premi�re it�ration
     */
	virtual void onCreation() = 0;
        
    /**
     * Appel� pour l'affichage
     */
    virtual void onDraw(sf::RenderTarget& target);
    
    /**
     * Retourne le type d'acteur
     */
    ActorType getActorType() const;
    
    int getMaxHealth() const;
    int getHealth() const;

	Direction getDirection () const;
    
    /**
     * Retire de la vie � l'acteur
     */
    void hit(unsigned int damage);
    
    /**
     * Action � faire lorsque l'acteur saute
     */
	virtual void jump();
    
    /**
     * Se d�placer vers la gauche
     */
    virtual void moveLeft();
    
    /**
     * Se d�placer vers la droite
     */
    virtual void moveRight();
    
    /**
     * Attendre sur place
     */
    virtual void wait();
    
    /**
     * Permet d'assigner une direction de vision
     */
    void setFacingDirection(Direction direction);
    
    /**
     * Informe si l'acteur est au sol
     */
    bool onFloor() const;
    
    BoxBody* getBoxBody() const;
    
    void setLife(int health);
};

}
#endif
