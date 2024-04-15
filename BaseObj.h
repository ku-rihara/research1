#pragma once
#include<Novice.h>
#include"struct.h"

//前方宣言
class Camera;
class Mapchip;

class BaseObj{
protected:
	////包含
	
	Camera* camera_;
	Mapchip* mapchip_;

	//座標
	Vector2 worldPos_;
	Vector2 oldWorldPos_;
	Vector2i fitMapsizePos_;

	//Mapnum
	Vector2 centerMapNum_;
	Vertex mapNum_;
	Vertex oldMapNum_;
	bool isFlight_;

	//Parameter
	Vector2 velocity_;
	Vector2 acceleration_;
	Vector2 scale_;
	Vector2 size_;
	Vector2 radius_;
	float theta_;

	//頂点とマトリックス
	Vertex screenVertex_;
	Vertex localVertex_;
	Matrix3x3 matrix_;
	Matrix3x3 wvpVpMatrix_;
public:
	BaseObj();//コンストラクタ
	~BaseObj();//デストラクタ

	virtual void Init();
	virtual void RenderingPipeline();
	virtual void MapChipColligion();
	
	Vector2 GetWorldPos()const { return worldPos_; }
	Vertex GetScreenVertex()const { return screenVertex_; }
	Vector2 GetRadius()const { return radius_; }

	void SetWorldPos(Vector2 pos) { this->worldPos_ = pos; }
	void SetWorldPosX(float pos) { this->worldPos_.x = pos; }
	void SetWorldPosY(float pos) { this->worldPos_.y = pos; }
};

