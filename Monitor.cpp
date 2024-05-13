#include "Monitor.h"
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
	size_ = { 48.0f*15,48.0f*9 };
	scale_ = { 1,1 };
	localVertex_ = MakeLoalVertex(size_);
}

//更新
void Monitor::Update(float mapSize) {
	ImGui::Begin("Window");
	ImGui::DragFloat2("MonitorScreenPos(L)", &worldPos_.x, 1.0f);
	ImGui::End();
	mapTransformedSize_.x = mapSize * (size_.x /miniCamera_->GetOrthoGraphic().width);
	mapTransformedSize_.y = mapSize * (size_.y / miniCamera_->GetOrthoGraphic().height);
	drawSize_ = { 48.0f * 15 + (mapTransformedSize_.x),48.0f * 9 - (mapTransformedSize_.y)};
	oldWorldPos_.x = worldPos_.x;
	oldWorldPos_.y = worldPos_.y;	
}

//描画
void Monitor::Draw() {
	newDrawQuad(screenVertex_, mapTransformedSize_.x, 0, drawSize_.x, drawSize_.y, texture_.Handle, WHITE);
}

//レンダリングパイプライン
void Monitor::RenderingPipeline() {
	camera_->MakeCamelaMatrix();
	BaseObj::RenderingPipeline();
}
