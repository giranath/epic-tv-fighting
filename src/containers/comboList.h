#ifndef _COMBOTREE_
#define _COMBOTREE_

#include "AnimationSequence.h"
#include "Dash.h"
#include "vector.h"
#include "Player.h"
#include <assert.h>
#include "Shoot.h"
#include "EmitSound.h"

namespace beat {

	class combo {
		friend class comboTree;
	private:
		AnimationSequence *_anim;
		vecteur<attack_effect*> effects;

		combo* _a1;
		combo* _a2;
		combo* _d;
		combo* _g;

		combo() {
			_anim = NULL;
			_a1 = NULL;
			_a2 = NULL;
			_d = NULL;
			_g = NULL;
		}

		combo(AnimationSequence* anim) {
			_anim = anim;
			_a1 = NULL;
			_a2 = NULL;
			_d = NULL;
			_g = NULL;
		}
	public:
		~combo() {
			for (int i = 0; i < effects.getDim(); ++i)
				delete effects[i];
		}
	};

	class comboTree {
	private:
		combo* _root;
	public:		
		class iterator {
			friend class comboTree;
		private:
			combo* _current;
			comboTree*_from;
            
		public:
			iterator() {
				_current = NULL;
				_from = NULL;
			}

			iterator(combo* current, comboTree* from) {
				_current = current;
				_from = from;
			}

			const AnimationSequence& operator*() const{
				return *(_current->_anim);
			}

			AnimationSequence& operator*() {
				return *(_current->_anim);
			}

			void onStart() {
				int i = 0;
				for(;i<_current->effects.getDim();++i)
					_current->effects[i]->onStart();
			}

			void onHit(Player* ennemy) {
				int i = 0;
				for(;i<_current->effects.getDim();++i)
					_current->effects[i]->onHit(ennemy);
			}

			void onUpdate(int delta, Player* me) {
				int i = 0;
				for(;i<_current->effects.getDim();++i)
					_current->effects[i]->onUpdate(delta, me);
			}

			bool goa1() {
				assert(_current != NULL);
				if(_current->_a1 != NULL) {
					_current = _current->_a1;
					onStart();
					return true;
                }
				return false;
			}
            
			bool goa2() {
				assert(_current != NULL);
				if(_current->_a2 != NULL) {
					_current = _current->_a2;
					onStart();
					return true;
                }
				return false;
			}
			
            bool god() {
				assert(_current != NULL);
				if(_current->_d != NULL) {
					_current = _current->_d;
					onStart();
					return true;
                }
				return false;
			}
			
            bool gog() {
				assert(_current != NULL);
				if(_current->_g != NULL) {
					_current = _current->_g;
					onStart();
					return true;
                }
				return false;
			}

			bool operator==(iterator it) {
				return (_from == it._from && _current == it._current);
			}
		};
		
		comboTree() {
			_root = NULL;
		}

		void clear(comboTree::iterator it) {
			if(it._current == NULL)
				return;
			clear(iterator(it._current->_a1, this));
			delete it._current->_a1;
			clear(iterator(it._current->_a2, this));
			delete it._current->_a2;
			clear(iterator(it._current->_d, this));
			delete it._current->_d;
			clear(iterator(it._current->_g, this));
			delete it._current->_g;
		}

		~comboTree() {
			clear(begin());
		}

		void addA1(comboTree::iterator it, AnimationSequence* anim) {
			assert(it._from == this);
			it._current->_a1 = new combo(anim);
		}
		void addA2(comboTree::iterator it, AnimationSequence* anim) {
			assert(it._from == this);
			it._current->_a2 = new combo(anim);
		}
		void addD(comboTree::iterator it, AnimationSequence* anim) {
			assert(it._from == this);
			it._current->_d = new combo(anim);
		}
		void addG(comboTree::iterator it, AnimationSequence* anim) {
			assert(it._from == this);
			it._current->_g = new combo(anim);
		}

		comboTree::iterator begin() {
			return iterator(_root, this);
		}

		void loadFromFile(std::string fileName, Player& dood) {
			std::ifstream entree;
			std::string tokken;
			comboTree::iterator it;
			int index;
			std::string who;

			entree.open(fileName.c_str());
			if(!entree)
				std::cout << "Impossible de ouvrir " << fileName << "!";


			entree >> tokken;
			while(entree.good()) {
				if(tokken == "idle:") {
					entree >> index;
					_root = new combo(&(dood.getAnimationSequence(index)));
				}
				else if(tokken == "root")
					it = begin();
				else if(tokken == "a1")
					it.goa1();
				else if(tokken == "a2")
					it.goa2();
				else if(tokken == "front")
					it.god();
				else if(tokken == "back")
					it.gog();
				else if(tokken == "seqIndex:") {
					entree >> who >> index;
					if(who == "a1") {
						it._current->_a1 = new combo(&(dood.getAnimationSequence(index)));
						it.goa1();
					}
					else if (who == "a2") {
						it._current->_a2 = new combo(&(dood.getAnimationSequence(index)));
						it.goa2();
					}
					else if (who == "front") {
						it._current->_d = new combo(&(dood.getAnimationSequence(index)));
						it.god();
					}
					else if (who == "back") {
						it._current->_g = new combo(&(dood.getAnimationSequence(index)));
						it.gog();
					}
				}

				else if(tokken == "dash:") {
					float x, y;
					int time;
					entree >> time >> x >> y;
					it._current->effects.push_back(new dash(time, x, y));
				}
                else if(tokken == "shoot:") {
                    
                    unsigned int frame;
                    unsigned int startID;
                    std::string type;
                    
                    entree >> frame >> startID >> type;
                    if(type == "guntherken")
						it._current->effects.push_back(new Shoot(frame, startID, *it._current->_anim, Shoot::GUNTHERKEN));
					else if (type == "prinnyhat")
						it._current->effects.push_back(new Shoot(frame, startID, *it._current->_anim, Shoot::PRINNYHAT));
                }
                else if(tokken == "emitSnd:") {
                    unsigned int startID;
                    std::string file;
                    
                    entree >> startID >> file;
                    
                    it._current->effects.push_back(new EmitSound(startID, file, *it._current->_anim));
                }
				entree >> tokken;
			}
		}
	};
}

#endif
