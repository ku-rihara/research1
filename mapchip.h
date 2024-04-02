#pragma once
#include"struct.h"
#include"Camera.h"

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

//マップチップクラス
class Mapchip {
private:
	Camera* camera_;
	//pos
	Vector2 scrollPos_;
	Vector2 pos_[mapyMax][mapxMax];
	Vector2 scale_;
	//Matrix&Vertex
	Matrix3x3 matrix_[mapyMax][mapxMax];
	Matrix3x3 wvMatrix_[mapyMax][mapxMax];
	Vertex ScreenVertex_[mapyMax][mapxMax];
	Vertex localVertex_;
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

	void RenderingPipeline();

	//setter
	void SetCamelaMatrix(Camera* camelamatrix) { camera_ = camelamatrix; }
	void SetScrollPosX(float scrollPosX) { this->scrollPos_.x = scrollPosX; }

	//getter
	Vector2 GetScrollPos() const { return scrollPos_; }
	Vector2 GetPos(int x, int y)const { return pos_[y][x]; }
	float GetMapchipSize()const { return size_; }
};


