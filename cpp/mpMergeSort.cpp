#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

using namespace std;

struct ms {
	int *a;
	int n;
};

struct m {
	int *l;
	int ls;
	int *r;
	int rs;
};

struct ms mss[4];
struct m mms[4];

void merge(int *l, int ls, int *r, int rs) {
	//in-place merge
int li = 0, ri = 0;

while (li < ls) {
	if (l[li] <= r[0]) {
		li++;
	} else if (l[li] > r[0]) {
		int tmp = l[li];
		l[li] = r[0];
		r[0] = tmp;
		li++;
		//bubble up new value
		while (ri < rs - 1) {
			if (r[ri] > r[ri + 1]) {
				int tmp = r[ri];
				r[ri] = r[ri + 1];
				r[ri + 1] = tmp;
			}
			ri++;
		}
		ri = 0;
	}
}
}

void mergeSort(int *a, int n) {
	if (n > 1) {
		mergeSort(a, n / 2);
		mergeSort(a + n / 2, n - n / 2);
		merge(a, n / 2, a + n / 2, n - n / 2);
	}
}

void *mpMergeSort(void *p) {
	struct ms *arg = (struct ms *)p;
	mergeSort(arg->a, arg->n);
}

void *mpMerge(void *p)
{
	struct m *arg = (struct m *)p;
	merge(arg->l, arg->ls, arg->r, arg->rs);
}

int num = 1 << 4;

int *a = NULL;

void generateRandomArray(int *a, int n)
{
	for (int i = 0; i < n; i++) {
		a[i] = rand();
	}
}

int main(int argc, char *argv[]) {

	if (argc > 1) {
		num = 1 << atoi(argv[1]);
	}
	a = new int[num];
	//generate random array
	generateRandomArray(a, num);
	cout << "Generate Random Array Done!\n";

	struct timeval start, end;
	long mtime, seconds, useconds;    

    	gettimeofday(&start, NULL);
	mergeSort(a, num);
	gettimeofday(&end, NULL);

	seconds  = end.tv_sec  - start.tv_sec;
	useconds = end.tv_usec - start.tv_usec;

	mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;

	printf("Elapsed time: %ld milliseconds\n", mtime);

	cout << "Do Test!\n";
	for (int i = 0; i < num - 1; i++) {
		if (a[i] > a[i + 1]) {
			cout << "a[" << i << "] = " << a[i] << " > " << "a[" << i + 1 << "] = " << a[i + 1] << endl;
		}
	}

	generateRandomArray(a, num);
	pthread_t ta[4];
	for (int i = 0; i < 4; i++) {
		mss[i].a = a + (num / 4) * i;
		mss[i].n = num / 4;
		pthread_create(&ta[i], NULL, mpMergeSort, &mss[i]);
	}

	for (int i = 0; i < 4; i++) {
		pthread_join(ta[i], NULL);
	}

	cout << "Phrase 1 done. Next MP Merge!\n";

	int rparts = 4;

	while (rparts > 1) {
		cout << rparts << " remaining parts... \n";
		int pnum = rparts / 2;
		for (int i = 0; i < pnum; i++) {
			mms[i].l = a + (num / pnum) * i;
			mms[i].ls = (num / rparts);
			mms[i].r = mms[i].l + mms[i].ls;
			mms[i].rs = mms[i].ls;
			pthread_create(&ta[i], NULL, mpMerge, &mms[i]);
		}

		for (int i = 0; i < pnum; i++) {
			pthread_join(ta[i], NULL);
		}
		rparts = pnum;
	}

	//check
	cout << "Do Test!\n";
	for (int i = 0; i < num - 1; i++) {
		if (a[i] > a[i + 1]) {
			cout << "a[" << i << "] = " << a[i] << " > " << "a[" << i + 1 << "] = " << a[i + 1] << endl;
		}
	}

	return 0;
}
