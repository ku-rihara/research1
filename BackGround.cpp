#include "BackGround.h"
#include"BoxRelated.h"
#include"Matrix3x3.h"
#ifdef _DEBUG
#include<imgui.h>
#endif

BackGround::BackGround() {

	texture_.Handle = Novice::LoadTexture("./Resources/bg.png");
}
BackGround::~BackGround() {

}

void BackGround::Init() {
	BaseObj::Init();
	scale_ = { 1,1 };
	size_ = { 1280,720 };
	localVertex_ = MakeLoalVertex(size_);
	/*worldPos_ = { 640,360 };
	camera_->SetBackPos(Vector2(640,360));
	miniCamera_->SetBackPos(Vector2(640, 360));*/
}

void BackGround::Update() {

	Vector2 world{ (worldPos_.x + (size_.x / 2.0f)) * miniCamera_->GetZoomLevel().x
				  ,(worldPos_.y + (size_.y / 2.0f)) * miniCamera_->GetZoomLevel().y };
	BackGroundDrawRangeCut(world, camera_->GetViewPort().width * miniCamera_->GetZoomLevel().x, camera_->GetViewPort().height * miniCamera_->GetZoomLevel().y);
}

void BackGround::Draw() {
	newDrawQuad(screenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

void BackGround::MiniDraw() {
	newDrawQuad(MiniScreenVertex_, drawStart_.x, drawStart_.y, drawEnd_.x, drawEnd_.y, texture_.Handle, WHITE);
	
}

void BackGround::RenderingPipeline() {
	camera_->MakeBackCamelaMatrix();
	BaseObj::RenderingPipeline();
}

void BackGround::MiniRenderingPipeline() {
	miniCamera_->MakeBackCamelaMatrix();
	BaseObj::MiniRenderingPipeline();
}

void BackGround::BackGroundDrawRangeCut(Vector2 centerPos,float viewportWidth, float viewportHeight) {
	BaseObj::BackGroundDrawRangeCut(centerPos,viewportWidth,viewportHeight);
}