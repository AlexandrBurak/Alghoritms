#include <iostream>
using namespace std;

int BinarySearch(long a[], long key, int n) {
	int l = 0;
	int r = n - 1;
	while (l <= r) {
		int m = (l + r) / 2;
		
		if (a[m] == key) {
			return 1;
		}
		else if (key < a[m]) {
			r = m - 1;
		}
		else {
			l = m + 1;
		}
	}
	return 0;

}

int BinarySearchL(long a[], long key, int n) {
	int l = -1;
	int r = n;
	while (r - l > 1) {
		int m = (l + r) / 2;
		if (a[m] < key) {
			l = m;
		}
		else {
			r = m;
		}
	}
	return r;

}

int BinarySearchR(long a[], long key, int n) {
	int l = -1;
	int r = n;
	while (l < r - 1) {
		int m = (l + r) / 2;
		if (a[m] <= key) {
			l = m;
		}
		else {
			r = m;
		}
	}
	return r;

}

int main() {
	int n;
	cin >> n;
	long* arr = new long[n];
	long var;
	for (int i = 0; i < n; i++) {
		cin >> var;
		arr[i] = var;
	}
	int k;
	cin >> k;
	long* enemies = new long[k];
	for (int i = 0; i < k; i++) {
		cin >> var;
		enemies[i] = var;
	}
	for (int i = 0; i < k; i++) {
		cout << BinarySearch(arr, enemies[i], n) << " " << BinarySearchL(arr, enemies[i], n) << " " << BinarySearchR(arr, enemies[i], n) << endl;
	}
	return 0;
}