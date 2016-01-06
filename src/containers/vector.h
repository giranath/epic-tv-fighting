/*
Nom : Luc Bosse
Fichier : vecteur.h
Date :25 sept 2013
Description : Creation d'un objet vecteur avec push_back, insert, erase

*/

#ifndef _VECTEUR
#define _VECTEUR
#include <iostream>
#include<assert.h>

template <class TYPE>
class vecteur
{
protected:
	TYPE *_tab;			//pointeur sur le vecteur d’entier

	int _dim;			//dimension du vecteur
public:
	vecteur();
	vecteur(int nb);	//construit le vecteur à la dimension de nb
	virtual ~vecteur();	//destructeur essentiel avec l’allocation dynamique

	vecteur(const vecteur<TYPE>& vec);          //Copyeur

	void push_back(const TYPE& num);			//Entre une donner a fin du vecteur
	void print(std::ostream& sortie) const;     //Affiche le vecteur
	void resize(int nb);                        //Change la taille du vecteur
    TYPE& at(int pos) const;					//Return la valeur a telle place du vecteur
	TYPE& operator[](int pos) const;				//Surcharge de l'operateur comme un tableau
	void insert(int pos,const TYPE& number);	//Insert une valeur a une position
	void erase(int a, int b);					//Efface une partit du vecteur
	bool isSymetric(const vecteur<TYPE>& v) const;  //Si symetric
	void swap(vecteur<TYPE>& v);                //Change la valeure entre deux vecteurs
    void shift(int decalage);                   //Fait un decalage dans le vecteur
    void inverse();                             //Inverse la position des valeur dans le vecteur

	void clear();                               //Efface le vecteur

	int getDim() const;                         //return la taille du vecteur
	TYPE &getFront() const;                     //return la premiere valeur
	TYPE &getBack() const;                      //return la derniere valeur
    const vecteur<TYPE>& operator=(vecteur<TYPE> const& v);                               //operateur =
	vecteur<TYPE> operator+(const vecteur<TYPE>& v) const ;                         //operateur +

	vecteur<TYPE>& operator+=(const vecteur<TYPE>& v2);   //Operateur +=

	bool operator==(const vecteur<TYPE>& v) const;                                  //Si les 2 vecteur sont equivalent
};

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const vecteur<TYPE> &v);     //operateur <<


template <class TYPE>
vecteur<TYPE>::vecteur() {
    _dim = 0;
	_tab = NULL;
}

template <class TYPE>
vecteur<TYPE>::vecteur(int nb) {
	assert(nb >= 0);
	_dim = nb;
	if(nb == 0)   //Tab Null
		_tab = NULL;
	else
		_tab = new int [nb];
}

template <class TYPE>
vecteur<TYPE>::~vecteur() {
    clear();
}

template <class TYPE>
vecteur<TYPE>::vecteur(const vecteur<TYPE>& vec) {
	_dim = vec._dim;
	if(_dim > 0)
	{
		_tab = new TYPE [vec._dim];
		for(int i = 0; i < vec._dim; i++)   //Copy les element vecteur en parametre
			*(_tab+i) = *(vec._tab + i);
	}
	else
		_tab = NULL;
}

template <class TYPE>
void vecteur<TYPE>::push_back(const TYPE& num) {
    if(_dim == 0) {
        _tab = new TYPE [1];
        _dim = 1;
        *_tab = num;
        return;
    }
	TYPE *temp;
	temp = new TYPE [_dim +1];
	for(int i = 0; i < _dim; i++)   //copy le contenu de l'ancien vecteur dans le nouveau
		*(temp+i) = *(_tab+i);
	delete [] _tab;
	_tab = temp;
	*(_tab+_dim) = num;             //On met le dernier nombre
	temp = NULL;
	_dim++;
}

template <class TYPE>
void vecteur<TYPE>::print(std::ostream& sortie) const {
    if(_dim == 0 || _dim == NULL)
        return;
	for(int i = 0; i<_dim;i++)
		sortie << *(_tab+i) << " " ;
}

template <class TYPE>
void vecteur<TYPE>::resize(int nb) {
    assert(nb>=0);

	if(_dim == 0)
	{
		_dim = nb;
		_tab = new TYPE [nb];
		return;
	}

    if(nb == _dim)      //Si on resize au meme nombre
        return;
    if(nb == 0) {       //Si on resize a 0
        clear();
        return;
    }
    TYPE *temp = _tab;
	_tab = new TYPE[nb];

	for(int i = 0; i < nb; i++)
		*(_tab+i) = *(temp+i);

    if(_dim > 0)
        delete[] temp;
	_dim = nb;
}

template <class TYPE>
TYPE& vecteur<TYPE>::at(int pos) const{
	assert(pos >= 0);
	assert(pos < _dim);
	return *(_tab+pos);
}

template <class TYPE>
void vecteur<TYPE>::insert(int pos, const TYPE& number) {
	assert(pos >= 0);
	assert(pos <= _dim);
	if(pos == _dim) {
        push_back(number);
        return;
	}
	TYPE *temp = _tab;
	_tab = new TYPE[_dim+1];
	_dim++;
	for(int i = 0; i<pos;i++) //on met tout les nombre avant le insert
		*(_tab+i) = *(temp+i);
	*(_tab+pos) = number;     //insert le nombre
	for(int i = pos+1; i<_dim;i++)  //on met le reste
		*(_tab+i) = *(temp+i+pos-1);

	delete[] temp;
}

template <class TYPE>
void vecteur<TYPE>::erase(int debut, int fin) {
	assert((_dim - (fin - debut) -1) > 0);
	assert(debut >= 0 &&fin >= 0);
	assert(debut < _dim && fin < _dim);
	assert(debut <= fin);
	TYPE *temp = _tab;
	_tab = new TYPE[_dim - (fin - debut) -1];
	for(int i = 0; i < debut; i++)  //on met tout avant le erase
		*(_tab+i) = *(temp+i);
	for(int i = 0; i<_dim - fin; i++) //on met le reste apres le delete
		*(_tab+i+debut) = *(temp+i+fin+1);


	_dim = _dim - (fin - debut) -1;
	delete[] temp;
}

template <class TYPE>
void vecteur<TYPE>::swap(vecteur<TYPE>& v) {
    TYPE *temp = _tab;
    int tempDim = _dim;
    _tab = v._tab;
    v._tab = temp;
    _dim = v._dim;
    v._dim = tempDim;
}

template <class TYPE>
void vecteur<TYPE>::shift(int decalage) {
    if(_dim == 0)
        return;
    if(decalage % _dim == 0)  //on decale pas
        return;
    TYPE* temp = _tab;
    _tab = new TYPE[_dim];
    for(int i = 0; i<_dim;i++)    //on remet tout en decalage
        *(_tab+i) = *(temp + ((i+decalage)%_dim));
    delete[] temp;
}

template <class TYPE>
void vecteur<TYPE>::inverse() {
    if(_dim == 0)
        return;
	TYPE temp;
    for(int i = 0; i<_dim/2;i++)  //inverse
	{
		temp = *(_tab+i);
        *(_tab+i) = *(_tab - i + _dim - 1);
		*(_tab - i + _dim - 1) = temp;
	}

}

template <class TYPE>
void vecteur<TYPE>::clear() {
    if(_dim == 0)
        return;
	delete[] _tab;
	_dim = 0;
	_tab = NULL;
}

template <class TYPE>
int vecteur<TYPE>::getDim() const {
	return _dim;
}

template <class TYPE>
TYPE &vecteur<TYPE>::getFront() const {
    assert(_dim != 0);
	return *_tab;
}

template <class TYPE>
TYPE &vecteur<TYPE>::getBack() const {
    assert(_dim != 0);
	return *(_tab+_dim-1);
}

template <class TYPE>
TYPE& vecteur<TYPE>::operator[](int pos) const{
    return at(pos);
}

template <class TYPE>
const vecteur<TYPE>& vecteur<TYPE>::operator=(vecteur<TYPE> const& v) {
    if(this == &v)  //si ses le meme vecteur
        return *this;
    if(v._dim == 0) //si le vecteur entrant est vide
      {
        clear();
        return v;
      }
    if(_dim != 0)   //si il n'est pas zero
        clear();
    _tab = new TYPE[v._dim];
    for(int i = 0; i < v._dim;i++)  //on met le nouveau vecteur
        *(_tab+i) = *(v._tab+i);
    _dim = v._dim;
	return *this;
}

template <class TYPE>
vecteur<TYPE> vecteur<TYPE>::operator+(const vecteur<TYPE>& v) const {
    int dim = _dim + v._dim;
    if(v._dim == 0) //si le vecteur est vide
        return *this;
    if(_dim == 0)   //si le vecteur est vide
        return v;

    vecteur resultat(dim);        //resultat du +
    for(int i = 0; i < _dim;i++)  //on met le premier vecteur
        *(resultat._tab+i) = *(_tab+i);
    for(int i = _dim; i < dim;i++)  //on met le deuxieme vecteur
        *(resultat._tab+i) = *(v._tab+i-_dim);
    return resultat;
}

template <class TYPE>
vecteur<TYPE>& vecteur<TYPE>::operator+=(const vecteur<TYPE>& v2) {
    if(v2._dim == 0)  //si le vecteur est vide
        return *this;
    if(_dim==0)       //si le vecteur est vide
        return v2;

    TYPE *temp = _tab;
    _tab = new TYPE[_dim + v2._dim];

    int i;
    for(i = 0; i < _dim;i++)    //on met le premier vecteur
        *(_tab+i) = *(temp+i);
    int dim = _dim + v2._dim;
    for(i = _dim; i < dim;i++)  //on met le deuxieme vecteur
        *(_tab+i) = *(v2._tab+i-_dim);
    _dim = dim;
    delete[] temp;
    return *this;
}

template <class TYPE>
bool vecteur<TYPE>::operator==(const vecteur<TYPE>& v) const {
    if(_dim != v._dim)  //si les dimention son differente
        return false;
    if(_dim == 0)  //si il sont tout les 2 vide
        return true;
    for(int i = 0; i < _dim; i++)   //on scan toute le vecteur
        if(*(_tab+i) != *(v._tab+i))
            return false;
    return true;
}

template <class TYPE>
bool vecteur<TYPE>::isSymetric(const vecteur<TYPE>& v) const {
    if(_dim != v._dim)  //si le size est different
        return false;
    for(int i = 0; i<_dim;i++)  //on scan le vecteur
        if(*(_tab+i) != *(v._tab-i+_dim-1))
            return false;
    return true;
}

template <class TYPE>
std::ostream& operator<<(std::ostream& sortie, const vecteur<TYPE> &v) {
	v.print(sortie);
	return sortie;
}

#endif
