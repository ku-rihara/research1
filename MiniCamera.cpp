#include "MiniCamera.h"

//class
#include"Player.h"
#include"mapchip.h"
#include"BackGround.h"

MiniCamera::MiniCamera(Vector2 monitorPos):BaseMiniCamera(monitorPos) {
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
		miniCamera_[i][0]->;
		miniCamera_[i][1]->;
		miniCamera_[i][2]->;	
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