#include "mtbm.h"

MTBM::MTBM(){

}

MTBM::MTBM(vector<vector<int> > P, int alpha){
	alphabet = alpha;
	pattern = P;
	int M = pattern.size();
	int m = pattern[0].size();
	pattern_prefix_index = createPrefixIndex(pattern);
	suffix.resize(m);
	bmGs.resize(m);
	suffixes();
	preBmBc();
	preBmGs();
	return;
}

void MTBM::createTrie(){
	mt_trie.addPattern(pattern);
	mt_trie.CalcReverseGotoFunc();
	return;
}

vector<vector<int> > MTBM::createPrefixIndex(vector<vector<int> > &mt_string){
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

vector<vector<int> > MTBM::radixSort(vector<vector<int> > &mt_string, int start, int end){
	int M = mt_string.size();
	vector<int> index(M);
	for(int i = 0;i < M;i++){
		index[i] = i;
	}
	for(int i = end;i >= start;i--){
		vector<queue<int> > bucket(alphabet);
		for(int j = 0;j < M;j++){
			bucket[mt_string[index[j]][i]].push(index[j]);
		}
		int j = 0;
		int k = 0;
		while(j < M){
			while(bucket[k].size() > 0){
				index[j] = bucket[k].front();
				bucket[k].pop();
				j++;
			}
			k++;
		}
	}
	vector<vector<int> > result(M);
	for(int i = 0;i < M;i++){
		result[i] = mt_string[index[i]];
	}
	return result;
}

bool MTBM::compareCollumn(int start1, int index1, vector<vector<int> > &string1, vector<vector<int> > &prefix_index1, int start2, int index2, vector<vector<int> > &string2, vector<vector<int> > &prefix_index2){
	int N = pattern.size();
	for(int i = 0;i < N;i++){
		if(string1[prefix_index1[i][start1]][index1] != string2[prefix_index2[i][start2]][index2]){
			return 0;
		}
	}
	return 1;
}

vector<int> MTBM::bucketSortCollumn(vector<vector<int> > &mt_string, int index){
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

void MTBM::suffixes(){
	int m = pattern[0].size();
	int f, g, i;
	suffix[m - 1] = m;
	g = m - 1;
	for(i = m - 2; i >= 0; --i) {
		if(i > g && suffix[i + m - 1 - f] < i - g){
			suffix[i] = suffix[i + m - 1 - f];
		} else{
			if(i < g){
				g = i;
			}
			f = i;
			while(g >= 0 && compareCollumn(f, g, pattern, pattern_prefix_index, m - 1, g + m - 1 - f, pattern, pattern_prefix_index)){
				--g;
			}
			suffix[i] = f - g;
		}
	}
	return;
}

void MTBM::preBmBc(){
	int m = pattern[0].size();
	int M = pattern.size();
	for(int i = 0; i < m - 1; ++i){
		vector<int> temp;
		for(int j = 0;j < M;j++){
			temp.push_back(pattern[pattern_prefix_index[j][i]][i]);
		}
		bmBc[temp] = m - i - 1;
	}
	return;
}

void MTBM::preBmGs(){
	int m = pattern[0].size();
	int M = pattern.size();
	int i, j;
	for(i = 0; i < m; ++i){
		bmGs[i] = m;
	}
	j = 0;
	for(i = m - 1; i >= 0; --i){
		if(suffix[i] == i + 1){
			for(; j < m - 1 - i; ++j){
				if(bmGs[j] == m){
					bmGs[j] = m - 1 - i;
				}
			}
		}
	}
	for(i = 0; i <= m - 2; ++i){
		bmGs[m - 1 - suffix[i]] = m - 1 - i;
	}
	return;
}

vector<int> MTBM::match(vector<vector<int> > &text){
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
			j += bmGs[0];
		} else{
			vector<int> temp;
			for(int k = 0;k < M;k++){
				temp.push_back(text[text_prefix_index[k][i + j]][i + j]);
			}
			auto it = bmBc.find(temp);
			if(it == bmBc.end()){
				j += max(bmGs[i], 1 + i);
			} else{
				j += max(bmGs[i], it->second - m + 1 + i);
			}
		}
	}
	return result;
}

vector<int> MTBM::matchTrie(vector<vector<int> > &text){
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
			j += bmGs[0];
		} else{
			vector<int> temp = bucketSortCollumn(text, i + j);
			auto it = bmBc.find(temp);
			if(it == bmBc.end()){
				j += max(bmGs[i], 1 + i);
			} else{
				j += max(bmGs[i], it->second - m + 1 + i);
			}
		}
	}
	return result;
}