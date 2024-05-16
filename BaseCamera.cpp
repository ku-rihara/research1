#include "BaseCamera.h"
#include"InputManager.h"
#include"Matrix3x3.h"
//class
#include"Player.h"
#include"mapchip.h"

void BaseCamera::Init() {
	worldPos_ = {};
	zoomLevel_ = { 1,1 };
	worldMatrix_ = {};
	viewMatrix_ = {};
	orthoMatrix_ = {};
	viewportMatrix_ = {};
	//通常カメラの値にする
	viewprot_={ 0,0,1280,720 };
	orthoGraphic_ = { 0,0,1280,720 };
	backViewprot_ = { 0,0,1280,720 };
	backOrthoGraphic_ = { -640, -360, 640, 360 };
}

void BaseCamera::Update(const Player& player, const Mapchip& mapchip) {


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

	//スクロール範囲の制限
	const float LeftMost = 248.0f *zoomLevel_.x;
	const float RightMost = (mapchip.GetMapchipSize()) * (mapxMax - 16.5f * zoomLevel_.x) - (LeftMost);
	const float TopMost = 240.0f * zoomLevel_.y;
	const float BottomMost = (mapchip.GetMapchipSize()) * (mapyMax - 5 * zoomLevel_.y) - (TopMost);

	//カメラの動き
	//X
	if (player.GetWorldPos().x >= LeftMost && player.GetWorldPos().x <= RightMost) {
	worldPos_.x= player.GetWorldPos().x - LeftMost;
	}
	//スクロール範囲外はスクロールしない
	else {
		if (player.GetWorldPos().x <= LeftMost/* || zoomLevel_.x >= zoomOutMax*/) {
			worldPos_.x=0;
		}

		if (player.GetWorldPos().x >= RightMost/* && zoomLevel_.x < zoomOutMax*/) {
			worldPos_.x=RightMost - LeftMost;
		}
	}

	//Y
	if (player.GetWorldPos().y >= TopMost && player.GetWorldPos().y <= BottomMost) {
		worldPos_.y= player.GetWorldPos().y - TopMost;
	}
	//スクロール範囲外はスクロールしない
	else {
		if (player.GetWorldPos().y <= TopMost) {
			worldPos_.y = 0;
		}

		if (player.GetWorldPos().y >= BottomMost) {
			worldPos_.y = BottomMost - TopMost;
		}
	}
}

void BaseCamera::MakeCamelaMatrix() {

	worldMatrix_ = MakeAffineMatrix(zoomLevel_+ plusZoomLevel_, 0, worldPos_);
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(orthoGraphic_.left, orthoGraphic_.top, orthoGraphic_.width, orthoGraphic_.height);
	viewportMatrix_ = MakeViewwportmatrix(viewprot_.left, viewprot_.top, viewprot_.width, viewprot_.height);
}

void BaseCamera::MakeBackCamelaMatrix() {

	if (zoomLevel_.x + plusZoomLevel_.x <= 1.0f && zoomLevel_.y + plusZoomLevel_.y <= 1.0f) {
		worldMatrix_ = MakeAffineMatrix(zoomLevel_+ plusZoomLevel_, 0, backPos_);
	}
	else {
		worldMatrix_ = MakeAffineMatrix(Vector2(1.0f, 1.0f), 0, backPos_);
	}
	viewMatrix_ = InverseMatrix(worldMatrix_);
	orthoMatrix_ = MakeOrthographicMatrix(backOrthoGraphic_.left, backOrthoGraphic_.top, backOrthoGraphic_.width, backOrthoGraphic_.height);
	viewportMatrix_ = MakeViewwportmatrix(backViewprot_.left, backViewprot_.top, backViewprot_.width, backViewprot_.height);
}