/*
* Jeffrey Chen
* Time: 35 minutes
* 11/11 test cases
* Difficulty: 5/10
* It was a standard flood fill. I just had to be careful about calculating the perimeter.
*/

#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int n;
int perim = 0;
int bestPerim = 0;
int bestArea = 0;
int arr[1009][1009];
int oriArr[1009][1009];

pair<bool, int> floodFill(int x, int y) {
	if (x < 0 || x >= n || y < 0 || y >= n || (arr[x][y] == 0 && oriArr[x][y] == 0)) return make_pair(true, 0);
	if (arr[x][y] == 0 && oriArr[x][y] == 1) return make_pair(false, 0);
	arr[x][y] = 0;
	int curArr = 1;
	pair<bool, int> p1, p2, p3, p4;
	p1 = floodFill(x - 1, y);
	p2 = floodFill(x + 1, y);
	p3 = floodFill(x, y - 1);
	p4 = floodFill(x, y + 1);
	if (p1.first) ++perim;
	if (p2.first) ++perim;
	if (p3.first) ++perim;
	if (p4.first) ++perim;
	curArr += p1.second;
	curArr += p2.second;
	curArr += p3.second;
	curArr += p4.second;
	return make_pair(false, curArr);
}

int main(int argc, char* argv[]) {
	const char* FIN = "perimeter.in";
	const char* FOUT = "perimeter.out";
	const char* inFile = argc > 1 ? argv[1] : FIN;
	ifstream cin(inFile);
	ofstream cout(FOUT);

	cin >> n;
	for (int i = 0; i < n; ++i) {
		string s;
		cin >> s;
		for (int j = 0; j < n; ++j) {
			if (s[j] == '#') {
				arr[i][j] = 1;
				oriArr[i][j] = 1; 
			}
			else {
				arr[i][j] = 0;
				oriArr[i][j] = 0;
			}
		}
	}
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			if (arr[i][j]) {
				perim = 0;
				pair<bool, int> p = floodFill(i, j);
				if (p.second > bestArea) {
					bestPerim = perim;
					bestArea = p.second;
				}
				if (p.second == bestArea && perim < bestPerim) {
					bestPerim = perim;
				}
			}
		}
	}
	cout << bestArea << " " << bestPerim << endl;
	return 0;
}