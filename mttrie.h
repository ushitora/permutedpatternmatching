#pragma once

#ifndef MT_TRIE
#define MT_TRIE

#include <vector>
#include <map>

using namespace std;

class MTTrie{
	private:
	struct State{
		map<int, State*> child;
		int depth;
		int weight;
	};
	State* root;
	//vector<State> states;
	vector<vector<int> > pattern;

	public:
	MTTrie();
	MTTrie(vector<vector<int> > P);
	void addPattern(vector<vector<int> > P);
	void CalcGotoFunc(void);
	void CalcReverseGotoFunc(void);
	int PatternMatch(vector<vector<int> > &text, int index);
	int reversePatternMatch(vector<vector<int> > &text, int index);
};

#endif