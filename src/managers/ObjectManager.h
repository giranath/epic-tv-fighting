/**
 * FICHIER: ObjectManager.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Objet permmetant de gérer tous les objets dynamiques du jeu 
 *      Note: L'objet n'est ni copiable, ni assignable
 */

#ifndef __TP3__ObjectManager__
#define __TP3__ObjectManager__

#include "List.h"
#include "Object.h"
#include "PhysicWorld.h"

namespace beat {
    class ObjectManager {
    private:
        /**
         * Une liste d'objet
         * TODO: Remplacer la std::list par une maison
         */
        cegep::list<Object*> _objectList;
        
        /**
         * On désactive le constructeur de copie
         */
        ObjectManager(ObjectManager const& copy);
        
        /**
         * On désactive l'assignateur
         */
        ObjectManager& operator=(ObjectManager const& other);
        
        /**
         * Le monde physique
         * Peut-être pas la meilleure place ici
         */
        PhysicWorld *_world;
        
    public:
        /**
         * Constructeur
         */
        ObjectManager();
        
        /**
         * Destructeur
         */
        ~ObjectManager();
        
        /**
         * Ajoute un objet dans le gestionnaire
         */
        void addObject(Object* object);
        
        /**
         * Retire un objet de la liste
         */
        void removeObject(Object* object);
        
        /**
         * Retire un objet de la liste à partir de son identifiant, prévilégier l'envoi du pointeur car plus couteuse par identifiant
         */
        void removeObject(ObjectUID UID);
        
        /**
         * Mise à jour de l'ensemble des objets
         */
        void step(int deltaMs);
        
        /**
         * Affiche tous les objets visibles
         */
        void drawVisibles(sf::RenderTarget& target);
        
        /**
         * Retourne un pointeur vers l'objet ayant l'identifiant demandé. 0 si introuvable
         * Cette méthode est couteuse. Il faut parcourir toute la liste à la recherche de l'identifiant
         */
        Object* getObjectWithUID(ObjectUID UID) const;
        
        /**
         * Retourne une référence vers un monde physique
         */
        PhysicWorld& getWorld();
        
        /**
         * Efface tous les objets présent dans le gestionnaire
         */
        void clear();
        
    };
}

#endif
