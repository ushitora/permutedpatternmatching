#include "mthorspool.h"

MTHorspool::MTHorspool(){

}

MTHorspool::MTHorspool(vector<vector<int> > P, int alpha){
	alphabet = alpha;
	pattern = P;
	//pattern = radixSort(P, 0, P[0].size() - 1);
	int M = pattern.size();
	int m = pattern[0].size();
	pattern_prefix_index = createPrefixIndex(pattern);
	preHBc();
	return;
}

void MTHorspool::createTrie(){
	mt_trie.addPattern(pattern);
	mt_trie.CalcReverseGotoFunc();
	return;
}

vector<vector<int> > MTHorspool::createPrefixIndex(vector<vector<int> > &mt_string){
	int N = mt_string.size();
	int n = mt_string[0].size();
	vector<vector<int> > result(N, vector<int>(n, 0));
	for(int i = 0;i < n;i++){
		vector<queue<int> > bucket(alphabet);
		if(i == 0){
			for(int j = 0;j < N;j++){
				bucket[mt_string[j][i]].push(j);
			}
		} else{
			for(int j = 0;j < N;j++){
				bucket[mt_string[result[j][i - 1]][i]].push(result[j][i - 1]);
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

vector<int> MTHorspool::getSortedCollumn(vector<vector<int> > &mt_string, int index){
	vector<int> ans;
	int N = mt_string.size();
	int n = mt_string[0].size();

	for(int j = 0;j < N;j++){
		ans.push_back(mt_string[text_prefix_index[j][index]][index]);
	}
	return ans;
}

vector<int> MTHorspool::bucketSortCollumn(vector<vector<int> > &mt_string, int index){
	vector<int> ans;
	int M = mt_string.size();
	int m = mt_string[0].size();

	vector<int> bucket(alphabet, 0);
	for(int j = 0;j < M;j++){
		bucket[mt_string[j][index]]++;
	}
	int j = 0;
	int k = 0;
	while(j < M){
		while(bucket[k] > 0){
			ans.push_back(k);
			bucket[k]--;
			j++;
		}
		k++;
	}
	return ans;
}

bool MTHorspool::compareCollumn(int start1, int index1, vector<vector<int> > &string1, vector<vector<int> > &prefix_index1, int start2, int index2, vector<vector<int> > &string2, vector<vector<int> > &prefix_index2){
	int N = pattern.size();
	for(int i = 0;i < N;i++){
		if(string1[prefix_index1[i][start1]][index1] != string2[prefix_index2[i][start2]][index2]){
			return 0;
		}
	}
	return 1;
}

void MTHorspool::preHBc(){
	int m = pattern[0].size();
	int M = pattern.size();
	for(int i = 0; i < m - 1; ++i){
		vector<int>  temp;
		for(int j = 0;j < M;j++){
			temp.push_back(pattern[pattern_prefix_index[j][i]][i]);
		}
		hBc[temp] = m - i - 1;
	}
	return;
}

vector<int> MTHorspool::match(vector<vector<int> > &text){
	vector<int> result;
	int M = pattern.size();
	int m = pattern[0].size();
	int N = text.size();
	int n = text[0].size();
	text_prefix_index = createPrefixIndex(text);

	int i, j;
	i = j = 0;
	while(j <= n - m) {
		for(i = m - 1; i >= 0 && compareCollumn(m - 1, i, pattern, pattern_prefix_index, j + m - 1, i + j, text, text_prefix_index); --i);
		if(i < 0) {
			result.push_back(j);
		}
		vector<int> temp = getSortedCollumn(text, j + m - 1);
		auto it = hBc.find(temp);
		if(it == hBc.end()){
			j += m;
		} else{
			j += it->second;
		}
	}
	return result;
}

vector<int> MTHorspool::matchTrie(vector<vector<int> > &text){
	vector<int> result;
	int M = pattern.size();
	int m = pattern[0].size();
	int N = text.size();
	int n = text[0].size();

	int i, j;
	i = j = 0;
	while(j <= n - m) {
		i = mt_trie.reversePatternMatch(text, j);
		if(i < 0) {
			result.push_back(j);
		}
		vector<int> temp = bucketSortCollumn(text, j+m-1);
		auto it = hBc.find(temp);
		if(it == hBc.end()){
			j += m;
		} else{
			j += it->second;
		}
	}
	return result;
}