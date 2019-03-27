#pragma once

#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <map>

using namespace std;

class FilterBM{
	private:
	int alphabet;
	vector<vector<int> > pattern;
	vector<vector<int> > pattern_bucket;
	vector<int> suffix;
	map<vector<int>, int> bmBc;
	vector<int> bmGs;

	public:
	FilterBM();
	FilterBM(vector<vector<int> > P, int alpha);

	vector<vector<int> > radixSort(vector<vector<int> > &mt_String, int start, int end);
	vector<vector<int> > createBucket(vector<vector<int> > mt_string);
	bool compareCollumnInt(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2);
	bool compareCollumnString(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2);
	bool exactMatch(vector<vector<int> > &p, vector<vector<int> > &t, int start);

	void suffixes();
	void preBmBc();
	void preBmGs();
	vector<int> match(vector<vector<int> > &text);
};