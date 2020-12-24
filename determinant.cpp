#include <omp.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

typedef long double ld;

const size_t MAX_THREAD_NUM = omp_get_max_threads();

struct ToCompare {
	size_t index;
	ld value;

	ToCompare(size_t index, ld value) {
		this -> index = index;
		this -> value = value;
	}

	ToCompare() {
		index = 0;
		value = 0;
	}
};

void LUP_decompositon(vector<vector<ld>> &a, vector<size_t> &p) {
	const size_t n = a.size();

	for (size_t i = 0; i <= n; ++i) {
		p[i] = i;
	}

	ToCompare local_max[MAX_THREAD_NUM];
	for (size_t i = 0; i < n; ++i) {
		for (ToCompare &el : local_max) {
			el = ToCompare(i, 0.0);
		}
		#pragma omp parallel for
		for (size_t k = i; k < n; ++k) {
			ToCompare &local = local_max[omp_get_thread_num()];
			ld candidate = fabs(a[k][i]);
			if (local.value < candidate) {
				local.index = k;
				local.value = candidate;
			}
		}

		ToCompare tc = local_max[0];
		for (ToCompare local : local_max) {
			if (tc.value < local.value) {
				tc = local;
			}
		}

		if (tc.index != i) {
			swap(p[i], p[tc.index]);
			swap(a[i], a[tc.index]);
			p[n]++;
		}

		for (size_t j = i + 1; j < n; ++j) {
			a[j][i] /= a[i][i];
			for (size_t k = i + 1; k < n; ++k) {
				a[j][k] -= a[j][i] * a[i][k];
			}
		}
	}
}

ld LUP_determinant(const vector<vector<ld>> &a, const vector<size_t> &p) {
	const size_t n = a.size();

	ld result = a[0][0];
	#pragma omp parallel for reduction(*:result)
	for (size_t i = 1; i < n; ++i) {
		result *= a[i][i];
	}

	return (p[n] - n) % 2 == 0 ? result : -result;
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

	vector<size_t> permutations(n + 1);
	LUP_decompositon(matrix, permutations);
	cout << setprecision(8);
	#ifndef TESTING
	cout << "Determinant: ";
	#endif
	cout << LUP_determinant(matrix, permutations) << "\n";
}

