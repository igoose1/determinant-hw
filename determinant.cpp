#include <omp.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

typedef long double ld;

const ld EPS = 1e-9;
const size_t MAX_THREAD_NUM = omp_get_max_threads();

ld determinant(vector<vector<ld>> matrix) {
	const size_t n = matrix.size();
	ld result = 1;

	for (size_t i = 0; i < n; ++i) {
		size_t maxi = i;
		for (size_t j = i; j < n; ++j) {
			if (fabs(matrix[j][i]) > fabs(matrix[maxi][i])) {
				maxi = j;
			}
		}
		if (maxi != i) {
			result *= -1;
		}
		if (fabs(matrix[maxi][i]) < EPS) {
			return 0;
		}
		swap(matrix[i], matrix[maxi]);

		result *= matrix[i][i];
		const ld divide_by = matrix[i][i];
		#pragma omp parallel for
		for (size_t j = i + 1; j < n; ++j) {
			matrix[i][j] /= divide_by;
		}

		const vector<ld> &line = matrix[i];
		#pragma omp parallel for
		for (size_t j = 0; j < n; ++j) {
			if (j == i || fabs(matrix[j][i]) < EPS) {
				continue;
			}
			for (size_t k = i + 1; k < n; ++k) {
				matrix[j][k] -= line[k] * matrix[j][i];
			}
		}
	}

	return result;
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

	cout << setprecision(8);
	#ifndef TESTING
	cout << "Determinant: ";
	#endif
	cout << determinant(matrix) << "\n";
}

