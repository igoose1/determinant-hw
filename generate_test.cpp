#include <iostream>
#include <stdlib.h>

using namespace std;

int main(void) {
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	cerr.tie(NULL);

	int LIMIT = 10;
	int FLOAT_LIMIT = 10;
	int n;
	cin >> n >> LIMIT >> FLOAT_LIMIT;

	cerr << n << "\n";
	string for_sympy = "Matrix([";
	for (int i = 0; i < n; ++i) {
		for_sympy += "[";
		for (int j = 0; j < n; ++j) {
			int before_dot = arc4random() % LIMIT;
			int after_dot = arc4random() % FLOAT_LIMIT;
			double element = before_dot + (double)after_dot / FLOAT_LIMIT;
			cerr << element << " ";
			for_sympy += to_string(before_dot) + "." + to_string(after_dot);
			for_sympy += (j + 1 == n ? "" : ",");
		}
		cerr << "\n";
		for_sympy += "]";
		for_sympy += (i + 1 == n ? "" : ",");
	}
	for_sympy += "]).det()";

	cout << for_sympy << "\n";
}

