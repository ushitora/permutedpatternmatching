#include <ctime>
#include <iostream>
#include <set>

#include "acautomaton.h"
#include "filterbm.h"
#include "filterhorspool.h"
#include "filterkmp.h"
#include "mtacautomaton.h"
#include "mtbm.h"
#include "mthorspool.h"
#include "mtkmp.h"
#include "mtmatchautomaton.h"
#include "mtstringgenerator.h"
#include "subfilterkmp.h"

using namespace std;

string alphabet = "abcdefghijklmnopqrstuvwxyz";

void printMultiTrack(vector<vector<int> > &mt){
	for(int i = 0;i < mt.size();i++){
		for(int j = 0;j < mt[i].size();j++){
			cout << alphabet[mt[i][j]];
		}
		cout << endl;
	}
}

void embedPattern(vector<vector<int> >& T, vector<vector<int> >& P, int k){
	mt19937 generator((unsigned) chrono::system_clock::now().time_since_epoch().count());
	int N = T.size();
	int n = T[0].size();
	int M = P.size();
	int m = P[0].size();
	int width = n / k - m;
	for(int i = 0;i < k;i++){
		vector<int> permutation;
		set<int> check;
		int start = n*i / k;
		int shift = generator() % width;
		while(permutation.size() != M){
			int temp = generator() % N;
			if(check.find(temp) == check.end()){
				permutation.push_back(temp);
				check.insert(temp);
			}
		}
		for(int j = 0;j < M;j++){
			for(int l = 0;l < m;l++){
				T[permutation[j]][l + start + shift] = P[j][l];
			}
		}
	}
}

void debug(){
	vector<vector<int> > result;
	MTStringGenerator mt_generator;
	vector<vector<int> > pattern = mt_generator.generateMultiTrack(3, 3, 2);
	vector<vector<int> > text = mt_generator.generateMultiTrack(1000, 3, 2);
	printMultiTrack(pattern);
	printMultiTrack(text);

	ACAutomaton acautomaton(pattern, 2);
	result.push_back(acautomaton.match(text));
	for(int i = 0;i < result[result.size()-1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	MTKMP mtkmp(pattern, 2);
	result.push_back(mtkmp.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}
	
	MTACAutomaton mtaca(2);
	mtaca.addPattern(pattern);
	mtaca.CalcACAutomaton();
	result.push_back(mtaca.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	MTMatchAutomaton mtma(pattern, 2);
	result.push_back(mtma.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	MTBM mtbm(pattern, 2);
	result.push_back(mtbm.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	MTBM mtbm_trie(pattern, 2);
	mtbm_trie.createTrie();
	result.push_back(mtbm_trie.matchTrie(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}
	
	MTHorspool mthors(pattern, 2);
	result.push_back(mthors.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}
	
	MTHorspool mthors_trie(pattern, 2);
	mthors_trie.createTrie();
	result.push_back(mthors_trie.matchTrie(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	FilterKMP filter_kmp(pattern, 2);
	result.push_back(filter_kmp.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	FilterBM filter_bm(pattern, 2);
	result.push_back(filter_bm.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	FilterHorspool filter_horspool(pattern, 2);
	result.push_back(filter_horspool.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}
}

void debugSub(){
	vector<vector<int> > result;
	MTStringGenerator mt_generator;
	vector<vector<int> > pattern = mt_generator.generateMultiTrack(5, 6, 2);
	vector<vector<int> > text = mt_generator.generateMultiTrack(100, 10, 2);
	embedPattern(text, pattern, 4);
	printMultiTrack(pattern);
	printMultiTrack(text);

	ACAutomaton acautomaton(pattern, 2);
	result.push_back(acautomaton.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}

	SubFilterKMP sub_filter_kmp(pattern, 2);
	result.push_back(sub_filter_kmp.match(text));
	for(int i = 0;i < result[result.size() - 1].size();i++){
		cout << result[result.size() - 1][i];
		if(i < result[result.size() - 1].size() - 1){
			cout << ", ";
		} else{
			cout << endl;
		}
	}
}

void measureTime(int n, int N, int m, int M, int alphabet, int repetition){
	vector<vector<int> > result;
	vector<double> preprocess_time;
	vector<double> match_time;
	clock_t time[3];
	clock_t preprocess_timer;
	clock_t match_timer;
	MTStringGenerator mt_generator;
	vector<vector<vector<int> > > pattern;
	vector<vector<vector<int> > > text;
	for(int i = 0;i < repetition;i++){
		text.push_back(mt_generator.generateMultiTrack(n, N, alphabet));
		pattern.push_back(mt_generator.generateMultiTrack(m, M, alphabet));
		embedPattern(text[i], pattern[i], 5);
	}
	cout << n << ", " << N << ", " << m << ", " << M << ", " << alphabet;

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		ACAutomaton acautomaton(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(acautomaton.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double)match_timer / (double) CLOCKS_PER_SEC/ (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();


	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTKMP mtkmp(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(mtkmp.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTACAutomaton mtaca(alphabet);
		mtaca.addPattern(pattern[i]);
		mtaca.CalcACAutomaton();
		time[1] = clock();
		result.push_back(mtaca.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTMatchAutomaton mtma(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(mtma.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTBM mtbm(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(mtbm.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTBM mtbm_trie(pattern[i], alphabet);
		mtbm_trie.createTrie();
		time[1] = clock();
		result.push_back(mtbm_trie.matchTrie(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTHorspool mthors(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(mthors.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		MTHorspool mthors_trie(pattern[i], alphabet);
		mthors_trie.createTrie();
		time[1] = clock();
		result.push_back(mthors_trie.matchTrie(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		FilterKMP filter_kmp(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(filter_kmp.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		FilterBM filter_bm(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(filter_bm.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		FilterHorspool filter_horspool(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(filter_horspool.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	cout << endl;
}

void measureTimeSub(int n, int N, int m, int M, int alphabet, int repetition){
	vector<vector<int> > result;
	vector<double> preprocess_time;
	vector<double> match_time;
	clock_t time[3];
	clock_t preprocess_timer;
	clock_t match_timer;
	MTStringGenerator mt_generator;
	vector<vector<vector<int> > > pattern;
	vector<vector<vector<int> > > text;
	for(int i = 0;i < repetition;i++){
		text.push_back(mt_generator.generateMultiTrack(n, N, alphabet));
		pattern.push_back(mt_generator.generateMultiTrack(m, M, alphabet));
		embedPattern(text[i], pattern[i], 5);
	}
	cout << n << ", " << N << ", " << m << ", " << M << ", " << alphabet;

	preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		ACAutomaton acautomaton(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(acautomaton.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

		preprocess_timer = 0;
	match_timer = 0;
	for(int i = 0;i < repetition;i++){
		time[0] = clock();
		SubFilterKMP sub_filter_kmp(pattern[i], alphabet);
		time[1] = clock();
		result.push_back(sub_filter_kmp.match(text[i]));
		time[2] = clock();
		preprocess_timer += time[1] - time[0];
		match_timer += time[2] - time[1];
	}
	preprocess_time.push_back((double) preprocess_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	match_time.push_back((double) match_timer / (double) CLOCKS_PER_SEC / (double) repetition);
	cout << ", " << preprocess_time[preprocess_time.size() - 1] << ", " << match_time[match_time.size() - 1] << ", " << preprocess_time[preprocess_time.size() - 1] + match_time[match_time.size() - 1] << ", " << result[result.size() - 1].size();

	cout << endl;
}

int main(int argc, char** argv){
	if(argc < 7){
		debug();
		debugSub();
	}else{
		int n = atoi(argv[1]);
		int N = atoi(argv[2]);
		int m = atoi(argv[3]);
		int M = atoi(argv[4]);
		int alphabet = atoi(argv[5]);
		int repetition = atoi(argv[6]);
		if(M < N){
			measureTimeSub(n, N, m, M, alphabet, repetition);
		} else if(M == N){
			measureTime(n, N, m, M, alphabet, repetition);
		}
	}
	return 0;
}

