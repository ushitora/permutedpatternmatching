#include "mtacautomaton.h"

MTACAutomaton::MTACAutomaton(){
}

MTACAutomaton::MTACAutomaton(int alpha){
	alphabet = alpha;
}

void MTACAutomaton::addPattern(vector<vector<int> >& P){
	patterns.push_back(P);
	PPA.push_back(createPA(P));
	return;
}

void MTACAutomaton::CalcACAutomaton(void){
	root = new State;
	root->depth = 0;
	root->next_output = NULL;
	CalcGotoFunc();
	CalcFailFunc();
	return;
}

void MTACAutomaton::CalcGotoFunc(void){
	for(int i = 0; i < patterns.size(); i++){
		vector<vector<int> > p = patterns[i];
		int M = p.size();
		State* active_state = root;
		int m = p[0].size();
		for(int k = 0; k < m; k++){
			vector<int> trans = getCollumn(p, k, PPA[i], 0);
			if(active_state->child.find(trans) == active_state->child.end()){
				State* new_state = new State;
				new_state->depth = k + 1;
				new_state->pattern_num = i;
				new_state->next_output = NULL;
				active_state->child[trans] = new_state;
				active_state = new_state;
			} else{
				active_state = active_state->child[trans];
			}
			if(k == m - 1){
				active_state->output = i;
			} else{
				active_state->output = -1;
			}
		}
	}
	return;
}

void MTACAutomaton::CalcFailFunc(void){
	queue<State*> q;

	root->failure = root;
	for(auto it = root->child.begin(); it != root->child.end(); it++){
		it->second->failure = root;
		q.push(it->second);
	}

	while(!q.empty()){
		State* active_state = q.front();
		q.pop();

		for(auto it = active_state->child.begin(); it != active_state->child.end(); it++){
			State* st = it->second;
			q.push(st);
			State* fail_state = active_state->failure;
			vector<int> trans = getCollumn(patterns[st->pattern_num], st->depth - 1, PPA[st->pattern_num], st->depth - 1 - fail_state->depth);
			while(fail_state->child.find(trans) == fail_state->child.end() && fail_state != root){
				fail_state = fail_state->failure;
				trans = getCollumn(patterns[st->pattern_num], st->depth - 1, PPA[st->pattern_num], st->depth - 1 - fail_state->depth);
			}

			if(fail_state == root && fail_state->child.find(trans) == fail_state->child.end()){
				st->failure = root;
			} else{
				fail_state = fail_state->child[trans];
				st->failure = fail_state;
				if(fail_state->output >= 0){
					st->next_output = fail_state;
				}
			}
		}
	}
	return;
}

vector<int> MTACAutomaton::match(vector<vector<int> >& T){
	vector<int> ans;
	TPA = createPA(T);
	int n = T[0].size();
	int N = T.size();

	State* active_state = root;
	for(int i = 0; i < n; i++){
		vector<int> trans = getCollumn(T, i, TPA, i - active_state->depth);
		while(active_state->child.find(trans) == active_state->child.end() && active_state != root){
			active_state = active_state->failure;
			trans = getCollumn(T, i, TPA, i - active_state->depth);
		}
		if(active_state->child.find(trans) != active_state->child.end()){
			active_state = active_state->child[trans];
			State* out_state = active_state;
			while(out_state->next_output != NULL){
				out_state = out_state->next_output;
				ans.push_back(i - out_state->depth + 1);
			}
			if(active_state->output >= 0){
				ans.push_back(i - active_state->depth + 1);
			}
		}
	}
	return ans;
}

vector<vector<int>> MTACAutomaton::createPA(vector<vector<int> > mt_string){
	int N = mt_string.size();
	int n = mt_string[0].size();
	vector<vector<int> > result(N, vector<int>(n, 0));
	for(int i = n - 1; i >= 0; i--){
		vector<queue<int> > bucket(alphabet);
		if(i == n - 1){
			for(int j = 0; j < N; j++){
				bucket[mt_string[j][i]].push(j);
			}
		} else{
			for(int j = 0; j < N; j++){
				bucket[mt_string[result[j][i + 1]][i]].push(result[j][i + 1]);
			}
		}
		int j = 0;
		int k = 0;
		while(j < N){
			while(bucket[k].size() > 0){
				result[j][i] = bucket[k].front();
				bucket[k].pop();
				j++;
			}
			k++;
		}
	}
	return result;
}

bool MTACAutomaton::compareCollumn(int start1, int index1, vector<vector<int> >& mt1, vector<vector<int> >& PA1, int start2, int index2, vector<vector<int> >& mt2, vector<vector<int> >& PA2){
	int N = mt1.size();
	for(int i = 0; i < N; i++){
		if(mt1[PA1[i][start1]][index1] != mt2[PA2[i][start2]][index2]){
			return 0;
		}
	}
	return 1;
}

vector<int> MTACAutomaton::getCollumn(vector<vector<int>>& str, int index, vector<vector<int> >& SI, int si){
	vector<int> out;
	for(int i = 0; i < str.size(); i++){
		out.push_back(str[SI[i][si]][index]);
	}
	return out;
}
