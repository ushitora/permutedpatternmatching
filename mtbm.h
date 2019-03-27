#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

#include "mttrie.h"

using namespace std;

class MTBM{
	private:
	int alphabet;
	vector<vector<int> > pattern;
	vector<vector<int> > pattern_prefix_index;
	vector<vector<int> > text_prefix_index;
	vector<int> suffix;
	map<vector<int>, int> bmBc;
	vector<int> bmGs;
	MTTrie mt_trie;

	public:
	MTBM();
	MTBM(vector<vector<int> > P, int alpha);

	void createTrie();
	vector<vector<int> > createPrefixIndex(vector<vector<int> > &mt_string);
	vector<int> bucketSortCollumn(vector<vector<int> > &mt_string, int index);
	vector<vector<int> > radixSort(vector<vector<int> > &mt_String, int start, int end);
	bool compareCollumn(int start1, int index1, vector<vector<int> > &string1, vector<vector<int> > &prefix_index1, int start2, int index2, vector<vector<int> > &string2, vector<vector<int> > &prefix_index2);

	void suffixes();
	void preBmBc();
	void preBmGs();
	vector<int> match(vector<vector<int> > &text);
	vector<int> matchTrie(vector<vector<int> > &text);
};