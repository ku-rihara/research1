#pragma once
#include"struct.h"
#include"Vector2C.h"
#include"BaseObj.h"

//‘O•ûéŒ¾
class Camera;

class BaseMiniCamera:public BaseObj{
	
	Camera* camera_;
	//Pos,ZoomLevel
	 Vector2 worldPos_;
	 Vector2 zoomLevel_;

	Matrix3x3 worldMatrix_;
	Matrix3x3 viewMatrix_;
	Matrix3x3 orthoMatrix_;
	Matrix3x3 viewportMatrix_;
public:

	BaseMiniCamera();
	~BaseMiniCamera();
	virtual void Init();
	virtual void MakeCamelaMatrix();
	virtual void  RenderingPipeline()override;
	
	//getter
	/*Matrix3x3 GetWorldMatrix()const { return worldMatrix_; }
	Matrix3x3 GetViewMatrix()const { return viewMatrix_; }
	Matrix3x3 GetOrthoMatrix()const { return orthoMatrix_; }
	Matrix3x3 GetViewportMatrix()const { return viewportMatrix_; }*/
	Vector2 GetPos()const { return worldPos_; }
	/*Vector2 GetZoomLevel()const { return zoomLevel_; }*/

	//setter
	void SetPosX(float posX) { this->worldPos_.x = posX; }
	void SetPosY(float posY) { this->worldPos_.y = posY; }
	void SetIncPosX(float posX) { this->worldPos_.x += posX; }
	void SetIncPosY(float posY) { this->worldPos_.y += posY; }
	/*void SetZoomLevelX(float Zoom) { this->zoomLevel_.x = Zoom; }
	void SetZoomLevelY(float Zoom) { this->zoomLevel_.y = Zoom; }*/
};



