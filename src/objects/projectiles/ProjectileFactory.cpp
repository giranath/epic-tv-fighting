/**
 * FICHIER: ProjectileFactory
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 */

#include "ProjectileFactory.h"

namespace beat {
    TextureManager* ProjectileFactory::_textureManager = 0;
    
    Guntherken* ProjectileFactory::createGuntherKen(Object* sender, sf::Vector2f relativePosition, sf::Vector2f initialVelocity) {
        Guntherken* g = new Guntherken(sender);
        
        if(_textureManager != 0) {
            g->setTextureHandler(_textureManager->getHandler("graphics/projectiles/guntherken2.png"));
        }
        
        g->setPosition(sender->getPosition().x + relativePosition.x, sender->getPosition().y + relativePosition.y);
        g->setVelocity(initialVelocity.x, initialVelocity.y);
        
        return g;
    }

	prinnyHat*  ProjectileFactory::createPrinnyHat(Object* sender, sf::Vector2f relativePosition, sf::Vector2f initialVelocity) {
        prinnyHat* g = new prinnyHat(sender);
        
        //if(_textureManager != 0) {
        //    g->setTextureHandler(_textureManager->getHandler("guntherken2.png"));
        //}
        
        g->setPosition(sender->getPosition().x + relativePosition.x, sender->getPosition().y + relativePosition.y);
        g->setVelocity(initialVelocity.x, initialVelocity.y);
        
        return g;
    }
    
    void ProjectileFactory::setTextureManager(TextureManager* textureManager) {
        _textureManager = textureManager;
    }
}