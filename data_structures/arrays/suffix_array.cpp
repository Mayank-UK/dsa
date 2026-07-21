#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class SuffixArray {
public:
    vector<int> p;   // The Suffix Array
    vector<int> c;   // The Equivalence Classes
    vector<int> lcp; // The Longest Common Prefix Array
    string s;

    SuffixArray(string input_string) {
        // Append a sentinel character that is lexicographically smaller than any valid character
        s = input_string + "$"; 
        int n = s.length();
        
        p.assign(n, 0);
        c.assign(n, 0);

        buildSuffixArray();
        buildLCPArray();
    }

private:
    // Helper function for O(N) Radix/Counting Sort
    void count_sort() {
        int n = p.size();
        vector<int> cnt(n, 0);
        
        // Count frequencies of equivalence classes
        for (auto x : c) {
            cnt[x]++;
        }
        
        vector<int> p_new(n);
        vector<int> pos(n);
        pos[0] = 0;
        
        // Determine starting positions for each bucket
        for (int i = 1; i < n; i++) {
            pos[i] = pos[i - 1] + cnt[i - 1];
        }
        
        // Distribute elements into buckets
        for (auto x : p) {
            int i = c[x];
            p_new[pos[i]] = x;
            pos[i]++;
        }
        p = p_new;
    }

    // Phase 1: Build the Suffix Array in O(N log N)
    void buildSuffixArray() {
        int n = s.size();

        // Base case: k = 0 (Sort substrings of length 1)
        vector<pair<char, int>> a(n);
        for (int i = 0; i < n; i++) {
            a[i] = {s[i], i};
        }
        
        // Initial standard sort is O(N log N)
        sort(a.begin(), a.end());
        
        for (int i = 0; i < n; i++) p[i] = a[i].second;
        
        // Assign initial equivalence classes
        c[p[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (a[i].first == a[i - 1].first) {
                c[p[i]] = c[p[i - 1]];
            } else {
                c[p[i]] = c[p[i - 1]] + 1;
            }
        }

        // Transitions: Sort substrings of length 2^k -> 2^(k+1)
        int k = 0;
        while ((1 << k) < n) {
            // Shift current sorted suffixes to act as the second half of the new substrings
            for (int i = 0; i < n; i++) {
                p[i] = (p[i] - (1 << k) + n) % n;
            }

            // Radix sort by the first half (which is already reflected in p)
            count_sort();

            // Update equivalence classes for the new 2^(k+1) length substrings
            vector<int> c_new(n);
            c_new[p[0]] = 0;
            for (int i = 1; i < n; i++) {
                pair<int, int> prev = {c[p[i - 1]], c[(p[i - 1] + (1 << k)) % n]};
                pair<int, int> now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
                
                if (now == prev) {
                    c_new[p[i]] = c_new[p[i - 1]];
                } else {
                    c_new[p[i]] = c_new[p[i - 1]] + 1;
                }
            }
            c = c_new;
            k++;
        }
    }

    // Phase 2: Build the LCP Array using Kasai's Algorithm in O(N)
    void buildLCPArray() {
        int n = s.size();
        lcp.assign(n, 0);
        int k = 0; // Tracks the currently matched prefix length
        
        // Note: We ignore the last character (the sentinel '$')
        for (int i = 0; i < n - 1; i++) {
            int pi = c[i];     // Where does the suffix starting at i reside in the sorted array?
            int j = p[pi - 1]; // The starting index of the suffix just before it in the sorted array
            
            // Expand the matching prefix window
            while (s[i + k] == s[j + k]) {
                k++;
            }
            
            lcp[pi] = k;
            
            // The LCP of the next suffix in the original string will be at least k - 1
            k = max(k - 1, 0); 
        }
    }
};

int main() {
    // String to process
    string text = "ababba";
    cout << "Original Text: " << text << "\n\n";

    // Initialize and build the Suffix Array and LCP Array
    SuffixArray sa(text);

    cout << "--- Suffix Array Results ---\n";
    cout << "Index\tSA[i]\tLCP[i]\tSuffix\n";
    cout << "--------------------------------------\n";
    
    // Iterate through the processed string (including the sentinel '$')
    for (int i = 0; i < sa.s.length(); i++) {
        cout << i << "\t" 
             << sa.p[i] << "\t" 
             << sa.lcp[i] << "\t" 
             << sa.s.substr(sa.p[i]) << "\n";
    }
    cout << "--------------------------------------\n";

    return 0;
}