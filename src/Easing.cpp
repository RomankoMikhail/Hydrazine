#include "Easing.hpp"

float easeLinear(const float & t) {
	return t;
}

float easeQuadIn(const float & t) {
	return t * t;
}

float easeQuadOut(const float & t) {
	return -(t * (t - 2.0f));
}

float easeQuadInOut(const float & t) {
	if (t < 0.5) {
		return 2 * t * t;
	} else {
		return (-2 * t * t) + (4 * t) - 1;
	}
}

float easeCubeIn(const float & t) {
	return t * t * t;
}

float easeCubeOut(const float & t) {
	float f = (t - 1);
	return f * f * f + 1;
}

float easeCubeInOut(const float & t) {
	if (t < 0.5) {
		return 4 * t * t * t;
	} else {
		float f = ((2 * t) - 2);
		return 0.5 * f * f * f + 1;
	}
}

float easeSineIn(const float & t) {
	return sinf((t - 1) * M_PI_2) + 1;
}

float easeSineOut(const float & t) {
	return sinf(t * M_PI_2);
}

float easeSineInOut(const float & t) {
	return 0.5f * (1.0f - cosf(t * M_PI));
}
