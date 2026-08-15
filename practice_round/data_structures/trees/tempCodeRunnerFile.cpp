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