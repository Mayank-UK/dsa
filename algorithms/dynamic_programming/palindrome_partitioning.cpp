#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Check whether s[left..right] is a palindrome.
bool isPalindrome(const string& s, int left, int right) {
    while (left < right) {
        if (s[left++] != s[right--]) return false;
    }
    return true;
}

// Backtracking: enumerate EVERY partition of s into palindrome pieces.
void backtrack(int start, const string& s,
               vector<string>& currentPath, vector<vector<string>>& result) {
    if (start == (int)s.length()) {
        result.push_back(currentPath);  // reached the end with valid pieces
        return;
    }

    for (int end = start; end < (int)s.length(); end++) {
        if (isPalindrome(s, start, end)) {
            currentPath.push_back(s.substr(start, end - start + 1));  // choose
            backtrack(end + 1, s, currentPath, result);               // explore
            currentPath.pop_back();                                   // un-choose
        }
    }
}

vector<vector<string>> partition(const string& s) {
    vector<vector<string>> result;
    vector<string> currentPath;
    backtrack(0, s, currentPath, result);
    return result;
}

static void printPartitions(const string& s) {
    auto parts = partition(s);
    cout << "  \"" << s << "\" -> " << parts.size() << " partition(s)\n";
    for (const auto& vec : parts) {
        cout << "    [ ";
        for (const string& str : vec) cout << "\"" << str << "\" ";
        cout << "]\n";
    }
}

int main() {
    cout << "============= Palindrome Partitioning =============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n * 2^n)   up to 2^(n-1) partitions, each checked\n";
    cout << "  Space : O(n)         recursion + current path\n";
    cout << "  Note  : backtracking ENUMERATOR (not the min-cuts DP variant)\n\n";

    cout << "[Demo]\n";
    printPartitions("aab");
    cout << "\n";

    cout << "[Cases]\n";
    printPartitions("a");
    printPartitions("aa");
    printPartitions("aba");
    cout << "\n";

    cout << "[Edge Cases]\n";
    printPartitions("");          // empty string -> one empty partition
    printPartitions("racecar");   // whole string is a palindrome
    cout << "\n";

    return 0;
}
