#ifndef _DASH_
#define _DASH_
#include "attack_effect.h"

namespace beat {
	class dash : public attack_effect {
	private:
		int _timeLenght;
		sf::Vector2f _deplacement;
		int _elapsedTime;
		float x, y;
	public:
		dash();
		dash(int timeLenght, float depx, float depy);
		virtual ~dash();

		virtual void onUpdate(int delta, beat::Player* me);
		virtual void onHit(beat::Player* enemy);
		virtual void onStart();
	};
}
#endif