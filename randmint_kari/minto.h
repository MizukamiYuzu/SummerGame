#pragma once
class minto
{
public:
	minto();
	~minto();

	void SetPlant(bool plant) { m_plant = plant; }
	bool GetPlant() { return m_plant; }
	void GetAddEnergy(int addEnergy);
	void GetWither();



private:
	int m_energy = 0;	// エネルギー
	
	bool m_plant;

	
};



