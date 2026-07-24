#include <iostream>
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

class Trie {

private:

    struct Node {

        unordered_map<char, Node*> children;
        bool isEndOfWord;

        Node() {
            isEndOfWord = false;
        }
    };

    Node* root;

    // ---------------- Destructor ----------------

    void destroy(Node* node) {

        if (node == nullptr)
            return;

        for (auto& child : node->children)
            destroy(child.second);

        delete node;
    }

    // ---------------- Count Words ----------------

    int countWords(Node* node) {

        if (node == nullptr)
            return 0;

        int total = node->isEndOfWord ? 1 : 0;

        for (auto& child : node->children)
            total += countWords(child.second);

        return total;
    }

    // ---------------- Count Nodes ----------------

    int countNodes(Node* node) {

        if (node == nullptr)
            return 0;

        int total = 1;

        for (auto& child : node->children)
            total += countNodes(child.second);

        return total;
    }

    // ---------------- Display ----------------

    void display(Node* node, string currentWord) {

        if (node == nullptr)
            return;

        if (node->isEndOfWord)
            cout << currentWord << endl;

        for (auto& child : node->children) {

            display(child.second,
                    currentWord + child.first);
        }
    }

    // ---------------- Prefix Search ----------------

    void collectWords(Node* node, string currentWord) {

        if (node == nullptr)
            return;

        if (node->isEndOfWord)
            cout << currentWord << endl;

        for (auto& child : node->children) {

            collectWords(child.second, currentWord + child.first);
        }
    }

public:

    Trie() {

        root = new Node();
    }

    // ---------------- Insert ----------------

    void insert(string word) {

        Node* current = root;

        for (char ch : word) {

            if (current->children.find(ch)
                == current->children.end()) {

                current->children[ch] =
                    new Node();
            }

            current =
                current->children[ch];
        }

        current->isEndOfWord = true;
    }

    // ---------------- Search ----------------

    bool search(string word) {

        Node* current = root;

        for (char ch : word) {

            if (current->children.find(ch)
                == current->children.end())
                return false;

            current =
                current->children[ch];
        }

        return current->isEndOfWord;
    }

    // ---------------- Starts With ----------------

    bool startsWith(string prefix) {

        Node* current = root;

        for (char ch : prefix) {

            if (current->children.find(ch)
                == current->children.end())
                return false;

            current =
                current->children[ch];
        }

        return true;
    }

    // ---------------- Remove ----------------

    void remove(string word) {

        Node* current = root;

        for (char ch : word) {

            if (current->children.find(ch)
                == current->children.end())
                return;

            current =
                current->children[ch];
        }

        current->isEndOfWord = false;
    }

        // ---------------- Display All Words ----------------

    void display() {

        cout << "Words in Trie:\n";

        display(root, "");
    }

    // ---------------- Print Words With Prefix ----------------

    void wordsWithPrefix(string prefix) {

        Node* current = root;

        for (char ch : prefix) {

            if (current->children.find(ch)
                == current->children.end()) {

                cout << "No words found.\n";
                return;
            }

            current = current->children[ch];
        }

        cout << "Words starting with \"" << prefix << "\":\n";

        collectWords(current, prefix);
    }

    // ---------------- Count Words ----------------

    int size() {

        return countWords(root);
    }

    // ---------------- Count Nodes ----------------

    int nodeCount() {

        return countNodes(root);
    }

    // ---------------- Empty ----------------

    bool empty() {

        return size() == 0;
    }

    // ---------------- Clear ----------------

    void clear() {

        destroy(root);

        root = new Node();
    }

    // ---------------- Destructor ----------------

    ~Trie() {

        destroy(root);
    }

};

int main() {

    cout << "==================== Trie ====================\n";

    Trie trie;

    trie.insert("cat");
    trie.insert("car");
    trie.insert("cart");
    trie.insert("care");
    trie.insert("dog");
    trie.insert("door");
    trie.insert("doll");
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");

    cout << "===== All Words =====\n";
    trie.display();

    cout << "\n===== Search =====\n";

    cout << "cat : " << (trie.search("cat") ? "Found" : "Not Found") << endl;

    cout << "care : " << (trie.search("care") ? "Found" : "Not Found") << endl;

    cout << "cow : " << (trie.search("cow") ? "Found" : "Not Found") << endl;

    cout << "\n===== Prefix Check =====\n";

    cout << "ca : " << (trie.startsWith("ca") ? "Yes" : "No") << endl;

    cout << "app : " << (trie.startsWith("app") ? "Yes" : "No") << endl;

    cout << "xyz : " << (trie.startsWith("xyz") ? "Yes" : "No") << endl;

    cout << "\n===== Words With Prefix =====\n";

    trie.wordsWithPrefix("ca");

    cout << endl;

    trie.wordsWithPrefix("do");

    cout << endl;

    trie.wordsWithPrefix("app");

    cout << "\n===== Statistics =====\n";

    cout << "Total Words : " << trie.size() << endl;

    cout << "Total Nodes : " << trie.nodeCount() << endl;

    cout << "\n===== Remove =====\n";

    trie.remove("care");
    trie.remove("dog");

    trie.display();

    cout << "\nSearch care : " << (trie.search("care") ? "Found" : "Not Found") << endl;

    cout << "Search dog : " << (trie.search("dog") ? "Found" : "Not Found") << endl;

    cout << "\n===== Clear =====\n";

    trie.clear();

    cout << "Empty : " << (trie.empty() ? "Yes" : "No") << endl;

    cout << "\n=============================================\n";
    return 0;
}