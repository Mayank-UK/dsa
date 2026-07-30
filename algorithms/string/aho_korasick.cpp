#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

// Aho-Corasick: a trie automaton that finds ALL of a set of patterns in a text
// in a single O(n + matches) pass. Each node carries a failure link (longest
// proper suffix that is also a pattern prefix) so that on a mismatch we fall
// back to the right state instead of restarting — the KMP idea generalized to a
// dictionary. Output links propagate matches along failure chains.
//
// NOTE: this implementation assumes lowercase 'a'-'z' only (alphabet size 26).

const int ALPHABET_SIZE = 26;

struct TrieNode {
    int children[ALPHABET_SIZE];
    int fail_link;
    vector<int> out;            // pattern indices that end (via output links) here

    TrieNode() {
        fill(begin(children), end(children), -1);
        fail_link = -1;
    }
};

struct Match {
    int patternIndex;
    int start;                  // inclusive, in the text
    int end;                    // inclusive
};

class AhoCorasick {
private:
    vector<TrieNode> trie;
    vector<string> patterns;

    static int charIndex(char c) { return c - 'a'; }

    void buildTrie() {
        for (int pi = 0; pi < (int)patterns.size(); ++pi) {
            int cur = 0;
            for (char c : patterns[pi]) {
                int idx = charIndex(c);
                if (trie[cur].children[idx] == -1) {
                    trie[cur].children[idx] = (int)trie.size();
                    trie.emplace_back();
                }
                cur = trie[cur].children[idx];
            }
            trie[cur].out.push_back(pi);        // mark pattern end
        }
    }

    void buildFailureLinks() {
        queue<int> q;
        for (int i = 0; i < ALPHABET_SIZE; ++i) {     // depth-1 nodes → fail to root
            int child = trie[0].children[i];
            if (child != -1) { trie[child].fail_link = 0; q.push(child); }
            else            { trie[0].children[i] = 0; }   // missing edge at root → root
        }
        while (!q.empty()) {
            int cur = q.front(); q.pop();
            for (int i = 0; i < ALPHABET_SIZE; ++i) {
                int child = trie[cur].children[i];
                if (child != -1) {
                    trie[child].fail_link = trie[trie[cur].fail_link].children[i];
                    // Merge outputs reachable via the failure link (output links).
                    for (int pi : trie[trie[child].fail_link].out)
                        trie[child].out.push_back(pi);
                    q.push(child);
                } else {
                    // Automaton optimization: route missing edges through the fail link.
                    trie[cur].children[i] = trie[trie[cur].fail_link].children[i];
                }
            }
        }
    }

public:
    AhoCorasick(const vector<string>& pats) : patterns(pats) {
        trie.emplace_back();                    // root = node 0
        buildTrie();
        buildFailureLinks();
    }

    // Returns every occurrence of every pattern in `text`, in text order.
    vector<Match> search(const string& text) const {
        vector<Match> matches;
        int cur = 0;
        for (int i = 0; i < (int)text.length(); ++i) {
            cur = trie[cur].children[charIndex(text[i])];
            for (int pi : trie[cur].out) {
                int len = (int)patterns[pi].length();
                matches.push_back({ pi, i - len + 1, i });
            }
        }
        return matches;
    }

    const vector<string>& getPatterns() const { return patterns; }
};

// ─── Demo helpers ───
static void printMatches(const vector<string>& patterns, const vector<Match>& m) {
    if (m.empty()) { cout << "  result : Not Found\n"; return; }
    for (const Match& mt : m)
        cout << "  '" << patterns[mt.patternIndex] << "' at [" << mt.start
             << ".." << mt.end << "]\n";
}

static void runCase(const string& label, const vector<string>& patterns, const string& text) {
    cout << "[" << label << "]\n";
    cout << "  text    : " << text << "\n  patterns: ";
    for (size_t i = 0; i < patterns.size(); ++i) cout << patterns[i] << (i + 1 < patterns.size() ? ", " : "");
    cout << "\n";
    printMatches(patterns, AhoCorasick(patterns).search(text));
    cout << "\n";
}

int main() {
    cout << "==================== Aho-Corasick Multi-Pattern Search ====================\n\n";

    cout << "[Complexity]\n";
    cout << "  Build  : O(sum of pattern lengths)        trie + failure links (BFS)\n";
    cout << "  Search : O(n + total matches)             one pass over the text\n";
    cout << "  Space  : O(sum of pattern lengths * |Σ|)\n";
    cout << "  Notes  : failure link = KMP generalized to a dictionary; output links\n";
    cout << "           let one position report several patterns. Lowercase a-z only.\n\n";

    cout << "[Demo]\n";
    vector<string> patterns = {"he", "she", "his", "hers"};
    string text = "ahishers";
    cout << "  text    : " << text << "\n  patterns: he, she, his, hers\n";
    printMatches(patterns, AhoCorasick(patterns).search(text));
    cout << "\n";

    cout << "[Edge Cases]\n";
    runCase("overlapping dict", {"a", "aa", "aaa"}, "aaaa");   // many overlapping hits
    runCase("none present    ", {"xyz", "q"},      "abcdef");
    runCase("single pattern  ", {"ab"},             "ababcab");
    runCase("pattern > text  ", {"abcdef"},         "abc");

    return 0;
}
