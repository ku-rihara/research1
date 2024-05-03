#pragma once
#include"struct.h"
struct ViewPort{
	float left;
	float top;
	float width;
	float height;
 };
class BaseCamera{
protected:
	//Pos,ZoomLevel
	 Vector2 worldPos_;
	Vector2 backPos_;
	ViewPort viewprot_;
	//Matrix
	Matrix3x3 worldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;
public:
	 Vector2 zoomLevel_;

	BaseCamera();
	~BaseCamera();
	virtual void Init();
	virtual void Update();
	virtual void MakeCamelaMatrix();
	virtual void MakeBackCamelaMatrix();
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
	void SetBackPos(Vector2 pos) { this->backPos_ = pos; }
	void IncrementPosX(float posX) { this->worldPos_.x += posX; }
	void IncrementPosY(float posY) { this->worldPos_.y += posY; }
	void SetZoomLevelX(float Zoom) { this->zoomLevel_.x = Zoom; }
	void SetZoomLevelY(float Zoom) { this->zoomLevel_.y = Zoom; }

};

