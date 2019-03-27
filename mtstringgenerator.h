#pragma once

#include <string>
#include <random>
#include <chrono>
#include <vector>

using namespace std;

class MTStringGenerator{
	private:
	mt19937 generator;
	public:
	MTStringGenerator(): generator((unsigned)chrono::system_clock::now().time_since_epoch().count()) {};
	MTStringGenerator(int seed): generator(seed) {};
	vector<vector<int> > generateMultiTrack(int N, int M, int sigma);
};