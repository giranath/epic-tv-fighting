/*
 *  FICHIER: AnimationSequence.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-22
 *  DESCRIPTION:
 *  Il s'agit d'un objet qui décrit une animation, c'est à dire une séquence de rectangles à sélectionner dans les textures
 */

#ifndef __TP3__AnimationSequence__
#define __TP3__AnimationSequence__

#include <SFML/Graphics.hpp>
#include <fstream>
#include "vector.h"

/**
 * Pour une meilleure lisibilité(selon moi) les FrameRect remplace les sf::IntRect
 */
typedef sf::FloatRect FrameRect;
typedef sf::Vector2f FrameOrigin;

struct Hitbox {
    // La boite de collision
    sf::FloatRect box;
    
    // Un entier pouvant représenter une information sur la hitbox
    // Un nombre pour les différencier par exemple
    unsigned int informations;
    
    Hitbox() {
        
    }
    
    Hitbox(sf::FloatRect const& rect, unsigned int infos = 0) {
        box = rect;
        informations = infos;
    }
    
    Hitbox(Hitbox const& box) {
        this->box = box.box;
        informations = box.informations;
    }
};

/**
 * Représente une image dans la séquence
 */
struct Frame {
	FrameRect _r;					//Frame Rect
	FrameOrigin _o;					//Origine de Nathan
	vecteur<Hitbox> _h;		//vecteur de hitbox pour la frame
	
	Frame(FrameRect r, FrameOrigin o) {
		_r = r;
		_o = o;
	}

	Frame() {
	}
};

namespace beat {
    /**
     * Un type représentant une durée en milisecondes
     */
    typedef unsigned int DurationMs;
    
    class AnimationSequence {
    public:
        /**
         * Constructeur
         */
        AnimationSequence();
        
        /**
         * Constructeur à partir d'un vecteur de frame et une durée
         */
        AnimationSequence(vecteur<FrameRect> const& frames, DurationMs duration);
        
        /**
         * Constructeur de copie
         */
        AnimationSequence(AnimationSequence const& other);
        
		/**
		 * Ajoute une frame a fin
		 */
		void appendFrame(FrameRect const& rect, FrameOrigin const& origin);
        
        /**
         * Modifie le point d'ancrage à une frame donnée
         */
        void setFrameOriginAt(unsigned int index, FrameOrigin const& origin);
        
        /**
         * Retourne le rectangle à utilisé actuellement
         */
        FrameRect getFrameRect(unsigned int valX = 1, unsigned int valY = 1) const;
        
        /**
         * Met à jours l'animation
         */
        void update(unsigned int elapsedMs);
        
        /**
         * Retourne la durée de la séquence
         */
        DurationMs getDuration() const;
        
        /**
         * Assigne une durée à la séquence
         */
        void setDuration(DurationMs duration);
        
        /**
         * L'animation peut-être jouée
         */
        void play();
        
        /**
         * Recommence la séquences de rectangle
         */
        void restart();
        
        /**
         * Met en pause l'animation
         */
        void stop();
        
        /**
         * Assignateur
         */
        AnimationSequence const& operator=(AnimationSequence const& other);
        
        /**
         * Informe si l'animation est en cours de lecture
         */
        bool isPlaying() const;
        
        /**
         * Informe si la séquence est rendu à la fin
         */
        bool finished() const;
        
        /**
         * Charge à partir d'un fichier
         */
        bool loadFromFile(std::string const& filepath);
        
        /**
         * Retourne l'index sur lequel l'animation pointe
         */
        unsigned int getFrameIndex() const;
        
        /**
         * Assigne l'index du rectangle à afficher
         */
        void setFrameIndex(unsigned int index);
        
        /**
         * Retourne le point d'ancrage d'une frame
         */
        FrameOrigin getActualOrigin(unsigned int valX = 1, unsigned int valY = 1);
        
        unsigned int getNbHitbox() const;
        Hitbox getHitboxAt(unsigned int index);
        
        Hitbox getHitboxWithID(unsigned int ID);
        
    private:
        
        /**
         * Flag permettant de savoir si l'animation doit être jouée
         */
        bool _playing;
        
        /**
         * Un tableau de rectangle
         */
        vecteur<Frame> _rects;
        
        /**
         * La durée de la séquence en milisecondes
         */
        DurationMs _durationMS;
        
        /**
         * Le temps écoulé depuis le début de l'animation [entre 0 et la durée]
         */
        DurationMs _elapsedTime;
        
        /**
         * L'index de la frame à afficher
         */
        unsigned int _frameIndex;
    };
}

#endif
