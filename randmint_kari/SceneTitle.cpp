#include "SceneTitle.h"

SceneTitle::SceneTitle():
	m_isEnd(false),
	m_isKeyDownBefore(false)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::Init()
{
	m_isEnd = false;
	m_isKeyDownBefore = false;
	
	// タイトル背景画像グラフ
	m_BgTitleGraph = LoadGraph("data/img/RandoMitoTitle.jpeg");

	RuleSousa1Handle = LoadGraph("data/img/Rule/Sousa1.PNG");
	RuleSousa2Handle = LoadGraph("data/img/Rule/Sousa2.PNG");
	RuleSousa3Handle = LoadGraph("data/img/Rule/Sousa3.PNG");
	RuleWin1Handle = LoadGraph("data/img/Rule/Win1.PNG");
	RuleWin2Handle = LoadGraph("data/img/Rule/Win2.PNG");
	RuleWin3Handle = LoadGraph("data/img/Rule/Win3.PNG");
	RuleWin4Handle = LoadGraph("data/img/Rule/Win4.PNG");
	RuleFinaleHandle = LoadGraph("data/img/Rule/finale.PNG");
	RuleArrowHandle = LoadGraph("data/img/Rule/arrow.PNG");
	RuleCloseHandle = LoadGraph("data/img/Rule/close.gif");


	m_fontHandle = CreateFontToHandle("クラフト明朝", 48, -1, -1);

	// サウンド
	m_soundHandle = LoadSoundMem("data/sound/TitleSceneBgm.mp3");
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_LOOP);
}

void SceneTitle::End()
{
	DeleteGraph(m_BgTitleGraph);
	DeleteSoundMem(m_soundHandle);
	DeleteGraph(RuleSousa1Handle);
	RuleSousa2Handle = LoadGraph("data/img/Rule/Sousa2.PNG");
	RuleSousa3Handle = LoadGraph("data/img/Rule/Sousa3.PNG");
	DeleteGraph(RuleSousa1Handle);
	DeleteGraph(RuleSousa2Handle);
	DeleteGraph(RuleSousa3Handle);
	DeleteGraph(RuleWin1Handle);
	DeleteGraph(RuleWin2Handle);
	DeleteGraph(RuleWin3Handle);
	DeleteGraph(RuleWin4Handle);
	DeleteGraph(RuleFinaleHandle);
	DeleteGraph(RuleArrowHandle);
	DeleteGraph(RuleCloseHandle);
}

void SceneTitle::Update()
{
	
	bool isKeyDownNow = (GetMouseInput() == MOUSE_INPUT_LEFT);
	bool isKeyPressedThisFrame = (!m_isKeyDownBefore) && isKeyDownNow;
	if (isKeyPressedThisFrame)
	{
		m_isEnd = true;
	}
	
}

void SceneTitle::Draw()
{
	DrawRectRotaGraph(0 + Game::kScreenWidth / 2, 0 + Game::kScreenHeight / 2, 0, 0,Game::kScreenWidth,Game::kScreenHeight, 1.0,0.0, m_BgTitleGraph, true);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - 200, Game::kScreenHeight / 2 + 30, GetColor(0, 0, 0), m_fontHandle, "Please left-click");
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 + 90, GetColor(0, 0, 0), m_fontHandle, "the mouse.");
	
}
