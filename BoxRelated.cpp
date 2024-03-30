#include "BoxRelated.h"


float RightSide(float PosX, float SizeX) {
	return PosX + (SizeX / 2 - 1);
}

float LeftSide(float PosX, float SizeX) {
	return PosX - (SizeX / 2);
}

float UpSide(float PosY, float SizeY) {
	return PosY - (SizeY / 2);
}

float LowerSide(float PosY, float SizeY) {
	return PosY + (SizeY / 2 - 1);
}

bool isBoxColligion(Vector2 obj1_LeftTop, Vector2  obj1_RightBottom, Vector2 obj2_LeftTop, Vector2 obj2_RightBottom) {

	if (obj1_LeftTop.x<obj2_RightBottom.x && obj1_RightBottom.x>obj2_LeftTop.x && obj1_LeftTop.y<obj2_RightBottom.y && obj1_RightBottom.y>obj2_LeftTop.y) {
		return true;
	}
	else {
		return false;
	}
}

bool isInBox(Vector2 pos1, Vector2 size1, Vector2 pos2, Vector2 size2)
{
	if (pos1.x >= pos2.x
		&& pos1.x + size1.x <= pos2.x + size2.x
		&& pos1.y >= pos2.y
		&& pos1.y + size1.y <= pos2.y + size2.y)
	{
		return true;
	}
	return false;
}

Vertex MakeLoalVertex(Vector2 size) {
	Vertex vertex;

	vertex.LeftTop.x = size.x;
	vertex.RightTop.x = size.x;
	vertex.LeftBottom.x = size.x;
	vertex.RightBottom.x = size.x;
	vertex.LeftTop.y = size.y;
	vertex.RightTop.y = size.y;
	vertex.LeftBottom.y = size.y;
	vertex.RightBottom.y = size.y;

	return vertex;
}

Vertex MakeLoalVertex(float size) {
	Vertex vertex;

	vertex.LeftTop.x = size;
	vertex.RightTop.x = size;
	vertex.LeftBottom.x = size;
	vertex.RightBottom.x = size;
	vertex.LeftTop.y = size;
	vertex.RightTop.y = size;
	vertex.LeftBottom.y = size;
	vertex.RightBottom.y = size;

	return vertex;
}

void newDrawQuad(Vertex VerTex, float startx, float starty, float DrawWidth, float DrawHeigth, int Handle, int Color) {

	Novice::DrawQuad(int(VerTex.LeftTop.x), int(VerTex.LeftTop.y), int(VerTex.RightTop.x), int(VerTex.RightTop.y), int(VerTex.LeftBottom.x), int(VerTex.LeftBottom.y), int(VerTex.RightBottom.x), int(VerTex.RightBottom.y), int(startx), int(starty), int(DrawWidth), int(DrawHeigth), Handle, Color);
}

