#include "ScenePrototype.h"
#include"InputManager.h"

ScenePrototype::ScenePrototype() {
	player_ = new Player();
	mapchip_ = new Mapchip();
	camera_ = new Camera();
}

void ScenePrototype::Init() {

}

void ScenePrototype::Update() {
	
	player_->Update();//プレイヤーの更新
	mapchip_->Update();

	//当たり判定
	player_->MapChipColligion();
	//レンダリングパイプライン	
	player_->RenderingPipeline();
	mapchip_->RenderingPipeline();
}

void ScenePrototype::Draw() {
	mapchip_->Draw();
	player_->Draw();
}