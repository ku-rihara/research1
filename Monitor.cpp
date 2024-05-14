#include "Monitor.h"

#include "Player.h"
#include"BoxRelated.h"
#include"InputManager.h"
#include<imgui.h>

Monitor::Monitor() {
	texture_.Handle = Novice::LoadTexture("./Resources/monitor.png");
}

Monitor::~Monitor() {

}

void Monitor::Init() {
	BaseObj::Init();
	worldPos_ = { 1200,1000 };
	size_ = { 48.0f * 15,48.0f * 9 };
	scale_ = { 1,1 };
	localVertex_ = MakeLoalVertex(size_);
}

//更新
void Monitor::Update() {
	ImGui::Begin("Window");
	ImGui::DragFloat2("MonitorScreenPos(L)", &worldPos_.x, 1.0f);
	ImGui::End();
	oldWorldPos_.x = worldPos_.x;
	oldWorldPos_.y = worldPos_.y;
}

//描画
void Monitor::Draw() {
	newDrawQuad(screenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

//レンダリングパイプライン
void Monitor::RenderingPipeline() {
	camera_->MakeCamelaMatrix();
	BaseObj::RenderingPipeline();
}
