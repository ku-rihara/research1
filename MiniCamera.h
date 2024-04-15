#pragma once
#include"BaseMiniCamera.h"

const int miniCameraNum=1;//ミニカメラの数
const int objNum = 3;//オブジェクト数

//前方宣言
class Player;
class Mapchip;
class BackGround;

class MiniCamera:public BaseMiniCamera{
public:
	Player* player_;
	Mapchip* mapchip_;
	BackGround* backGround_;
	BaseMiniCamera* miniCamera_[miniCameraNum][objNum];
public:

	MiniCamera(Vector2 monitorPos);
	~MiniCamera();
	void Init()override;
	void MakeCamelaMatrix()override;



};

