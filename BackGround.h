#pragma once
#include"BaseObj.h"

class Camera;

class BackGround :public BaseObj {
private:

	//画像ハンドル
	GH texture_;
public:
	BackGround();
	~BackGround();
	void Init()override;
	void Update();
	void Draw();
	void MiniDraw();
	void RenderingPipeline()override;
	void MiniRenderingPipeline()override;
    void BackGroundDrawRangeCut(Vector2 centerPos, Vector2 zoomLevel, float viewportWidth, float viewportHeight)override;
};

