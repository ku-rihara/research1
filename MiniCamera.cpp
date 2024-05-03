#include<Novice.h>
#include "MiniCamera.h"
//function
#include"Matrix3x3.h"
#include"BoxRelated.h"
#include"Camera.h"

MiniCamera::MiniCamera() {

}

MiniCamera::~MiniCamera() {

}

void MiniCamera::Init() {
	BaseCamera::Init();
	viewprot_ = { 0,0,640,320 };
}
void MiniCamera::MakeCamelaMatrix() {
	BaseCamera::MakeCamelaMatrix();

	/*worldMatrix_ = MakeAffineMatrix(Camera::zoomLevel_, 0, Camera::worldPos_);
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(0, 0, 1280, 720);
	viewportMatrix_ = MakeViewwportmatrix(monitorPos_.x, monitorPos_.y, 1280.0f/2, 720.0f/2);*/
}

//void MiniCamera::MakeBackCamelaMatrix() {
//	if (zoomLevel_.x <= 1.0f && zoomLevel_.y <= 1.0f) {
//		worldMatrix_ = MakeAffineMatrix(zoomLevel_, 0, backPos_);
//	}
//	else {
//		worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0, backPos_);
//	}
//	viewMatrix_ = InverseMatrix(worldMatrix_);
//	orthoMatrix_ = MakeOrthographicMatrix(-640, -360, 640, 360);
//	viewportMatrix_ = MakeViewwportmatrix(0, 0, 1280, 720);
//}

//void MiniCamera::RenderingPipeline() {
//	matrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
//	wvpVpMatrix_ = wvpVpMatrix(matrix_, camera_->GetViewMatrix(), camera_->GetOrthoMatrix(), camera_->GetViewportMatrix());
//	screenVertex_ = Transform(localVertex_, wvpVpMatrix_);
//}