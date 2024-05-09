#pragma once
#include"BaseObj.h"
class Monitor:public BaseObj{
private:
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

