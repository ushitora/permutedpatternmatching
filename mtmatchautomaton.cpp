#include "mtmatchautomaton.h"

MTMatchAutomaton::MTMatchAutomaton(){
	root = new State;
	root->depth = 0;
}

MTMatchAutomaton::MTMatchAutomaton(vector<vector<int>> P, int sig){
	root = new State;
	root->depth = 0;
	sigma = sig;
	pattern = P;
	calcGotoFunc();
	calcFailFunc();
}

void MTMatchAutomaton::addPattern(vector<vector<int>> P, int sig){
	if(pattern.size()){
		sigma = sig;
		pattern = P;
		calcGotoFunc();
		calcFailFunc();
	}
}

void MTMatchAutomaton::calcGotoFunc(void){
	int M = pattern.size();
	root->weight = M;
	depth_states.resize(pattern[0].size() + 2);
	depth_states[0].push_back(root);
	for(int j = 0;j < M;j++){
		State* active_state = root;
		int m = pattern[j].size();
		for(int k = 0;k < m;k++){
			int c = pattern[j][k];
			if(active_state->child.find(c) == active_state->child.end()){
				State* new_state = new State;
				new_state->depth = k + 1;
				new_state->weight = 1;
				depth_states[new_state->depth].push_back(new_state);
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

void MTMatchAutomaton::calcFailFunc(void){
	int m = pattern[0].size();
	int M = pattern.size();
	vector<State*> active_states;
	root->failure = root;
	for(auto it = root->child.begin();it != root->child.end();it++){
		it->second->failure = root;
		active_states.push_back(it->second);
	}
	for(int i = 1;i < m;i++){
		vector<State*> temp_states = active_states;
		
		int flag = 0;
		while(!flag){
			flag = 1;
			vector<State*> failure_states;
			vector<State*> next_states;
			for(int j = 0;j < temp_states.size();j++){
				State* failure_state;
				failure_state = temp_states[j]->failure;
				failure_states.push_back(failure_state);
				for(auto it = active_states[j]->child.begin(); it != active_states[j]->child.end();it++){
					int c = it->first;
					State* s = it->second;
					if(failure_state->child.find(c) == failure_state->child.end()){
						flag = 0;
					}
				}
			}
			if(flag){
				int counter = 0;
				for(int j = 0;j < failure_states.size();j++){
					for(auto it = active_states[j]->child.begin(); it != active_states[j]->child.end();it++){
						int c = it->first;
						State* st = it->second;
						next_states.push_back(failure_states[j]->child[c]);
						next_states[counter]->weight -= it->second->weight;
						if(next_states[counter]->weight < 0){
							flag = 0;
						}
						counter++;
					}
				}
				counter = 0;
				for(int j = 0;j < failure_states.size();j++){
					for(auto it = active_states[j]->child.begin(); it != active_states[j]->child.end();it++){
						int c = it->first;
						State* st = it->second;
						next_states[counter]->weight += it->second->weight;
						counter++;
					}
				}
			}
			if(flag){
				int counter = 0;
				for(int j = 0;j < temp_states.size();j++){
					for(auto it = active_states[j]->child.begin(); it != active_states[j]->child.end();it++){
						int c = it->first;
						State* st = it->second;
						st->failure = next_states[counter];
						counter++;
					}
				}
			} else if(temp_states[0] == root){
				flag = 1;
				for(int j = 0;j < active_states.size();j++){
					for(auto it = active_states[j]->child.begin(); it != active_states[j]->child.end();it++){
						State* st = it->second;
						st->failure = root;
					}
				}
			} else{
				temp_states = failure_states;
			}
		}
		temp_states.clear();
		for(int j = 0;j < active_states.size();j++){
			for(auto it = active_states[j]->child.begin(); it != active_states[j]->child.end();it++){
				temp_states.push_back(it->second);
			}
		}
		active_states = temp_states;
	}
}

vector<int> MTMatchAutomaton::match(vector<vector<int>>& text){
	vector<int> result;
	if(pattern.empty()){
		return result;
	}
	int N = text.size();
	int n = text[0].size();
	int m = pattern[0].size();
	int M = pattern.size();
	vector<State*> state(N, root);
	int i = 0;
	for(i = 0;i < n;i++){
		int fail = 1;
		while(fail){
			fail = 0;
			vector<State*> next_states;
			for(int j = 0;j < N;j++){
				int c = text[j][i];
				auto it = state[j]->child.find(c);
				if(state[j]->child.find(c) == state[j]->child.end()){
					fail = 1;
				}
			}
			if(!fail){
				for(int j = 0;j < N;j++){
					int c = text[j][i];
					next_states.push_back(state[j]->child[c]);
					next_states[j]->weight--;
					if(next_states[j]->weight < 0){
						fail = 1;
					}
				}
				for(int j = 0;j < N;j++){
					next_states[j]->weight++;
				}
			}
			if(fail && state[0] == root){
				fail = 0;
			} else if(!fail){
				state = next_states;
			} else{
				for(int j = 0;j < N;j++){
					state[j] = state[j]->failure;
				}
			}
			int sum = 0;
		}
		if(state[0]->depth == m){
			result.push_back(i - m + 1);
		}
	}

	return result;
}

