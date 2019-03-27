#pragma once

#include <map>
#include <queue>
#include <vector>

using namespace std;

class MTACAutomaton{
	private:
	struct State{
		map<vector<int>, State*> child;
		//int parent;
		State* failure;
		int depth;
		int pattern_num;
		int output;
		State* next_output;
	};
	int alphabet;
	State* root;
	vector<vector<vector<int> > > patterns;
	vector<vector<vector<int> > > PPA;
	vector<vector<int> > TPA;

	public:
	MTACAutomaton();
	MTACAutomaton(int alpha);
	State CreateState(void);
	void reset(void);
	void addPattern(vector<vector<int> > &P);
	void CalcACAutomaton(void);
	void CalcGotoFunc(void);
	void CalcFailFunc(void);
	vector<int> match(vector <vector<int> > &T);
	vector<vector<int> > createPA(vector<vector<int> > mt_string);
	bool compareCollumn(int start1, int index1, vector<vector<int> > &mt1, vector<vector<int> > &PA1, int start2, int index2, vector<vector<int> > &mt2, vector<vector<int> > &PA2);
	vector<int> getCollumn(vector<vector<int> > &str, int index, vector<vector<int> > &SI, int si);
//	long long GetTrieSize(void);
//	void PrintAutomaton();
};