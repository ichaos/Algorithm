/**
 * Find the maximum subarray problem
 * brute-force
 * divide and conquer
 * stack
 * nonrecursive, linear-time algorithm
 */
#include <iostream>
using namespace std;

struct result {
	int i; //start index
	int j; //end index
	int max_sum;
};

/*
 * input: array with positive and negative elements
 * output: the maximum subarray
 * brute-force
 */
result max_subarray_bf(int *arr, int length) {
	result res;
	int max = (1 << 31);
	int sum = 0;
	for (int i = 0; i < length; i++) {
		sum = 0;
		for (int j = i; j < length; j++) {
			sum += arr[j];
			if (max < sum) {
				max = sum;
				res.i = i;
				res.j = j;
				res.max_sum = max;
			}
		}
	}
	//cout << res.max_sum << endl;
	return res;
}

result max_cross_subarray(int *arr, int left, int right, int mid) {
	int lmax = (1 << 31);
	int sum = 0;
	int l = 0;
	//to left
	for (int i = mid; i >= left; i--) {
		sum += arr[i];
		if (sum > lmax) {
			l = i;
			lmax = sum;
		}
	}
	sum = 0;
	int rmax = (1 << 31);
	int r = 0;
	for (int i = mid + 1; i <= right; i++) {
		sum += arr[i];
		if (sum > rmax) {
			rmax = sum;
			r = i;
		}
	}

	result res;
	res.i = l;
	res.j = r;
	res.max_sum = lmax + rmax;
	return res;
}

/*
 * divide and conquer
 */
result max_subarray_dc(int *arr, int left, int right) {
	result res;
	if (left > right) return res;

	if (right == left) {
		res.i = left;
		res.j = right;
		res.max_sum = arr[left];
		return res;
	}

	int mid = (left + right) / 2;
	result lres = max_subarray_dc(arr, left, mid);
	result rres = max_subarray_dc(arr, mid + 1, right);
	result cres = max_cross_subarray(arr, left, right, mid);
	if (lres.max_sum >= rres.max_sum && lres.max_sum >= cres.max_sum) {
		return lres;
	} else if (rres.max_sum >= lres.max_sum &&
		rres.max_sum >= cres.max_sum) {
		return rres;
	} else {
		return cres;
	}
}

/*
 * stack based method
 */
result max_subarray_stack(int *arr, int length) {
	result res;
	int aux[length + 1];
	aux[0] = 0;
	for (int i = 0; i < length; i++) {
		aux[i + 1] = aux[i] + arr[i];
	}
	int li = 0;
	int lowest = aux[0];
	res.max_sum = 0;
	for (int i = 1; i < length + 1; i++) {
		if (aux[i] - lowest > res.max_sum) {
			res.max_sum = aux[i] - lowest;
			res.i = li;
			res.j = i - 1;
		}
		if (aux[i] < lowest) {
			lowest = aux[i];
			li = i;
		}
	}
	return res;
}

result max_subarray_l(int *arr, int length) {
	result res;
	if (length < 1) return res; //error

	res.i = 0;
	res.j = 0;
	res.max_sum = arr[0];

	if (length < 2) {
		return res;
	}

	int max = (1 << 31);
	int sum = arr[0];
	int lowest = sum;
	int p = 0;
	int k = 0;
	for (int i = 1; i < length; i++) {
		p += arr[i];
		sum += arr[i];
		if (res.j == i - 1) {
			if (arr[i] >= 0) {
				res.j++;
				res.max_sum += arr[i];
			}
		} else if (p > res.max_sum) {
				res.i = k;
				res.j = i;
				res.max_sum = p;
				//p = 0;
		}
		if (lowest > sum) {
			lowest = sum;
			k = i + 1;
			p = 0;
		}
	}
	return res;
}

int main() {
	int test[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 
		12, -5, -22, 15, -4, 7};

	result res = max_subarray_bf(test, 16);
	cout << "brute-force: from " << res.i << " to " << res.j << ", sum = " 
	<< res.max_sum << endl;
	res = max_subarray_dc(test, 0, 15);
	cout << "divide and conquer: from " << res.i << " to " << res.j << ", sum = " 
	<< res.max_sum << endl;
	res = max_subarray_l(test, 16);
	cout << "linear-time: from " << res.i << " to " << res.j << ", sum = " 
	<< res.max_sum << endl;
	res = max_subarray_stack(test, 16);
	cout << "stack: from " << res.i << " to " << res.j << ", sum = " 
	<< res.max_sum << endl;
	return 0;
}