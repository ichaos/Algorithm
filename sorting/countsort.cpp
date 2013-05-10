#include <iostream>

//implementation of count sorting
//corner case: array[i] == 0 or array[i] < 0
int countingSort(int *arr, int length) {
	int min = arr[0];
	int max = min;
	
	//find maximum number from this array		
	for (int i = 0; i < length; i++) {
		if (max < arr[i])
			max = arr[i];
		if (min > arr[i])
			min = arr[i];
	}

	if (min >= 0) {
		max++; //for zero
	} else if (min < 0) {
		max -= min; //for negative
		max++;
	}

	if (max >= length) {
		std::cout << "Array size: " << length << " and maximum is " << max << ". It seems counting sort is not very suitable.\n";
	}
	int *cp = new int[length];

	int *countbase = new int[max];
	
	
	for (int i = 0; i < max; i++)
		countbase[i] = 0;

	int *count = countbase - min;
	//std::cout << count << ":" << countbase << " - " <<  &count[min] << "\n";
	for (int i = 0; i < length; i++) {
		count[arr[i]]++;
		cp[i] = arr[i];
	}

	int total = 0;
	int tmp = 0;
	for (int i = 0; i < max; i++) {
		tmp = countbase[i];
		countbase[i] = total;
		total += tmp;
	}


	for (int i = 0; i < length; i++) {
		arr[count[cp[i]]] = cp[i];
		count[cp[i]]++;
	}

	delete [] cp;
	delete [] countbase;
	return 0;
}

int main () {
	int arr[] = {1, 3, 2, 5, 4, 9, 8, 6, 7, 9, 9, 8, 1, 3, 1, 2, 1, 0, 0, 0, 0, 0, -1, -2, -3, -2, -2}; //
	int length = 17 + 10;
	countingSort(arr, length);

	for (int i = 0; i < length; i++)
		std::cout << arr[i];
	std::cout << "\n";
	return 0;
}
