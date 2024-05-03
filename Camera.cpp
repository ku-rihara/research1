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

void Camera::Update() {
	BaseCamera::Update();
}

//void Camela::ZoomOut() {
//
//	if (zoomOut_.isEasing == true) {
//
//		zoomOut_.easingTime += zoomOut_.easingPlus;
//
//		if (zoomOut_.easingTime >= 60) {
//			zoomOut_.easingTime = 60;
//		}
//
//		zoomLevel_.x = easeInQuart(zoomOut_.easingTime / 60, 1, 2.0f);
//		zoomLevel_.y = easeInQuart(zoomOut_.easingTime / 60, 1, 2.0f);
//	}
//}
//
//void Camela::ZoomIn() {
//
//	if (zoomIn_.isEasing == true) {
//
//		zoomIn_.easingTime += zoomIn_.easingPlus;
//
//		if (zoomIn_.easingTime >= 60) {
//			zoomIn_.easingTime = 60;
//
//		}
//
//		zoomLevel_.x = easeInQuart(zoomIn_.easingTime / 60, 2.0f, 1.0f);
//		zoomLevel_.y = easeInQuart(zoomIn_.easingTime / 60, 2.0f, 1.0f);
//	}
//
//
//}