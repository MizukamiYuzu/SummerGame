#include "minto.h"

minto::minto()
{
}

minto::~minto()
{
}

void minto::GetAddEnergy(int addEnergy)
{
	m_energy += addEnergy;
}

void minto::GetWither()
{
	m_plant = false;
	m_energy = 0;
}

