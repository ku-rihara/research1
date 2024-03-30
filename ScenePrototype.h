#pragma once
#include "BaseScene.h"

class ScenePrototype:public BaseScene{
private:

public:
	ScenePrototype();//コンストラクタ
	//Function
	void Init()override;
	void Update()override;
	void Draw()override;
};

