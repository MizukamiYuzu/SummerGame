#pragma once
class minto
{
public:
	minto();
	~minto();

	void SetPlant(int plant) { m_plant = plant; }
	void GetWither();

private:
	int m_energy = 0;	// エネルギー
	
	bool m_plant;

	
};

