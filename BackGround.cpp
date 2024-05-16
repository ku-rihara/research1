#include "BackGround.h"
#include"BoxRelated.h"
#include"Matrix3x3.h"
#include<imgui.h>

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

	// ビューポート内にあるかどうかの判定
	/*bool withinX = ( size_.x / 2 >= camera_->GetWorldPos().x) && ( - size_.x / 2 <= camera_->GetWorldPos().x + camera_->GetViewPort().width);
	bool withinY = ( size_.y / 2 >= camera_->GetWorldPos().y) && ( - size_.y / 2 <= camera_->GetWorldPos().y + camera_->GetViewPort().height);*/

	//if (withinX && withinY) {
		// 左端がはみ出ている場合の調整
	Vector2 world{ (worldPos_.x + (size_.x / 2.0f)) * camera_->GetZoomLevel().x
				  ,(worldPos_.y + (size_.y / 2.0f)) * camera_->GetZoomLevel().y };
	drawStart_.x = 0;
	drawStart_.y = 0;
	drawEnd_.x = size_.x - drawStart_.x;
	drawEnd_.y = size_.y - drawStart_.y;

	float localLeft = size_.x;
	
	if (camera_->GetZoomLevel().x < 1.0f) {
		localLeft = (size_.x / 2 + ((world.x - size_.x / 2))) * 2;
		drawStart_.x = (size_.x) - (size_.x - (-(world.x - size_.x / 2)));
		drawEnd_.x = size_.x - drawStart_.x*2;
		drawStart_.y = (size_.y) - (size_.y - (-(world.y - size_.y / 2)));
		drawEnd_.y = size_.y - drawStart_.y * 2;
	}

	// 右端がはみ出ている場合の調整
	float localRight = size_.x;
	if (world.x + size_.x / 2 > (camera_->GetViewPort().width * camera_->GetZoomLevel().x)) {
		localRight = (size_.x / 2 - ((world.x + size_.x / 2) - ((camera_->GetViewPort().width * camera_->GetZoomLevel().x)))) * 2;
	}

	// 上端がはみ出ている場合の調整
	float localTop = size_.y;
	if (camera_->GetZoomLevel().y < 1.0f) {
		localTop = (size_.y / 2 + ((world.y - size_.y / 2))) * 2;
	}

	// 下端がはみ出ている場合の調整
	float localBottom = size_.y;
	if (world.y + size_.y / 2 > (camera_->GetViewPort().height * camera_->GetZoomLevel().y)) {
		localBottom = (size_.y / 2 - ((world.y + size_.y / 2) - (camera_->GetViewPort().height * camera_->GetZoomLevel().y))) * 2;
	}
	miniLocalVertex_ = { Vector2(localLeft, localTop),
							Vector2(localRight, localTop),
							 Vector2(localLeft, localBottom),
							 Vector2(localRight, localBottom),
	};

}

void BackGround::RenderingPipeline() {
	camera_->MakeBackCamelaMatrix();
	BaseObj::RenderingPipeline();
}

void BackGround::MiniRenderingPipeline() {
	miniCamera_->MakeBackCamelaMatrix();
	BaseObj::MiniRenderingPipeline();
}

void BackGround::Draw() {
	newDrawQuad(screenVertex_, 0, 0, size_.x, size_.y, texture_.Handle, WHITE);
}

void BackGround::MiniDraw() {
	newDrawQuad(MiniScreenVertex_, drawStart_.x, drawStart_.y, drawEnd_.x, drawEnd_.y, texture_.Handle, WHITE);
	
}
