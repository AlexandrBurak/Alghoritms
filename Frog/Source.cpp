#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <vector>
#include <ctime> 
#include <algorithm>
using namespace std;

int main() {
	int n;
	cin >> n;
	int* arr = new int[n];
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
	if (n == 1) {
		cout << arr[0] << endl;
		cout << 1;
		delete[] arr;
		return 0;
	}
	int* cur = new int[n];
	for (int i = 0; i < n; i++) {
		cur[i] = -1;
	}
	cur[0] = arr[0];
	if (n > 2){
		for (int i = 0; i < n; ++i) {
			if (i + 2 < n) {
				cur[i + 2] = max(cur[i] + arr[i + 2], cur[i + 2]);
			}
			if (i + 3 < n) {
				cur[i + 3] = max(cur[i] + arr[i + 3], cur[i + 3]);
			}
		}
	}
	if (cur[n - 1] == -1) {
		cout << cur[n - 1];
		delete[] cur;
		delete[] arr;
		return 0;
	}
	cout << cur[n - 1] << endl;
	vector<int> path;
	int c = n - 1;
	path.push_back(n);
	while (c >= 3) {
		if (cur[c - 2] >= cur[c - 3]) {
			path.push_back(c - 1);
			c = c - 2;
		}
		else {
			path.push_back(c - 2);
			c = c - 3;
		}
	}
	if (c == 2) {
		path.push_back(1);
	}
	reverse(path.begin(), path.end());
	//cout << cur[n - 1] << endl;
	for (int obj : path) {
		cout << obj << " ";
	}
	delete[] cur;
	delete[] arr;
	//cout << "runtime = " << clock() / 1000.0 << endl; // גנולÿ נאבמעû ןנמדנאללû
	return 0;
}