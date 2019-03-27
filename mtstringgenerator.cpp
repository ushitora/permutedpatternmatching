#include "mtstringgenerator.h"

vector<vector<int>> MTStringGenerator::generateMultiTrack(int N, int M, int sigma)
{
	vector<vector<int> > mt;
	for(int i = 0;i < M;i++){
		vector<int> track;
		for(int j = 0;j < N;j++){
			track.push_back(generator()%sigma);
		}
		mt.push_back(track);
	}
	return mt;
}
