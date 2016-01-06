/**
 * PROJET: Stack_Overflow
 * FICHIER: Stack.h
 * AUTHEUR: Nathan Giraldeau
 *
 * DATE: 11 octobre 2013
 * DESCRIPTION: 
 * Implémentation d'un conteneur de type pile (LIFO)
 */


#ifndef __Stack_Overflow__Stack__
#define __Stack_Overflow__Stack__
#include <assert.h>

/*
 * DÉFINIR RECURSIVE_STACK permet de compiler la classe en mode récursive (Affectateur, comparaison==)
 */
#define RECURSIVE_STACK

namespace cegep {
	template <class TYPE>
	class Stack {
	private:
		// Constructeur de copie désactivé
		Stack(Stack const& copy) {										
		}
		
	protected:
		struct StackCell {																// Définition d'une structure interne représenteant une couche de la pile
			TYPE element;																		// L'élément sauvegardé
			StackCell* next;																// L'élément stocket "en dessous"
			
			StackCell(const TYPE& e, StackCell* n) {				// Petit constructeur pour rendre le code plus lisible
				element = e;
				next = n;
			}
		};
		
		StackCell* _top;																	// Pointe vers le premier élément de la pile
		unsigned int _size;																// Taille de la pile
		
	public:	
		// Constructeur de pile
		Stack() {															
			_size = 0;
			_top = 0;
		}
		
		// Affectateur
		Stack const& operator=(Stack const& other) {
			if(&other == this)
				return *this;
			
			this->clear();
			
			_size = other._size;														// On modifie la taille
			
			if(_size == 0)
				return *this;
			
			_top = new StackCell(other._top->element, 0);
			
			#ifdef RECURSIVE_STACK													// La façon récursive
				empiler(_top, other._top->next);
			#else																						// La façon itérative
				StackCell *tempA = _top, 
									*tempB = other._top->next;
			
				while(tempB != 0) {														// Tant qu'on a pas parcouru toute la seconde pile
					StackCell* newCell = new StackCell(tempB->element, 0);
					tempA->next = newCell;
					
					tempA = tempA->next;												// Itération
					tempB = tempB->next;
				}
			#endif
			
			return *this;
		}
		
		// Méthode récursive permettant la copie récursivement
		void empiler(StackCell *stackIterator1, StackCell *stackIterator2) {
			if(stackIterator2 == 0) return;
			
			StackCell* newCell = new StackCell(stackIterator2->element, 0);	
			stackIterator1->next = newCell;
			
			return empiler(stackIterator1->next, stackIterator2->next);
		}
		
		// Destructeur
		virtual ~Stack() {												
			this->clear();
		}
		
		// Efface le contenu de la pile
		void clear() {																		
			while(!isEmpty()) {
				this->pop();
			}
		}
		
		// Place un nouvel élément sur le dessus de la pile
		void push(TYPE const& value) {
			_top = new StackCell(value, _top);
			_size++;
		}
		
		// Retire le premier élément de la pile
		void pop() {
			assert(!isEmpty());
			
			StackCell* temp = _top->next;
			delete _top;
			_top = temp;
			_size--;
		}
		
		// Retourne le dessus de la pile
        TYPE& top() const {
			return _top->element;
		}
		
		// Indique si la pile est vide
		bool isEmpty() const {
			return _top == 0;
		}
		
		// Retourne la taille
		unsigned int getSize() const {
			return _size;
		}
		
		// Opérateur de comparaison
		bool operator==(Stack const& other) const {
			if(_size != other._size)												// Si les deux stacks n'ont pas la même taille alors ils sont différent
				return false;
			
			#ifdef RECURSIVE_STACK
				return areTheSame(_top, other._top);
			#else
				StackCell *cellA = _top, *cellB = other._top;		// Deux pointeurs qui permettront de parcourir les piles
				
				while(cellA != 0) {									// Puisque les deux ont la même taille, on vérifie qu'un seul des pointeurs n'atteigne pas 0
					if(cellA->element != cellB->element)			// Si les deux éléments sont différent on retourne faux
						return false;
					
					cellA = cellA->next;							// Sinon on repointe les pointeurs vers les suivants
					cellB = cellB->next;
				}
			#endif
			return true;
		}
		
	private:
		// Fonction amie permettant une comparaison récursive
		friend bool areTheSame(StackCell* it1, StackCell* it2) {
			if(it1 == 0 && it2 == 0)
				return true;
			
			if(it1 == 0 || it2 == 0)
				return false;
			
			
			return it1->element == it2->element && areTheSame(it1->next, it2->next);
		}
	};
};

#endif 
