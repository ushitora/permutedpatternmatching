#include "mtkmp.h"

MTKMP::MTKMP(){
}

MTKMP::MTKMP(vector<vector<int> > P, int alpha){
	alphabet = alpha;
	pattern = P;
	int M = pattern.size();
	int m = pattern[0].size();
	int i, j;
	PPA = createPA(P);
	kmpNext.resize(m + 1);
	vector<int> data;
	for(int i = 0;i < M;i++){
		data.push_back(i);
	}
	i = 0;
	j = kmpNext[0] = -1;
	while(i < m) {
		while(j > -1 && !comparePattern(0, i - j, j)){
			j = kmpNext[j];
		}
		i++;
		j++;
		kmpNext[i] = j;
	}
}

vector<vector<int>> MTKMP::createPA(vector<vector<int> > mt_string)
{
	int N = mt_string.size();
	int n = mt_string[0].size();
	vector<vector<int> > result(N, vector<int>(n, 0));
	for(int i = n - 1;i >= 0;i--){
		vector<queue<int> > bucket(alphabet);
		if(i == n - 1){
			for(int j = 0;j < N;j++){
				bucket[mt_string[j][i]].push(j);
			}
		} else{
			for(int j = 0;j < N;j++){
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

vector<vector<int> > MTKMP::radixSort(vector<vector<int> >& mt_string, int start, int end){
	int M = mt_string.size();
	vector<int> index(M);
	for(int i = 0;i < M;i++){
		index[i] = i;
	}
	for(int i = end;i >= start;i--){
		vector<queue<int> > bucket(alphabet);
		for(int j = 0;j < M;j++){
			bucket[mt_string[index[j]][i] - 'A'].push(index[j]);
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

int MTKMP::calculateTreshold(vector<int> data, int index){
	int m = pattern[0].size();
	if(index >= m){
		return m;
	}
	int result = index;
	vector<vector<int> > bucket(alphabet);
	for(int i = 0;i < data.size();i++){
		bucket[pattern[data[i]][index]].push_back(data[i]);
	}
	for(int i = 0;i < alphabet;i++){
		if(bucket[i].size() > 1){
			result = max(result, calculateTreshold(bucket[i], index + 1));
		}
	}
	return result;
}

bool MTKMP::compareCollumn(int start1, int index1, vector<vector<int> >& text, int start2, int index2){
	int N = pattern.size();
	for(int i = 0;i < N;i++){
		if(pattern[PPA[i][start1]][index1] != text[TPA[i][start2]][index2]){
			return 0;
		}
	}
	return 1;
}

bool MTKMP::comparePattern(int index1, int index2, int l){
	int M = pattern.size();
	for(int j = 0;j < M;j++){
		if(pattern[PPA[j][index1]][index1 + l] != pattern[PPA[j][index2]][index2 + l]){
			return 0;
		}
	}
	return 1;
}

vector<int> MTKMP::match(vector<vector<int> >& text){
	vector<int> result;
	int M = pattern.size();
	int m = pattern[0].size();
	int N = text.size();
	int n = text[0].size();
	TPA = createPA(text);
	int i, j;
	i = j = 0;
	while(j < n) {
		while(i > -1 && !compareCollumn(0, i, text, j - i, j)){
			i = kmpNext[i];
		}
		i++;
		j++;
		if(i >= m) {
			result.push_back(j - i);
			i = kmpNext[i];
		}
	}
	return result;
}
