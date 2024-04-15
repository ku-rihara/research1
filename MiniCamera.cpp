#include "MiniCamera.h"

//class
#include"Player.h"
#include"mapchip.h"
#include"BackGround.h"

MiniCamera::MiniCamera(Vector2 monitorPos):BaseMiniCamera(monitorPos) {
	player_ = new Player();
	mapchip_ = new Mapchip();
	backGround_ = new BackGround();
	for (int i = 0; i < miniCameraNum; i++) {
		for (int j = 0; j < objNum; j++) {
			miniCamera_[i][j] = new BaseMiniCamera(monitorPos);
		}
	}
	Init();
}
MiniCamera::~MiniCamera() {

}

void MiniCamera::Init() {
	for (int i = 0; i < miniCameraNum; i++) {
	/*	miniCamera_[i][0]->SetWorldPos(player_->GetWorldPos());
		miniCamera_[i][1]->SetWorldPos(mapchip_->GetPos());
		miniCamera_[i][2]->SetWorldPos(player_->GetWorldPos());
		miniCamera_[i][0]->SetWorldPos(player_->GetWorldPos());
		miniCamera_[i][1]->SetWorldPos(player_->GetWorldPos());
		miniCamera_[i][2]->SetWorldPos(player_->GetWorldPos());*/
	}

	BaseMiniCamera::Init();
}

void MiniCamera::MakeCamelaMatrix() {
	for (int i = 0; i < miniCameraNum; i++) {
		for (int j = 0; j < objNum; j++) {
			miniCamera_[i][j]->BaseMiniCamera::MakeCamelaMatrix();
		}
	}
}