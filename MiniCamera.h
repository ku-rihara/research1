#pragma once
#include"struct.h"
#include"Vector2C.h"
#include"BaseCamera.h"
//前方宣言
class Camera;

class MiniCamera:public BaseCamera {
private:
	
public:

	MiniCamera();
	~MiniCamera();
	 void Init()override;
	 void Update()override;
	 void MakeCamelaMatrix()override;
	 void MakeBackCamelaMatrix()override;
};



