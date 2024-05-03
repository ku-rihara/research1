#pragma once
#include"BaseObj.h"

class Player:public BaseObj{
private:
	
	DIRECTION direction_;
	GH texture_;
public:
	Player();//コンストラクタ
	~Player();//デストラクタ

	void Init()override;
	void Update();
	void Draw();
	void MiniDraw();
	//その他関数
	void Move();
	void RenderingPipeline()override;
	void MiniRenderingPipeline()override;
	void MapChipColligion()override;

};

