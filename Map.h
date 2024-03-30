#pragma once

#include"struct.h"

Vector2 LeftTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 LeftBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 RightTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2 RightBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size);

Vector2i fitMapSize(Vector2 worldPos, Vector2 oldWorldPos, float mapSize);

