#include "Monitor.h"

#include "Player.h"
#include"BoxRelated.h"
#include"InputManager.h"
#ifdef _DEBUG
#include<imgui.h>
#endif
#include"Matrix3x3.h"

Monitor::Monitor() {
	texture_.Handle = Novice::LoadTexture("./Resources/monitor.png");
	isRockScreen_ = false;
}

Monitor::~Monitor() {

}

void Monitor::Init() {
	BaseObj::Init();
	worldPos_ = { 1200,1000 };
	size_ = { 48.0f * 11,48.0f * 6 };
	movePos_ = { 929,204 };
	scale_ = { 1,1 };
	localVertex_ = MakeLoalVertex(size_);
}

//更新
void Monitor::Update() {
#ifdef _DEBUG
	ImGui::Begin("Monitor");
	ImGui::DragFloat2("MonitorWorldPos", &worldPos_.x, 1.0f);
	ImGui::DragFloat2("MonitorScale", &scale_.x, 0.01f);
	ImGui::DragFloat2("MovePos", &movePos_.x, 1.0f);
	ImGui::End();
#endif
	oldWorldPos_.x = worldPos_.x;
	oldWorldPos_.y = worldPos_.y;
	if (InputManager::GetIsTriggerKey(DIK_SPACE)) {
		if (isRockScreen_) {
			isRockScreen_ = false;
		}
		else if (!isRockScreen_) {
			isRockScreen_ = true;
		}
	}

	if (!isRockScreen_) {
	}
	else if (isRockScreen_) {
		worldPos_ = camera_->GetWorldPos() + movePos_;
		
	}
}

//描画
void Monitor::Draw() {
	
		newDrawQuad(screenVertex_, 0, 0, 48.0f * 15, 48.0f * 9, texture_.Handle, WHITE);
	
}

//レンダリングパイプライン
void Monitor::RenderingPipeline() {
	camera_->MakeCamelaMatrix(isRockScreen_);
	BaseObj::RenderingPipeline();
}
