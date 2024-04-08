#pragma once
#include"BaseObj.h"

class Camera;

class BackGround:public BaseObj{
private:
	Camera* camera_;
	//画像ハンドル
	GH texture_;
public:
	BackGround();
	~BackGround();
	void Init()override;
	void Update();
	void Draw();

};

