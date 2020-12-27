#include <omp.h>

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <chrono>
#include <stdio.h>

using namespace std;

typedef long double ld;

int MAX_THREAD_NUM = omp_get_max_threads();

const ld EPS = 1e-9;

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


int main(int argc, char *argv[]) {
	const auto started_at = chrono::high_resolution_clock::now();

#ifndef TESTING
	if (argc < 2) {
		cerr << "No thread number provided.\n";
		return 2;
	}

	MAX_THREAD_NUM = atoi(argv[1]);
	cerr << MAX_THREAD_NUM << "\n";
	omp_set_num_threads(MAX_THREAD_NUM);

	if (argc < 3) {
		cerr << "No input file provided.\n";
		return 1;
	}

	if (!freopen(argv[2], "r", stdin)) {
		cerr << "Couldn't open file for reading.\n";
		return 1;
	}

	if (argc > 3) {
		if (!freopen(argv[3], "w", stdout)) {
			cerr << "Couldn't open file for writing.\n";
			return 1;
		}
	}
#endif

	size_t n;
	cin >> n;

	vector<vector<ld>> matrix(n, vector<ld> (n));

	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			cin >> matrix[i][j];
		}
	}

	const auto scanned_at = chrono::high_resolution_clock::now();

	cout << setprecision(8);
	cerr << setprecision(8);
#ifndef TESTING
	cout << "Determinant: ";
#endif
	cout << determinant(matrix) << "\n";

	const auto computed_at = chrono::high_resolution_clock::now();
#ifdef TESTING
	cerr << "Done in "
		<< chrono::duration_cast<std::chrono::milliseconds>(
				computed_at - started_at
			).count() << "ms.\n"
		<< "Scanned in "
		<< chrono::duration_cast<std::chrono::milliseconds>(
				scanned_at - started_at
			).count() << "ms.\n"
		<< "Computed in "
		<< chrono::duration_cast<std::chrono::milliseconds>(
				computed_at - scanned_at
			).count() << "ms.\n";
#else
	fprintf(
		stderr,
		"\nTime (%i thread(s)): %f ms.\n",
		MAX_THREAD_NUM,
		(double)chrono::duration_cast<std::chrono::milliseconds>(
			computed_at - scanned_at
		).count()
	);
#endif
}

