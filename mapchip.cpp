#include <Novice.h>
#include <stdio.h>
#include"mapchip.h"

//function
#include"Matrix3x3.h"
#include "BoxRelated.h"
//class
#include"Camera.h"
#include"MiniCamera.h"
#include<imgui.h>

Mapchip::Mapchip() {

	fileLoad();
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

	dotLevel_ =2.0f;
	localVertexDot_ = MakeLoalVertex(dotLevel_);

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

	ImGui::Begin("Window");
	ImGui::DragFloat2("MapChipMiniScreenPos(L)", &ScreenVertex_[0][0].LeftTop.x, 0.01f);
	ImGui::End();

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
			wvMatrix_[y][x] = wvpVpMatrix(matrix_[y][x], camera_->GetViewMatrix(), camera_->GetOrthoMatrix(), camera_->GetViewportMatrix());
			//スクリーンに変換＆描画
			ScreenVertex_[y][x] = Transform(localVertex_, wvMatrix_[y][x]);
		}
	}
}

void Mapchip::MiniRenderingPipeline() {
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			//マップチップ行列の作成
			miniCamera_->MakeCamelaMatrix();
			miniMatrix_[y][x] = MakeAffineMatrix(scale_, 0, worldPos_[y][x]);
			miniwvMatrix_[y][x] = wvpVpMatrix(miniMatrix_[y][x], miniCamera_->GetViewMatrix(), miniCamera_->GetOrthoMatrix(), miniCamera_->GetViewportMatrix());
			//スクリーンに変換＆描画
			miniScreenVertex_[y][x] = Transform(localVertex_, miniwvMatrix_[y][x]);
		}
	}
}

void Mapchip::Draw() {
	//スクロール座標の取得
	scrollPos_ = camera_->GetWorldPos();

	viewportWidth_ = camera_->GetViewPort().width * camera_->GetZoomLevel().x; // ズームレベルに応じた幅
	viewportHeight_ = camera_->GetViewPort().height * camera_->GetZoomLevel().y; // ズームレベルに応じた高さ

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			bool withinX = (worldPos_[y][x].x + size_ / 2 >= scrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= scrollPos_.x + viewportWidth_);
			bool withinY = (worldPos_[y][x].y + size_ / 2 >= scrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= scrollPos_.y + viewportHeight_);

			//画面内のみ描画する
			if (withinX && withinY && map[y][x] == BLOCK) {
				newDrawQuad(ScreenVertex_[y][x], 0, 0, size_, size_, mapTexture.Handle, WHITE);
			}
		}
	}
}
//void Mapchip::MiniDraw() {
//	
//	// ミニマップのビューポートの範囲を取得
//	float miniViewportWidth = miniCamera_->GetViewPort().width * miniCamera_->GetZoomLevel().x;
//	float miniViewportHeight = miniCamera_->GetViewPort().height * miniCamera_->GetZoomLevel().y;
//	Vector2 miniScrollPos = miniCamera_->GetWorldPos();
//
//	// ブロックのサイズを取得
//	int blockSize = static_cast<int>(size_);
//	miniCamera_->MakeCamelaMatrix();
//
//	for (int y = 16; y < 17; y++) {
//		for (int x = 0; x < 1; x++) {
//			// ミニマップのビューポート内にあるかどうかの判定
//			bool withinMiniX = (worldPos_[y][x].x + blockSize / 2 >= miniScrollPos.x) && (worldPos_[y][x].x - blockSize / 2 <= miniScrollPos.x + miniViewportWidth);
//			bool withinMiniY = (worldPos_[y][x].y + blockSize / 2 >= miniScrollPos.y) && (worldPos_[y][x].y - blockSize / 2 <= miniScrollPos.y + miniViewportHeight);
//
//			// ミニマップのビューポート内にある場合のみ描画
//			if (withinMiniX && withinMiniY && map[y][x] == BLOCK) {
//				// ブロックの各ドットごとに描画
//				for (int dotY = 0; dotY < blockSize; dotY+= int(dotLevel_)) {
//					for (int dotX = 0; dotX < blockSize; dotX+= int(dotLevel_) ){
//						// ドットがビューポート内にあるかどうかの判定
//						float dotWorldPosX = worldPos_[y][x].x - blockSize / 2 + dotX;
//						float dotWorldPosY = worldPos_[y][x].y - blockSize / 2 + dotY;
//						bool withinDotX = (dotWorldPosX >= miniScrollPos.x) && (dotWorldPosX <= miniScrollPos.x + miniViewportWidth);
//						bool withinDotY = (dotWorldPosY >= miniScrollPos.y) && (dotWorldPosY <= miniScrollPos.y + miniViewportHeight);
//						
//						miniMatrix_ = MakeAffineMatrix(scale_, 0, Vector2{ dotWorldPosX , dotWorldPosY });
//						miniwvMatrix_ = wvpVpMatrix(miniMatrix_, miniCamera_->GetViewMatrix(), miniCamera_->GetOrthoMatrix(), miniCamera_->GetViewportMatrix());
//						//スクリーンに変換＆描画
//						miniScreenVertex_ = Transform(localVertexDot_, miniwvMatrix_);
//
//						// ドットがビューポート内にある場合のみ描画
//						if (withinDotX && withinDotY) {
//							// ドットを描画
//							newDrawQuad(miniScreenVertex_, 0, 0, 48, 48, mapTexture.Handle, RED);
//							/*Novice::DrawBox(int(dotWorldPosX), int(dotWorldPosY),1,1,0,RED,kFillModeSolid);
//						*/}
//					}
//				}
//			}
//		}
//
//	}
//}

void Mapchip::MiniDraw() {
	//スクロール座標の取得
	scrollPos_ = camera_->GetWorldPos();

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			bool withinX = (worldPos_[y][x].x + size_ / 2 >= scrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= scrollPos_.x + viewportWidth_);
			bool withinY = (worldPos_[y][x].y + size_ / 2 >= scrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= scrollPos_.y + viewportHeight_);

			if (withinX && withinY && map[y][x] == BLOCK) {
				newDrawQuad(miniScreenVertex_[y][x], 0, 0, size_, size_, mapTexture.Handle, RED);
			}
		}
	}
}
