﻿#pragma once

#include "BaseScene.h"

#include"Player.h"
#include"mapchip.h"
#include"Camera.h"
#include"BackGround.h"

class ScenePrototype:public BaseScene{
private:
	Player* player_;
	Mapchip* mapchip_;
	Camera* camera_;
	BackGround* backGround_;
public:
	ScenePrototype();//コンストラクタ
	//Function
	void Init()override;
	void Update()override;
	void Draw()override;
};
