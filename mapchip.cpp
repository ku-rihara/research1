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
	scrollPos_ = { 0,0 };
	localVertex_ = MakeLoalVertex(size_);
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			worldPos_[y][x] = {};
			matrix_[y][x] = {};
		}
	}

	dotLevel_ = 1.0f;
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
	ImGui::DragFloat2("MapChipMiniScreenPos(L)", &miniLoaclVertex[0][0].LeftTop.x, 0.01f);
	ImGui::End();

	//マップチップの座標取得
	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			worldPos_[y][x].x = float(x * size_) + (size_ / 2);
			worldPos_[y][x].y = float(y * size_) + (size_ / 2);
		}
	}

	//for (int y = 0; y < mapyMax; y++) {
	//	for (int x = 0; x < mapxMax; x++) {

	//		// ブロックの左上座標と右下座標を計算
	//		blockLeft_[x] = worldPos_[y][x].x - size_ / 2;
	//		blockRight_[x] = worldPos_[y][x].x + size_ / 2;
	//		blockTop_[y] = worldPos_[y][x].y - size_ / 2;
	//		blockBottom_[y] = worldPos_[y][x].y + size_ / 2;

	//		// 描画範囲外に出た場合には、描画する部分を切り抜く
	//		drawLeft_[x] = max(blockLeft_[x], scrollPos_.x);
	//		drawRight_[x] = min(blockRight_[x], scrollPos_.x + viewportWidth_);
	//		drawTop_[y] = max(blockTop_[y], scrollPos_.y);
	//		drawBottom_[y] = min(blockBottom_[y], scrollPos_.y + viewportHeight_);


	//			miniLoaclVertex[y][x] = { Vector2(drawLeft_[x] - scrollPos_.x ,drawTop_[y] - scrollPos_.y),
	//									  Vector2(drawRight_[x] - drawLeft_[x],drawTop_[y] - scrollPos_.y),
	//									  Vector2(drawLeft_[x] - scrollPos_.x,drawBottom_[y] - drawTop_[y]),
	//									  Vector2(drawRight_[x] - drawLeft_[x],drawBottom_[y] - drawTop_[y]),
	//			};
	//		
	//	}
	//}

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {

			// ブロックの左上座標と右下座標を計算
			float blockLeft = worldPos_[y][x].x - size_ / 2;
			float blockRight = worldPos_[y][x].x + size_ / 2;
			float blockTop = worldPos_[y][x].y - size_ / 2;
			float blockBottom = worldPos_[y][x].y + size_ / 2;

			// 描画範囲外に出た場合には、描画する部分を切り抜く
			float drawLeft = max(blockLeft, scrollPos_.x);
			float drawRight = min(blockRight, scrollPos_.x + viewportWidth_);
			float drawTop = max(blockTop, scrollPos_.y);
			float drawBottom = min(blockBottom, scrollPos_.y + viewportHeight_);

			// ローカル頂点を計算
			float width = drawRight - drawLeft;
			float height = drawBottom - drawTop;
			float offsetX = drawLeft - blockLeft;
			float offsetY = drawTop - blockTop;

			miniLoaclVertex[y][x] = {
				Vector2(offsetX, offsetY),
				Vector2(width, offsetY),
				Vector2(offsetX, height),
				Vector2(width, height)
			};
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

void Mapchip::MiniDraw() {
	// スクロール座標の取得
	scrollPos_ = camera_->GetWorldPos();

	for (int y = 0; y < mapyMax; y++) {
		for (int x = 0; x < mapxMax; x++) {
			/*bool withinX = (worldPos_[y][x].x + size_ / 2 >= scrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= scrollPos_.x + viewportWidth_);
			bool withinY = (worldPos_[y][x].y + size_ / 2 >= scrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= scrollPos_.y + viewportHeight_);*/

			// 切り抜いた範囲が有効なら描画する
			if (/*withinX && withinY && */ map[y][x] == BLOCK) {
				newDrawQuad(miniScreenVertex_[y][x], 0, 0, size_, size_, mapTexture.Handle, WHITE);
				/*	newDrawQuad(miniScreenVertex_[y][x], 0,0,1,1, mapTexture.Handle, RED);*/
			}
		}
	}
}


//void Mapchip::MiniDraw() {
//	// ミニマップのビューポートの範囲を取得
//	float miniViewportWidth = miniCamera_->GetViewPort().width * miniCamera_->GetZoomLevel().x;
//	float miniViewportHeight = miniCamera_->GetViewPort().height * miniCamera_->GetZoomLevel().y;
//	Vector2 miniScrollPos = miniCamera_->GetWorldPos();
//
//	// ブロックのサイズを取得
//	int blockSize = static_cast<int>(size_);
//	miniCamera_->MakeCamelaMatrix();
//
//	for (int y = 0; y < mapyMax; y++) {
//		for (int x = 0; x < mapxMax; x++) {
//			bool withinX = (worldPos_[y][x].x + size_ / 2 >= scrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= scrollPos_.x + viewportWidth_);
//			bool withinY = (worldPos_[y][x].y + size_ / 2 >= scrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= scrollPos_.y + viewportHeight_);
//
//			// ミニマップのビューポート内にある場合のみ描画
//			if (withinX && withinY && map[y][x] == BLOCK) {
//				// ドットがビューポート内にあるかどうかの判定
//				float dotWorldPosX = worldPos_[y][x].x - blockSize / 2;
//				float dotWorldPosY = worldPos_[y][x].y - blockSize / 2;
//				bool withinDotX = (dotWorldPosX >= miniScrollPos.x) && (dotWorldPosX <= miniScrollPos.x + miniViewportWidth);
//				bool withinDotY = (dotWorldPosY >= miniScrollPos.y) && (dotWorldPosY <= miniScrollPos.y + miniViewportHeight);
//
//				// 描画範囲を計算して修正
//				float drawX = 0, drawY = 0, drawWidth = float(blockSize), drawHeight = float(blockSize);
//				if (!withinDotX) {
//					if (dotWorldPosX < miniScrollPos.x)
//						drawX = miniScrollPos.x - dotWorldPosX;
//					else
//						drawWidth -= dotWorldPosX + blockSize - (miniScrollPos.x + miniViewportWidth);
//				}
//				if (!withinDotY) {
//					if (dotWorldPosY < miniScrollPos.y)
//						drawY = miniScrollPos.y - dotWorldPosY;
//					else
//						drawHeight -= dotWorldPosY + blockSize - (miniScrollPos.y + miniViewportHeight);
//				}
//				// 描画
//				newDrawQuad(miniScreenVertex_[y][x], drawX, drawY, drawWidth, drawHeight, mapTexture.Handle, RED);
//
//			}
//		}
//	}
//}
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
	//	for (int y = 0; y < mapyMax; y++) {
	//		for (int x = 0; x < mapxMax; x++) {
	//			// ミニマップのビューポート内にあるかどうかの判定
	//			bool withinMiniX = (worldPos_[y][x].x + size_ / 2 >= scrollPos_.x) && (worldPos_[y][x].x - size_ / 2 <= scrollPos_.x + viewportWidth_);
	//			bool withinMiniY = (worldPos_[y][x].y + size_ / 2 >= scrollPos_.y) && (worldPos_[y][x].y - size_ / 2 <= scrollPos_.y + viewportHeight_);
	//
	//			// ミニマップのビューポート内にある場合のみ描画
	//			if (withinMiniX && withinMiniY && map[y][x] == BLOCK) {
	//				// ブロックの各ドットごとに描画
	//				for (int dotY = 0; dotY < blockSize; dotY++) {
	//					for (int dotX = 0; dotX < blockSize; dotX++) {
	//						// ドットがビューポート内にあるかどうかの判定
	//						dotWorldPosX[y][x] = worldPos_[y][x].x - blockSize / 2 + dotX;
	//						dotWorldPosY[y][x] = worldPos_[y][x].y - blockSize / 2 + dotY;
	//						withinDotX[y][x] = (dotWorldPosX[y][x] >= miniScrollPos.x) && (dotWorldPosX[y][x] <= miniScrollPos.x + miniViewportWidth);
	//						withinDotY[y][x] = (dotWorldPosY[y][x] >= miniScrollPos.y) && (dotWorldPosY[y][x] <= miniScrollPos.y + miniViewportHeight);
	//					}
	//				}
	//
	//					// ドットを描画
	//					newDrawQuad(miniScreenVertex_[y][x], 0, 0, dotWorldPosX[y][x], dotWorldPosY[y][x], mapTexture.Handle, RED);
	//					/*Novice::DrawBox(int(dotWorldPosX), int(dotWorldPosY),1,1,0,RED,kFillModeSolid);
	//				*/
	//				
	//			}
	//		}
	//
	//	}
	//}
	//
	//
