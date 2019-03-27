#include "filterbm.h"

FilterBM::FilterBM(){

}

FilterBM::FilterBM(vector<vector<int> > P, int alpha){
	alphabet = alpha;
	pattern = radixSort(P, 0, P[0].size() - 1);
	int M = pattern.size();
	int m = pattern[0].size();
	pattern_bucket = createBucket(pattern);

	suffix.resize(m);
	bmGs.resize(m);
	suffixes();
	preBmBc();
	preBmGs();
	return;
}

vector<vector<int> > FilterBM::radixSort(vector<vector<int> > &mt_string, int start, int end){
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

vector<vector<int> > FilterBM::createBucket(vector<vector<int> > mt_string){
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

bool FilterBM::compareCollumnInt(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2){
	for(int i = 0;i < mt_string1.size();i++){
		if(mt_string1[i][index1] != mt_string2[i][index2]){
			return 0;
		}
	}
	return 1;
}

bool FilterBM::compareCollumnString(vector<vector<int> > &mt_string1, int index1, vector<vector<int> > &mt_string2, int index2){
	for(int i = 0;i < mt_string1.size();i++){
		if(mt_string1[i][index1] != mt_string2[i][index2]){
			return 0;
		}
	}
	return 1;
}

bool FilterBM::exactMatch(vector<vector<int> > &p, vector<vector<int> > &t, int start){
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

void FilterBM::suffixes(){
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
			while(g >= 0 && compareCollumnInt(pattern_bucket, g, pattern_bucket, g + m - 1 - f)){
				--g;
			}
			suffix[i] = f - g;
		}
	}
	return;
}

void FilterBM::preBmBc(){
	int m = pattern_bucket[0].size();
	int M = pattern_bucket.size();
	for(int i = 0; i < m - 1; ++i){
		vector<int> temp(M);
		for(int j = 0;j < M;j++){
			temp[j] = pattern_bucket[j][i];
		}
		bmBc[temp] = m - i - 1;
	}
	return;
}

void FilterBM::preBmGs(){
	int m = pattern[0].size();
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

vector<int> FilterBM::match(vector<vector<int> > &text){
	vector<int> result;
	int M = pattern.size();
	int m = pattern[0].size();
	int N = text.size();
	int n = text[0].size();
	vector<vector<int> > text_bucket = createBucket(text);

	int i, j;
	i = j = 0;
	while(j <= n - m) {
		for(i = m - 1; i >= 0 && compareCollumnInt(pattern_bucket, i, text_bucket, i + j); --i);
		if(i < 0) {
			if(exactMatch(pattern, text, j)){
				result.push_back(j);
			}
			j += bmGs[0];
		} else{
			vector<int> temp(pattern_bucket.size());
			for(int k = 0;k < pattern_bucket.size();k++){
				temp[k] = text_bucket[k][i + j];
			}
			map<vector<int>, int>::iterator it = bmBc.find(temp);
			if(it == bmBc.end()){
				j += max(bmGs[i], 1 + i);
			} else{
				j += max(bmGs[i], it->second - m + 1 + i);
			}
		}
	}
	return result;
}