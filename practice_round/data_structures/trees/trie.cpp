/*
            ############################################# Practice round 1 #############################################
*/

// #include <iostream>
// #include <unordered_map>
// #include <string>

// using std::cout;
// using std::string;
// using std::unordered_map;

// struct Node
// {
//     unordered_map<char, Node *> children;
//     bool isEndOfWord;

//     Node()
//     {
//         isEndOfWord = false;
//     }
// };

// class Trie
// {
// private:
//     Node *root;

//     int countWords(Node *node)
//     {
//         /*
//             Start at root
//             Loop recursively and count all the nodes having isEndOfWord == true
//         */

//         if (node == nullptr)
//         {
//             return 0;
//         }

//         int total = node->isEndOfWord ? 1 : 0;

//         for (auto &child : node->children)
//         {
//             total += countWords(child.second);
//         }

//         return total;
//     }

//     void display(Node *node, string currentWord)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         if (node->isEndOfWord == true)
//         {
//             cout << currentWord << "\n";
//         }

//         for (auto &child : node->children)
//         {
//             display(child.second, currentWord + child.first);
//         }
//     }

//     void destroy(Node *node)
//     {
//         if (node == nullptr)
//         {
//             return;
//         }

//         for (auto &child : node->children)
//         {
//             destroy(child.second);
//         }

//         delete node;
//     }

// public:
//     Trie()
//     {
//         root = new Node();
//     }

//     Trie(const Trie &) = delete;
//     Trie &operator=(const Trie &) = delete;

//     ~Trie()
//     {
//         destroy(root);
//     }

//     bool insert(string word)
//     {
//         Node *current = root;

//         for (char ch : word)
//         {
//             if (current->children.find(ch) == current->children.end())
//             {
//                 current->children[ch] = new Node();
//             }

//             current = current->children[ch];
//         }

//         current->isEndOfWord = true;

//         return true;
//     }

//     bool search(string word)
//     {
//         Node *current = root;

//         for (char ch : word)
//         {
//             if (current->children.find(ch) == current->children.end())
//             {
//                 return false;
//             }

//             current = current->children[ch];
//         }

//         if (current->isEndOfWord == true)
//         {

//             return true;
//         }

//         return false;
//     }

//     bool startsWith(string word)
//     {
//         Node *current = root;

//         for (char ch : word)
//         {
//             if (current->children.find(ch) == current->children.end())
//             {
//                 return false;
//             }

//             current = current->children[ch];
//         }

//         return true;
//     }

//     int countPrefix(string word)
//     {
//         Node *current = root;

//         for (char ch : word)
//         {
//             if (current->children.find(ch) == current->children.end())
//             {
//                 return 0;
//             }

//             current = current->children[ch];
//         }

//         return countWords(current);
//     }

//     int countWords()
//     {
//         return countWords(root);
//     }

//     bool remove(string word)
//     {
//         Node *current = root;

//         for (char ch : word)
//         {
//             if (current->children.find(ch) == current->children.end())
//             {
//                 return false;
//             }

//             current = current->children[ch];
//         }

//         if (current->isEndOfWord == true)
//         {
//             current->isEndOfWord = false;
//             return true;
//         }

//         return false;
//     }

//     void display()
//     {
//         display(root, "");
//     }
// };

// int main()
// {
//     Trie trie;

//     // Insert words
//     trie.insert("apple");
//     trie.insert("app");
//     trie.insert("application");
//     trie.insert("banana");
//     trie.insert("band");
//     trie.insert("bat");

//     // Search
//     cout << "Search apple: " << trie.search("apple") << "\n";
//     cout << "Search app: " << trie.search("app") << "\n";
//     cout << "Search appl: " << trie.search("appl") << "\n";
//     cout << "Search cat: " << trie.search("cat") << "\n";

//     cout << "\n";

//     // StartsWith
//     cout << "StartsWith app: " << trie.startsWith("app") << "\n";
//     cout << "StartsWith ban: " << trie.startsWith("ban") << "\n";
//     cout << "StartsWith cat: " << trie.startsWith("cat") << "\n";

//     cout << "\n";

//     // Count total words
//     cout << "Total words: " << trie.countWords() << "\n";

//     // Count words with prefix
//     cout << "Words with prefix 'app': " << trie.countPrefix("app") << "\n";
//     cout << "Words with prefix 'ban': " << trie.countPrefix("ban") << "\n";
//     cout << "Words with prefix 'bat': " << trie.countPrefix("bat") << "\n";
//     cout << "Words with prefix 'cat': " << trie.countPrefix("cat") << "\n";

//     cout << "\n";

//     // Display all words
//     cout << "All words:\n";
//     trie.display();

//     cout << "\n";

//     // Remove words
//     cout << "Remove apple: " << trie.remove("apple") << "\n";
//     cout << "Search apple after removal: " << trie.search("apple") << "\n";

//     cout << "\n";

//     cout << "Remove cat: " << trie.remove("cat") << "\n";
//     cout << "Remove app: " << trie.remove("app") << "\n";

//     cout << "\n";

//     // Display after removal
//     cout << "Words after removal:\n";
//     trie.display();

//     cout << "\n";

//     // Verify count after removal
//     cout << "Total words after removal: "
//          << trie.countWords() << "\n";

//     cout << "Words with prefix 'app' after removal: "
//          << trie.countPrefix("app") << "\n";

//     return 0;
// }

/*
            ############################################# Practice round 2 #############################################
*/

#include <iostream>
#include <string>
#include <unordered_map>

using std::cout;
using std::string;
using std::unordered_map;

struct Node
{
    unordered_map<char, Node *> children;
    bool isEndOfWord;

    Node()
    {
        isEndOfWord = false;
    }
};

class Trie
{
private:
    Node *root;

    int countWords(Node *node)
    {
        if (node == nullptr)
        {
            return 0;
        }

        int total = node->isEndOfWord ? 1 : 0;

        for (auto &child : node->children)
        {
            total += countWords(child.second);
        }

        return total;
    }

    void display(Node *node, string currentWord)
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->isEndOfWord)
        {
            cout << currentWord << "\n";
        }

        for (auto &child : node->children)
        {
            display(child.second, currentWord + child.first);
        }
    }

    bool remove(Node *node, string word)
    {
        Node *current = node;

        for (char ch : word)
        {
            if (current->children.find(ch) == current->children.end())
            {
                return false;
            }

            current = current->children[ch];
        }

        current->isEndOfWord = false;

        return true;
    }

    void destroy(Node *node)
    {
        if (node == nullptr)
        {
            return;
        }

        for (auto &child : node->children)
        {
            destroy(child.second);
        }

        delete node;
    }

public:
    Trie()
    {
        root = new Node();
    }

    Trie(const Trie &) = delete;
    Trie &operator=(const Trie &) = delete;

    ~Trie()
    {
        destroy(root);
    }

    bool insert(string word)
    {
        Node *current = root;

        for (char ch : word)
        {
            if (current->children.find(ch) == current->children.end())
            {
                current->children[ch] = new Node();
            }

            current = current->children[ch];
        }

        current->isEndOfWord = true;

        return true;
    }

    bool search(string word)
    {
        Node *current = root;

        for (char ch : word)
        {
            if (current->children.find(ch) == current->children.end())
            {
                return false;
            }

            current = current->children[ch];
        }

        if (current->isEndOfWord == true)
        {
            return true;
        }

        return false;
    }

    bool startsWith(string word)
    {
        Node *current = root;

        for (char ch : word)
        {
            if (current->children.find(ch) == current->children.end())
            {
                return false;
            }

            current = current->children[ch];
        }

        return true;
    }

    int countWords()
    {
        return countWords(root);
    }

    int countPrefix(string word)
    {
        Node *current = root;

        for (char ch : word)
        {
            if (current->children.find(ch) == current->children.end())
            {
                return 0;
            }

            current = current->children[ch];
        }

        return countWords(current);
    }

    void display()
    {
        display(root, "");
    }

    bool remove(string word)
    {

        return remove(root, word);
    }
};

int main()
{
    Trie trie;

    // Insert words
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("banana");
    trie.insert("band");
    trie.insert("bat");

    // Search
    cout << "Search apple: " << trie.search("apple") << "\n";
    cout << "Search app: " << trie.search("app") << "\n";
    cout << "Search appl: " << trie.search("appl") << "\n";
    cout << "Search cat: " << trie.search("cat") << "\n";

    cout << "\n";

    // StartsWith
    cout << "StartsWith app: " << trie.startsWith("app") << "\n";
    cout << "StartsWith ban: " << trie.startsWith("ban") << "\n";
    cout << "StartsWith cat: " << trie.startsWith("cat") << "\n";

    cout << "\n";

    // Count total words
    cout << "Total words: " << trie.countWords() << "\n";

    // Count words with prefix
    cout << "Words with prefix 'app': " << trie.countPrefix("app") << "\n";
    cout << "Words with prefix 'ban': " << trie.countPrefix("ban") << "\n";
    cout << "Words with prefix 'bat': " << trie.countPrefix("bat") << "\n";
    cout << "Words with prefix 'cat': " << trie.countPrefix("cat") << "\n";

    cout << "\n";

    // Display all words
    cout << "All words:\n";
    trie.display();

    cout << "\n";

    // Remove words
    cout << "Remove apple: " << trie.remove("apple") << "\n";
    cout << "Search apple after removal: " << trie.search("apple") << "\n";

    cout << "\n";

    cout << "Remove cat: " << trie.remove("cat") << "\n";
    cout << "Remove app: " << trie.remove("app") << "\n";

    cout << "\n";

    // Display after removal
    cout << "Words after removal:\n";
    trie.display();

    cout << "\n";

    // Verify count after removal
    cout << "Total words after removal: "
         << trie.countWords() << "\n";

    cout << "Words with prefix 'app' after removal: "
         << trie.countPrefix("app") << "\n";

    return 0;
}