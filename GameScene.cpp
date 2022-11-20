#include "GameScene.h"
#include <cassert>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	delete spriteBG;
	delete object3d;
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);

	this->dxCommon = dxCommon;
	this->input = input;

	// デバッグテキスト用テクスチャ読み込み
	Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png");
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	Sprite::LoadTexture(1, L"Resources/background.png");

	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });

	// 3Dオブジェクト生成

	XMFLOAT3 position = { 0, 0, 0 };
	position = { 0, 0, 0 };

	object3d = Object3d::Create();
	object3d->SetPosition(position);
	object3d->Update();

	for (int i = 0; i < 100; i++)
	{
		XMFLOAT3 pos{};

		const float md_width = 10.0f;

		pos.x = (float)rand() / RAND_MAX * md_width - md_width / 2.0f;
		pos.y = (float)rand() / RAND_MAX * md_width - md_width / 2.0f;
		pos.z = (float)rand() / RAND_MAX * md_width - md_width / 2.0f;


		XMFLOAT3 vel{};

		const float md_vel = 0.1f;

		vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;


		XMFLOAT3 acc{};

		const float md_acc = 0.001f;

		acc.y = -(float)rand() / RAND_MAX * md_acc;

		object3d->Add(300, pos, vel, acc, 1.0f, 0.0f);
	}
}

void GameScene::Update()
{
	int move  = 5;

	if (input->TriggerKey(DIK_1))
	{
		for (int i = 0; i < 100; i++)
		{
			XMFLOAT3 pos{};

			const float md_width = 10.0f;

			pos.x = ((float)rand() / RAND_MAX * md_width - md_width / 2.0f ) - move;
			pos.y = ((float)rand() / RAND_MAX * md_width - md_width / 2.0f );
			pos.z = ((float)rand() / RAND_MAX * md_width - md_width / 2.0f );


			XMFLOAT3 vel{};

			const float md_vel = 0.1f;

			vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;


			XMFLOAT3 acc{};

			const float md_acc = 0.001f;

			acc.y = -(float)rand() / RAND_MAX * md_acc;

			object3d->Add(300, pos, vel, acc, 1.0f, 0.0f);
		}
	}

	if (input->TriggerKey(DIK_2))
	{
		for (int i = 0; i < 100; i++)
		{
			XMFLOAT3 pos{};

			const float md_width = 10.0f;

			pos.x = ((float)rand() / RAND_MAX * md_width - md_width / 2.0f ) + move;
			pos.y = ((float)rand() / RAND_MAX * md_width - md_width / 2.0f );
			pos.z = ((float)rand() / RAND_MAX * md_width - md_width / 2.0f );


			XMFLOAT3 vel{};

			const float md_vel = 0.1f;

			vel.x = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel.y = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;
			vel.z = (float)rand() / RAND_MAX * md_vel - md_vel / 2.0f;


			XMFLOAT3 acc{};

			const float md_acc = 0.001f;

			acc.y = -(float)rand() / RAND_MAX * md_acc;

			object3d->Add(300, pos, vel, acc, 1.0f, 0.0f);
		}
	}

	// オブジェクト移動
	if (input->PushKey(DIK_UP) || input->PushKey(DIK_DOWN) || input->PushKey(DIK_RIGHT) || input->PushKey(DIK_LEFT))
	{
		// 現在の座標を取得
		XMFLOAT3 position = object3d->GetPosition();

		// 移動後の座標を計算
		if (input->PushKey(DIK_UP)) { position.y += 1.0f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 1.0f; }
		if (input->PushKey(DIK_RIGHT)) { position.x += 1.0f; }
		else if (input->PushKey(DIK_LEFT)) { position.x -= 1.0f; }

		// 座標の変更を反映
		object3d->SetPosition(position);
	}

	// カメラ移動
	if (input->PushKey(DIK_W) || input->PushKey(DIK_S) || input->PushKey(DIK_D) || input->PushKey(DIK_A))
	{
		/*if (input->PushKey(DIK_W)) { Object3d::CameraMoveVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveVector({ -1.0f,0.0f,0.0f }); }*/

		if (input->PushKey(DIK_W)) { Object3d::CameraMoveEyeVector({ 0.0f,+1.0f,0.0f }); }
		else if (input->PushKey(DIK_S)) { Object3d::CameraMoveEyeVector({ 0.0f,-1.0f,0.0f }); }
		if (input->PushKey(DIK_D)) { Object3d::CameraMoveEyeVector({ +1.0f,0.0f,0.0f }); }
		else if (input->PushKey(DIK_A)) { Object3d::CameraMoveEyeVector({ -1.0f,0.0f,0.0f }); }
	}
	object3d->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Object3d::PreDraw(cmdList);

	// 3Dオブクジェクトの描画
	object3d->Draw();

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>

	// 3Dオブジェクト描画後処理
	Object3d::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	//Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}
