#include<Novice.h>
#include"InputManager.h"
//function
#include"Matrix3x3.h"
//class
#include"Camera.h"

Camera::Camera() {
	Init();
}

Camera::~Camera() {

}

void Camera::Init() {
	BaseCamera::Init();

}
void Camera::MakeCamelaMatrix() {
	BaseCamera::MakeCamelaMatrix();
}

void Camera::MakeBackCamelaMatrix() {
	BaseCamera::MakeBackCamelaMatrix();
}

void Camera::Update(const Player& player, const Mapchip& mapchip) {
	BaseCamera::Update(player,mapchip);
}

