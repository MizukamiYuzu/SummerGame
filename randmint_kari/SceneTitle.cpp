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

	m_fontHandle = CreateFontToHandle("クラフト明朝", 48, -1, -1);

	// サウンド
	m_soundHandle = LoadSoundMem("data/sound/TitleSceneBgm.mp3");
	PlaySoundMem(m_soundHandle, DX_PLAYTYPE_LOOP);
}

void SceneTitle::End()
{
	DeleteGraph(m_BgTitleGraph);
	DeleteSoundMem(m_soundHandle);
}

void SceneTitle::Update()
{
	
	bool isKeyDownNow = (GetMouseInput() == MOUSE_INPUT_LEFT);
	bool isKeyPressedThisFrame = (!m_isKeyDownBefore) && isKeyDownNow;
	if (isKeyPressedThisFrame)
	{
		m_isEnd = true;
	}
	m_isKeyDownBefore = isKeyDownNow;
}

void SceneTitle::Draw()
{
	DrawRectRotaGraph(0 + Game::kScreenWidth / 2, 0 + Game::kScreenHeight / 2, 0, 0,Game::kScreenWidth,Game::kScreenHeight, 1.0,0.0, m_BgTitleGraph, true);
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - 200, Game::kScreenHeight / 2 + 30, GetColor(0, 0, 0), m_fontHandle, "Please left-click");
	DrawFormatStringToHandle(Game::kScreenWidth / 2 - 100, Game::kScreenHeight / 2 + 90, GetColor(0, 0, 0), m_fontHandle, "the mouse.");
}
