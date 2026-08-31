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
	
	bool isKeyDownNow = (CheckHitKey(KEY_INPUT_RETURN) != 0);
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
	
}
