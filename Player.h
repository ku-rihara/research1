#pragma once
#include"BaseObj.h"
class Player:public BaseObj{
private:

public:
	Player();//コンストラクタ
	~Player();//デストラクタ

	void Init()override;
	void Update();
	void Draw();
	void RenderingPipeline()override;
};

