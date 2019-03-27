#pragma once

#include <map>
#include <queue>
#include <vector>

using namespace std;

class MTMatchAutomaton{
	private:
	struct State{
		map<int, State*> child;
//		int parent;
		int depth;
		int weight;
		State* failure;
	};
//	vector<State> states; //ACオートマトン
	State* root;
	int sigma;
	vector<vector<int> > pattern;
	vector<vector<State*> > depth_states;

	public:
	MTMatchAutomaton();
	MTMatchAutomaton(vector<vector<int> > P, int sig);
//	State CreateState(void);		//状態の作成
//	void reset(void);					//	ACオートマトンの初期化
	void addPattern(vector<vector<int> > P, int sig);
//	void calcACAutomaton(void);
	void calcGotoFunc(void);
	void calcFailFunc(void);
	vector<int> match(vector<vector<int> > &text);
};

