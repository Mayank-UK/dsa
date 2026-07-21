#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Assuming lowercase English alphabet for simplicity
const int ALPHABET_SIZE = 26;

// Trie Node structure
struct Node {
    int children[ALPHABET_SIZE];
    int fail_link;
    vector<int> matched_patterns; // Stores indices of patterns that end at this node

    Node() {
        fill(begin(children), end(children), -1);
        fail_link = -1;
    }
};

class AhoCorasick {
private:
    vector<Node> trie;
    vector<string> patterns;

    // Helper to get character index
    int charToIndex(char c) {
        return c - 'a';
    }

public:
    // Constructor initializes the root node and builds the automaton
    AhoCorasick(const vector<string>& input_patterns) {
        patterns = input_patterns;
        trie.emplace_back(); // Initialize root node at index 0
        
        buildTrie();
        buildFailureLinks();
    }

    // Phase 1: Build a standard Trie from the given patterns
    void buildTrie() {
        for (int i = 0; i < patterns.size(); ++i) {
            int current_node = 0;
            for (char c : patterns[i]) {
                int index = charToIndex(c);
                // If path doesn't exist, create a new node
                if (trie[current_node].children[index] == -1) {
                    trie[current_node].children[index] = trie.size();
                    trie.emplace_back();
                }
                current_node = trie[current_node].children[index];
            }
            // Mark the end of the pattern by storing its index
            trie[current_node].matched_patterns.push_back(i);
        }
    }

    // Phase 2: Build failure links using Breadth-First Search (BFS)
    void buildFailureLinks() {
        queue<int> q;

        // Initialize root's children
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            if (trie[0].children[i] != -1) {
                trie[trie[0].children[i]].fail_link = 0;
                q.push(trie[0].children[i]);
            } else {
                // Optimization: Missing root children point back to root
                trie[0].children[i] = 0;
            }
        }

        // BFS to set failure links for deeper nodes
        while (!q.empty()) {
            int current_node = q.front();
            q.pop();

            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                if (trie[current_node].children[i] != -1) {
                    int child_node = trie[current_node].children[i];
                    int fail_node = trie[current_node].fail_link;
                    
                    // Set the failure link of the child
                    trie[child_node].fail_link = trie[fail_node].children[i];
                    
                    // Merge matched patterns from the failure link (Dictionary Link integration)
                    // This ensures we catch substrings that are also patterns
                    int child_fail = trie[child_node].fail_link;
                    for (int pattern_idx : trie[child_fail].matched_patterns) {
                        trie[child_node].matched_patterns.push_back(pattern_idx);
                    }
                    
                    q.push(child_node);
                } else {
                    // Automaton optimization: Point missing edges to the failure node's edges
                    trie[current_node].children[i] = trie[trie[current_node].fail_link].children[i];
                }
            }
        }
    }

    // Phase 3: Search the text using the built automaton
    void search(const string& text) {
        int current_node = 0;
        bool found = false;

        cout << "--- Search Results ---\n";
        for (int i = 0; i < text.length(); ++i) {
            int index = charToIndex(text[i]);
            current_node = trie[current_node].children[index];

            // If there are matches ending at the current state, print them
            for (int pattern_idx : trie[current_node].matched_patterns) {
                found = true;
                const string& match = patterns[pattern_idx];
                int start_pos = i - match.length() + 1;
                cout << "Pattern '" << match << "' found from index " 
                     << start_pos << " to " << i << "\n";
            }
        }

        if (!found) {
            cout << "No patterns found in the text.\n";
        }
        cout << "----------------------\n";
    }
};

int main() {
    // Array of keywords to search for
    vector<string> patterns = {"he", "she", "his", "hers"};
    
    // Initialize the Aho-Corasick automaton
    AhoCorasick ac(patterns);

    // Text to search within
    string text = "ahishers";
    
    cout << "Text: " << text << "\n";
    cout << "Patterns: ";
    for(const string& p : patterns) cout << p << " ";
    cout << "\n\n";

    // Perform the search
    ac.search(text);

    return 0;
}