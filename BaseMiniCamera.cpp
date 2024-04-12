#include<Novice.h>
#include "BaseMiniCamera.h"
//function
#include"Matrix3x3.h"
#include"BoxRelated.h"
//class
#include"Camera.h"

BaseMiniCamera::BaseMiniCamera( Vector2 monitorPos) {
	camera_ = new Camera();
	monitorPos_ = monitorPos;
}

BaseMiniCamera::~BaseMiniCamera() {

}

void BaseMiniCamera::Init() {
	scale_ = { 1,1 };
	localVertex_ = MakeLoalVertex(size_);
	worldMatrix_ = {};
	viewMatrix_ = {};
	orthoMatrix_ = {};
	viewportMatrix_ = {};

}
void BaseMiniCamera::MakeCamelaMatrix() {

	worldMatrix_ = MakeAffineMatrix(Camera::zoomLevel_, 0, Camera::worldPos_);
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(0, 0, 1280, 720);
	viewportMatrix_ = MakeViewwportmatrix(monitorPos_.x, monitorPos_.y, 1280.0f/2, 720.0f/2);
}

void BaseMiniCamera::RenderingPipeline() {
	matrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
	wvpVpMatrix_ = wvpVpMatrix(matrix_, camera_->GetViewMatrix(), camera_->GetOrthoMatrix(), camera_->GetViewportMatrix());
	screenVertex_ = Transform(localVertex_, wvpVpMatrix_);
}