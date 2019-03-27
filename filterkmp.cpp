#include "filterkmp.h"

FilterKMP::FilterKMP(){

}

FilterKMP::FilterKMP(vector<vector<int> > P, int alpha){
	alphabet = alpha;
	pattern = radixSort(P, 0, P[0].size() - 1);
	int M = pattern.size();
	int m = pattern[0].size();
	int i, j;
	kmpNext.resize(m + 1);
	pattern_bucket = createBucket(pattern);
	i = 0;
	j = kmpNext[0] = -1;
	while(i < m) {
		while(j > -1 && !compareCollumnInt(pattern_bucket, i, pattern_bucket, j)){
			j = kmpNext[j];
		}
		i++;
		j++;
		if(i < m && compareCollumnInt(pattern_bucket, i, pattern_bucket, j)){
			kmpNext[i] = kmpNext[j];
		} else{
			kmpNext[i] = j;
		}
	}
}

vector<vector<int> > FilterKMP::radixSort(vector<vector<int> > &mt_string, int start, int end){
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

vector<vector<int> > FilterKMP::createBucket(vector<vector<int> > mt_string){
	int M = mt_string.size();
	int m = mt_string[0].size();
	vector<vector<int> > bucket(alphabet, vector<int>(m, 0));
	for(int i = 0;i < m;i++){
		for(int j = 0;j < M;j++){
			bucket[mt_string[j][i]][i]++;
		}
	}
	return bucket;
}

bool FilterKMP::compareCollumnInt(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2){
	for(int i = 0;i < mt_string1.size();i++){
		if(mt_string1[i][index1] != mt_string2[i][index2]){
			return 0;
		}
	}
	return 1;
}

bool FilterKMP::compareCollumnString(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2){
	for(int i = 0;i < mt_string1.size();i++){
		if(mt_string1[i][index1] != mt_string2[i][index2]){
			return 0;
		}
	}
	return 1;
}

bool FilterKMP::exactMatch(vector<vector<int> > &p, vector<vector<int> > &t, int start){
	int M = p.size();
	int m = p[0].size();
	vector<vector<int> > sorted_t = radixSort(t, start, start + m - 1);
	for(int i = 0;i < m;i++){
		if(!compareCollumnString(p, i, sorted_t, start + i)){
			return 0;
		}
	}
	return 1;
}


vector<int> FilterKMP::match(vector<vector<int> > &text){
	vector<int> result;
	int M = pattern.size();
	int m = pattern[0].size();
	int N = text.size();
	int n = text[0].size();
	vector<vector<int> > text_bucket = createBucket(text);

	int i, j;
	i = j = 0;
	while(j < n) {
		while(i > -1 && !compareCollumnInt(pattern_bucket, i, text_bucket, j))
			i = kmpNext[i];
		i++;
		j++;
		if(i >= m) {
			if(exactMatch(pattern, text, j - i)){
				result.push_back(j - i);
			}
			i = kmpNext[i];
		}
	}
	return result;
}