#pragma once

#include <map>
#include <queue>
#include <vector>

using namespace std;

class ACAutomaton{
	private:
	struct State{
		map<int, State*> child;
		State* failure;
		int depth;
		int output;
	};
	int sigma;
	vector<vector<int> > multi_track;
	State* root;
	State* aux;
	void calcGoto();
	void calcFailure();

	public:
	ACAutomaton();
	ACAutomaton(vector<vector<int> > mt, int sig);
	void addMultiTrack(vector<vector<int> > mt, int sig);
	vector<int> match(vector<vector<int> > mt);
};