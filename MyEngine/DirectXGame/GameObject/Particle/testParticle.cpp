#include "testParticle.h"

void TestParticle::Initialize() {

	particle0_ = std::make_unique<PlaneParticle>(100);
	particle0_->Initialize();

	particle1_ = std::make_unique<PlaneParticle>(100);
	particle1_->Initialize();
	uint32_t textureHandle = TextureManager::GetInstance()->Load("monsterBall.png");
	particle1_->SetTextureHandle(textureHandle);

	scale = { 1, 1, 1 };
}

void TestParticle::Update() {

#ifdef _DEBUG
	ImGui::Begin("particlePos");
	ImGui::SliderFloat3("pos", &pos.x, -10, 10);
	ImGui::SliderFloat3("scale", &scale.x, -10, 10);
	ImGui::End();
#endif // _DEBUG

	particle0_->SetEmitterPos(pos);
	particle0_->SetEmitterScale(scale);
	particle1_->SetEmitterPos(pos);
	particle1_->SetEmitterScale(scale);

	particle0_->Update();
	particle1_->Update();
}

void TestParticle::Draw() {

	particle0_->Draw();
	particle1_->Draw();

}

void TestParticle::EmitterDraw() {
	particle0_->EmitterDraw();
	particle1_->EmitterDraw();
}
