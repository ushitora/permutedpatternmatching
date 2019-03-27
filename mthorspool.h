#pragma once

#include <vector>
#include <algorithm>
#include <queue>
#include <map>

#include "mttrie.h"

using namespace std;

class MTHorspool{
	private:
	int alphabet;
	vector<vector<int> > pattern;
	vector<vector<int> > pattern_prefix_index;
	vector<vector<int> > text_prefix_index;
	map<vector<int>, int> hBc;
	MTTrie mt_trie;

	public:
	MTHorspool();
	MTHorspool(vector<vector<int> > P, int alpha);

	void createTrie();
	vector<vector<int> > createPrefixIndex(vector<vector<int> > &mt_string);
	vector<int> getSortedCollumn(vector<vector<int> > &mt_string, int index);
	vector<int> bucketSortCollumn(vector<vector<int> > &mt_string, int index);
	bool compareCollumn(int start1, int index1, vector<vector<int> > &string1, vector<vector<int> > &prefix_index1, int start2, int index2, vector<vector<int> > &string2, vector<vector<int> > &prefix_index2);

	void preHBc();
	vector<int> match(vector<vector<int> > &text);
	vector<int> matchTrie(vector<vector<int> > &text);
};