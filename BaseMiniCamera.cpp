#include<Novice.h>
#include "BaseMiniCamera.h"
//function
#include"Matrix3x3.h"
#include"BoxRelated.h"
//class
#include"Camera.h"

BaseMiniCamera::BaseMiniCamera() {
	Init();
	camera_ = new Camera;
}

BaseMiniCamera::~BaseMiniCamera() {

}

void BaseMiniCamera::Init() {
	scale_ = { 1,1 };
	size_ = {};
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
	viewportMatrix_ = MakeViewwportmatrix(0, 0, 1280/2, 720/2);
}

void BaseMiniCamera::RenderingPipeline() {
	BaseObj::RenderingPipeline();
}