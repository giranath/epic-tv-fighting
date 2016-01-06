/*
Compatibilite entre xcode et visual studio car il n'y a pas fmax
*/

#ifndef _MATH_LUC_
#define _MATH_LUC_
#include <cmath>
float fmax(float a, float b) {
	if(a < b)
		return b;
	return a;
}

#endif