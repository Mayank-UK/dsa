# agentic_development.md
#
# Living project guide for the C/C++ DSA repo. Every new chat reads this first.
# Maintain it delta-only (see ⚙️ MAINTENANCE DIRECTIVE). Status markers:
#   ✅ done · 🚧 in progress · ⏳ pending

structure: dsa-cpp-single-file

- Project snapshot
    - Path: /Users/mak/Development/personal/c:c++/dsa
    - Stack: C++ (target C++17). Compiled with Apple clang++ (clang-2100). No build system — every .cpp is standalone with its own `main()`.
    - Layout: data_structures/<category>/<name>.cpp and algorithms/<category>/<name>.cpp. Each file is a self-contained, independently-compilable unit that defines a class/struct + a `main()` demo.
    - Build (per file):  clang++ -std=c++17 -g -Wall -Wextra <file>.cpp -o <file>
        - VS Code default task uses `/usr/bin/clang++` on the active file (see .vscode/tasks.json). Match `-std=c++17` when building manually; the task omits it so add it.
    - Run: ./<file>   (some demos read ./input.txt — keep input.txt at repo root, current content: `10 20 30 40 50`)
    - Canonical file map (AUTHORITATIVE):
        - Stacks ........... data_structures/stacks/{array,linked_list}_stack.cpp
        - Queues ........... data_structures/queues/queue/{array,cicular,linked_list,priority}_queue.cpp
        - Deques ........... data_structures/queues/deque/{array,linked_list}_deque.cpp
        - Linked lists ..... data_structures/linked_list/{singly,doubly,circular_singly,circular_doubly}_linked_list.cpp
        - Arrays ........... data_structures/arrays/{fixed,dynamic,suffix}_array.cpp
        - Hashing .......... data_structures/hashing/{separate_chaining,linear_probing,quadratic_probing,double}_hashing.cpp
        - Graphs ........... data_structures/graphs/{undirected,directed,weighted,multi}_graph.cpp
        - Trees ............ data_structures/trees/{binary,binary_search,avl,red_black,b,b_plus,treap,trie,heap,segment,binary_indexed,suffix}_tree.cpp
        - Algorithms ....... algorithms/<category>/*.cpp (out of scope for this backlog unless asked)

- Invariants (apply to EVERY task — read first)
    - Self-contained files: each .cpp includes its own headers + `main()`. No shared headers, no cross-file includes. Do not introduce a build system or a common header without explicit approval.
    - Compile-clean: after any edit, the touched file MUST compile warning-free under
        clang++ -std=c++17 -Wall -Wextra <file>.cpp -o /tmp/<basename>
      Run it before marking done. Zero warnings, zero errors.
    - No resource leaks: every `new`/`malloc` has a matching `delete`/`free` path. Node-based structures ship a destructor. Run `leaks /tmp/<basename>` or valgrind-equivalent if behavior is doubtful.
    - Correctness over cosmetics: do not change algorithmic behavior to make output pretty. Output changes are additive (labels/banners/states), not logic changes — unless an operation is genuinely buggy, in which case call it out separately.
    - Consistency: when unsure how to format something, match data_structures/graphs/undirected_graph.cpp (the gold-standard demo) and data_structures/trees/binary_search_tree.cpp.

- Output standard (the banner/section shape every demo must follow)
    - A title banner at the top:   ===== <Structure Name> =====   (or a delimited header block).
    - Sectioned, labeled phases, each prefixed with a tag, e.g. [Build], [Insert], [Lookup], [Delete], [Query], [Stats], [Edge Cases], [Traversal].
    - Before/after states shown explicitly when mutating (print state, perform op, print state again) — never a single bare line.
    - A stats block where meaningful (size/count, capacity, load factor, height, degree, min/max).
    - Edge cases demonstrated, not just claimed: overflow/underflow, empty-structure ops, search miss, duplicate keys, single-element remove.
    - One blank line between sections; aligned columns for tabular stats. Human-readable booleans ("Found"/"Not Found"), not raw 0/1.

- Operation completeness (each structure must expose its full conventional API)
    - Stacks:        push, pop, peek/top, isEmpty, isFull (if bounded), size, clear, display.
    - Queues:        enqueue, dequeue, front, rear, isEmpty, isFull (if bounded), size, clear, display.
    - Deques:        addFront, addRear, removeFront, removeRear, getFront, getRear, isEmpty, size, display.
    - Linked lists:  insertAtBeginning/End/Position, deleteByValue/ByPosition, search, reverse, size/length, getNthFromEnd, clear, display. Doubly variants: backward display. Circular variants: show the wrap-around.
    - Arrays:        get/set, insert, remove, search, size, capacity, display. Dynamic: amortized growth visible (print capacity changes). Suffix array: construct, print ranks/LCP if reasonable.
    - Hashing:       put/insert, get/lookup, remove, contains, size, loadFactor, clear, display (all buckets incl. empty). Open-addressing variants must show probe sequence / clustering behavior.
    - Graphs:        addVertex, addEdge, removeEdge, removeVertex, hasVertex, hasEdge, degree, vertex/edge counts, bfs, dfs, connected components, cycle detection, display. Directed: in/out degree. Weighted: edge weights shown, neighbor iteration. Multi: parallel-edge counts.
    - Trees:         insert, remove, search, traversals (in/pre/post/level), height, size, min, max, display. BST-family: predecessor/successor. Self-balancing (AVL/RB/B/B+/treap): rotations/rebalancing shown or at least height verified. Trie: insert, search, startsWith, remove, word count. Heap: insert, extractMax/Min, peek, heapify, heapsort demo, size. Segment/Fenwick: range query + point/range update with before/after. Suffix tree: build + a sample search.

- Conventions
    - Files: snake_case, one class per file, class named after the structure (PascalCase).
    - One file = one demo main(). Keep main() a readable script of the structure's story (build → query → mutate → edge cases).
    - Comments: section banners with `// ─── Name ───`; explain the non-obvious line (why, not what), as undirected_graph.cpp does.
    - Do NOT add third-party deps. STL only.

- Decision log (compressed — replaces pasted AI dialogs)
    - Single-file, no build system: chosen because the repo is a study reference, each file is read/compiled in isolation. (Why: lowest friction for browsing one concept at a time; matches existing .vscode/tasks.json.)
    - C++17 baseline: sufficient for structured bindings/optional/any used in some files; broadly available on the target clang. (Why: avoid C++20 feature drift in a learning repo.)
    - Gold-standard demo = undirected_graph.cpp: richest, most pedagogical output in the repo; adopted as the format target for the standardization pass.
    - Scope of this pass = data_structures/* only (34 files); algorithms/* left untouched unless explicitly requested.

- Definition of Done (per backlog item — ALL must hold)
    1. Full operation set per "Operation completeness" above is present and correct.
    2. Demo follows the "Output standard": banner + tagged sections + before/after + stats + edge cases — not single bare lines.
    3. File compiles warning-free: clang++ -std=c++17 -Wall -Wextra <file>.cpp -o /tmp/<file>  (run it).
    4. Program runs and the output reads as a clear narrative of the structure.

- Backlog (status · file · structure-specific gaps to close on top of global DoD)
    # Tier 1 — sparsest output / most gaps (do first)
    - ✅ hashing/separate_chaining_hashing.cpp — add contains, size, loadFactor, rehashing, clear; banner + sections; show search hit/miss, duplicate-key update.
    - ✅ hashing/linear_probing_hashing.cpp — show probe sequence + primary clustering; add contains, size, loadFactor, clear.
    - ✅ hashing/quadratic_probing_hashing.cpp — show probe sequence (contrast vs linear); contains/size/loadFactor/clear.
    - ✅ hashing/double_hashing.cpp — show second hash reducing clustering; contains/size/loadFactor/clear.
    - ✅ linked_list/singly_linked_list.cpp — add insertAtPosition, deleteByPosition, reverse, size, getNthFromEnd, clear; labeled search results (not raw boolalpha).
    - ✅ linked_list/doubly_linked_list.cpp — add forward+backward display, insertAtPosition, reverse, size, clear.
    - ✅ linked_list/circular_singly_linked_list.cpp — show wrap-around; size, split/​length, clear.
    - ✅ linked_list/circular_doubly_linked_list.cpp — bidirectional wrap display; size, clear.
    - ✅ stacks/array_stack.cpp — demo overflow/underflow edges; add clear; banner + before/after on push/pop.
    - ✅ stacks/linked_list_stack.cpp — same standard; add clear; edge demo on empty pop/peek.
    # Tier 2 — queues / arrays
    - ✅ queues/queue/array_queue.cpp — demo full/empty edges; clear; before/after.
    - ✅ queues/queue/cicular_queue.cpp — show wrap-around clearly (front/rear indices); isFull vs isEmpty distinction (the classic head==tail ambiguity); clear.
    - ✅ queues/queue/linked_list_queue.cpp — clear; size; edge demo.
    - ✅ queues/queue/priority_queue.cpp — show dequeue-by-priority order across insertions; clear; peek.
    - ✅ queues/deque/array_deque.cpp — front/rear wrap; both-end ops; clear.
    - ✅ queues/deque/linked_list_deque.cpp — both-end ops; clear; size.
    - ✅ arrays/fixed_array.cpp — bounds-edge messages; size/capacity; display.
    - ✅ arrays/dynamic_array.cpp — make amortized growth visible (print capacity on resize); clear; shrink-to-fit demo.
    - ✅ arrays/suffix_array.cpp — build + rank display; a substring search / LCP if reasonable.
    # Tier 3 — graphs (already strong; normalize output + verify op set)
    - ✅ graphs/undirected_graph.cpp — gold standard; verify op set, minor banner polish only.
    - ✅ graphs/directed_graph.cpp — in/out-degree display; strongly-connected vs weakly-connected note; banner polish.
    - ✅ graphs/weighted_graph.cpp — weights shown in display + traversal cost; Dijkstra/MST hook optional.
    - ✅ graphs/multi_graph.cpp — parallel-edge counts; display.
    # Tier 4 — trees
    - ✅ trees/binary_tree.cpp — traversals + height + leaf/count; banner.
    - ✅ trees/binary_search_tree.cpp — already strong; add predecessor/successor; banner polish.
    - ✅ trees/avl_tree.cpp — print balance factors / rotations performed; verify op set.
    - ✅ trees/red_black_tree.cpp — verify rotations + recolors; banner.
    - ✅ trees/b_tree.cpp — show splits on insert; min-degree t stated; banner.
    - ✅ trees/b_plus_tree.cpp — leaf-chain display; range query demo.
    - ✅ trees/treap.cpp — priorities shown; verify rotations.
    - ✅ trees/trie.cpp — startsWith, remove, word count; banner.
    - ✅ trees/heap.cpp — extract order; heapsort demo; build-heap; clear.
    - ✅ trees/segment_tree.cpp — range query + update before/after; banner.
    - ✅ trees/binary_indexed_tree.cpp — prefix-sum query + update before/after; banner.
    - ✅ trees/suffix_tree.cpp — build + sample pattern search; banner.

# ⚙️ MAINTENANCE DIRECTIVE
# Keep this file delta-only — do not rewrite stable sections each turn.
# `structure: dsa-cpp-single-file` above is the marker that gates maintenance:
# if the project's fundamental shape changes (e.g. introducing a build system,
# shared headers, or splitting a file), update `structure:` and the Project
# snapshot; otherwise edit only the touched Backlog lines and Decision log.
# When a backlog item is completed, flip its ⏳→✅ and, if the chat learned a
# reusable decision, append one line to the Decision log.
