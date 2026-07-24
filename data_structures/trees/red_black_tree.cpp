#include <iostream>
#include <queue>
#include <optional>
#include <algorithm>

using namespace std;

class RedBlackTree {

private:

    // ─────────────────── Color ───────────────────

    enum class Color { RED, BLACK };

    // ─────────────────── Node ───────────────────

    struct Node {

        int   data;
        Color color;
        Node* left;
        Node* right;
        Node* parent;

        Node(int value, Color c, Node* sentinel = nullptr)
            : data(value), color(c), left(sentinel), right(sentinel), parent(sentinel) {}
    };

    // A single shared sentinel BLACK leaf node.
    // Every null boundary in the tree points here instead of nullptr.
    // This eliminates scattered null-checks throughout the implementation
    // and allows deleteFixup to navigate up through nil->parent safely.
    Node* nil;
    Node* root;

    // ─────────────────── Left Rotation ───────────────────

    void leftRotate(Node* x) {

        Node* y  = x->right;
        x->right = y->left;

        if (y->left != nil)
            y->left->parent = x;

        y->parent = x->parent;

        if      (x->parent == nil)         root             = y;
        else if (x == x->parent->left)     x->parent->left  = y;
        else                               x->parent->right = y;

        y->left   = x;
        x->parent = y;
    }

    // ─────────────────── Right Rotation ───────────────────

    void rightRotate(Node* y) {

        Node* x = y->left;
        y->left = x->right;

        if (x->right != nil)
            x->right->parent = y;

        x->parent = y->parent;

        if      (y->parent == nil)         root             = x;
        else if (y == y->parent->left)     y->parent->left  = x;
        else                               y->parent->right = x;

        x->right  = y;
        y->parent = x;
    }

    // ─────────────────── Insert Fixup ───────────────────

    // Restores RB invariants after a RED node is inserted.
    // Three cases per side (six total, symmetric):
    //   Case 1 — Uncle RED:   recolor, push violation upward.
    //   Case 2 — Uncle BLACK, triangle path: rotate parent to reduce to Case 3.
    //   Case 3 — Uncle BLACK, straight path: rotate grandparent + recolor.
    void insertFixup(Node* z) {

        while (z->parent->color == Color::RED) {

            if (z->parent == z->parent->parent->left) {

                Node* uncle = z->parent->parent->right;

                if (uncle->color == Color::RED) {

                    // Case 1: Uncle RED — recolor and walk violation upward
                    z->parent->color         = Color::BLACK;
                    uncle->color             = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;

                } else {

                    if (z == z->parent->right) {

                        // Case 2: Triangle (LR) — left-rotate to straighten into Case 3
                        z = z->parent;
                        leftRotate(z);
                    }

                    // Case 3: Line (LL) — single right rotation + recolor resolves violation
                    z->parent->color         = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    rightRotate(z->parent->parent);
                }

            } else {

                // Symmetric: parent is the right child of grandparent

                Node* uncle = z->parent->parent->left;

                if (uncle->color == Color::RED) {

                    // Case 1
                    z->parent->color         = Color::BLACK;
                    uncle->color             = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    z = z->parent->parent;

                } else {

                    if (z == z->parent->left) {

                        // Case 2: Triangle (RL)
                        z = z->parent;
                        rightRotate(z);
                    }

                    // Case 3: Line (RR)
                    z->parent->color         = Color::BLACK;
                    z->parent->parent->color = Color::RED;
                    leftRotate(z->parent->parent);
                }
            }
        }

        // Re-enforce property 2 (root is BLACK), which Case 1 may have violated
        root->color = Color::BLACK;
    }

    // ─────────────────── Insert ───────────────────

    void insertNode(int value) {

        Node* z       = new Node(value, Color::RED, nil);
        Node* parent  = nil;
        Node* current = root;

        while (current != nil) {

            parent = current;

            if      (z->data < current->data) current = current->left;
            else if (z->data > current->data) current = current->right;
            else {
                delete z;   // Duplicate keys not supported — discard silently
                return;
            }
        }

        z->parent = parent;

        if      (parent == nil)          root          = z;
        else if (z->data < parent->data) parent->left  = z;
        else                             parent->right = z;

        insertFixup(z);
    }

    // ─────────────────── Transplant ───────────────────

    // Replaces the subtree rooted at u with the subtree rooted at v.
    // Setting v->parent unconditionally (even when v is nil) lets
    // deleteFixup navigate upward via the sentinel's parent pointer.
    void transplant(Node* u, Node* v) {

        if      (u->parent == nil)         root             = v;
        else if (u == u->parent->left)     u->parent->left  = v;
        else                               u->parent->right = v;

        v->parent = u->parent;
    }

    // ─────────────────── Delete Fixup ───────────────────

    // Restores the uniform black-height invariant after a BLACK node is removed.
    // x conceptually carries a "double-black" credit that must be absorbed or propagated.
    //
    //   Case 1 — Sibling RED:             rotate parent, convert to Case 2/3/4.
    //   Case 2 — Sibling BLACK, both nephews BLACK: push deficit upward.
    //   Case 3 — Sibling BLACK, far nephew BLACK, near nephew RED:
    //             rotate sibling to expose a RED far nephew → Case 4.
    //   Case 4 — Sibling BLACK, far nephew RED:  rotation + recolor absorbs deficit.
    void deleteFixup(Node* x) {

        while (x != root && x->color == Color::BLACK) {

            if (x == x->parent->left) {

                Node* w = x->parent->right;   // sibling

                if (w->color == Color::RED) {

                    // Case 1
                    w->color         = Color::BLACK;
                    x->parent->color = Color::RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }

                if (w->left->color  == Color::BLACK &&
                    w->right->color == Color::BLACK) {

                    // Case 2: Push double-black upward
                    w->color = Color::RED;
                    x = x->parent;

                } else {

                    if (w->right->color == Color::BLACK) {

                        // Case 3: Convert to Case 4
                        w->left->color = Color::BLACK;
                        w->color       = Color::RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }

                    // Case 4: Absorb double-black via rotation + recolor
                    w->color         = x->parent->color;
                    x->parent->color = Color::BLACK;
                    w->right->color  = Color::BLACK;
                    leftRotate(x->parent);
                    x = root;   // Force loop termination
                }

            } else {

                // Symmetric: x is right child

                Node* w = x->parent->left;

                if (w->color == Color::RED) {

                    // Case 1
                    w->color         = Color::BLACK;
                    x->parent->color = Color::RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }

                if (w->right->color == Color::BLACK &&
                    w->left->color  == Color::BLACK) {

                    // Case 2
                    w->color = Color::RED;
                    x = x->parent;

                } else {

                    if (w->left->color == Color::BLACK) {

                        // Case 3
                        w->right->color = Color::BLACK;
                        w->color        = Color::RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }

                    // Case 4
                    w->color         = x->parent->color;
                    x->parent->color = Color::BLACK;
                    w->left->color   = Color::BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }

        // Resolve any remaining double-black by painting x BLACK
        x->color = Color::BLACK;
    }

    // ─────────────────── Delete ───────────────────

    void deleteNode(int value) {

        Node* z = searchNode(root, value);

        if (z == nil)
            return;   // Key not present — no-op

        Node* y              = z;
        Color yOriginalColor = y->color;
        Node* x;

        if (z->left == nil) {

            x = z->right;
            transplant(z, z->right);

        } else if (z->right == nil) {

            x = z->left;
            transplant(z, z->left);

        } else {

            // Two children: splice in the in-order successor (min of right subtree)
            y              = findMin(z->right);
            yOriginalColor = y->color;
            x              = y->right;

            if (y->parent == z) {

                // x (possibly nil) needs y as its parent so deleteFixup
                // can navigate upward even through the sentinel node.
                x->parent = y;

            } else {

                transplant(y, y->right);
                y->right         = z->right;
                y->right->parent = y;
            }

            transplant(z, y);
            y->left         = z->left;
            y->left->parent = y;
            y->color        = z->color;
        }

        delete z;

        // Only a removed BLACK node can violate the uniform black-height invariant
        if (yOriginalColor == Color::BLACK)
            deleteFixup(x);
    }

    // ─────────────────── Search ───────────────────

    Node* searchNode(Node* node, int value) const {

        while (node != nil) {

            if      (value == node->data) return node;
            else if (value <  node->data) node = node->left;
            else                          node = node->right;
        }

        return nil;
    }

    // ─────────────────── Minimum / Maximum ───────────────────

    Node* findMin(Node* node) const {

        while (node->left != nil)
            node = node->left;

        return node;
    }

    Node* findMax(Node* node) const {

        while (node->right != nil)
            node = node->right;

        return node;
    }

    // ─────────────────── Height ───────────────────

    int getHeight(Node* node) const {

        if (node == nil)
            return 0;

        return 1 + max(getHeight(node->left), getHeight(node->right));
    }

    // ─────────────────── Black Height ───────────────────

    // Returns the count of BLACK nodes on any root-to-nil path (nil excluded).
    // By RB invariant 5 all such paths are equal, so traversing left always suffices.
    int getBlackHeight(Node* node) const {

        if (node == nil)
            return 0;

        return getBlackHeight(node->left) + (node->color == Color::BLACK ? 1 : 0);
    }

    // ─────────────────── Count ───────────────────

    int count(Node* node) const {

        if (node == nil)
            return 0;

        return 1 + count(node->left) + count(node->right);
    }

    // ─────────────────── Traversals ───────────────────

    void inorder(Node* node) const {

        if (node == nil) return;

        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void preorder(Node* node) const {

        if (node == nil) return;

        cout << node->data << " ";
        preorder(node->left);
        preorder(node->right);
    }

    void postorder(Node* node) const {

        if (node == nil) return;

        postorder(node->left);
        postorder(node->right);
        cout << node->data << " ";
    }

    // ─────────────────── Verify (debug / testing) ───────────────────

    // Recursively validates:
    //   Property 4 — No two consecutive RED nodes.
    //   Property 5 — All root-to-nil paths have equal black-node count.
    bool verifyNode(Node* node, int currentBlack, int& expectedBlack) const {

        if (node == nil) {

            if (expectedBlack == -1)
                expectedBlack = currentBlack;

            return currentBlack == expectedBlack;
        }

        if (node->color == Color::RED &&
            (node->left->color  == Color::RED || node->right->color == Color::RED))
            return false;

        int blackCount = currentBlack + (node->color == Color::BLACK ? 1 : 0);

        return verifyNode(node->left,  blackCount, expectedBlack) && verifyNode(node->right, blackCount, expectedBlack);
    }

    // ─────────────────── Destroy ───────────────────

    void destroy(Node* node) {

        if (node == nil) return;

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:

    RedBlackTree() {

        nil         = new Node(0, Color::BLACK);
        nil->left   = nil;
        nil->right  = nil;
        nil->parent = nil;

        root = nil;
    }

    ~RedBlackTree() {
        destroy(root);
        delete nil;
    }

    // Raw-pointer ownership cannot be safely duplicated without a deep copy.
    // Delete copy operations to prevent accidental shallow copies and double-frees.
    RedBlackTree(const RedBlackTree&)            = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    // ─────────────────── Mutators ───────────────────

    void insert(int value) { insertNode(value); }
    void remove(int value) { deleteNode(value); }

    void clear() {
        destroy(root);
        root = nil;
    }

    // ─────────────────── Queries ───────────────────

    [[nodiscard]] bool search(int value) const {
        return searchNode(root, value) != nil;
    }

    [[nodiscard]] optional<int> getMin() const {
        return (root != nil) ? optional<int>(findMin(root)->data) : nullopt;
    }

    [[nodiscard]] optional<int> getMax() const {
        return (root != nil) ? optional<int>(findMax(root)->data) : nullopt;
    }

    [[nodiscard]] int  height()      const { return getHeight(root); }
    [[nodiscard]] int  blackHeight() const { return getBlackHeight(root); }
    [[nodiscard]] int  size()        const { return count(root); }
    [[nodiscard]] bool isEmpty()     const { return root == nil; }

    // Verifies all five RB invariants. Useful in unit tests and assertions.
    // O(n) time — do not call in hot paths.
    [[nodiscard]] bool isValid() const {

        if (root != nil && root->color != Color::BLACK)
            return false;

        int expectedBlack = -1;
        return verifyNode(root, 0, expectedBlack);
    }

    // ─────────────────── Traversals ───────────────────

    void inorder()   const { inorder(root);   cout << "\n"; }
    void preorder()  const { preorder(root);  cout << "\n"; }
    void postorder() const { postorder(root); cout << "\n"; }

    void levelOrder() const {

        if (root == nil) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            cout << current->data << " ";

            if (current->left  != nil) q.push(current->left);
            if (current->right != nil) q.push(current->right);
        }

        cout << "\n";
    }

    // Annotates each value with its color: R = RED, B = BLACK.
    // Use this to visually verify RB invariants during development.
    void levelOrderColored() const {

        if (root == nil) return;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {

            Node* current = q.front();
            q.pop();

            cout << current->data << (current->color == Color::RED ? "R" : "B") << " ";

            if (current->left  != nil) q.push(current->left);
            if (current->right != nil) q.push(current->right);
        }

        cout << "\n";
    }
};

int main() {

    cout << "=========== Red-Black Tree (self-balancing) ===========\n";

    RedBlackTree rbt;

    rbt.insert(50);
    rbt.insert(30);
    rbt.insert(70);
    rbt.insert(20);
    rbt.insert(40);
    rbt.insert(60);
    rbt.insert(80);
    rbt.insert(10);
    rbt.insert(25);
    rbt.insert(35);
    rbt.insert(45);

    cout << "Inorder:               ";
    rbt.inorder();

    cout << "Preorder:              ";
    rbt.preorder();

    cout << "Postorder:             ";
    rbt.postorder();

    cout << "Level Order:           ";
    rbt.levelOrder();

    cout << "Level Order (colored): ";
    rbt.levelOrderColored();

    cout << "\nMinimum:      " << rbt.getMin().value_or(-1) << "\n";
    cout << "Maximum:      " << rbt.getMax().value_or(-1) << "\n";
    cout << "Height:       " << rbt.height()       << "\n";
    cout << "Black Height: " << rbt.blackHeight()   << "\n";
    cout << "Size:         " << rbt.size()          << "\n";
    cout << "Valid RBT:    " << (rbt.isValid() ? "Yes" : "No") << "\n";

    cout << "\nSearch 60:  " << (rbt.search(60)  ? "Found" : "Not Found") << "\n";
    cout << "Search 100: " << (rbt.search(100) ? "Found" : "Not Found") << "\n";

    rbt.remove(20);
    cout << "\nAfter deleting 20:\n";
    cout << "  Inorder:               ";
    rbt.inorder();
    cout << "  Level Order (colored): ";
    rbt.levelOrderColored();
    cout << "  Valid RBT: " << (rbt.isValid() ? "Yes" : "No") << "\n";

    rbt.remove(30);
    cout << "\nAfter deleting 30:\n";
    cout << "  Inorder:               ";
    rbt.inorder();
    cout << "  Level Order (colored): ";
    rbt.levelOrderColored();
    cout << "  Valid RBT: " << (rbt.isValid() ? "Yes" : "No") << "\n";

    rbt.remove(50);
    cout << "\nAfter deleting 50:\n";
    cout << "  Inorder:               ";
    rbt.inorder();
    cout << "  Level Order (colored): ";
    rbt.levelOrderColored();
    cout << "  Valid RBT: " << (rbt.isValid() ? "Yes" : "No") << "\n";

    cout << "\nFinal Level Order:           ";
    rbt.levelOrder();
    cout << "Final Level Order (colored): ";
    rbt.levelOrderColored();
    cout << "Final Height:       " << rbt.height()       << "\n";
    cout << "Final Black Height: " << rbt.blackHeight()   << "\n";
    cout << "Final Size:         " << rbt.size()          << "\n";
    cout << "Final Valid RBT:    " << (rbt.isValid() ? "Yes" : "No") << "\n";

    cout << "\n======================================================\n";
    return 0;
}