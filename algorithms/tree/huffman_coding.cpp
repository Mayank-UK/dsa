#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

// ===== Huffman Coding =====
// Greedy prefix-code: repeatedly merge the two lowest-frequency nodes.
// DUPLICATE of algorithms/greedy/huffman_coding.cpp — kept here under tree/
// because the Huffman tree itself is a canonical binary-tree structure; the
// greedy/ version leads with the greedy-choice framing, this one with the tree.

class HuffmanCoding {
public:

    // ----------------------------------------------------------
    // Node
    // ----------------------------------------------------------
    struct Node {
        char ch;
        int freq;
        Node* left;
        Node* right;

        Node(char c, int f) {
            ch = c;
            freq = f;
            left = nullptr;
            right = nullptr;
        }
    };

private:

    // ----------------------------------------------------------
    // Comparator for Min Heap
    // ----------------------------------------------------------
    struct Compare {
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    unordered_map<char, string> huffmanCode;
    Node* treeRoot; // stored so the destructor can free the whole tree

    // ----------------------------------------------------------
    // Build Codes (tree walk)
    // ----------------------------------------------------------
    void generateCodes(Node* root, const string& code) {

        if (root == nullptr)
            return;

        // Leaf Node
        if (root->left == nullptr &&
            root->right == nullptr) {
            // Single-character alphabet edge case: the root IS the only leaf,
            // so the walk never appended a bit. Give it a 1-bit code.
            huffmanCode[root->ch] = code.empty() ? "0" : code;
        }

        generateCodes(root->left,  code + "0");
        generateCodes(root->right, code + "1");
    }

    // Post-order free — every node is `new`-ed (leaves + internal '$' nodes).
    void freeTree(Node* node) {
        if (node == nullptr)
            return;
        freeTree(node->left);
        freeTree(node->right);
        delete node;
    }

public:

    HuffmanCoding() : treeRoot(nullptr) {}

    ~HuffmanCoding() { freeTree(treeRoot); }

    // ----------------------------------------------------------
    // Build Huffman Tree
    // Time: O(n log n) — n heap pushes/pops, each O(log n)
    // ----------------------------------------------------------
    Node* build(const unordered_map<char, int>& frequency) {

        // Guard empty input — calling pq.top() below would be UB.
        if (frequency.empty())
            return nullptr;

        priority_queue<
            Node*,
            vector<Node*>,
            Compare
        > minHeap;

        // Create leaf nodes
        for (const auto& entry : frequency)
            minHeap.push(
                new Node(entry.first, entry.second));

        // Build tree by merging the two smallest until one remains.
        while (minHeap.size() > 1) {

            Node* left = minHeap.top();
            minHeap.pop();

            Node* right = minHeap.top();
            minHeap.pop();

            Node* parent =
                new Node('$',
                         left->freq + right->freq);

            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        treeRoot = minHeap.top();

        generateCodes(treeRoot, "");

        return treeRoot;
    }

    // ----------------------------------------------------------
    // Encode
    // ----------------------------------------------------------
    string encode(const string& text) const {

        string result;

        for (char c : text) {
            auto it = huffmanCode.find(c);
            if (it == huffmanCode.end())
                return ""; // char not in the code table
            result += it->second;
        }

        return result;
    }

    // ----------------------------------------------------------
    // Decode
    // ----------------------------------------------------------
    string decode(Node* root,
                  const string& encoded) const {

        if (root == nullptr || encoded.empty())
            return "";

        string result;

        // Single-leaf tree: every emitted bit is the lone char.
        if (root->left == nullptr && root->right == nullptr) {
            for (char bit : encoded) {
                (void)bit;
                result += root->ch;
            }
            return result;
        }

        Node* current = root;

        for (char bit : encoded) {

            if (bit == '0')
                current = current->left;
            else
                current = current->right;

            if (current->left == nullptr &&
                current->right == nullptr) {

                result += current->ch;
                current = root;
            }
        }

        return result;
    }

    // ----------------------------------------------------------
    // Print Codes
    // ----------------------------------------------------------
    void printCodes() const {

        cout << "Huffman Codes:\n";

        for (const auto& entry : huffmanCode)
            cout << "  " << entry.first << " : "
                 << entry.second << endl;
    }

    const unordered_map<char, string>& codes() const {
        return huffmanCode;
    }
};

int main() {

    cout << "===== Huffman Coding =====\n";

    cout << "\n[Complexity]\n";
    cout << "Time : O(n log n) build — n heap ops at O(log n) each\n";
    cout << "        O(n) for the code walk; encode/decode are O(bits)\n";
    cout << "Space: O(n) — tree nodes + code table\n";
    cout << "Note : Greedy choice = always merge the two lowest-frequency "
            "nodes (see greedy/huffman_coding.cpp).\n";

    cout << "\n[Demo]\n";

    unordered_map<char, int> frequency = {
        {'A', 5},
        {'B', 9},
        {'C', 12},
        {'D', 13},
        {'E', 16},
        {'F', 45}
    };

    HuffmanCoding hc;

    auto root = hc.build(frequency);

    hc.printCodes();

    string text = "FACE";
    string encoded = hc.encode(text);
    string decoded = hc.decode(root, encoded);

    cout << "\nEncode / decode round-trip:\n";
    cout << "  Original : " << text << endl;
    cout << "  Encoded  : " << encoded << endl;
    cout << "  Decoded  : " << decoded << endl;

    cout << "\n[Verify]\n";
    bool roundTripOk = (decoded == text);
    cout << "decode(encode(text)) == text : "
         << (roundTripOk ? "Yes" : "No — MISMATCH") << endl;

    // Compression sanity: encoded bits vs 8-bit ASCII baseline.
    int encodedBits = (int)encoded.size();
    int asciiBits   = (int)text.size() * 8;
    cout << "Bits: Huffman " << encodedBits
         << " vs ASCII " << asciiBits << endl;

    cout << "\n[Edge Cases]\n";

    // Empty text — encode returns "".
    HuffmanCoding hcEmpty;
    hcEmpty.build(frequency);
    cout << "encode(\"\")  -> \"" << hcEmpty.encode("") << "\"\n";
    cout << "decode(\"\", root) -> \"" << hcEmpty.decode(root, "") << "\"\n";

    // Single-character alphabet — tree is a single leaf; give it a 1-bit code.
    HuffmanCoding hcSingle;
    unordered_map<char, int> oneChar = { {'Z', 7} };
    auto singleRoot = hcSingle.build(oneChar);
    hcSingle.printCodes();
    string sEnc = hcSingle.encode("ZZZ");
    string sDec = hcSingle.decode(singleRoot, sEnc);
    cout << "  encode(\"ZZZ\") = \"" << sEnc << "\" -> decode = \""
         << sDec << "\" (round-trip "
         << (sDec == "ZZZ" ? "Ok)" : "FAIL)") << "\n";

    return 0;
}
