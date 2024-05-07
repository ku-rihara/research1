﻿#include "Player.h"
#include"BoxRelated.h"
#include"InputManager.h"


Player::Player() {

	texture_.Handle = Novice::LoadTexture("white1x1.png");
}

Player::~Player() {

}

void Player::Init() {
	BaseObj::Init();
	worldPos_ = { 48 * 2,48 * 2 };
	size_ = { 48.0f,48.0f };
	scale_ = { 1,1 };
	localVertex_ = MakeLoalVertex(size_);
}

//更新
void Player::Update() {
	oldWorldPos_.x = worldPos_.x;
	oldWorldPos_.y = worldPos_.y;
	Move();

	//スクロール範囲の制限
	const float LeftMost = 248.0f*camera_->GetZoomLevel().x;
	const float RightMost = (mapchip_->GetMapchipSize()) * (mapxMax-16.5f * camera_->GetZoomLevel().x) - (LeftMost);
	const float TopMost = 240.0f * camera_->GetZoomLevel().y;
	const float BottomMost = (mapchip_->GetMapchipSize()) * (mapyMax-5 * camera_->GetZoomLevel().y) - (TopMost);

	//カメラの動き
	//X
	if (worldPos_.x >= LeftMost && worldPos_.x <= RightMost) {
	camera_->SetPosX(worldPos_.x - LeftMost);
	}
	//スクロール範囲外はスクロールしない
	else {
		if (worldPos_.x <= LeftMost|| camera_->GetZoomLevel().x >= zoomOutMax) {
			camera_->SetPosX(0);
		}

		if (worldPos_.x >= RightMost&& camera_->GetZoomLevel().x < zoomOutMax) {
			camera_->SetPosX(RightMost - LeftMost);
		}
	}

	//Y
	if (worldPos_.y >= TopMost && worldPos_.y <= BottomMost) {
		camera_->SetPosY(worldPos_.y - TopMost);
	}
	//スクロール範囲外はスクロールしない
	else {
		if (worldPos_.y <= TopMost) {
			camera_->SetPosY(0);
		}

		if (worldPos_.y >= BottomMost) {
			camera_->SetPosY(BottomMost - TopMost);
		}
	}
}

//描画
void Player::Draw() {
	newDrawQuad(screenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

void Player::MiniDraw() {
	newDrawQuad(MiniScreenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

void Player::Move() {
	//左右移動
	if (InputManager::GetIsPressKey(DIK_D)) {
		velocity_.x = 4;
	}
	else	if (InputManager::GetIsPressKey(DIK_A)) {
		velocity_.x = -4;
	}
	//ジャンプ
	if (InputManager::GetIsPressKey(DIK_W) && isFlight_ == false) {
		velocity_.y = -15;
		isFlight_ = true;
	}
	//ジャンプしてるときは加速度1
	if (isFlight_ == true) {
		acceleration_.y = 1.0f;
	}
	//落下速度一定以上で加速スピードを維持
	if (velocity_.y >= 16.0f) {
		acceleration_.y = 0;
	}
	velocity_.y += acceleration_.y;
	worldPos_.y += velocity_.y;
	if (InputManager::GetIsPressKey(DIK_A) || InputManager::GetIsPressKey(DIK_D)) {
		worldPos_.x += velocity_.x;
	}
}

//レンダリングパイプライン
void Player::RenderingPipeline() {
	camera_->MakeCamelaMatrix();
	BaseObj::RenderingPipeline();
}

void Player::MiniRenderingPipeline() {
	miniCamera_->MakeCamelaMatrix();
	BaseObj::MiniRenderingPipeline();
}
//マップチップとの当たり判定
void Player::MapChipColligion() {
	BaseObj::MapChipColligion();
}