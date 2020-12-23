#include <omp.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

typedef long double ld;

struct ToCompare {
	ld value;
	size_t index;
};

void LUP_decompositon(vector<vector<ld>> &a, vector<int> &p) {
	const size_t n = (int)a.size();
	size_t i;
	#pragma omp parallel for private(i)
	for (i = 0; i <= n; ++i) {
		p[i] = i;
	}

	size_t k, j;
	ld candidate;
	for (i = 0; i < n; ++i) {
		ToCompare tc;
		tc.index = i, tc.value = a[i][i];
		for (k = i; k < n; ++k) {
			candidate = fabs(a[k][i]);
			if (a[tc.index][i] <= candidate) {
				tc.index = k;
				tc.value = candidate;
			}
		}

		if (tc.index != i) {
			swap(p[i], p[tc.index]);
			swap(a[i], a[tc.index]);
			p[n]++;
		}

		#pragma omp parallel for
		for (j = i + 1; j < n; ++j) {
			a[j][i] /= a[i][i];
			for (k = i + 1; k < n; ++k) {
				a[j][k] -= a[j][i] * a[i][k];
			}
		}
	}
}

ld LUP_determinant(const vector<vector<ld>> &a, const vector<int> &p) {
	const int n = (int)a.size();

	int i;
	ld result = a[0][0];
	#pragma omp parallel for reduction(*:result)
	for (i = 1; i < n; ++i) {
		result *= a[i][i];
	}

	if (p[n] - n == 0 || !result) {
		return result;
	} else {
		return -result;
	}
}


int main(void) {
	size_t n;
	cin >> n;

	vector<vector<ld>> matrix(n, vector<ld> (n));

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			cin >> matrix[i][j];
		}
	}

	vector<int> permutations(n + 1);
	LUP_decompositon(matrix, permutations);
	cout << setprecision(8);
	#ifndef TESTING
	cout << "Determinant: ";
	#endif
	cout << LUP_determinant(matrix, permutations) << "\n";
}

