#include <iostream>
#include <fstream>
#include <set>
using namespace std;

int main() {
	ofstream out;
	ifstream in;
	set <long long> st;
	long long val;
	int size;
	in.open("input.txt");
	out.open("output.txt");
	if (!in.is_open()) {
		in.close();
		out.close();
		return 0;
	}
	
	while (!in.eof()) {
		in >> val;
		st.insert(val);
	}

	size = st.size();
	set <long long> ::iterator it = st.begin();
	long long sum = 0;
	for (long long el:st)
	{
		sum += el;
	}
	out << sum;
	in.close();
	out.close();
	return 0;
}