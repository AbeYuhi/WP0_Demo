#include "InGameScene.h"

InGameScene::InGameScene() {

}

InGameScene::~InGameScene() {

}

void InGameScene::Finalize() {}

void InGameScene::Initialize() {
	sceneNo_ = INGAME;

	//基本機能
	winApp_ = WinApp::GetInstance();
	directXCommon_ = DirectXCommon::GetInstance();
	input_ = InputManager::GetInstance();
	audioManager_ = AudioManager::GetInstance();
	randomManager_ = RandomManager::GetInstance();
	mainCamera_ = MainCamera::GetInstance();
	spriteCamera_ = SpriteCamera::GetInstance();

	//デバックモード中ならdebugカメラを有効に
	isDebugCamera_ = debugMode_;

	//インゲームカメラ
	gameCamera_ = std::make_unique<InGameCamera>();
	gameCamera_->Initialize();
	//デバッグカメラ
	debugCamera_ = std::make_unique<DebugCamera>();
	debugCamera_->Initialize();

	//スプライトカメラの初期化
	spriteCamera_->Initialize();

	//平行光源
	lightObj_ = std::make_unique<LightObject>();
	lightObj_->Initialize();

	//影
	shadow_ = std::make_unique<Shadow>();
	shadow_->Initialize();

	//ブレンドモード
	blendMode_ = kBlendModeNormal;

	//ゲームオブジェクト
	testParticle1_ = std::make_unique<TestParticle>();
	testParticle1_->Initialize();

	yukariModel_ = Model::Create("yukari", "yukari.obj");
	yukariModelInfo_.Initialize();
	yukariModelInfo_.materialInfo_.material_->enableLightint = false;
	yukariModelInfo_.worldTransform_.data_.translate_.y = 1;

	cubeModel_ = Model::Create("cubeGltf", "cube.gltf");
	cubeModelInfo_.Initialize();
}

void InGameScene::Update() {

	//カメラの更新
#ifdef _DEBUG
	ImGui::Begin("Debug");
	ImGui::Checkbox("UseDebugCamera", &isDebugCamera_);
	ImGui::End();
#endif // _DEBUG
	
	if (isDebugCamera_) {
		debugCamera_->Update();
		mainCamera_->Update(debugCamera_->GetWorldMatrix(), debugCamera_->GetProjectionMatrix());
	}
	else {
		gameCamera_->Update();
		mainCamera_->Update(gameCamera_->GetWorldMatrix(), gameCamera_->GetProjectionMatrix());
	}
	//スプライトカメラの更新
	spriteCamera_->Update();
	//ライトの更新
	lightObj_->Update();
	//影の更新
	shadow_->Update(lightObj_->GetDirectionalLightData(0).direction);

	//パーティクルの更新
	testParticle1_->Update();

	if (input_->IsTriggerKey(DIK_SPACE)) {
		sceneNo_ = TITLE;
	}

#ifdef _DEBUG
	ImGui::BeginTabBar("RenderItemInfo");
	if (ImGui::BeginTabItem("YukariModel")) {
		ImGui::SliderFloat3("pos", &yukariModelInfo_.worldTransform_.data_.translate_.x, -10, 10);
		ImGui::SliderFloat3("rotate", &yukariModelInfo_.worldTransform_.data_.rotate_.x, -10, 10);
		ImGui::SliderFloat3("scale", &yukariModelInfo_.worldTransform_.data_.scale_.x, -10, 10);
		ImGui::SliderFloat("shininess", &yukariModelInfo_.materialInfo_.material_->shininess, 0, 100);
		ImGui::EndTabItem();
	}
	if (ImGui::BeginTabItem("cubeModel")) {
		ImGui::SliderFloat3("pos", &cubeModelInfo_.worldTransform_.data_.translate_.x, -10, 10);
		ImGui::SliderFloat3("rotate", &cubeModelInfo_.worldTransform_.data_.rotate_.x, -10, 10);
		ImGui::SliderFloat3("scale", &cubeModelInfo_.worldTransform_.data_.scale_.x, -10, 10);
		ImGui::Checkbox("isAnimation", &cubeModelInfo_.animationInfo_.isAnimation);
		for (int index = 0; index < cubeModel_->GetAnimationNum(); index++) {
			if (ImGui::Button(cubeModel_->GetAnimationName(index).c_str())) {
				cubeModelInfo_.animationInfo_.name = cubeModel_->GetAnimationName(index);
			}
		}

		ImGui::EndTabItem();
	}
	ImGui::EndTabBar();

	ImGui::Begin("BlendMode");
	const char* modes[] = { "None", "Normal", "Add", "SubTract", "MultiPly", "Screen" };
	ImGui::Combo("blendMode", &blendMode_, modes, IM_ARRAYSIZE(modes));
	GraphicsPipelineManager::GetInstance()->SetBlendMode(static_cast<BlendMode>(blendMode_));
	ImGui::End();
#endif // _DEBUG

	yukariModelInfo_.Update();
	cubeModelInfo_.Update();
}

void InGameScene::Draw() {
	//カメラの転送
	mainCamera_->Draw();
	//ライティングの転送
	lightObj_->Draw();
	//シャドウの転送
	shadow_->Draw();

	///背景スプライトの描画開始 

	

	///背景スプライト描画終了
	//深度バッファのクリア
	directXCommon_->ClearDepthStencilBuffer();

	///前面スプライトの描画開始



	///前面スプライトの描画終了

	///オブジェクトの描画開始

	yukariModel_->Draw(yukariModelInfo_);
	cubeModel_->Draw(cubeModelInfo_);
	testParticle1_->EmitterDraw();

	///オブジェクトの描画終了

	///パーティクルの描画

	testParticle1_->Draw();


	///パーティクルの描画終了
}