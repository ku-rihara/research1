#include "ScenePrototype.h"
#include"InputManager.h"

ScenePrototype::ScenePrototype() {
	player_ = new Player();
	mapchip_ = new Mapchip();
	camera_ = new Camera();
	miniCamera_ = new MiniCamera();
	backGround_ = new BackGround();

	//借りる*********************************************
	//カメラ
	player_->SetCamera(camera_);
	mapchip_->SetCamera(camera_);
	backGround_->SetCamera(camera_);
	//ミニカメラ
	player_->SetMiniCamera(miniCamera_);
	/*mapchip_->SetMiniCamera(minicamera_);*/
	backGround_->SetMiniCamera(miniCamera_);
	player_->SetMapChip(mapchip_);

	//初期化
	miniCamera_->Init();
	backGround_->Init();
	player_->Init();
	mapchip_->Init();
}

void ScenePrototype::Init() {

}

void ScenePrototype::Update() {
	camera_->Update();//カメラの更新
	player_->Update();//プレイヤーの更新
	mapchip_->Update();//マップチップの更新
	
	//当たり判定
	player_->MapChipColligion();
	backGround_->Update();

	//レンダリングパイプライン	
	player_->RenderingPipeline();
	mapchip_->RenderingPipeline();

	player_->MiniRenderingPipeline();
}

void ScenePrototype::Draw() {
	Novice::ScreenPrintf(200, 200, "%f", player_->GetWorldPos().x);
	Novice::ScreenPrintf(200, 220, "%f", player_->GetWorldPos().y);
	Novice::ScreenPrintf(200, 270, "%f", camera_->GetWorldPos().x);
	Novice::ScreenPrintf(200, 280, "%f", camera_->GetWorldPos().y);
	/*backGround_->Draw();*/
	mapchip_->Draw();
	player_->Draw();
	player_->MiniDraw();
}