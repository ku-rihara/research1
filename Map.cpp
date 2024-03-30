#include<Novice.h>

#include"Map.h"
#include"Function.h"

Vector2 LeftTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) - (heigth / 2)) / size;
	mapnum.x = ((worldpos.x * zoomScale) - (width / 2)) / size;

	return mapnum;
}

Vector2 LeftBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) + (heigth / 2 - 1)) / size;
	mapnum.x = ((worldpos.x * zoomScale) - (width / 2)) / size;

	return mapnum;
}

Vector2 RightTopMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) - (heigth / 2)) / size;
	mapnum.x = ((worldpos.x * zoomScale) + (width / 2 - 1)) / size;

	return mapnum;
}

Vector2 RightBottomMapNum(Vector2 worldpos, float zoomScale, float heigth, float width, float size) {

	Vector2 mapnum;

	mapnum.y = ((worldpos.y * zoomScale) + (heigth / 2 - 1)) / size;
	mapnum.x = ((worldpos.x * zoomScale) + (width / 2 - 1)) / size;

	return mapnum;
}

Vector2i fitMapSize(Vector2 worldPos, Vector2 oldWorldPos, float mapSize) {
	Vector2i fitMapSizePos;
	Vector2 maxPos;

	maxPos.x = MAX(worldPos.x, oldWorldPos.x);
	maxPos.y = MAX(worldPos.y, oldWorldPos.y);

	fitMapSizePos.intx = int(maxPos.x / (mapSize / 2));
	fitMapSizePos.intx = int(fitMapSizePos.intx * (mapSize / 2));

	fitMapSizePos.inty = int(maxPos.y / (mapSize / 2));
	fitMapSizePos.inty = int(fitMapSizePos.inty * (mapSize / 2));

	return fitMapSizePos;
}

