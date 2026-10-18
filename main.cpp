#include <iostream>
#include <new>
using namespace std;

void delete_matrix(int** a, size_t n)
{
	if (a == 0) return;
	for (size_t i = 0; i < n; ++i)
		delete[] a[i];
	delete[] a;
}

int** concat_rows(
	const int* const* lhs, size_t n1, size_t m1,
	const int* const* rhs, size_t n2, size_t m2)
{
	size_t n = (n1 > n2) ? n1 : n2;
	int** result = new int*[n]();
	try {
		for (size_t i = 0; i < n; ++i) {
			size_t left = (i < n1) ? m1 : 0;
			size_t right = (i < n2) ? m2 : 0;

			result[i] = new int[left + right];

			for (size_t j = 0; j < left; ++j)
				result[i][j] = lhs[i][j];

			for (size_t j = 0; j < right; ++j)
				result[i][left+j] = rhs[i][j];
		}
	}
	catch (...) {
		delete_matrix(result, n);
		throw;
	}
	return result;
}

int main()
{
	size_t n1=0, m1=0, n2=0, m2=0;
	size_t n =0;
	int** a = 0;
	int** b = 0;
	int** c = 0;
	try {
		if (!(cin >> n1 >> m1) || n1 == 0 || m1 == 0)
			return 1;
		a = new int*[n1]();

		for (size_t i = 0; i < n1; ++i) {
			a[i] = new int[m1];
			for (size_t j = 0; j < m1; ++j)
				if (!(cin >> a[i][j])) {
					delete_matrix(a, n1);
					return 1;
				}
		}
		if (!(cin >> n2 >> m2) || n2 == 0 || m2 == 0) {
                        	delete_matrix(a, n1);
				return 1;
		}

		b = new int*[n2]();
		for (size_t i = 0; i < n2; ++i) {
			b[i] = new int[m2];

			for (size_t j = 0; j < m2; ++j)
				if (!(cin >> b[i][j])) {
					delete_matrix(a, n1);
					delete_matrix(a, n2);
					return 1;
				}
		}
		c = concat_rows(a,n1,m1,b,n2,m2);
		size_t n = (n1 > n2) ? n1 : n2;
		for (size_t i = 0; i < n; ++i) {
			size_t left = (i < n1) ? m1 : 0;
			size_t right = (i < n2) ? m2 : 0;
			for (size_t j = 0; j < left + right; ++j)
				cout << c[i][j] << ' ';
			cout << '\n';
		}
	}
	catch (const bad_alloc&) {
		delete_matrix(a, n1);
        	delete_matrix(b, n2);
        	delete_matrix(c, n);
		cerr << "memory allocation error\n";
		return 2;
	}
	delete_matrix(a, n1);
        delete_matrix(b, n2);
        delete_matrix(c, n);

	return 0;
}






























