#include<assert.h>
#define _USE_MATH_DEFINES
#include <math.h>

#include"Function.h"

Vector2 normalize(Vector2 pos) {

	Vector2 result;

	float distance = sqrtf(pos.x * pos.x + pos.y * pos.y);
	if (distance != 0) {
		result.x = pos.x / distance;
		result.y = pos.y / distance;
	}

	else {
		result.x =0;
		result.y =0;
	}
	return result;
}

Vector2 normalize(Vector2 objPos1, Vector2 objPos2) {

	Vector2 result;
	Vector2 objDistance;

	objDistance.x = objPos1.x - objPos2.x;
	objDistance.y = objPos1.y - objPos2.y;

	float c = sqrtf(objDistance.x * objDistance.x + objDistance.y * objDistance.y);

	if (c != 0) {
		result.x = objDistance.x / c;
		result.y = objDistance.y / c;
	}
	else {
		result.x = 0;
		result.y = 0;
	}
	return result;
}

float Length(Vector2 posA, Vector2 posB) {

	float x = posA.x - posB.x;
	float y = posA.y - posB.y;

	return sqrtf(x * x + y * y);
}

float Length(Vector2 posA) {

	float c = sqrtf(posA.x * posA.x + posA.y * posA.y);

	return c;
}

float MAX(float a, float b) {

	if (a > b) {
		return	a;
	}

	else {
		return b;
	}
}
float Clamp(float n, float min, float max) {
	if (n > max) {
		return max;
	}
	if (n < min) {
		return min;
	}
	return n;
}

float Dot(Vector2 obj1, Vector2 obj2) {
	return obj1.x * obj2.x + obj1.y * obj2.y;
}


void  CircleColligion(Vector2 posA, Vector2 posB,float radA,float radB,bool&isColligion) {
	
	float distance;

	float x = posA.x - posB.x;
	float y = posA.y - posB.y;

	distance= sqrtf(x * x + y * y);

	if (distance <= radA + radB) {
		isColligion = true;
	}

}
