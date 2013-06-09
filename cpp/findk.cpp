class Solution {
    private:
    int binarySearch(int A[], int lo, int hi, int target) {
        if (lo > hi) return 0;
        int a = lo, b = hi;
        while (a < b) {
            int mid = (a + b) / 2;
            if (A[mid] > target) {
                b = mid - 1;
            } else if (A[mid] < target) {
                a = mid + 1;
            } else {
                return mid - lo + 1;
            }
        }
        if (a >= b) {
            if (A[a] > target) {
                return a - lo;
            } else if (A[a] <= target) {
                return a - lo + 1;
            }
        }
        //return 0;
    }
    
    int findk(int *A, int m, int *B, int n, int k) {
        if (m > n) {
            int half = m / 2;
            int mid = A[half];
            int pos = binarySearch(B, 0, n - 1, mid);
            if (half + 1 + pos == k) {
                return mid;
            } else if (half + 1 + pos < k) {
                k -= half + 1 + pos;
                return findk(A + half + 1, m - half - 1, B + pos, n - pos, k);
            } else {
                return findk(A, half, B, pos, k);
            }
        } else {
            int half = n / 2;
            int mid = B[half];
            int pos = binarySearch(A, 0, m - 1, mid);
            if (half + 1 + pos == k)
                return mid;
            else if (half + 1 + pos < k) {
                k -= half + 1 + pos;
                return findk(A + pos, m - pos, B + half + 1, n - half - 1, k);
            } else {
                return findk(A, pos, B, half, k);
            }
        }
        return 0;
    }
public:
    double findMedianSortedArrays(int A[], int m, int B[], int n) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function
        int k = 0;
        if ((m + n) % 2 == 1) {
            return findk(A, m, B, n, (m + n) / 2 + 1);
        } else
            return (findk(A, m, B, n, (m + n) / 2) + findk(A, m, B, n, (m + n) / 2 + 1)) / 2.0;
            //return 0;
    }
};