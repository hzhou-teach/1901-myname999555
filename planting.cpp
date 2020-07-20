/*
* Jeffrey Chen
* Time: 5 minutes
* 10/10 test cases
* Difficulty: 2/10
* The answer is just the maximum degree + 1, so a linear scan suffices.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
	const char* FIN = "planting.in";
	const char* FOUT = "planting.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	int n;
	cin >> n;
	vector<int> deg(n);
	for (int i = 0; i < n - 1; ++i) {
		int a, b;
		cin >> a >> b;
		++deg[a - 1];
		++ deg[b - 1];
	}
	int best = 0;
	for (int i = 0; i < n; ++i) {
		best = max(best, deg[i]);
	}
	cout << best+1 << endl;
	return 0;
}