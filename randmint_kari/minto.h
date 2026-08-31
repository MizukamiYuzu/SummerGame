#pragma once
#include "Dxlib.h"
#include "Game.h"

class minto
{
public:
	minto();
	~minto();

	void Init();
	void End();
	void Draw();

	void SetPlant(bool plant) { m_plant = plant; }
	bool GetPlant() { return m_plant; }
	void GetAddEnergy(int addEnergy);
	void GetWither();

	void SetHandle(int handle) { m_handle = handle; }

	int GetGrow() { return m_energy; }



private:
	int m_energy = 0;	// エネルギー

	int m_fontHandle;	// フォント
	
	bool m_plant = true;

	int m_handle;

	
	
};



