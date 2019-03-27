#pragma once

#include <algorithm>
#include <queue>
#include <vector>

using namespace std;

class MTKMP{
	private:
	vector<vector<int> > pattern;
	vector<vector<int> > PPA;
	vector<vector<int> > TPA;
	vector<vector<int> > sorted_pattern;
	vector<int> kmpNext;
	int alphabet;
	public:
	MTKMP();
	MTKMP(vector<vector<int> > P, int alpha);

	vector<vector<int> > createPA(vector<vector<int> > mt_string);
	vector<vector<int> > radixSort(vector<vector<int> > &mt_string, int start, int end);
	int calculateTreshold(vector<int> data, int index);
	bool compareCollumn(int start1, int index1, vector<vector<int> > &text, int start2, int index2);
	bool comparePattern(int index1, int index2, int l);
	vector<int> match(vector<vector<int> > &text);
};