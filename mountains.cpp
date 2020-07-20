/*
* Jeffrey Chen
* Time: 45 minutes
* 11/11 test cases
* Difficulty: 7/10
* At first I tried to brute force it, but it was too slow. I then realized that 
* sorting the peaks and checking how many mountains were inside the top mountain worked.
*/


#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
#define pii pair<int, int>

bool sortDif(pii p1, pii p2) {
	if (p1.second - p1.first != p2.second - p2.first) {
		return (p1.second - p1.first > p2.second - p2.first);
	}
	return p1.first + p1.second >= p2.first + p2.second;
}
bool checkSum(pii p1, pii p2) {
	return p1.first + p1.second >= p2.first + p2.second;
}

int main(int argc, char* argv[]) {
	const char* FIN = "mountains.in";
	const char* FOUT = "mountains.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	int n;
	cin >> n;
	vector<pii> peaks(n);
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		peaks[i] = make_pair(x, y);
	}
	int ans = 0;
	sort(peaks.begin(), peaks.end(), sortDif);
	while (!peaks.empty()) {
		vector<pii> newPeak;
		for (int i = 1; i < peaks.size(); ++i) {
			if (!checkSum(peaks[0], peaks[i])) {
				newPeak.push_back(peaks[i]);
			}
		}
		peaks = newPeak;
		++ans;
	}
	cout << ans << endl;

	return 0;
}