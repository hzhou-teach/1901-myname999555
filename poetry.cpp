/*
* Jeffrey Chen
* Time: 2 hours 15 minutes
* 16/16 test cases
* Difficulty: 9/10
* This problem was somewhat "math-ish", so I used a lot of combinatorics + 
* optimizations to solve this problem. I also spent 1 hour fixing typoes so
* I need to be more careful about that
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

int n, m, k;
const ll MOD = 1000000007;
vector<int> length;
vector<pii> rhyme;
vector<int> scheme;
ll dpArr[5010];
bool dpCheck[5010];
vector<ll> colourAmt;

ll dpAmt(int l) {
	if (l < 0) return 0;
	if (l == 0) return 1;
	if (dpCheck[l]) return dpArr[l];
	ll sum = 0;
	for (int i = 0; i < n; ++i) {
		sum += dpAmt(l - length[i]);
		sum %= MOD;
	}
	dpArr[l] = sum;
	dpCheck[l] = true;
	return sum;
}

void fillColour() {
	int curVal = rhyme[0].second;
	colourAmt.push_back(0);
	for (int i = 0; i < n; ++i) {
		if (rhyme[i].second == curVal) {
			colourAmt[colourAmt.size() - 1] += dpAmt(k - rhyme[i].first);
			colourAmt[colourAmt.size() - 1] %= MOD;
		}
		else {
			colourAmt.push_back(0);
			colourAmt[colourAmt.size() - 1] += dpAmt(k - rhyme[i].first);
			colourAmt[colourAmt.size() - 1] %= MOD;
			curVal = rhyme[i].second;
		}
	}
}

ll powr(ll r, ll k) {
	ll z = 1;
	while (k) {
		if (k & 1) z = (z * r) % MOD;
		r = (r * r) % MOD;
		k >>= 1;
	}
	return z;
}

ll colourSyll(int dif) {
	ll sum = 0;
	for (int j = 0; j < colourAmt.size(); ++j) {
		sum += powr(colourAmt[j], dif);
		sum %= MOD;
	}
	return sum;
}

bool sortSec(pii p1, pii p2) {
	return p1.second < p2.second;
}

int main(int argc, char* argv[]) {
	const char* FIN = "poetry.in";
	const char* FOUT = "poetry.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	cin >> n >> m >> k;
	for (int i = 0; i < n; ++i) {
		int s, c;
		cin >> s >> c;
		rhyme.push_back(make_pair(s, c));
		length.push_back(s);
	}
	for (int i = 0; i < m; ++i) {
		char c;
		cin >> c;
		scheme.push_back(c - 'A');
	}
	sort(scheme.begin(), scheme.end());
	sort(rhyme.begin(), rhyme.end(), sortSec);
	fillColour();
	int curVal = scheme[0];
	int curPos = 0;
	ll ans = 1;
	vector<ll> sSize;
	for (int i = 0; i < m; ++i) {
		if (scheme[i] != curVal) {
			sSize.push_back(i - curPos);
			curPos = i;
			curVal = scheme[i];
		}
	}
	sSize.push_back(m - curPos);
	sort(sSize.begin(), sSize.end());
	curVal = sSize[0];
	curPos = 0;
	for (int i = 0; i < sSize.size(); ++i) {
		if (sSize[i] != curVal) {
			ans *= powr(colourSyll(curVal), i - curPos);
			ans %= MOD;
			curVal = sSize[i];
			curPos = i;
		}
	}
	ans *= powr(colourSyll(curVal), sSize.size() - curPos);
	ans %= MOD;

	cout << ans << endl;
	return 0;
}
