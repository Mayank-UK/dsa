#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
using namespace std;

class HuffmanCoding {
private:

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

    // ----------------------------------------------------------
    // Comparator for Min Heap
    // ----------------------------------------------------------
    struct Compare {
        bool operator()(Node* a, Node* b) {
            return a->freq > b->freq;
        }
    };

    unordered_map<char, string> huffmanCode;

    // ----------------------------------------------------------
    // Build Codes
    // ----------------------------------------------------------
    void generateCodes(Node* root, string code) {

        if (root == nullptr)
            return;

        // Leaf Node
        if (root->left == nullptr &&
            root->right == nullptr)
            huffmanCode[root->ch] = code;

        generateCodes(root->left, code + "0");
        generateCodes(root->right, code + "1");
    }

    // ----------------------------------------------------------
    // Print Tree (Inorder)
    // ----------------------------------------------------------
    void inorder(Node* root) {

        if (root == nullptr)
            return;

        inorder(root->left);

        if (root->ch != '$')
            cout << root->ch << " : "
                 << root->freq << endl;

        inorder(root->right);
    }

public:

    // ----------------------------------------------------------
    // Build Huffman Tree
    // Time: O(n log n)
    // ----------------------------------------------------------
    Node* build(
        unordered_map<char, int>& frequency) {

        priority_queue<
            Node*,
            vector<Node*>,
            Compare
        > minHeap;

        // Create leaf nodes
        for (auto& entry : frequency)
            minHeap.push(
                new Node(entry.first, entry.second));

        // Build tree
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

        Node* root = minHeap.top();

        generateCodes(root, "");

        return root;
    }

    // ----------------------------------------------------------
    // Encode
    // ----------------------------------------------------------
    string encode(const string& text) {

        string result;

        for (char c : text)
            result += huffmanCode[c];

        return result;
    }

    // ----------------------------------------------------------
    // Decode
    // ----------------------------------------------------------
    string decode(Node* root,
                  const string& encoded) {

        string result;

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
    void printCodes() {

        cout << "\nHuffman Codes\n";

        for (auto& entry : huffmanCode)
            cout << entry.first
                 << " : "
                 << entry.second
                 << endl;
    }

    void printTree(Node* root) {
        inorder(root);
    }
};

int main() {

    unordered_map<char, int> frequency = {

        {'A',5},
        {'B',9},
        {'C',12},
        {'D',13},
        {'E',16},
        {'F',45}
    };

    HuffmanCoding hc;

    auto root = hc.build(frequency);

    hc.printCodes();

    string text = "FACE";

    string encoded =
        hc.encode(text);

    cout << "\nOriginal : "
         << text << endl;

    cout << "Encoded  : "
         << encoded << endl;

    cout << "Decoded  : "
         << hc.decode(root, encoded)
         << endl;

    return 0;
}