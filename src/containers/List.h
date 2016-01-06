/*
 *  FICHIER: List.h
 *  PROJET:  List
 *
 *  AUTHEUR: Nathan Giraldeau
 *  DATE:    2013-11-20
 *  DESCRIPTION:
 *      Impl�mentation d'une liste et de son it�rateur
 *
 */

#ifndef List_List_h
#define List_List_h

#include <assert.h>

namespace cegep {
    template <typename TYPE>
    class list;
    
    template <typename TYPE>
    class cell {
        friend class list<TYPE>;
        
        TYPE element;
        cell<TYPE> *next;
        cell<TYPE> *previous;
        
        /**
         * Constructeur de cellule
         */
        cell(const TYPE& e, cell<TYPE> *p = 0, cell<TYPE> *n = 0) {
            element = e;
            next = n;
            previous = p;
        }
    };
    
    template<typename TYPE>
    class list {
    private:
        cell<TYPE> *_first;
        
        /**
         * Copieur d�sactiv�
         */
        list(const list<TYPE> &l);
        
        /**
         * Retourne l'arri�re d'une liste
         */
        cell<TYPE>* BACK() const;
        
        /**
         * Retourne le devant d'une liste
         */
        cell<TYPE>* FRONT() const;
    public:
        
        /**
         * Un it�rateur permet de manipuler une liste de mani�re s�curitaire
         */
        class iterator {
            friend class list;
        private:
            cell<TYPE>* _current;
            const list<TYPE>* _list;
            
            /**
             * Constructeur avec param�tres
             */
            iterator(cell<TYPE>* cell, list<TYPE>* list);
            
        public:
            /**
             * Constructeur
             */
            iterator();
            
            /**
             * Destructeur
             */
            ~iterator();
            
            /**
             * Assignateur
             */
            const iterator& operator=(const iterator& I);
            
            /**
             * Compare si deux it�rateur pointe vers le m�me �l�ment
             */
            bool operator==(const iterator	& I)const;
            bool operator!=(const iterator& I)const;
            
            /**
             * Permet de d�placer le curseur vers la "droite"
             */
            iterator operator++(int i);
            const iterator& operator++();
            
            /**
             * Permet de d�placer le curseur vers la "gauche"
             */
            iterator operator--(int i);
            const iterator& operator--();
            
            /**
             * Permet d'acceder � l'�l�ment point�
             */
            TYPE& operator*();
            const TYPE& operator*()const;
        };
        
        /**
         * Constructeur
         */
        list(void);
        
        /**
         * Destructeur
         */
		virtual ~list(void);
        
        /**
         * Efface le contenu d'une liste
         */
		void clear();
		
        /**
         * Informe si la liste est vide
         */
        bool empty() const;
        
        /**
         * Retourne un it�rateur vers le d�but
         */
        iterator begin() const;
        
        /**
         * Retourne un it�rateur vers la fin
         */
        iterator end() const;
        
        /**
         * Ins�re un �l�ment � un endroit donn�
         */
        iterator insert(iterator I, const TYPE& e);
        
        /**
         * Efface un �l�ment � un endroit pr�cis
         */
        iterator erase (iterator I);
        
        /**
         * Efface les �l�ments situ�s entre les deux it�rateurs
         */
        iterator erase (iterator first, iterator last);
        
        /**
         * Retourne l'�l�ment contenu � un it�rateur donn�e
         */
        TYPE& operator[](const iterator & I);
        const TYPE& operator[](const iterator& I) const;
        
        /**
         * Recherche un �l�ment et retourne la position
         */
        iterator operator()(const TYPE&)const;
        iterator operator()(const TYPE&, iterator)const;
        
        /**
         * Copie une liste dans une autre
         */
        const list<TYPE>& operator=(const list<TYPE>& l);
    };
    
    // Impl�mentation de l'it�rateur
    template<class TYPE>
    list<TYPE>::iterator::iterator() {
        _current = 0;
        _list = 0;
    }
    
    template<class TYPE>
    list<TYPE>::iterator::iterator(cell<TYPE>* cell, list<TYPE>* list) {
        _current = cell;
        _list = list;
    }
    
    template<class TYPE>
    list<TYPE>::iterator::~iterator() {
        _current = 0;
        _list = 0;
    }
    
    template<class TYPE>
    const typename list<TYPE>::iterator& list<TYPE>::iterator::operator=(const iterator& I) {
        this->_current = I._current;
        this->_list = I._list;
        
        return *this;
    }
    
    template<class TYPE>
    bool list<TYPE>::iterator::operator==(const iterator& I)const {
        assert(_list != 0);
        assert(_list == I._list);
        
        return _current == I._current;
    }
    
    template<class TYPE>
    bool list<TYPE>::iterator::operator!=(const iterator& I)const {
        return !this->operator==(I);
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::iterator::operator++(int i) {
        assert(_list != 0);
        assert(_current != 0);
        
        iterator it = *this;
        
        _current = _current->next;
        
        return it;
    }
    
    template<class TYPE>
    const typename list<TYPE>::iterator& list<TYPE>::iterator::operator++() {
        assert(_list != 0);
        assert(_current != 0);
        
        _current = _current->next;
        
        return *this;
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::iterator::operator--(int i) {
        assert(_list != 0);
        assert(_current != _list->_first);
        
        iterator it = *this;
        
        if(_current == 0) {
            _current = _list->_first->previous;
        }
        else {
            _current = _current->previous;
        }
        
        return it;
    }
    
    template<class TYPE>
    const typename list<TYPE>::iterator& list<TYPE>::iterator::operator--() {
        assert(_list != 0);
        assert(_current != _list->_first);
        
        if(_current == 0) {
            _current = _list->_first->previous;
        }
        else
            _current = _current->previous;
        
        return *this;
    }
    
    template<class TYPE>
    TYPE& list<TYPE>::iterator::operator*() {
        assert(_current != 0);
        
        return _current->element;
    }
    
    template<class TYPE>
    const TYPE& list<TYPE>::iterator::operator*()const {
        assert(_current != 0);
        
        return _current->element;
    }
    
    // Impl�mentation de la liste
    template<class TYPE>
    cell<TYPE>* list<TYPE>::BACK() const {
        return _first->previous;
    }
    
    template<class TYPE>
    cell<TYPE>* list<TYPE>::FRONT() const {
        return _first;
    }
    
    template<class TYPE>
    list<TYPE>::list(void) {
        _first = 0;
    }
    
    template<class TYPE>
    list<TYPE>::~list(void) {
        clear();
    }
    
    template<class TYPE>
    void list<TYPE>::clear() {
        for(iterator it = begin(); it != end(); it++) {
            erase(it);
        }
        
        _first = 0;
    }
    
    template<class TYPE>
    bool list<TYPE>::empty() const {
        return _first == 0;
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::begin() const {
        iterator it;
        it._current = _first;
        it._list = this;
        
        return it;
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::end() const {
        iterator it;
        it._current = 0;
        it._list = this;
        
        return it;
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::insert(iterator I, const TYPE& e) {
        // On s'assure que l'it�rateur correspond � la liste actuelle
        assert(I._list == this);
        
        // Si l'it�rateur pointe sur le premier �l�ment
        if(I._current == _first) {
            if(_first != 0) {
                cell<TYPE>* temp = _first;
                
                _first = new cell<TYPE>(e, _first->previous, _first);
                
                temp->previous = _first;
            }
            else {
                _first = new cell<TYPE>(e);
                _first->previous = _first;
            }
            
            return begin();
        }
        // Si l'it�rateur pointe sur null, cela veut signifier qu'il pointe vers la fin
        else if(I._current == 0) {
            // On cr�e une nouvelle cellule son next doit �tre nul est le pr�vious, l'ancien dernier
            cell<TYPE> *newCell = new cell<TYPE>(e, _first->previous);
            
            // L'ancien dernier pointe dor�navant sur newCell
            _first->previous->next = newCell;
            _first->previous = newCell;
            
            return iterator(_first->previous, this);
        }
        // Si l'it�rateur n'est pas sur la fin ou le d�but
        else {
            cell<TYPE>* newCell = new cell<TYPE>(e, I._current->previous, I._current);
            
            I._current->previous->next = newCell;
            I._current->previous = newCell;
            
            return iterator(newCell, this);
        }
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::erase(iterator I) {
        assert(I._list == this);
        assert(_first != 0);
        
        // Si on supprime le premier
        if(I._current == _first) {
            cell<TYPE>* temp = _first;
            //_first->previous->next = _first->next;
            
            if(_first->next != 0)
                _first->next->previous = _first->previous;
            
            _first = _first->next;
            delete temp;
            
            return begin();
        }
        // Si on est sur le dernier
        else if(I._current->next == 0) {
            // On garde un pointeur sur le dernier �lement
            cell<TYPE>* temp = _first->previous;
            _first->previous = temp->previous;
            temp->previous->next = 0;
            
            delete temp;
            
            return end();
        }
        // Sinon pour tous les autres
        else {
            cell<TYPE>* temp = I._current;
            
            iterator tempIt(I._current->next, this);
            
            I._current->previous->next = I._current->next;
            
            if(I._current->next != 0)
                I._current->next->previous = I._current->previous;
            else
                _first->previous = I._current->previous;
            
            delete temp;
            
            return tempIt;
        }
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::erase(iterator first, iterator last) {
        assert(first._list == this && last._list == this);
        iterator it = first;
        
        while(it != last) {
            it = erase(it);
        }
        
        return it;
    }
    
    template<class TYPE>
    TYPE& list<TYPE>::operator[](const iterator & I) {
        assert(I._list == this);
        assert(I._current != 0);
        
        return I._current->element;
    }
    
    template<class TYPE>
    const TYPE& list<TYPE>::operator[](const iterator& I) const {
        assert(I._list == this);
        assert(I._current != 0);
        
        return I._current->element;
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& element) const {
        for(iterator it = begin(); it != end(); it++) {
            if(*it == element)
                return it;
        }
        
        return end();
    }
    
    template<class TYPE>
    typename list<TYPE>::iterator list<TYPE>::operator()(const TYPE& element, iterator it) const {
        for(iterator it2 = it; it2 != end(); it2++) {
            if(*it2 == element)
                return it2;
        }
        
        return end();
    }
    
    template<class TYPE>
    const list<TYPE>& list<TYPE>::operator=(const list<TYPE>& l) {
        // On s'assure qu'il ne s'agit pas d'une assignation � soi-m�me
        if(&l == this)
            return *this;
        
        // On efface le contenu d�j� pr�sent
        clear();
        
        // Si la liste � copier est vide, on s'arr�te ici
        if(l.empty())
            return *this;
        
        for(iterator it = l.begin(); it != l.end(); it++) {
            insert(end(), *it);
        }
        
        // On retourne la liste apr�s assignation
        return *this;
    }
};



#endif
