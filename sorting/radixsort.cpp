#include "SortingTester.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <cstdlib>

using namespace std;

/*
 * Using lsd to sort 32-bits integer
 */
int lsd(int* a, int n) {
	int width = 8;
	int *aux = new int[n];

	int w = sizeof(int) * 8 / width;
	int R = 1 << w;
	int tmp;
	int count[R + 1];
	for (int i = 0; i < w; i++) {
		int shift = 4 * i;
		int mask = 0xf;

		for (int j = 0; j <= R; j++) {
			count[j] = 0;
		}
		for (int j = 0; j < n; j++) {
			tmp = (a[j] >> shift) & mask;
			count[tmp + 1]++;
		}
		for (int j = 0; j <= R; j++) {
			count[j + 1] += count[j];
		}
		for (int j = 0; j < n; j++) {
			tmp = (a[j] >> shift) & mask;
			//cout << "tmp " << tmp << " : " << a[j] << "; ";
			aux[count[tmp]++] = a[j];
		}
		for (int j = 0; j < n; j++) {
			a[j] = aux[j];
		}
	}
	return 0;
}

extern void quicksort(int *arr, int length);

int compare_ints(const void* a, const void* b)   // comparison function
{
    int arg1 = *reinterpret_cast<const int*>(a);
    int arg2 = *reinterpret_cast<const int*>(b);
    if(arg1 < arg2) return -1;
    if(arg1 > arg2) return 1;
    return 0;
}

//test 1M 32-bits integer
int main() {
	SortingTester::STester(lsd);
	int length = 1 << 20;
	int *test = new int[length];
	int *test2 = new int[length];
	int *test3 = new int[length];
	for (int i = 0; i < length; i++) {
		test[i] = rand();
		test2[i] = test[i];
		test3[i] = test2[i];
	}
	struct timeval begin, end; 
	gettimeofday(&begin, NULL);
	lsd(test, length);
	gettimeofday(&end, NULL);
	long dur = (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec;
	cout << "lsd: " << dur << endl;

	gettimeofday(&begin, NULL);
	quicksort(test2, length);
	gettimeofday(&end, NULL);
	dur = (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec;
	cout << "qsort: " << dur << endl;

	//std::size_t size = sizeof(test3)/sizeof(int);
	gettimeofday(&begin, NULL);
	//std::qsort(test3, length, sizeof(int), compare_ints);
	sort(test3, test3 + length);
	gettimeofday(&end, NULL);
	dur = (end.tv_sec - begin.tv_sec) * 1000000 + end.tv_usec - begin.tv_usec;
	cout << "std::qsort: " << dur << endl;
}   