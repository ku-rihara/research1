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
void Camera::MakeCamelaMatrix(bool isZoomRock) {
	BaseCamera::MakeCamelaMatrix(isZoomRock);
}

void Camera::MakeBackCamelaMatrix() {
	BaseCamera::MakeBackCamelaMatrix();
}

void Camera::Update(const Player& player, const Mapchip& mapchip, Vector2 startPos) {
	ImGui::Begin("Camera");
	ImGui::DragFloat2("ScrollPos", &worldPos_.x, 0.1f);
	ImGui::DragFloat2("PlusZoom", &plusZoomLevel_.x, 0.01f);
	ImGui::End();
	BaseCamera::Update(player,mapchip,startPos);
}

