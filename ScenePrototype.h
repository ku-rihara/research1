#pragma once

#include "BaseScene.h"

#include"Player.h"
#include"mapchip.h"
#include"Camera.h"
#include "MiniCamera.h"
#include"BackGround.h"
#include"Monitor.h"

class ScenePrototype:public BaseScene{
private:
	Player* player_;
	Mapchip* mapchip_;
	Camera* camera_;
	MiniCamera* miniCamera_;
	BackGround* backGround_;
	Monitor* monitor_;
public:
	ScenePrototype();//コンストラクタ
	//Function
	void Init()override;
	void Update()override;
	void Draw()override;
};

