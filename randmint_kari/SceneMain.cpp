#include "SceneMain.h"
#include "Dxlib.h"

namespace
{
	constexpr int contentNumMax = 20;
}

SceneMain::SceneMain() : 
	m_frameCount(0)
{
}

SceneMain::~SceneMain()
{
}

void SceneMain::Init()
{
	m_cardMana.Init();
	m_frameCount = 0;
	
}

void SceneMain::End()
{
	m_cardMana.End();
}

void SceneMain::Update()
{
	m_cardMana.Update();
	m_frameCount++;
}

void SceneMain::Draw()
{
	m_cardMana.Draw();
	DrawString(0, 0, "SceneMain", GetColor(255, 255, 255));
	DrawFormatString(0, 16, GetColor(255, 255, 255), "FRAME:%d", m_frameCount);
}
