#pragma once
#include"BaseCamera.h"

class Camera:public BaseCamera {
private:

	
	
public:
	Camera();
	~Camera();
	void Init()override;
	void Update()override;
	void MakeCamelaMatrix()override;
	void MakeBackCamelaMatrix()override;
	/*void ZoomOut();
	void ZoomIn();*/
};

