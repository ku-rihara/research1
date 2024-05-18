#include <Novice.h>
#include <stdio.h>
#include"mapchip.h"

//function
#include"Matrix3x3.h"
#include "BoxRelated.h"
#include"Function.h"
//class
#include"Camera.h"
#include"MiniCamera.h"
#include<imgui.h>

Mapchip::Mapchip() {

	fileLoad();
	mapTexture.Handle = Novice::LoadTexture("./Resources/block.png");//マップ画像
}

void Mapchip::Init() {
	size_ = 48.0f;
	scale_ = { 1,1 };
	MiniScrollPos_ = { 0,0 };
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

	if (fopen_s(&fp, "./Map/mapSampleGame.csv", "rt") != 0) {
		return;
	}
	int numRects = 0;

	while (numRects < mapxMax * mapyMax && fscanf_s(fp, "%d,", &map[numRects / mapxMax][numRects % mapxMax]) != EOF) {
		++numRects;
	}
	fclose(fp);
}

void Mapchip::Update() {

	//マップチップの座標取得
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			worldPos_[y][x].x = float(x * size_) + (size_ / 2);
			worldPos_[y][x].y = float(y * size_) + (size_ / 2);

			// ビューポート内にあるかどうかの判定
			bool withinX = (worldPos_[y][x].x + size_ / 2 >= MiniScrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= MiniScrollPos_.x + viewportWidth_);
			bool withinY = (worldPos_[y][x].y + size_ / 2 >= MiniScrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= MiniScrollPos_.y + viewportHeight_);

			if (withinX && withinY && map[y][x] == BLOCK) {
				// 左端がはみ出ている場合の調整
				drawStart_[y][x].x = 0;
				drawStart_[y][x].y = 0;
				drawEnd_[y][x].x = size_ - drawStart_[y][x].x;
				drawEnd_[y][x].y = size_ - drawStart_[y][x].y;

				float localLeft = size_;
				if (worldPos_[y][x].x - size_ / 2 < MiniScrollPos_.x) {
					localLeft =(size_/2+(-MiniScrollPos_.x + (worldPos_[y][x].x - size_/2)))*2;
					drawStart_[y][x].x =(size_)-(size_ - (MiniScrollPos_.x - (worldPos_[y][x].x - size_ / 2)));
					drawEnd_[y][x].x = size_ - drawStart_[y][x].x;
				}

				// 右端がはみ出ている場合の調整
				float localRight = size_;
				if (worldPos_[y][x].x + size_ / 2 > MiniScrollPos_.x + viewportWidth_) {
					localRight = (size_ / 2 - ((worldPos_[y][x].x + size_ / 2) - (MiniScrollPos_.x + viewportWidth_)))*2;
					drawStart_[y][x].x = 0;
					drawEnd_[y][x].x =(size_- ((worldPos_[y][x].x + size_ / 2) - (MiniScrollPos_.x + viewportWidth_)));
				}

				// 上端がはみ出ている場合の調整
				float localTop = size_;
				if (worldPos_[y][x].y - size_ / 2 < MiniScrollPos_.y) {
					localTop = (size_ / 2 + (-MiniScrollPos_.y + (worldPos_[y][x].y - size_ / 2))) * 2;
					drawStart_[y][x].y = (size_)-(size_ - (MiniScrollPos_.y - (worldPos_[y][x].y - size_ / 2)));
					drawEnd_[y][x].y = size_ - drawStart_[y][x].y;
				}

				// 下端がはみ出ている場合の調整
				float localBottom = size_;
				if (worldPos_[y][x].y + size_ / 2 > MiniScrollPos_.y + viewportHeight_) {
					localBottom = size_ - ((worldPos_[y][x].y + size_ / 2) - (MiniScrollPos_.y + viewportHeight_));
					drawStart_[y][x].y = 0;
					drawEnd_[y][x].y = (size_ - ((worldPos_[y][x].y + size_ / 2) - (MiniScrollPos_.y + viewportHeight_)));
				}
				miniLoaclVertex[y][x] = { Vector2(localLeft, localTop),	Vector2(localRight, localTop),
										  Vector2(localLeft, localBottom),Vector2(localRight, localBottom),
				};
			}
		}
	}

}

void Mapchip::Draw() {
	scrollPos_ = camera_->GetWorldPos();
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

void Mapchip::MiniDraw() {
	// スクロール座標の取得

	//スクロール座標の取得
	MiniScrollPos_ = miniCamera_->GetWorldPos();
	viewportWidth_ = camera_->GetViewPort().width * miniCamera_->GetZoomLevel().x; // ズームレベルに応じた幅
	viewportHeight_ = camera_->GetViewPort().height * miniCamera_->GetZoomLevel().y; // ズームレベルに応じた高さ

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			bool withinX = (worldPos_[y][x].x + size_ / 2 >= MiniScrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= MiniScrollPos_.x + viewportWidth_);
			bool withinY = (worldPos_[y][x].y + size_ / 2 >= MiniScrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= MiniScrollPos_.y + viewportHeight_);

			//// 切り抜いた範囲が有効なら描画する
			if (withinX && withinY &&  map[y][x] == BLOCK) {
				newDrawQuad(miniScreenVertex_[y][x], drawStart_[y][x].x, drawStart_[y][x].y, drawEnd_[y][x].x, drawEnd_[y][x].y, mapTexture.Handle, WHITE);
				/*	newDrawQuad(miniScreenVertex_[y][x], 0,0,1,1, mapTexture.Handle, RED);*/
			}
		}
	}
}

void Mapchip::RenderingPipeline() {
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			//マップチップ行列の作成
			camera_->MakeCamelaMatrix(false);
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
			miniCamera_->MakeCamelaMatrix(false);
			miniMatrix_[y][x] = MakeAffineMatrix(scale_, 0, worldPos_[y][x]);
			miniwvMatrix_[y][x] = wvpVpMatrix(miniMatrix_[y][x], miniCamera_->GetViewMatrix(), miniCamera_->GetOrthoMatrix(), miniCamera_->GetViewportMatrix());
			//スクリーンに変換＆描画
			miniScreenVertex_[y][x] = Transform(miniLoaclVertex[y][x], miniwvMatrix_[y][x]);
		}
	}
}