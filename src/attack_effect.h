/*
	Auteur : Luc Bosse
	Date : 2013-12-11
	Nom du fichier : attack_effect.h
	But : Faire les effet de lorsque tu fais un attack (Dash, Knock back)
*/
#ifndef _ATTACK_EFECT_
#define _ATTACK_EFECT_

#include "Player.h"
namespace beat {
	class attack_effect {
	public:
		virtual ~attack_effect() {
		}
		virtual void onUpdate(int delta, beat::Player* me) = 0;
		virtual void onHit(beat::Player* enemy) = 0;
		virtual void onStart() = 0;
	};
}
#endif