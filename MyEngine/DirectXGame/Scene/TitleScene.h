#pragma once
#include "IScene.h"
#include "Manager/ImGuiManager.h"
#include "Manager/TextureManager.h"
#include "Manager/InputManager.h"
#include "Manager/AudioManager.h"
#include "Manager/ParticleManager.h"
#include "Manager/RandomManager.h"
#include "GameObject/Camera/TitleCamera.h"
#include "GameObject/Camera/MainCamera.h"
#include "GameObject/Camera/SpriteCamera.h"
#include "Data/SpriteItem.h"
#include "Object/Model.h"
#include "Object/Sprite.h"

class TitleScene : public IScene
{
public:
	TitleScene();
	~TitleScene();

	void Initialize() override;

	void Update() override;

	void Draw() override;

	void Finalize() override;

private:
	MainCamera* mainCamera_;
	SpriteCamera* spriteCamera_;
	InputManager* input_;
	AudioManager* audioManager_;
	RandomManager* randomManager_;

	std::unique_ptr<TitleCamera> titleCamera_;


	//テクスチャハンドル
	uint32_t monsterBallHandle_;
	uint32_t fenceHandle_;

	std::shared_ptr<Sprite> sprite_[2];
	SpriteItem spriteInfo_[2];
};