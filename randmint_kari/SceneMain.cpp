#include "SceneMain.h"
#include "Dxlib.h"

namespace
{
	// constexprはコンパイル時に定数化
	// constは代入時に定数化する
	constexpr int kContentNumMax = 20;

	
}

SceneMain::SceneMain() : 
	m_isEnd(false),
	m_isKeyDownBefore(false),
	m_isClickBefore(false),
	m_isClickNow(false),
	m_frameCount(0),
	m_pCardManager(nullptr)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	// グラフのロード
	// 山札画像
	m_deckHandle = LoadGraph("data/img/deck.png");
	// スキップ画像
	m_skipGraphHandle = LoadGraph("data/img/skip_1.png");


	m_isEnd = false;
	m_isKeyDownBefore = false;
	// カードマネージャーの作成
	m_pCardManager = new CardManager;
	// カードマネージャーの初期化
	m_pCardManager->Init();


	// 山札の画像
	m_pCardManager->SetHandleDeck(m_deckHandle);
	// スキップの画像
	m_pCardManager->SteHandleSkip(m_skipGraphHandle);
	


	// フレームカウントの初期化
	m_frameCount = 0;

	
}

void SceneMain::End()
{
	m_pCardManager->End();
	DeleteGraph(m_deckHandle);
	DeleteGraph(m_skipGraphHandle);
}

void SceneMain::Update()
{

	bool isKeyDownNow = (CheckHitKey(KEY_INPUT_A) != 0);

	bool isKeyPressedThisFrame = (!m_isKeyDownBefore) && isKeyDownNow;

	m_isClickBefore = m_isClickNow;
	m_isClickNow = (GetMouseInput() & MOUSE_INPUT_LEFT);


	// カードマネージャーの更新
	m_pCardManager->Update();
	// フレームカウントの更新
	m_frameCount++;

	if (m_pCardManager->GetDead() == true || m_pCardManager->GetGrow() || m_pCardManager->GetWin())
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
