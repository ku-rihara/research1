#include<Novice.h>
#include"InputManager.h"
//function
#include"Matrix3x3.h"
//class
#include"Camera.h"
#include<imgui.h>

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
	ImGui::Begin("Window");
	ImGui::DragFloat2("ScrollPos", &worldPos_.x, 0.1f);
	ImGui::End();
	BaseCamera::Update(player,mapchip);
}

