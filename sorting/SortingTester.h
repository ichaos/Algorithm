class SortingTester {
public:
        SortingTester();

        typedef int (*sortFunc)(int *, int);

        static void STester(sortFunc sf);
        static void genRanArr(int *arr, int n);
        //static int
};
