#pragma once
#include"BaseObj.h"

class Monitor:public BaseObj{
private:
	bool isRockScreen_;
	Vector2 movePos_;
	Vector2 mapTransformedSize_;
	Vector2 drawSize_;
	GH texture_;
public:
	Monitor();//コンストラクタ
	~Monitor();//デストラクタ

	void Init()override;
	void Update();
	void Draw();

	//その他関数
	void RenderingPipeline()override;


};

