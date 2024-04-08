#include<Novice.h>
#include "BaseMiniCamera.h"
//function
#include"Matrix3x3.h"

BaseMiniCamera::BaseMiniCamera() {
	Init();
}

BaseMiniCamera::~BaseMiniCamera() {

}

void BaseMiniCamera::Init() {
	worldPos_ = {};
	zoomLevel_ = { 1,1 };
	worldMatrix_ = {};
	viewMatrix_ = {};
	orthoMatrix_ = {};
	viewportMatrix_ = {};

}
void BaseMiniCamera::MakeCamelaMatrix() {

	worldMatrix_ = MakeAffineMatrix(zoomLevel_, 0, worldPos_);
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(0, 0, 1280, 720);
	viewportMatrix_ = MakeViewwportmatrix(0, 0, 1280, 720);
}
