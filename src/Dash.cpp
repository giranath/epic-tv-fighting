#include "Dash.h"
#include <math.h>

namespace beat {
	dash::dash() {
	}
	dash::dash(int timeLenght, float depx, float depy) {
		_timeLenght = timeLenght;
		_deplacement.x = depx;
		_deplacement.y = depy;
	}
	dash::~dash() {
	}

	void dash::onUpdate(int delta, beat::Player* me) {
		if(x == 0) {
            // On récupère la direction du "dash"
			if(me->getDirection() == Actor::DIRECTION_RIGHT)
				x = 1;
			else
				x = -1;
        }

        // On récupère la vitesse
		x *= ((float)_deplacement.x / (float)_timeLenght);
		y = ((float)_deplacement.y / (float)_timeLenght);

		if(_elapsedTime < _timeLenght)
			me->getBoxBody()->setVelocity(sf::Vector2f(x, y + me->getBoxBody()->getVelocity().y));
		else
			me->getBoxBody()->setVelocity(sf::Vector2f(0,me->getBoxBody()->getVelocity().y));
		_elapsedTime += delta;
        
		x /= abs(x);
	}
	
	void dash::onHit(beat::Player* enemy) {
	}
    
	void dash::onStart() {
		_elapsedTime = 0;
		x = 0;
	}
}