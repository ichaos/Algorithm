#include "SortingTester.h"
#include <stdlib.h>
#include <iostream>

using namespace std;

static int seed = 42;

//test kinds of sorting code
SortingTester::SortingTester() {
}

void SortingTester::genRanArr(int *arr, int n) {
        seed = time(NULL);
        srand(seed);
        for (int i = 0; i < n; i++) {
                arr[i] = rand() % (10 * n);
        }
        seed = arr[n - 1];
}

void printArray(int *arr, int l) {
        for (int i = 0; i < l; i++)
                cout << arr[i] << " ";
        cout << "\n";
}

int testSorted(int *arr, int l, int dir) {
        for (int i = 0; i < l - 1; i++)
                if (arr[i] > arr[i + 1])
                        return i + 1;
        return 0;
}

void SortingTester::STester(SortingTester::sortFunc sf) {
        //test array length 1
        int arr1[1];
        SortingTester::genRanArr(arr1, 1);
        sf(arr1, 1);
        cout << "Test arr[1] for correctness: " << arr1[0] << endl;

        //test array with different length
        int kinds[] = {2, 3, 4, 8, 9, 16, 23, 32};
        int *arrTest = new int[kinds[sizeof(kinds) / sizeof(int) - 1]];
        for (int i = 0; i < sizeof(kinds) / sizeof(int); i++) {
                SortingTester::genRanArr(arrTest, kinds[i]);
                cout << "Test " << i << ":\nbefore sorting: ";
                printArray(arrTest, kinds[i]);
                sf(arrTest, kinds[i]);
                cout << "after sorting: ";
                printArray(arrTest, kinds[i]);
                //future work : check correctness
                if (testSorted(arrTest, kinds[i], 0))
                        cout << "======Test failed======\n";
        }
        delete []arrTest;
}
