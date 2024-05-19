#pragma once
#include"BaseObj.h"

class Player:public BaseObj{
private:
	
	GH texture_;
	GH directionRight_;
	GH directionLeft_;
	DIRECTION direction_;
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
	void DrawRangeCut(Vector2 scrollpos, float viewportWidth, float viewportHeight);
	void MapChipColligion()override;

};

