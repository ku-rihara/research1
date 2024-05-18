#pragma once
#include"struct.h"
#include"Vector2C.h"
#include"BaseCamera.h"
//前方宣言
class Monitor;
class MiniCamera:public BaseCamera {
private:
	const  float miniLevel_=2.0f;
public:

	MiniCamera();
	~MiniCamera();
	 void Init()override;
	 void Update(const Player& player, const Mapchip& mapchip, Vector2 startPos)override;
	 void MakeCamelaMatrix(bool isZoomRock)override;
	 void MakeBackCamelaMatrix()override;
	 void CombineMonitor(const Monitor&moniyor);

	 float GetMiniLevel()const { return miniLevel_; }
};



