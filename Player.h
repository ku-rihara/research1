#pragma once
#include"BaseObj.h"

//前方宣言
class Mapchip;

class Player:public BaseObj{
private:
	Mapchip* mapchip_;
	DIRECTION direction_;
	GH texture_;
public:
	Player();//コンストラクタ
	~Player();//デストラクタ

	void Init()override;
	void Update();
	void Draw();
	//その他関数
	void Move();
	void RenderingPipeline()override;
	void MapChipColligion()override;
};

