#include "MiniCamera.h"

MiniCamera::MiniCamera(Vector2 worldPos, Vector2 monitorPos, Vector2 size) {
	for (int i = 0; i < miniCameraNum; i++) {
		miniCamera_[i][0] = new BaseMiniCamera();
	
	Init(Vector2 worldPos, Vector2 monitorPos, Vector2 size);
}
MiniCamera::~MiniCamera() {

}

void MiniCamera::Init() {
	for (int i = 0; i < miniCameraNum; i++) {
		for (int j = 0; j < objNum; j++) {
			miniCamera_[i][j]->BaseMiniCamera::Init();
		}
	}
}

void MiniCamera::MakeCamelaMatrix() {
	for (int i = 0; i < miniCameraNum; i++) {
		for (int j = 0; j < objNum; j++) {
			miniCamera_[i][j]->BaseMiniCamera::MakeCamelaMatrix();
		}
	}
}