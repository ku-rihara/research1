#pragma once
#include"BaseMiniCamera.h"

const int miniCameraNum=1;//�~�j�J�����̐�
const int objNum = 3;//�I�u�W�F�N�g��

//�O���錾
class Player;
class Mapchip;
class BackGround;

class MiniCamera:public BaseMiniCamera{
public:
	BaseMiniCamera* miniCamera_[miniCameraNum][objNum];
public:

	MiniCamera(Vector2 monitorPos);
	~MiniCamera();
	void Init()override;
	void MakeCamelaMatrix()override;



};

