#include<Novice.h>
#include "MiniCamera.h"
//function
#include"Matrix3x3.h"
#include"BoxRelated.h"
//class
#include"Monitor.h"

MiniCamera::MiniCamera() {

}

MiniCamera::~MiniCamera() {

}

void MiniCamera::Init() {
	BaseCamera::Init();
	viewprot_ = { 0,0,1280/ miniLevel_,720/ miniLevel_ };
	orthoGraphic_ = { 0,0,1280,720 };
	backViewprot_ = { 0,0,640,320 };
	backOrthoGraphic_ = { -640/miniLevel_, -360/ miniLevel_, 640/ miniLevel_, 360/ miniLevel_ };
}

void MiniCamera::Update(const Player& player, const Mapchip& mapchip) {
	BaseCamera::Update( player,mapchip);
	

}
void MiniCamera::MakeCamelaMatrix() {
	BaseCamera::MakeCamelaMatrix();
	}

void MiniCamera::MakeBackCamelaMatrix() {
	BaseCamera::MakeBackCamelaMatrix();
}

void MiniCamera::CombineMonitor(const Monitor& monitor) {
	viewprot_ = { monitor.GetScreenVertex().LeftTop.x, monitor.GetScreenVertex().LeftTop.y,monitor.GetScreenVertex().RightBottom.x,monitor.GetScreenVertex().RightBottom.y};
}