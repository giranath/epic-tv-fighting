/**
 * FICHIER: State.h
 * PROJET:  TP3
 * AUTHEUR: Nathan Giraldeau
 *
 * DESCRIPTION;
 *     Classe virtuelle représentant un état dans un "finite-state-machine"
 */

#ifndef __TP3__State__
#define __TP3__State__

#include <iostream>

namespace beat {
    class State {
    public:
        /**
         * Constructeur
         */
        State();
        
        /**
         * Destructeur
         */
        virtual ~State();
        
    protected:
        /**
         * Appelée la première fois
         */
        virtual void onStart() = 0;
        
        /**
         * Appelée chaque frame
         */
        virtual void onUpdate(unsigned int delta) = 0;
        
        /**
         * Appelée à la fermeture de l'état
         */
        virtual void onClose() = 0;
    };
}
#endif
