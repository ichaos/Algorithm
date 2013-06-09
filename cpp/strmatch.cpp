/**
 * string match algorithm based on Introduction to the algorithm
 */

#include <iostream>
#include <string>
#include <map>

using namespace std;

/*
 * brute-force way
 */
int strstr(string p, string s) {
        int n = s.length();
        int m = p.length();
        bool match = true;
        if (m > n) return -1;

        for (int i = 0; i <= n - m; i++) {
                for (int j = 0; j < m; j++) {
                        if (p[j] != s[i + j]) {
                                match = false;
                                break;
                        }
                }
                if (match) return i;
                match = true;
        }
        return -1;
}

/*
 * Knuth-Morris-Pratt algorithm
 * assumption: pi.length === p.length
 */
void pre_func(string p, int pi[]) {
        pi[0] = 0;
        int k = 0;
        for (int i = 1; i < p.length(); i++) {
                while (k > 0 && p[k] != p[i])
                        k = pi[k - 1];
                if (p[k] == p[i])
                        k++;
                pi[i] = k;
        }
        for (int i = 0; i < p.length(); i++) {
                cout << pi[i] << " ";
        }
}

int kmp_match2(string p, string s) {
        int m = p.length();
        int n = s.length();
        int pi[m];
        int k = 0;
        pre_func(p, pi);

        int j = 0;
        for (int i = 0; i <= n - m; ) {
                for ( ; j < m; j++) {
                        if (p[j] != s[i + j])
                                break;
                }
                if (j == m) return i;
                if (j == 0) i++;
                i += j;
                j = pi[j];
        }
        return -1;
}

int kmp_match(string p, string s) {
        int m = p.length();
        int n = s.length();
        int pi[m];
        pre_func(p, pi);
        cout << endl;
        int k = 0;
        for (int i = 0; i < n; i++) {
                while (k > 0 && p[k] != s[i])
                        k = pi[k - 1];
                if (s[i] == p[k])
                        k++;
                if (k == m)
                        return i - m + 1;
        }
        return -1;
}

int sunday_match(string p, string t) {
        int m = p.length();
        int n = t.length();
        //build
        map<char, int> pos;
        for (int i = 0; i < m; i++) {
                pos[p[i]] = i + 1;
        }

        for (int i = 0; i <= n - m; i++) {
                int j;
                for (j = 0; j < m; j++) {
                        if (p[j] != t[i + j]) {
                                char next = t[i + m];
                                if (pos.find(next) == pos.end()) {
                                        i += m;
                                } else {
                                        i += (m - pos[next]);
                                }
                                break;
                        }
                }
                if (j == m) return i;
        }
        return -1;
}

int main(int argc, char *argv) {
        //test
        string p = "ab";
        string s = "aeabcd";
        while (1) {
                cin >> p;
                cin >> s;
                cout << "substring test(bf): " << p << " of " << s << " "
                     << strstr(p, s) << endl;
                cout << "substring test(kmp2): " << p << " of " << s << " "
                     << kmp_match2(p, s) << endl;
                cout << "substring test(kmp): " << p << " of " << s << " "
                     << kmp_match(p, s) << endl;
                cout << "substring test(sunday): " << p << " of " << s << " "
                     << sunday_match(p, s) << endl;
        }
}
