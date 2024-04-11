#pragma once
#include"BaseMiniCamera.h"

//ƒ~ƒjƒJƒƒ‰‚Ì”
const int miniCameraNum=1;
const int objNum = 3;

class MiniCamera:public BaseMiniCamera{
public:
	BaseMiniCamera* miniCamera_[miniCameraNum][objNum];
public:

	MiniCamera(Vector2 worldPos, Vector2 monitorPos, Vector2 size);
	~MiniCamera();
	void Init(Vector2 worldPos, Vector2 monitorPos, Vector2 size)override;
	void MakeCamelaMatrix()override;



};

