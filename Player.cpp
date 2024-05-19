﻿#include "Player.h"
#include"BoxRelated.h"
#include"InputManager.h"
#ifdef _DEBUG
#include<imgui.h>
#endif // DEBUG

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
	miniLocalVertex_ = localVertex_;
}

//更新
void Player::Update() {
#ifdef _DEBUG
	ImGui::Begin("Player");
	ImGui::DragFloat2("PlayerWorldPos", &worldPos_.x, 1.0f);
	ImGui::DragFloat2("PlayerLocal(LeftTop)", &localVertex_.LeftTop.x, 0.1f);
	ImGui::DragFloat2("PlayerLocal(RightTop)", &localVertex_.RightTop.x, 0.1f);
	ImGui::DragFloat2("PlayerLocal(LeftBottom)", &localVertex_.LeftBottom.x, 0.1f);
	ImGui::DragFloat2("PlayerLocal(RightBottom)", &localVertex_.RightBottom.x, 0.1f);
	ImGui::End();
#endif
	oldWorldPos_.x = worldPos_.x;
	oldWorldPos_.y = worldPos_.y;
	Move();
	DrawRangeCut(miniCamera_->GetWorldPos(), camera_->GetViewPort().width * miniCamera_->GetZoomLevel().x, camera_->GetViewPort().height * miniCamera_->GetZoomLevel().y);

}

//描画
void Player::Draw() {
	newDrawQuad(screenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

void Player::MiniDraw() {
	bool withinX = (worldPos_.x + size_.x / 2 >= miniCamera_->GetWorldPos().x) && (worldPos_.x - size_.x / 2 <= miniCamera_->GetWorldPos().x + (camera_->GetViewPort().width * miniCamera_->GetZoomLevel().x));
	bool withinY = (worldPos_.y + size_.y / 2 >= miniCamera_->GetWorldPos().y) && (worldPos_.y - size_.y / 2 <= miniCamera_->GetWorldPos().y + (camera_->GetViewPort().height * miniCamera_->GetZoomLevel().y));
	if (withinX && withinY) {
		newDrawQuad(MiniScreenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, RED);
	}
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
	camera_->MakeCamelaMatrix(false);
	BaseObj::RenderingPipeline();
}

void Player::MiniRenderingPipeline() {
	miniCamera_->MakeCamelaMatrix(false);
	BaseObj::MiniRenderingPipeline();
}
//マップチップとの当たり判定
void Player::MapChipColligion() {
	BaseObj::MapChipColligion();
}