﻿#include "ScenePrototype.h"
#include"InputManager.h"

ScenePrototype::ScenePrototype() {
	player_ = new Player();
	mapchip_ = new Mapchip();
	camera_ = new Camera();
	miniCamera_ = new MiniCamera();
	backGround_ = new BackGround();
	monitor_ = new Monitor();

	//借りる*********************************************
	//カメラ
	player_->SetCamera(camera_);
	mapchip_->SetCamera(camera_);
	backGround_->SetCamera(camera_);
	monitor_->SetCamera(camera_);
	//ミニカメラ
	player_->SetMiniCamera(miniCamera_);
	mapchip_->SetMiniCamera(miniCamera_);
	backGround_->SetMiniCamera(miniCamera_);
	player_->SetMapChip(mapchip_);

	//初期化
	miniCamera_->Init();
	backGround_->Init();
	player_->Init();
	mapchip_->Init();
	monitor_->Init();
}

void ScenePrototype::Init() {

}

void ScenePrototype::Update() {


	camera_->Update(*player_,*mapchip_);//カメラの更新
	miniCamera_->Update(*player_, *mapchip_);
	miniCamera_->CombineMonitor(*monitor_);
	player_->Update();//プレイヤーの更新
	mapchip_->Update();//マップチップの更新
	monitor_->Update();

	//当たり判定
	player_->MapChipColligion();


	//レンダリングパイプライン	
	player_->RenderingPipeline();
	mapchip_->RenderingPipeline();
	backGround_->RenderingPipeline();
	monitor_->RenderingPipeline();

	//ミニレンダリングパイプライン	
	player_->MiniRenderingPipeline();
	mapchip_->MiniRenderingPipeline();
	backGround_->MiniRenderingPipeline();
}

void ScenePrototype::Draw() {

	backGround_->Draw();
	backGround_->MiniDraw();
	mapchip_->Draw();
	player_->Draw();
	player_->MiniDraw();
	mapchip_->MiniDraw();
	monitor_->Draw();

	//debug------------------------------------------------------------------------------------------------------------------
	
	/*Novice::DrawEllipse(int(backGround_->GetScreenCenter().x), int(backGround_->GetScreenCenter().y), 10, 10, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(int(backGround_->GetMiniScreenCenter().x), int(backGround_->GetMiniScreenCenter().y), 10, 10, 0, GREEN, kFillModeSolid);*/

}