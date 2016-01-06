/*
 *  FICHIER: BoxBody.h
 *  PROJET:  TP3
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-26
 *  DESCRIPTION:
 */

#ifndef __TP3__BoxBody__
#define __TP3__BoxBody__

#include "PhysicBody.h"

namespace beat {
    
    class BoxBody : public PhysicBody {
    public:
        /**
         * Le constructeur
         */
        BoxBody(sf::Vector2f const& position = sf::Vector2f(), float width = 0, float height = 0, bool dynamic = true,  bool affected = true);
        
        /**
         * Retourne la largeur
         */
        float getWidth() const;
        
        /**
         * Retourne la hauteur
         */
        float getHeight() const;
        
        /**
         * Retourne le rectangle du corps
         */
        sf::FloatRect getBoundingBox() const;
        
        /**
         * Assigne une largeur au rectangle
         */
        void setWidth(float w);
        
        /**
         * Assigne une hauteur au rectangle
         */
        void setHeight(float h);
        
        /**
         * Assigne une dimension au rectangle
         */
        void setDimensions(float w, float h);
        
    protected:
        /**
         * Le rectangle
         */
        float     _width,
                  _height;
    };
}

#endif
