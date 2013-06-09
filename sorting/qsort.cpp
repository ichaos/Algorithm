#include <iostream>

inline int partition(int *arr, int s, int e) {
	//find a pivot
	int pivot = arr[s];
	int i, j;

	for (i = s + 1, j = s + 1; j <= e; j++) {
		if (arr[j] < pivot) {
			//swap
			int tmp = arr[j];
			arr[j] = arr[i];
			arr[i] = tmp;
			i++;
		}
	}

	arr[s] = arr[i - 1];
	arr[i - 1] = pivot;
	return i - 1;
}

void _qsort(int *arr, int s, int e) {
	//pivot index
	if (s >= e)
		return;
	int pi = partition(arr, s, e);
	//std::cout << pi << " - ";
	_qsort(arr, s, pi - 1);
	_qsort(arr, pi + 1, e);
}

//quick sort

void quicksort(int *arr, int length) {
	_qsort(arr, 0, length - 1);
}

/*
int main() {
	int arr[] = {10, 5, 7, 1, 4, 2, 9, 3, 7, 8};

	qsort(arr, 10);

	for (int i = 0; i < 10; i++)
		std::cout << arr[i];

	std::cout << "\n";

	return 0;
}
*/
