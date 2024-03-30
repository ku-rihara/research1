#pragma once

#include"struct.h"


Vector2 normalize(Vector2 pos);

Vector2 normalize(Vector2 objPos1, Vector2 objPos2);

float Length(Vector2 posA, Vector2 posB);

float Length(Vector2 posA);

float MAX(float a, float b);

float Clamp(float n, float min, float max);

float Dot(Vector2 obj1,Vector2 obj2);

void  CircleColligion(Vector2 posA, Vector2 posB, float radA, float radB, bool& isColligion);