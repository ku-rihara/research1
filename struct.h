#pragma once
#include"Vector2C.h"

struct Vector2i {
	int intx;
	int inty;
};

struct Vertex {
	Vector2 LeftTop;
	Vector2 RightTop;
	Vector2 LeftBottom;
	Vector2 RightBottom;
};

struct Matrix3x3 {

	float m[3][3];
};

struct Easing {
	bool isEasing;
	float easingTime;
	float easingIncrement;
	int easingCollTime;

};


struct Particle {
	Vector2 Pos;
	Vector2 direction;
	Vector2 velocity;
	float theta;
	int currentTime;
	bool isStart;
};


struct Emitter {
	Vector2 spownPos;
	Vector2 velocity;
	float direction;
	float theta;
	int lifeTime;
};

struct SE {
	int handle;
	int voiceHandle;
	bool isStart;
};

struct GH {
	int Handle;
};


enum DIRECTION {
	LEFT,
	RIGHT,
};

const float zoomOutMax = 1.49f;