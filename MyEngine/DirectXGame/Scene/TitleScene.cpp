#include "TitleScene.h"

TitleScene::TitleScene() {}

TitleScene::~TitleScene() {}

void TitleScene::Finalize() {

}

void TitleScene::Initialize() {
	sceneNo_ = TITLE;

	//基本機能
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();
	mainCamera_ = MainCamera::GetInstance();
	spriteCamera_ = SpriteCamera::GetInstance();

	//カメラ
	titleCamera_ = std::make_unique<TitleCamera>();
	titleCamera_->Initialize();

	//画像読み込み
	monsterBallHandle_ = TextureManager::Load("monsterBall.png");
	fenceHandle_ = TextureManager::Load("fence.png");

	sprite_[0] = Sprite::Create();
	spriteInfo_[0].Initialize(monsterBallHandle_, {320, 180});
	spriteInfo_[0].worldTransform_.data_.translate_ = {200, 360};

	sprite_[1] = Sprite::Create();
	spriteInfo_[1].Initialize(fenceHandle_, { 320, 180 });
	spriteInfo_[1].worldTransform_.data_.translate_ = { 600, 360 };
}

void TitleScene::Update() {
	titleCamera_->Update();
	mainCamera_->Update(titleCamera_->GetWorldMatrix(), titleCamera_->GetProjectionMatrix());
	spriteCamera_->Update();

	if (input_->IsTriggerKey(DIK_SPACE)) {
		sceneNo_ = INGAME;
	}

	spriteInfo_[0].Update();
	spriteInfo_[1].Update();
}

void TitleScene::Draw() {
	//カメラの転送
	mainCamera_->Draw();

	sprite_[0]->Draw(spriteInfo_[0]);
	sprite_[1]->Draw(spriteInfo_[1]);

}