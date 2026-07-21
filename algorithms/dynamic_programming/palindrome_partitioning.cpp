#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Helper function to check if a substring is a palindrome
bool isPalindrome(const string& s, int left, int right) {
    while (left < right) {
        if (s[left++] != s[right--]) {
            return false;
        }
    }
    return true;
}

// Backtracking helper function
void backtrack(int start, const string& s, vector<string>& currentPath, vector<vector<string>>& result) {
    // Base case: if we reach the end of the string, add the current partition to result
    if (start == s.length()) {
        result.push_back(currentPath);
        return;
    }

    // Try every possible prefix starting from 'start'
    for (int end = start; end < s.length(); end++) {
        // If the substring s[start...end] is a palindrome
        if (isPalindrome(s, start, end)) {
            // Choose: add it to the current path
            currentPath.push_back(s.substr(start, end - start + 1));
            
            // Explore: recurse for the remaining substring
            backtrack(end + 1, s, currentPath, result);
            
            // Un-choose: backtrack by removing the last element
            currentPath.pop_back();
        }
    }
}

// Main function to partition string into palindromes
vector<vector<string>> partition(string s) {
    vector<vector<string>> result;
    vector<string> currentPath;
    backtrack(0, s, currentPath, result);
    return result;
}

int main() {
    string s = "aab";
    vector<vector<string>> partitions = partition(s);

    cout << "Palindrome partitions for \"" << s << "\":\n";
    for (const auto& vec : partitions) {
        cout << "[ ";
        for (const string& str : vec) {
            cout << "\"" << str << "\" ";
        }
        cout << "]\n";
    }

    return 0;
}