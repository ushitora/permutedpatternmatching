#include "acautomaton.h"

ACAutomaton::ACAutomaton(){
	root = new State;
	aux = new State;
	root->depth = 0;
	root->output = 0;
	aux->depth = -1;
	aux->output = 0;
}

ACAutomaton::ACAutomaton(vector<vector<int> > mt, int sig){
	root = new State;
	aux = new State;
	root->depth = 0;
	root->output = 0;
	aux->depth = -1;
	aux->output = 0;
	sigma = sig;
	multi_track = mt;
	calcGoto();
	calcFailure();
}

void ACAutomaton::calcGoto(){
	for(int i = 0;i < sigma;i++){
		aux->child[i] = root;
	}
	for(int i = 0;i < multi_track.size();i++){
		State* st = root;
		for(int j = 0;j < multi_track[i].size();j++){
			auto it = st->child.find(multi_track[i][j]);
			if(it != st->child.end()){
				st = it->second;
			} else{
				State* new_st = new State;
				new_st->depth = st->depth + 1;
				new_st->output = 0;
				st->child[multi_track[i][j]] = new_st;
				st = new_st;
			}
			if(j == multi_track[i].size() - 1){
				st->output++;
			}
		}
	}
}

void ACAutomaton::calcFailure(){
	queue<State*> qu;
	aux->failure = root->failure = aux;
	qu.push(root);
	while(qu.size()){
		State* active_st = qu.front();
		qu.pop();
		for(auto it = active_st->child.begin();it != active_st->child.end();it++){
			int ch = it->first;
			State* next_st = it->second;
			State* fail_st = active_st->failure;
			while(fail_st->child.find(ch) == fail_st->child.end()){
				fail_st = fail_st->failure;
			}
			next_st->failure = fail_st->child[ch];
			qu.push(next_st);
		}
	}
}

void ACAutomaton::addMultiTrack(vector<vector<int> > mt, int sig){
	if(multi_track.size()){
		sigma = sig;
		multi_track = mt;
		calcGoto();
		calcFailure();
	}
}
vector<int> ACAutomaton::match(vector<vector<int>> mt){
	vector<int> result;
	if(multi_track.size()){
		vector<State*> pointers(mt.size(), root);
		for(int i = 0;i < mt[0].size();i++){
			int counter = multi_track.size();
			for(int j = 0;j < mt.size();j++){
				while(pointers[j]->child.find(mt[j][i]) == pointers[j]->child.end()){
					pointers[j] = pointers[j]->failure;
				}
				pointers[j] = pointers[j]->child[mt[j][i]];
				if(pointers[j]->output > 0){
					counter--;
				}
				pointers[j]->output--;
			}
			for(int j = 0;j < mt.size();j++){
				pointers[j]->output++;
			}
			if(counter <= 0){
				result.push_back(i - multi_track[0].size() + 1);
			}
		}
	}
	return result;
}
