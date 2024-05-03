#include "BackGround.h"
#include"BoxRelated.h"
#include"Matrix3x3.h"


BackGround::BackGround() {

	texture_.Handle = Novice::LoadTexture("./Resources/SkyBackgraund.png");
}
BackGround::~BackGround() {

}

void BackGround::Init() {
	BaseObj::Init();
	scale_ = { 1,1 };
	size_= { 1280,720 };
	localVertex_ = MakeLoalVertex(size_);
	worldPos_ = { 640,360 };
	camera_->SetBackPos(Vector2(640,360));
}

void BackGround::Update() {
	camera_->MakeBackCamelaMatrix();
	matrix_ = MakeAffineMatrix(scale_, theta_, worldPos_);
	wvpVpMatrix_ = wvpVpMatrix(matrix_, camera_->GetViewMatrix(), camera_->GetOrthoMatrix(), camera_->GetViewportMatrix());
	screenVertex_ = Transform(localVertex_, wvpVpMatrix_);
}

void BackGround::Draw() {
	newDrawQuad(screenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

