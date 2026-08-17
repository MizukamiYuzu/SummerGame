#include "SceneMain.h"
#include "Dxlib.h"

namespace
{
	// constexprはコンパイル時に定数化
	// constは代入時に定数化する
	constexpr int contentNumMax = 20;
}

SceneMain::SceneMain() : 
	m_isEnd(false),
	m_isKeyDownBefore(false),
	m_frameCount(0),
	m_pCardManager(nullptr)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_isEnd = false;
	m_isKeyDownBefore = false;
	// カードマネージャーの作成
	m_pCardManager = new CardManager;
	// カードマネージャーの初期化
	m_pCardManager->Init();
	// フレームカウントの初期化
	m_frameCount = 0;

	
}

void SceneMain::End()
{
	m_pCardManager->End();
}

void SceneMain::Update()
{

	bool isKeyDownNow = (CheckHitKey(KEY_INPUT_A) != 0);

	bool isKeyPressedThisFrame = (!m_isKeyDownBefore) && isKeyDownNow;


	// カードマネージャーの更新
	m_pCardManager->Update();
	// フレームカウントの更新
	m_frameCount++;

	if (m_pCardManager->GetDead() == true)
	{
		m_isEnd = true;
	}

	m_isKeyDownBefore = isKeyDownNow;
}

void SceneMain::Draw()
{
	// カードマネージャーの描画
	m_pCardManager->Draw();
	// 現在のシーン名の表示
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	// 現在のシーンの実行時間(フレーム数)の表示
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);

	
}
