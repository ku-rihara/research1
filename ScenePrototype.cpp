#include "ScenePrototype.h"
#include"InputManager.h"

ScenePrototype::ScenePrototype() {
	player_ = new Player();
	mapchip_ = new Mapchip();
	camera_ = new Camera();
	backGround_ = new BackGround();
}

void ScenePrototype::Init() {

}

void ScenePrototype::Update() {
	camera_->Update();
	player_->Update();//プレイヤーの更新
	mapchip_->Update();
	
	//当たり判定
	player_->MapChipColligion();
	backGround_->Update();

	//レンダリングパイプライン	
	player_->RenderingPipeline();
	mapchip_->RenderingPipeline();
}

void ScenePrototype::Draw() {
	Novice::ScreenPrintf(200, 200, "%f", player_->GetWorldPos().x);
	Novice::ScreenPrintf(200, 220, "%f", player_->GetWorldPos().y);
	Novice::ScreenPrintf(200, 270, "%f",  camera_->GetWorldPos().x);
	Novice::ScreenPrintf(200, 280, "%f", camera_->GetWorldPos().y);
	backGround_->Draw();
	mapchip_->Draw();
	player_->Draw();

}