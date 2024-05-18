#pragma once
#include"BaseCamera.h"

class Camera:public BaseCamera {
private:

	
	
public:
	Camera();
	~Camera();
	void Init()override;
	void Update(const Player& player, const Mapchip& mapchip, Vector2 startPos, Vector2 endPos)override;
	void MakeCamelaMatrix(bool isZoomRock)override;
	void MakeBackCamelaMatrix()override;
	/*void ZoomOut();
	void ZoomIn();*/
};

