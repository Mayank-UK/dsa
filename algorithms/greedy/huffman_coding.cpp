#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>

using namespace std;

// Node structure for the Huffman Tree
struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char character, int frequency) {
        ch = character;
        freq = frequency;
        left = right = nullptr;
    }
};

// Comparator for the min-priority queue
struct Compare {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq;
    }
};

// Recursive function to generate Huffman codes from the tree
void generateCodes(HuffmanNode* root, string str, unordered_map<char, string>& huffmanCodes) {
    if (!root) return;

    // If it's a leaf node, store the code
    if (!root->left && !root->right) {
        huffmanCodes[root->ch] = str;
    }

    generateCodes(root->left, str + "0", huffmanCodes);
    generateCodes(root->right, str + "1", huffmanCodes);
}

// Function to build Huffman Tree and print codes
void buildHuffmanTree(string text) {
    // Step 1: Count frequencies of each character
    unordered_map<char, int> freqMap;
    for (char ch : text) {
        freqMap[ch]++;
    }

    // Step 2: Create a min-priority queue
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;

    for (auto pair : freqMap) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }

// Step 3: Iterate until a single root node remains
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();

        // Create internal node with combined frequency (fixed typo)
        int sumFreq = left->freq + right->freq;
        HuffmanNode* internalNode = new HuffmanNode('\0', sumFreq); // '\0' indicates internal node
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    // Root of the Huffman Tree
    HuffmanNode* root = pq.top();

    // Step 4: Generate codes
    unordered_map<char, string> huffmanCodes;
    generateCodes(root, "", huffmanCodes);

    cout << "Huffman Codes for characters:\n";
    for (auto pair : huffmanCodes) {
        cout << "'" << pair.first << "' : " << pair.second << "\n";
    }

    // Print encoded text
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCodes[ch];
    }
    cout << "\nOriginal text: " << text << "\n";
    cout << "Encoded bitstream: " << encodedStr << "\n";
}

int main() {
    string text = "huffman coding algorithm example";
    buildHuffmanTree(text);

    return 0;
}