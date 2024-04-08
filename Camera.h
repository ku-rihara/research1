#pragma once

#include"struct.h"

class Camera {
public:

	//Pos,ZoomLevel
	static Vector2 worldPos_;
	Vector2 backPos_;
	static Vector2 zoomLevel_;
	static const float zoomOutMax_;

	Matrix3x3 worldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;


public:

	Camera();
	~Camera();
	void Init();
	void Update();
	void MakeCamelaMatrix();
	void MakeBackCamelaMatrix();
	/*void ZoomOut();
	void ZoomIn();*/

	//getter
	Matrix3x3 GetWorldMatrix()const { return worldMatrix_; }
	Matrix3x3 GetViewMatrix()const { return viewMatrix_; }
	Matrix3x3 GetOrthoMatrix()const { return orthoMatrix_; }
	Matrix3x3 GetViewportMatrix()const { return viewportMatrix_; }
	Vector2 GetWorldPos()const { return worldPos_; }
	Vector2 GetZoomLevel()const { return zoomLevel_; }


	//setter
	void SetPosX(float posX) { this->worldPos_.x = posX; }
	void SetPosY(float posY) { this->worldPos_.y = posY; }
	void SetIncPosX(float posX) { this->worldPos_.x += posX; }
	void SetIncPosY(float posY) { this->worldPos_.y += posY; }
	void SetZoomLevelX(float Zoom) { this->zoomLevel_.x = Zoom; }
	void SetZoomLevelY(float Zoom) { this->zoomLevel_.y = Zoom; }


};

