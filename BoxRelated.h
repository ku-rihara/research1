#pragma once
#include<Novice.h>
#include "struct.h"

float RightSide(float PosX, float SizeX);

float LeftSide(float PosX, float SizeX);

float UpSide(float PosY, float SizeY);

float LowerSide(float PosY, float SizeY);

bool isBoxColligion(Vector2 obj1_LeftTop, Vector2  obj1_RightBottom, Vector2 obj2_LeftTop, Vector2 obj2_RightBottom);

bool isInBox(Vector2 pos1, Vector2 size1, Vector2 pos2, Vector2 size2);

Vertex MakeLoalVertex(Vector2 size);

Vertex MakeLoalVertex(float size);

void newDrawQuad(Vertex VerTex, float startx, float starty, float DrawWidth, float DrawHeigth, int Handle, int Color);



