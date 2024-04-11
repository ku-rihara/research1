#include<Novice.h>
#include "BaseMiniCamera.h"
//function
#include"Matrix3x3.h"
#include"BoxRelated.h"
//class
#include"Camera.h"

BaseMiniCamera::BaseMiniCamera(Vector2 worldPos, Vector2 monitorPos, Vector2 size) {
	camera_ = new Camera;
	Init( worldPos,monitorPos,size);
}

BaseMiniCamera::~BaseMiniCamera() {

}

void BaseMiniCamera::Init(Vector2 worldPos, Vector2 monitorPos, Vector2 size) {
	scale_ = { 1,1 };
	worldPos_ = worldPos;
	monitorPos_ = monitorPos;
	size_ = size;
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