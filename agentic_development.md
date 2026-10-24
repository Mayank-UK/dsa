# agentic_development.md — living project guide for the C/C++ DSA repo. Every new chat reads this first.
# Maintain it delta-only (see ⚙️ MAINTENANCE DIRECTIVE at the end). Status markers: ✅ done · 🚧 in progress · ⏳ pending

structure: dsa-cpp-single-file

## Current state
- Project snapshot: /Users/mak/Development/personal/c:c++/dsa · C++17 on Apple clang++ (clang-2100), NO build system — every .cpp is a self-contained unit (own headers + a main() demo).
  Layout: data_structures/<category>/ · algorithms/<category>/ (+ <paradigm>_fundamentals.cpp) · techniques/ (top level) · important_questions/<strategy>/. README.md = front door;
  important_questions/PATTERNS.md = strategy-first coverage index (57 questions, links path-verified; techniques with no dedicated question are covered by techniques/ demos, noted there).
- Build/run: clang++ -std=c++17 -g -Wall -Wextra <file>.cpp -o <file> · ./<file> (some demos read ./input.txt — keep at repo root, current content `10 20 30 40 50`). VS Code default
  task (.vscode/tasks.json) matches the baseline: /usr/bin/clang++ with -std=c++17 -Wall -Wextra on the active file.
- Canonical file map (AUTHORITATIVE): Stacks data_structures/stacks/{array,linked_list}_stack · Queues data_structures/queues/queue/{array,cicular,linked_list,priority}_queue · Deques
  data_structures/queues/deque/{array,linked_list}_deque · Linked lists data_structures/linked_lists/{singly,doubly,circular_singly,circular_doubly}_linked_list · Arrays
  data_structures/arrays/{fixed,dynamic,suffix}_array · Hashing data_structures/hashing/{separate_chaining,linear_probing,quadratic_probing,double}_hashing · Graphs
  data_structures/graphs/{undirected,directed,weighted,multi}_graph · Trees data_structures/trees/{binary,binary_search,avl,red_black,b,b_plus,treap,trie,heap,segment,binary_indexed,
  suffix}_tree · algorithms/<category>/*.cpp (out of standardization-backlog scope unless asked).
- Invariants (EVERY task): no shared headers, no cross-file includes, no build system or common header without explicit approval · the touched file MUST compile warning-free under
  clang++ -std=c++17 -Wall -Wextra (RUN it) — zero warnings, zero errors · no leaks: every new/malloc matched; NODE-based structures ship a destructor (post-order freeTree);
  vector-backed = RAII, no destructor; verify with -fsanitize=address if doubtful (macOS `leaks` is entitlement-blocked) · correctness over cosmetics: output changes are additive
  (labels/banners/states), never logic changes; call genuine bugs out separately · consistency: match data_structures/graphs/undirected_graph.cpp (gold standard) +
  data_structures/trees/binary_search_tree.cpp.
- Output standard (every demo): ===== <Structure Name> ===== title banner · tagged phases ([Build]/[Insert]/[Lookup]/[Delete]/[Query]/[Stats]/[Edge Cases]/[Traversal]) · explicit
  before/after states on mutation (never a bare line) · stats block where meaningful (size/capacity/load factor/height/degree/min/max) · edge cases DEMONSTRATED, not claimed
  (overflow/underflow, empty-structure ops, search miss, duplicate keys, single-element remove) · blank line between sections; aligned columns; human-readable booleans.
- Operation completeness (each structure exposes its full conventional API): stacks push/pop/peek/isEmpty/isFull/size/clear/display · queues enqueue/dequeue/front/rear/… · deques
  addFront/addRear/removeFront/removeRear/getFront/getRear/… · lists insertAt{Beginning,End,Position} + deleteBy{Value,Position} + search/reverse/getNthFromEnd/clear (+doubly:
  backward display; +circular: wrap-around) · arrays get/set/insert/remove/search/size/capacity (+dynamic: print amortized growth; +suffix: ranks/LCP) · hashing put/get/remove/
  contains/loadFactor/clear/all-bucket display (+open addressing: probe sequence/clustering) · graphs addVertex/addEdge/remove*/has*/degree/counts/bfs/dfs/components/cycle (+directed:
  in/out degree; +weighted: weights + neighbor iteration; +multi: parallel-edge counts) · trees insert/remove/search/traversals/height/size/min/max (+BST pred/succ; +self-balancing:
  rotations shown or height verified; +trie startsWith/word count; +heap extract/peek/heapify/heapsort; +segment/Fenwick: range query + point/range update with before/after).
- Conventions: snake_case files, one class per file named after the structure (PascalCase); main() = a readable script of the structure's story (build → query → mutate → edge cases) ·
  `// ─── Name ───` section banners; comments explain the non-obvious WHY · STL only — never add third-party deps.
- Classification rule (user-ratified): algorithms/ holds technique implementations + classical named algorithms ONLY (TSP + Hamiltonian path/circuit stay there; max-flow split into
  ford_fulkerson + edmonds_karp; rolling_hash renamed rolling_hash_mechanism); LeetCode-style QUESTIONS live in important_questions/<strategy>/ — grouped by SOLVING STRATEGY, not
  data type (no patterns/ dir by design — strategy dirs replaced it). Duplicates across categories (greedy/ vs graph/ dijkstra-prim-kruskal, sorting/ vs divide_and_conquer/, string
  matchers, algorithms/tree vs data_structures/trees) keep BOTH angles + a cross-reference line — never silently delete a duplicate.
- Fundamentals philosophy (user): *_fundamentals.cpp = MECHANISM-ONLY demos on PLAIN DATA — [Data] first, the trace IS the explanation, NO problem framings (knapsack/coin-change/
  4-queens removed by user request), at most ONE [Note] line, 1-2 screens of output. Do NOT re-add problems or theory lectures — the user wants data + mechanism.
- Lessons (bug history — do not reintroduce): NEVER sed a size() cast by matching `i < X.size()` — it drops the comparator → infinite loop (hit b_plus_tree); always keep the comparator
  operand · "compiles clean, exits 0" can be silently wrong — ALWAYS hand-verify printed answers against computed values (bitmask_dp `n<n` dead loop; bellman_ford demo typo made a
  false negative cycle; sieve SPF OOB read) and RUN every file (macOS has no `timeout`) · count edges vs nodes before trusting an expected path length (tree-diameter spec catch) ·
  cast .size()/.length() to (int) in int loop bounds (-Wextra sign-compare) · bare move(x) under `using namespace std` warns (-Wunqualified-std-cast-call) — write std::move or drop ·
  functions taking non-const lvalue refs (euler/kruskal) need NAMED variables at call sites, never temporaries `{}` · helpers indexing adj up to n+1 need vector size 1+1 for
  single-node cases (else OOB/segfault) · algorithms RETURN results; ALL printing lives in main() (output-refactor convention) · show REAL degenerate behavior, never relabel it to
  match a cousin algorithm (jarvis vs graham on collinear input).
- Definition of Done (per backlog item — ALL must hold): full operation set present and correct · demo follows the Output standard · compiles warning-free under clang++ -std=c++17
  -Wall -Wextra AND runs · the output reads as a clear narrative of the structure.

## Active tasks
- None open. All 5 original backlog items ✅ (re-verified 2026-09-14); the algorithms/ standardization pass is complete (14 categories, ~138 files, all warning-free + run-verified);
  important_questions pattern coverage complete (57 questions + PATTERNS.md index). Full history: devlog.md.

# ⚙️ MAINTENANCE DIRECTIVE
# Keep this file delta-only — do not rewrite stable sections each turn. The `structure: dsa-cpp-single-file` marker above gates maintenance: if the project's fundamental shape
# changes (build system, shared headers, splitting a file), update `structure:` + the Project snapshot; otherwise edit only the touched lines. When a backlog item completes, flip
# its ⏳→✅ and, if the chat learned a reusable decision, append one line to the Lessons block — completed-detail and superseded narratives go to devlog.md (archive, don't delete).
