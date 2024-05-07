#include "BaseCamera.h"
#include"InputManager.h"
#include"Matrix3x3.h"

BaseCamera::BaseCamera() {

}

BaseCamera::~BaseCamera() {

}

void BaseCamera::Init() {
	worldPos_ = {};
	zoomLevel_ = { 1,1 };
	worldMatrix_ = {};
	viewMatrix_ = {};
	orthoMatrix_ = {};
	viewportMatrix_ = {};
	viewprot_={ 0,0,1280,720 };
	orthoGraphic_ = { 0,0,1280,720 };
}

void BaseCamera::MakeCamelaMatrix() {

	worldMatrix_ = MakeAffineMatrix(zoomLevel_, 0, worldPos_);
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(orthoGraphic_.left, orthoGraphic_.top, orthoGraphic_.width, orthoGraphic_.height);
	viewportMatrix_ = MakeViewwportmatrix(viewprot_.left, viewprot_.top, viewprot_.width, viewprot_.height);
}


void BaseCamera::Update() {
	//ズームイン
	if (InputManager::GetIsPressKey(DIK_UP)) {
		zoomLevel_ -= 0.01f;
	}
	//ズームアウト
	else if (InputManager::GetIsPressKey(DIK_DOWN)) {
		if (zoomLevel_.x < zoomOutMax) {
			zoomLevel_ += 0.01f;
		}
		else {
			zoomLevel_.x = zoomOutMax;
			zoomLevel_.y = zoomOutMax;
		}
	}
}

void BaseCamera::MakeBackCamelaMatrix() {

	if (zoomLevel_.x <= 1.0f && zoomLevel_.y <= 1.0f) {
		worldMatrix_ = MakeAffineMatrix(zoomLevel_, 0, backPos_);
	}
	else {
		worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0, backPos_);
	}
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(-640, -360, 640, 360);
	viewportMatrix_ = MakeViewwportmatrix(0, 0, 1280, 720);
}