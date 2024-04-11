#include <Novice.h>
#include <stdio.h>
#include"mapchip.h"

//function
#include"Matrix3x3.h"
#include "BoxRelated.h"

//class
#include"Camera.h"

Mapchip::Mapchip() {
	Init();
	fileLoad();
	camera_ = new Camera();
	mapTexture.Handle = Novice::LoadTexture("white1x1.png");//マップ画像
}

void Mapchip::Init() {
	size_ = 48.0f;
	scale_ = { 1,1 };
	scrollPos_ = { 0,0 };
	localVertex_ = MakeLoalVertex(size_);	
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			worldPos_[y][x] = {};
			matrix_[y][x] = {};
		}
	}
}

void Mapchip::fileLoad() {
	//ファイル読み込み
	FILE* fp = NULL;

	if (fopen_s(&fp, "./Map/mapSample1.csv", "rt") != 0) {
		return;
	}
	int numRects = 0;

	while (numRects < mapxMax * mapyMax && fscanf_s(fp, "%d,", &map[numRects / mapxMax][numRects % mapxMax]) != EOF) {
		++numRects;
	}
	fclose(fp);

	//char filePath[256];
	//for (int num = 1; num < 2; num++) {
	//	sprintf_s(filePath, "./Resources/map%d.csv", num);

	//	FILE* fp = NULL;
	//	fopen_s(&fp, filePath, "rt");
	//	if (fp == NULL) {
	//		return;
	//	}

	//	//マップ1の読み込み
	//	
	//		for (int row = 0; row < mapDelimitY; row++) {
	//			for (int column = 0; column < mapxMax; column++) {
	//				fscanf_s(fp, "%d,", &map[row][column]);
	//			}
	//		}
	//	

	//	////マップ2の読み込み
	//	//if (num == 2) {
	//	//	for (int row = 0; row < mapDelimitY; row++) {
	//	//		for (int column = 35; column < 70; column++) {
	//	//			fscanf_s(fp, "%d,", &map[row][column]);
	//	//		}
	//	//	}
	//	//}
	//	fclose(fp);
	//}
}

void Mapchip::Update() {

	//マップチップの座標取得
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			worldPos_[y][x].x = float(x * size_) + (size_ / 2);
			worldPos_[y][x].y = float(y * size_) + (size_ / 2);
		}
	}
}

void Mapchip::RenderingPipeline() {
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			//マップチップ行列の作成
			camera_->MakeCamelaMatrix();
			matrix_[y][x] = MakeAffineMatrix(scale_, 0, worldPos_[y][x]);
			wvMatrix_[y][x] = wvpVpMatrix(matrix_[y][x], camera_->GetViewMatrix(),camera_->GetOrthoMatrix(),camera_->GetViewportMatrix());
			//スクリーンに変換＆描画
			ScreenVertex_[y][x] = Transform(localVertex_, wvMatrix_[y][x]);
		}
	}
}

void Mapchip::Draw() {
	//スクロール座標の取得
	scrollPos_ = Camera::worldPos_;

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {	
			//画面内のみ描画する
			if (worldPos_[y][x].x - scrollPos_.x >= -size_ * Camera::zoomLevel_.x && worldPos_[y][x].x - scrollPos_.x <= (kWindowSizeX + size_) * Camera::zoomLevel_.x && worldPos_[y][x].y - scrollPos_.y >= -size_ * Camera::zoomLevel_.y && worldPos_[y][x].y - scrollPos_.y <= (kWindowSizeY + size_) * Camera::zoomLevel_.y) {
				if (map[y][x] == BLOCK) {
					newDrawQuad(ScreenVertex_[y][x], 0, 0, size_, size_, mapTexture.Handle, WHITE);
				}
			}
		}
	}
}