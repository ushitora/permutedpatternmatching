#include "mttrie.h"

MTTrie::MTTrie(){
}

MTTrie::MTTrie(vector<vector<int> > P){
	pattern = P;
	//CalcGotoFunc();
}

void MTTrie::addPattern(vector<vector<int> > P){
	pattern = P;
	return;
}

void MTTrie::CalcGotoFunc(void){
	root = new State;
	root->depth = 0;
	root->weight = pattern.size();
	int M = pattern.size();
	for(int j = 0;j < M;j++){
		State* active_state = root;
		int m = pattern[j].size();
		for(int k = 0;k < m;k++){
			int c = pattern[j][k];
			if(active_state->child.find(c) == active_state->child.end()){
				State* new_state = new State;
				new_state->depth = k + 1;
				new_state->weight = 1;
				active_state->child[c] = new_state;
				active_state = new_state;
			} else{
				active_state = active_state->child[c];
				active_state->weight++;
			}
		}
	}
	return;
}

void MTTrie::CalcReverseGotoFunc(void){
	root = new State;
	root->depth = 0;
	root->weight = pattern.size();
	int M = pattern.size();
	for(int j = 0;j < M;j++){
		State* active_state = root;
		int m = pattern[j].size();
		for(int k = m - 1;k >= 0;k--){
			char c = pattern[j][k];
			if(active_state->child.find(c) == active_state->child.end()){
				State* new_state = new State;
				new_state->depth = m - k;
				new_state->weight = 1;
				active_state->child[c] = new_state;
				active_state = new_state;
			} else{
				active_state = active_state->child[c];
				active_state->weight++;
			}
		}
	}
	return;
}

int MTTrie::PatternMatch(vector<vector<int> > &text, int index){
	int N = text.size();
	int m = pattern[0].size();
	vector<State*> state(N, root);
	int i = 0;
	for(i = 0;i < m;i++){
		int return_flag = 0;
		for(int j = 0;j < N;j++){
			int c = text[j][i + index];
			if(state[j]->child.find(c) == state[j]->child.end()){
				return_flag = 1;
			} else{
				state[j] = state[j]->child[c];
				state[j]->weight--;
				if(state[j]->weight < 0){
					return_flag = 1;
				}
			}
		}
		for(int j = 0;j < N;j++){
			if(state[j]->depth == i + 1){
				state[j]->weight++;
			}
		}
		if(return_flag){
			return i;
		}
	}
	return i;
}

int MTTrie::reversePatternMatch(vector<vector<int> > &text, int index){
	int N = text.size();
	int m = pattern[0].size();
	vector<State*> state(N, root);
	int i = 0;
	for(i = m - 1;i >= 0;i--){
		int return_flag = 0;
		for(int j = 0;j < N;j++){
			int c = text[j][i + index];
			if(state[j]->child.find(c) == state[j]->child.end()){
				return_flag = 1;
			} else{
				state[j] = state[j]->child[c];
				state[j]->weight--;
				if(state[j]->weight < 0){
					return_flag = 1;
				}
			}
		}
		for(int j = 0;j < N;j++){
			if(state[j]->depth == m-i){
				state[j]->weight++;
			}
		}
		if(return_flag){
			return i;
		}
	}
	return i;
}
