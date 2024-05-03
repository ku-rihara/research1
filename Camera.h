#pragma once
#include"BaseCamera.h"

class Camera:public BaseCamera {
private:

	
	
public:
	Camera();
	~Camera();
	void Init()override;
	void Update()override;
	void MakeCamelaMatrix();
	void MakeBackCamelaMatrix();
	/*void ZoomOut();
	void ZoomIn();*/
};

