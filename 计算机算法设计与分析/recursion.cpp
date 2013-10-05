#include <vector>
#include <iostream>

using namespace std;

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

//递归
void Perm(std::vector<int> &v, int k, int m) {
	if (k == m) {
		for (int i = 0; i <= m; i++)
			cout << v[i] << " ";
		cout << endl;
	} else {
		for (int i = k; i <= m; i++) {
			swap(v[i], v[m]);
			Perm(v, k + 1, m);
			swap(v[i], v[m]);
		}
	}
}

int main() {
	int arr[] = { 1, 2, 3, 4, 5, 6 };
	vector<int> v(arr, arr + 6);

	Perm(v, 0, 5);

	return 0;
}