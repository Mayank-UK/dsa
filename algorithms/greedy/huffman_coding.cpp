#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Huffman tree node. Internal nodes carry ch == '\0'; leaves carry a real char.
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    HuffmanNode(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Post-order free so the tree leaks nothing.
void freeTree(HuffmanNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// Greedy: repeatedly merge the two lowest-frequency nodes. The resulting prefix
// code is optimal (minimum weighted external path length) for the given counts.
struct HuffmanResult {
    unordered_map<char, string> codes;   // leaf char -> bitstring
    int distinctChars;
    int totalChars;
    long long encodedBits;               // length of the encoded bitstream
    string encodedText;
    double originalBits;                 // 8 bits/char baseline
};

// Walk the tree, assigning "0"/"1" edges; record a code at each leaf.
void fillCodes(HuffmanNode* root, const string& prefix,
               unordered_map<char, string>& codes) {
    if (!root) return;
    if (!root->left && !root->right) {
        codes[root->ch] = prefix.empty() ? "0" : prefix;  // single-char text edge case
        return;
    }
    fillCodes(root->left, prefix + "0", codes);
    fillCodes(root->right, prefix + "1", codes);
}

HuffmanResult buildHuffmanTree(const string& text) {
    unordered_map<char, int> freq;
    for (char c : text) freq[c]++;

    auto cmp = [](HuffmanNode* a, HuffmanNode* b) { return a->freq > b->freq; };
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, decltype(cmp)> pq(cmp);

    for (auto& [c, f] : freq) pq.push(new HuffmanNode(c, f));

    HuffmanResult res;
    if (freq.empty()) {           // empty text: no tree to build
        res.distinctChars = 0;
        res.totalChars = 0;
        res.encodedBits = 0;
        res.originalBits = 0.0;
        return res;
    }

    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    HuffmanNode* root = pq.top();
    fillCodes(root, "", res.codes);
    res.distinctChars = (int)freq.size();
    res.totalChars = (int)text.size();
    for (char c : text) res.encodedText += res.codes[c];
    res.encodedBits = (long long)res.encodedText.size();
    res.originalBits = (double)res.totalChars * 8.0;

    freeTree(root);
    return res;
}

int main() {
    cout << "================ Huffman Coding ================\n\n";

    cout << "[Complexity]\n";
    cout << "  Time  : O(n log k)   n = text length, k = distinct chars\n";
    cout << "  Space : O(k)\n";
    cout << "  Note  : greedy merge of two smallest frequencies -> optimal prefix code\n\n";

    cout << "[Demo]\n";
    string text = "huffman coding algorithm example";
    cout << "  text: \"" << text << "\"\n";
    HuffmanResult r = buildHuffmanTree(text);
    cout << "  distinct chars = " << r.distinctChars
         << ", total chars = " << r.totalChars << "\n";
    cout << "  codes (sorted by char):\n";
    vector<pair<char, string>> sorted(r.codes.begin(), r.codes.end());
    sort(sorted.begin(), sorted.end());
    for (auto& [c, code] : sorted) {
        cout << "    '" << (c == ' ' ? '_' : c) << "' : " << code << "\n";
    }
    cout << "  encoded bitstream = " << r.encodedBits << " bits\n";
    cout << "  vs 8-bit ASCII    = " << (long long)r.originalBits << " bits  ("
         << (100.0 * (1.0 - r.encodedBits / r.originalBits)) << "% smaller)\n\n";

    cout << "[Edge Cases]\n";
    cout << "  single character 'aaaa' : code = \""
         << buildHuffmanTree("aaaa").codes['a'] << "\"\n";
    cout << "  two characters 'ababab' :\n";
    {
        HuffmanResult s = buildHuffmanTree("ababab");
        cout << "    'a' = " << s.codes['a'] << ", 'b' = " << s.codes['b']
             << ", bits = " << s.encodedBits << "\n";
    }
    cout << "  empty string          : distinct = "
         << buildHuffmanTree("").distinctChars << "\n";
    cout << "\n";

    return 0;
}
