#pragma once
#include"struct.h"
#include"BaseObj.h"

//ウィンドウサイズ
const int kWindowSizeX = 1280;
const int kWindowSizeY = 720;

const int mapxMax = 40;
const int mapyMax = 30;

//ブロックのタイプ
enum BlockType {
	NONE,//0
	BLOCK,//1
	START,//2
};

class Camera;
//マップチップクラス
class Mapchip:public BaseObj {
private:
	Camera* camera_;
	BaseObj* baseobj_[mapyMax][mapxMax];
	
	//pos
	Vector2 scrollPos_;
	//Vector2 worldPos_[mapyMax][mapxMax];
	//Vector2 scale_;
	////Matrix&Vertex
	///*Matrix3x3 matrix_[mapyMax][mapxMax];
	//Matrix3x3 wvMatrix_[mapyMax][mapxMax];
	//Vertex ScreenVertex_[mapyMax][mapxMax];*/
	//Vertex localVertex_;
	//size,texture
	float size_;

	GH mapTexture;
	
public:
	BlockType map[mapyMax][mapxMax];

	Mapchip();
	void fileLoad();

	void Init();
	void Update();
	void Draw();

	void RenderingPipeline()override;

	//setter
	void SetCamelaMatrix(Camera* camelamatrix) { camera_ = camelamatrix; }
	void SetScrollPosX(float scrollPosX) { this->scrollPos_.x = scrollPosX; }

	//getter
	Vector2 GetScrollPos() const { return scrollPos_; }
	float GetMapchipSize()const { return size_; }
};


