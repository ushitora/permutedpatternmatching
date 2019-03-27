#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>

using namespace std;

class FilterKMP{
	private:
	int alphabet;
	vector<vector<int> > pattern;
	vector<vector<int> > pattern_bucket;
	vector<int> kmpNext;
	public:
	FilterKMP();
	FilterKMP(vector<vector<int> > P, int alpha);

	vector<vector<int> > radixSort(vector<vector<int> > &mt_String, int start, int end);
	vector<vector<int> > createBucket(vector<vector<int> > mt_string);
	bool compareCollumnInt(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2);
	bool compareCollumnString(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2);
	bool exactMatch(vector<vector<int> > &p, vector<vector<int> > &t, int start);
	vector<int> match(vector<vector<int> > &text);
};