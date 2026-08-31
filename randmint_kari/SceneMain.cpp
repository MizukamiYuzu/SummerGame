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
	// 背景画像
	m_graphBgMainHandle = LoadGraph("data/img/BgMainScene.jpg");
	// カードの背景
	m_graphCardBgHandle = LoadGraph("data/img/serihuwaku.png");

	m_fontHandle = CreateFontToHandle("クラフト明朝", 48, -1, -1);

	m_soundMainBgHandle = LoadSoundMem("data/sound/MainSceneBgm.mp3");
	PlaySoundMem(m_soundMainBgHandle, DX_PLAYTYPE_LOOP);

	m_isEnd = false;
	m_isKeyDownBefore = false;
	// カードマネージャーの作成
	m_pCardManager = new CardManager;
	// カードマネージャーの初期化
	m_pCardManager->Init();

	// タイマーの作成
	m_pTimer = new Timer;

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
	DeleteGraph(m_graphBgMainHandle);
	DeleteGraph(m_graphCardBgHandle);

	DeleteSoundMem(m_soundMainBgHandle);
}

void SceneMain::Update()
{

	bool isKeyDownNow = (CheckHitKey(KEY_INPUT_A) != 0);

	bool isKeyPressedThisFrame = (!m_isKeyDownBefore) && isKeyDownNow;

	m_isClickBefore = m_isClickNow;
	m_isClickNow = (GetMouseInput() & MOUSE_INPUT_LEFT);

	if (!(m_pCardManager->GetDead() == true || m_pCardManager->GetGrow() || m_pCardManager->GetWin()))
	{
		// カードマネージャーの更新
		m_pCardManager->Update();
	}
	else
	{
		if (!m_isTimerStart)
		{
			m_pTimer->SetReset(300);
			m_isTimerStart = true;
		}
		if (m_pTimer->IsTimeOver())
		{
			m_isEnd = true;
		}
	}
	
	// フレームカウントの更新
	m_frameCount++;

	

	m_isKeyDownBefore = isKeyDownNow;

	
	
	
}

void SceneMain::Draw()
{
	// 背景画像
	DrawRectRotaGraph(0 + Game::kScreenWidth / 2, 0 + Game::kScreenHeight / 2,
						0, 0,
						Game::kScreenWidth, Game::kScreenHeight,
						1.0, 0.0,
						m_graphBgMainHandle, true);

	// カード下の画像背景(自分のカード)
//	DrawExtendGraph(5, Game::kScreenHeight / 2 + 30, Game::kScreenWidth - 250, Game::kScreenHeight + 150 , m_graphCardBgHandle, true);
//	DrawExtendGraph(5, Game::kScreenHeight / 2 + 30, Game::kScreenWidth - 250, Game::kScreenHeight + 150, m_graphCardBgHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawRotaGraph3(Game::kScreenWidth / 2 - 140, Game::kScreenHeight -50, 1920 / 2, 1080 / 2, 0.55, 0.55, 0.0, m_graphCardBgHandle, true, false);
	/*DrawRectRotaGraph(1920/2 -450, Game::kScreenHeight - 50,
		0, 0,
		1920, 1080,
		0.55, 0.0,
		m_graphCardBgHandle, true);*/
	DrawRotaGraph3(Game::kScreenWidth - 380, 40, 1920 / 2, 1080 / 2, 0.4, 0.55, DX_PI, m_graphCardBgHandle, true, false);
	/*DrawRectRotaGraph(Game::kScreenWidth -500, 30,
		0, 0,
		1920, 1080,
		0.55, DX_PI,
		m_graphCardBgHandle, true);*/
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// カードマネージャーの描画
	m_pCardManager->Draw();
#ifdef _DEBUG
	// 現在のシーン名の表示
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	// 現在のシーンの実行時間(フレーム数)の表示
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
#endif // _DEBUG
	
	if (m_pCardManager->GetDead() == true || m_pCardManager->GetGrow() || m_pCardManager->GetWin())
	{
		DrawFormatString(Game::kScreenWidth/2, Game::kScreenHeight/2, GetColor(0, 0, 0), "%d", m_pTimer->GetTimer());
		DrawBox(100, Game::kScreenHeight / 2 - 50, Game::kScreenWidth - 100, Game::kScreenHeight / 2 + 100, GetColor(255, 255, 255), true);
		int posX = 100;
		if (m_pCardManager->GetDead() == true)
		{
			if (m_pCardManager->GetWhoWin())
			{
				m_WinText = "あなたはミント王になるために皆殺しにした";
			}
			else
			{
				m_WinText = "NPCはミント王になるために皆殺しにした";
			}
			posX = 500;
			
		}
		else if (m_pCardManager->GetGrow())
		{
			if (m_pCardManager->GetWhoWin())
			{
				m_WinText = "あなたはミント王になった";
			}
			else
			{
				m_WinText = "NPCはミント王になった";
			}

			posX = 300;
		}
		else
		{
			if (m_pCardManager->GetWhoWin())
			{
				m_WinText = "あなたは特殊な方法でミント王になった";
			}
			else
			{
				m_WinText = "NPCは特殊な方法でミント王になった";
			}
			posX = 450;
		}
		DrawFormatStringToHandle(Game::kScreenWidth / 2 - posX, Game::kScreenHeight / 2, GetColor(0, 0, 0), m_fontHandle,"%s", m_WinText.c_str());
		
		
			
	}

	
	

	
}
