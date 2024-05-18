#include<Novice.h>
#include "MiniCamera.h"
//function
#include"Matrix3x3.h"
#include"BoxRelated.h"
//class
#include"Monitor.h"
#include<imgui.h>

MiniCamera::MiniCamera() {

}

MiniCamera::~MiniCamera() {

}

void MiniCamera::Init() {
	BaseCamera::Init();
	viewprot_ = { 0,0,1280/ miniLevel_,720/ miniLevel_ };
	orthoGraphic_ = { 0,0,1280,720  };
	backViewprot_ = { 0,0,640,320 };
	backOrthoGraphic_ = { -640, -360, 640, 360 };
}

void MiniCamera::Update(const Player& player, const Mapchip& mapchip) {
	ImGui::Begin("Camera");
	ImGui::DragFloat2("MiniPlusZoom", &plusZoomLevel_.x, 0.01f);
	ImGui::End();
	BaseCamera::Update( player,mapchip);
	

}
void MiniCamera::MakeCamelaMatrix(bool isZoomRock) {
	BaseCamera::MakeCamelaMatrix(isZoomRock);
	}

void MiniCamera::MakeBackCamelaMatrix() {
	BaseCamera::MakeBackCamelaMatrix();
}

void MiniCamera::CombineMonitor(const Monitor& monitor) {
	viewprot_ = { monitor.GetScreenVertex().LeftTop.x, monitor.GetScreenVertex().LeftTop.y,monitor.GetScreenVertex().RightBottom.x,monitor.GetScreenVertex().RightBottom.y};
	backViewprot_= { monitor.GetScreenVertex().LeftTop.x, monitor.GetScreenVertex().LeftTop.y,monitor.GetScreenVertex().RightBottom.x,monitor.GetScreenVertex().RightBottom.y };
}