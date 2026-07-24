#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class SuffixTree {
private:
    struct Node {
        int start;
        int end; // -1 indicates this is a leaf node and should use the global 'leaf_end'
        int suffix_link;
        int suffix_index; // Stores the starting index of the suffix ending at this leaf
        unordered_map<char, int> children;

        Node(int s, int e) : start(s), end(e), suffix_link(-1), suffix_index(-1) {}
    };

    string text;
    vector<Node> nodes;
    int root;
    
    // Ukkonen's active point state variables
    int active_node;
    int active_edge;
    int active_length;
    
    int remaining_suffix_count;
    int leaf_end; // Shared end variable for all leaves to achieve O(1) extensions

    // Creates a new node and returns its index
    int newNode(int start, int end) {
        nodes.emplace_back(start, end);
        return nodes.size() - 1;
    }

    // Calculates the edge length, taking into account O(1) leaf extensions
    int edgeLength(int node_idx) {
        if (node_idx == root) return 0;
        int end = (nodes[node_idx].end == -1) ? leaf_end : nodes[node_idx].end;
        return end - nodes[node_idx].start + 1;
    }

    // Walks down the tree if active_length is greater than the current edge length
    bool walkDown(int curr_node) {
        int el = edgeLength(curr_node);
        if (active_length >= el) {
            active_edge += el;
            active_length -= el;
            active_node = curr_node;
            return true;
        }
        return false;
    }

    // Core Ukkonen's phase extension logic
    void extendSuffixTree(int pos) {
        leaf_end = pos; // Rule 1: Rapid leaf extension
        remaining_suffix_count++;
        int last_new_node = -1;

        while (remaining_suffix_count > 0) {
            if (active_length == 0) {
                active_edge = pos; // Look for the current character from the active node
            }

            char edge_char = text[active_edge];

            // If there is no outgoing edge starting with edge_char
            if (nodes[active_node].children.find(edge_char) == nodes[active_node].children.end()) {
                // Extension Rule 2 (Create a new leaf)
                int leaf = newNode(pos, -1);
                nodes[active_node].children[edge_char] = leaf;

                if (last_new_node != -1) {
                    nodes[last_new_node].suffix_link = active_node;
                    last_new_node = -1;
                }
            } else {
                int next_node = nodes[active_node].children[edge_char];
                
                // If we can walk down, update active point and continue
                if (walkDown(next_node)) continue; 

                // Current character being processed is already on the edge
                int current_char_idx = nodes[next_node].start + active_length;

                if (text[current_char_idx] == text[pos]) {
                    // Match found (Observation 2): Wait for next phase
                    if (last_new_node != -1 && active_node != root) {
                        nodes[last_new_node].suffix_link = active_node;
                        last_new_node = -1;
                    }
                    active_length++;
                    break;
                }

                // Extension Rule 2 (Character mismatch on edge: Split the edge)
                int split_end = nodes[next_node].start + active_length - 1;
                int split_node = newNode(nodes[next_node].start, split_end);
                
                nodes[active_node].children[edge_char] = split_node;
                
                int leaf = newNode(pos, -1);
                nodes[split_node].children[text[pos]] = leaf;
                
                nodes[next_node].start += active_length;
                nodes[split_node].children[text[nodes[next_node].start]] = next_node;

                if (last_new_node != -1) {
                    nodes[last_new_node].suffix_link = split_node;
                }
                last_new_node = split_node;
            }

            remaining_suffix_count--;

            // Determine the next active point
            if (active_node == root && active_length > 0) {
                active_length--;
                active_edge = pos - remaining_suffix_count + 1;
            } else if (active_node != root) {
                active_node = (nodes[active_node].suffix_link != -1) ? nodes[active_node].suffix_link : root;
            }
        }
    }

    // Depth-First Search to set suffix indices at the leaves
    void setSuffixIndexByDFS(int node_idx, int label_height) {
        if (node_idx == -1) return;

        bool is_leaf = true;
        for (auto const& pair : nodes[node_idx].children) {
            is_leaf = false;
            setSuffixIndexByDFS(pair.second, label_height + edgeLength(pair.second));
        }

        if (is_leaf) {
            nodes[node_idx].suffix_index = text.length() - label_height;
        }
    }

    // Helper for printing the tree
    void printDFS(int node_idx, int depth) {
        if (node_idx == -1) return;
        if (node_idx != root) {
            int end = (nodes[node_idx].end == -1) ? leaf_end : nodes[node_idx].end;
            cout << string(depth * 2, ' ') 
                 << "Edge: " << text.substr(nodes[node_idx].start, end - nodes[node_idx].start + 1);
            if (nodes[node_idx].suffix_index != -1) {
                cout << " [Suffix Index: " << nodes[node_idx].suffix_index << "]";
            }
            cout << "\n";
        }
        for (auto const& pair : nodes[node_idx].children) {
            printDFS(pair.second, depth + 1);
        }
    }

public:
    SuffixTree(const string& input_string) {
        // Sentinel character ensures no suffix is a prefix of another
        text = input_string + "$";
        
        active_node = 0;
        active_edge = 0;
        active_length = 0;
        remaining_suffix_count = 0;
        leaf_end = -1;

        root = newNode(-1, -1);
        active_node = root;

        // Build the tree online character by character
        for (int i = 0; i < (int)text.length(); i++) {
            extendSuffixTree(i);
        }

        // Label the leaves
        setSuffixIndexByDFS(root, 0);
    }

    void printTree() {
        cout << "--- Suffix Tree Structure ---\n";
        cout << "Root\n";
        printDFS(root, 0);
        cout << "-----------------------------\n";
    }

    // Pattern search in O(m) by walking edges from the root.
    // Returns true if `pattern` is a substring of the original text.
    bool contains(const string& pattern) {
        int cur = root;
        size_t pi = 0;
        while (pi < pattern.size()) {
            char c = pattern[pi];
            auto it = nodes[cur].children.find(c);
            if (it == nodes[cur].children.end()) return false;   // no matching edge

            int child = it->second;
            int len = edgeLength(child);
            for (int k = 0; k < len && pi < pattern.size(); k++) {
                char edgeChar = text[nodes[child].start + k];
                if (edgeChar == '$') return false;               // ran into sentinel
                if (edgeChar != pattern[pi]) return false;        // mismatch on edge
                pi++;
            }
            cur = child;
        }
        return true;   // whole pattern consumed along a valid path
    }
};

int main() {
    cout << "================== Suffix Tree ==================\n";

    string text = "banana";
    cout << "\n[Input] text = \"" << text << "\"\n";

    // Initialize and build the Suffix Tree (Ukkonen's algorithm, O(n))
    SuffixTree st(text);

    cout << "\n[Structure] edges (leaves tagged with their suffix start index)\n";
    st.printTree();

    // ── [Pattern search] O(m) per query ──────────────────────────────────────
    cout << "\n[Pattern Search] substring test via edge traversal\n";
    for (string pat : {"ban", "ana", "na", "nan", "xyz", "banana"}) {
        cout << "  \"" << pat << "\" -> " << (st.contains(pat) ? "FOUND" : "not found") << "\n";
    }

    cout << "\n=================================================\n";
    return 0;
}