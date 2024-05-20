#include "ScenePrototype.h"
#include"InputManager.h"
#include"Easing.h"

ScenePrototype::ScenePrototype() {
	player_ = new Player();
	mapchip_ = new Mapchip();
	camera_ = new Camera();
	miniCamera_ = new MiniCamera();
	backGround_ = new BackGround();
	monitor_ = new Monitor();
	texture_.Handle = Novice::LoadTexture("./Resources/RedArrow.png");

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
	et_ = 0;
}

void ScenePrototype::Init() {

}

void ScenePrototype::Update() {
	

	camera_->Update(*player_, *mapchip_, { 48 * 23,0 },{});//カメラの更新
	miniCamera_->Update(*player_, *mapchip_, { 0,0 },{48*12,0});
	miniCamera_->CombineMonitor(*monitor_);
	backGround_->Update();
	monitor_->Update();
	mapchip_->Update();//マップチップの更新
	player_->Update();//プレイヤーの更新

	if (player_->GetWorldPos().x < 1128) {
		et_ += 0.04f;
		miniCamera_->zoomLevel_.x = easeInSine(et_, 0, 0.5f);
		miniCamera_->zoomLevel_.y = easeInSine(et_, 0, 0.5f);
		monitor_->SetScaleX(easeInSine(et_, 0, 1.0f));
		monitor_->SetScaleY(easeInSine(et_, 0, 1.0f));
		if (et_ >= 1) {
			et_ = 1;
		}
	}
	else {
		et_ -= 0.04f;
		miniCamera_->zoomLevel_.x = easeInSine(et_, 0, 0.5f);
		miniCamera_->zoomLevel_.y = easeInSine(et_, 0, 0.5f);
		monitor_->SetScaleX(easeInSine(et_, 0, 1.0f));
		monitor_->SetScaleY(easeInSine(et_, 0, 1.0f));
		if (et_ <= 0) {
			et_ = 0;
		}
	}
	//当たり判定
	player_->MapChipColligion();

	//レンダリングパイプライン	
	backGround_->RenderingPipeline();
	monitor_->RenderingPipeline();
	player_->RenderingPipeline();
	mapchip_->RenderingPipeline();

	//ミニレンダリングパイプライン	
	player_->MiniRenderingPipeline();
	mapchip_->MiniRenderingPipeline();
	backGround_->MiniRenderingPipeline();
	
}

void ScenePrototype::Draw() {

	backGround_->Draw();
	backGround_->MiniDraw();
	mapchip_->Draw();
	player_->MiniDraw();
	mapchip_->MiniDraw();
	monitor_->Draw();
	Novice::DrawSprite(int(100), int(500),texture_.Handle, easeInSine(et_, 0, -1.5f), easeInSine(et_, 0, 1.0f), 0, WHITE);
	player_->Draw();

	//debug------------------------------------------------------------------------------------------------------------------

	/*Novice::DrawEllipse(int(backGround_->GetScreenCenter().x), int(backGround_->GetScreenCenter().y), 10, 10, 0, RED, kFillModeSolid);
	Novice::DrawEllipse(int(backGround_->GetMiniScreenCenter().x), int(backGround_->GetMiniScreenCenter().y), 10, 10, 0, GREEN, kFillModeSolid);*/

}