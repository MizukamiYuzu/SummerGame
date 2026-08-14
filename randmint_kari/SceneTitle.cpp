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
}

void SceneTitle::End()
{
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
	DrawFormatString(0, 0, GetColor(255, 255, 255), "nemuine");
}
