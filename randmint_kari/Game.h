#pragma once
#include <random>

//メルセンヌ・ツイスタ
int static MyRandom(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 mt(rd());

	std::uniform_int_distribution<int> dist(min, max);
	return dist(mt);
}

namespace Game
{
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	constexpr int kScreenDepth = 32;
}