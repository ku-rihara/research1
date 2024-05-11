#pragma once
#include"struct.h"
struct ViewPort{
	float left;
	float top;
	float width;
	float height;
 };
struct OrthoGraphic {
	float left;
	float top;
	float width;
	float height;
};
class Player;
class Mapchip;
class BaseCamera{
protected:
	Player* player_;
	Mapchip* mapchip_;
	//Pos,ZoomLevel
	 Vector2 worldPos_;
	Vector2 backPos_;
	ViewPort viewprot_;
	OrthoGraphic orthoGraphic_;
	ViewPort backViewprot_;
	OrthoGraphic backOrthoGraphic_;
	//Matrix
	Matrix3x3 worldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;
public:
	 Vector2 zoomLevel_;

	virtual void Init();
	virtual void Update(const Player& player, const Mapchip& mapchip);
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
	ViewPort GetViewPort()const { return viewprot_; }

	//setter
	void SetPosX(float posX) { this->worldPos_.x = posX; }
	void SetPosY(float posY) { this->worldPos_.y = posY; }
	void SetBackPos(Vector2 pos) { this->backPos_ = pos; }
	void IncrementPosX(float posX) { this->worldPos_.x += posX; }
	void IncrementPosY(float posY) { this->worldPos_.y += posY; }
	void SetZoomLevelX(float Zoom) { this->zoomLevel_.x = Zoom; }
	void SetZoomLevelY(float Zoom) { this->zoomLevel_.y = Zoom; }

};

