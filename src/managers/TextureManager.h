/**
 * FICHIER: TextureManager.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *      Objet permmetant de gérer les textures.
 */

#ifndef __TP3__TextureManager__
#define __TP3__TextureManager__

#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include "ResourcePath.h"

namespace beat {
    class TextureManager {
    public:
        /**
         * Un manipulateur de texture
         * Permet de garder une référence vers une texture
         * Compte aussi le nombre de références vers lui
         */
        class TextureHandler {
            friend class TextureManager;
        protected:
            sf::Texture* texture;
            unsigned int refCount;
            
            TextureHandler(sf::Texture* texture) {
                this->texture = texture;
                refCount = 0;
            }
            
        public:
            
            TextureHandler() {
                texture = 0;
                refCount = 0;
            }
            
            operator sf::Texture& () {
                return *this->texture;
            }
            
            void release() {
                if(refCount > 0)
                    refCount--;
            }
            
            void addRef() {
                refCount++;
            }
            
            unsigned int getRefCount() const {
                return refCount;
            }
            
            unsigned int getWidth() const {
                return texture->getSize().x;
            }
            
            unsigned int getHeight() const {
                return texture->getSize().y;
            }
        };
        
    private:
        
        /**
         * Une map de texture
         */
        std::map<std::string, TextureHandler> _textures;
        
        /**
         * Retourne le chemin de la texture (Rend le gestionnaire indépendant du système d'exploitation)
         */
        std::string getRealResPath(std::string const& path) const;
        
        /**
         * Crée une texture d'erreur affichant le nom problématique
         */
        void createPlaceHolderFor(std::string const& path);
        
    public:
        /**
         * Constructeur
         */
        TextureManager();
        
        /**
         * Destructeur
         */
        ~TextureManager();
        
        /**
         * Ajoute une texture au gestionnaire.
         * Si la texture ne peut être chargée, une d'erreur sera créée à la place avec le nom de la texture
         */
        bool addTexture(std::string const& filepath);
        
        /**
         * Retire une texture si son compteur de référence tombe à 0 ou si on force le gestionnaire à retirer la texture
         */
        bool removeTexture(std::string const& filepath, bool forced = false);
        
        /**
         * Retourne une texture. Si elle n'existe pas, addTexture sera appelée
         */
        sf::Texture& getTexture(std::string const& filepath);
        
        /**
         * Retourne le manipulateur de texture
         */
        TextureHandler& getHandler(std::string const& filepath);
        
        /**
         * Retourne le nombre d'utilisation actuelle d'une texture
         */
        unsigned int getRefCountOfTexture(std::string const& filepath) const;
        
        /**
         * Informe si une texture est présente dans le gestionnaire
         */
        bool exists(std::string const& filepath) const;
        
        /**
         * Permet de libérer une texture (Décrémente le nombre de référence)
         */
        void releaseTexture(std::string const& path, bool immediateErase = false);
        
        /**
         * Permet de libérer toute les textures ayant un refcount à 0
         */
        void clearUnusedTexture();
    };
}

#endif
