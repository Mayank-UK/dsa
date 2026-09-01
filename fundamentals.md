- Master fundamentals
    - Loop mastery
        - Pattern creation using loops and nested loops
        - It strengthens nested-loop thinking, boundary control, and matrix traversal
    - Recursion master
        - Pattern creation using recursion just like loops
        - Recursion solves a problem by calling itself on smaller subproblems.
        - Master recursive tree diagrams for writing the pseudo code
        - Recursion is essential for trees, graphs, backtracking, divide and conquer, DP, and combinatorics
        - Three pillars of recursion:
            1. Base case: when to stop.
            2. Recursive case: how to reduce problem.
            3. Trust: assume recursive call works.

- Data structures
    - Arrays
    - Linked lists
    - Stacks
    - Queues & Dequeues
    - Hash tables
    - Trees
        - AVL Tree
        - B & B Plus
        - Binary Tree
            - Binary Indexed Tree
            - Binary Search Tree
            - Heap
            - Red-Black Tree
            - Segment Tree
        - Suffix Tree
        - Treap
        - Trie
    - Graphs
        - Undirected graph
        - Directed graph
        - Weighted graph
        - Multi graph

- Suitability of data structures
    - Which data structure is suitable for which type of tasks

- Programming techniques
    - Divide and conquer
        - Definition:
            - Divide and conquer solves a problem by splitting it into independent subproblems, solving each recursively, and combining their answers.
        - Purpose
            - Use it when a problem can be naturally split into smaller independent parts.
        - Pseudo strategy
            - ```
              divide_and_conquer(input):
                  if input is small:
                      return base answer

                  split input into parts
                  answers = []

                  for part in parts:
                      answers.append(divide_and_conquer(part))

                  return combine(answers)
              ```

        - Examples
            - Merge sort
            - Quick sort
            - Binary search
            - Maximum subarray with divide and conquer
            - Closest pair of points
            - Strassen matrix multiplication

    - Greedy technique
        - Definition:
            - Greedy algorithms make the locally optimal choice at each step, hoping to reach a globally optimal solution.
        - Purpose
            - Use greedy when a sequence of locally safe choices produces the optimal answer.
            - Warning
                - Greedy is easy to misuse. Always try to find a counterexample. If counterexample exists, use DP or backtracking.
        - Pseudo strategy
            - ```
                sort or prioritize candidates
                result = empty

                for candidate in candidates:
                    if candidate is valid:
                        add candidate to result

                return result
              ```

        - Examples
            - Activity selection
            - Jump Game
            - Minimum number of arrows to burst balloons
            - Task scheduler
            - Huffman coding
            - Interval scheduling
            - Coin change for canonical coin systems

    - Backtracking
        - Definition:
            - Backtracking builds a solution step by step and abandons a partial solution as soon as it violates constraints.
        - Purpose
            - Use backtracking for generating all valid combinations, permutations, subsets, paths, or constraint satisfaction problems.
        - Pseudo strategy
            - ```
                backtrack(state):
                    if state is complete:
                        add state to answer
                        return

                    for choice in possible_choices(state):
                        if choice is valid:
                            make choice
                            backtrack(next_state)
                            undo choice
              ```

        - Examples
            - Subsets
            - Combinations
            - Permutations
            - N-Queens
            - Sudoku solver
            - Palindrome partitioning
            - Word search
            - Graph coloring

    - Branch and bound
        - Definition:
            - Branch and bound explores a search tree and prunes branches that cannot produce a better answer than the current best.
        - Purpose
            - Use it for optimization problems where exhaustive search can be reduced using bounds.
        - Pseudo strategy
            - ```
                initialize best answer
                create priority queue or stack of search nodes

                while candidates remain:
                    node = get most promising node

                    if bound(node) cannot beat best:
                        continue

                    if node is complete:
                        update best

                    for child in expand(node):
                        if bound(child) can beat best:
                            add child to candidates

                return best
              ```

        - Examples
            - 0/1 Knapsack with fractional bound
            - Traveling Salesman Problem
            - Job assignment
            - Integer programming
            - N-Queens with pruning

    - Dynamic programming
        - Definition:
            - Dynamic programming solves problems by breaking them into overlapping subproblems and storing their results.
        - Purpose
            - Use DP when the same subproblem is solved many times and optimal answers depend on optimal subanswers.
        - Pseudo strategy
            - Steps
                1. Define state.
                2. Define what dp[state] means.
                3. Define transition.
                4. Define base cases.
                5. Choose computation order.
                6. Return final answer.
            - Top-down strategy
                - ```
                    memo = {}

                    solve(state):
                        if state is base:
                            return base value

                        if state in memo:
                            return memo[state]

                        answer = initial value
                        for choice in choices:
                            answer = best(answer, solve(next_state))

                        memo[state] = answer
                        return answer
                  ```

            - Bottom-up strategy
                - ```
                    initialize dp table with base cases

                    for states in valid order:
                        dp[state] = transition from smaller states

                    return dp[final_state]
                  ```

        - Examples
            - 0/1 Knapsack
            - Coin change
            - Edit distance
            - Digit DP
            - Kadane's algorithm
            - Subset sum

- Linear traversal (loop optimizers)
    - These techniques optimize loops by reducing repeated work.
    - Sliding window
        - Definition:
            - Sliding window maintains a window over a contiguous part of an array or string while moving the right pointer forward.
        - Purpose
            - Use sliding window for subarray/substring problems where you need min/max/count under constraints.
        - Pseudo strategy
            - ```
                left = 0
                state = empty

                for right from 0 to n - 1:
                    add nums[right] to state

                    while window is invalid:
                        remove nums[left] from state
                        left += 1

                    update answer using current window
              ```

        - Examples
            - Maximum sum subarray of size k
            - Longest substring without repeating characters

    - Two pointers
        - Definition:
            - Two pointers use two indices moving over data to reduce nested loops.
        - Purpose
            - Use two pointers for sorted arrays, pair search, partitioning, merging, and palindrome checks.
        - Pseudo strategy
            - ```
                left = 0
                right = n - 1

                while left < right:
                    evaluate nums[left], nums[right]

                    if condition satisfied:
                        update answer
                        move pointers

                    else if value too small:
                        move left forward

                    else:
                        move right backward
              ```

        - Examples
            - Two sum in sorted array
            - Palindrome check

    - Fast and slow pointers
        - Definition:
            - Fast and slow pointers move through a sequence at different speeds.
        - Purpose
            - Use this technique for cycle detection, finding middle, and linked list rearrangement.
        - Pseudo strategy
            - ```
                slow = head
                fast = head

                while fast is not null and fast.next is not null:
                    slow = slow.next
                    fast = fast.next.next

                    if slow == fast:
                        cycle detected
              ```

        - Examples
            - Middle of linked list
            - Cycle detection

    - Prefix sum/Kadane
        - Definition:
            - Prefix sum stores cumulative sums to answer range-sum queries. Kadane's algorithm finds maximum subarray sum in linear time.
        - Purpose
            - Use prefix sum for range queries. Use Kadane for best contiguous subarray.
        - Pseudo strategy
            - ```
                prefix[0] = 0

                for i from 0 to n - 1:
                    prefix[i + 1] = prefix[i] + nums[i]

                range_sum(l, r) = prefix[r + 1] - prefix[l]
              ```

- Structure specific strategies
    - BFS & DFS
        - Definition:
            - BFS explores neighbors level by level. DFS explores as deep as possible before backtracking.
        - Purpose
            - Use BFS for shortest unweighted paths and level order. Use DFS for exhaustive search, connectivity, and tree recursion.
        - Pseudo strategy
            - BFS pseudo
                - ```
                    queue = [start]
                    visited.add(start)

                    while queue not empty:
                        node = queue.pop_front()

                        for neighbor in graph[node]:
                            if neighbor not visited:
                                visited.add(neighbor)
                                queue.push_back(neighbor)
                  ```

            - DFS pseudo
                - ```
                    dfs(node):
                        if node visited:
                            return

                        visited.add(node)

                        for neighbor in graph[node]:
                            dfs(neighbor)
                  ```

    - Topological sort
        - Definition:
            - Topological sort orders nodes in a directed acyclic graph so every edge u -> v has u before v
        - Purpose
            - Use it for scheduling, build order, prerequisites, and dependency resolution.
        - Pseudo strategy
            - ```
                compute indegree for all nodes
                queue = all nodes with indegree 0
                order = []

                while queue not empty:
                    node = queue.pop_front()
                    order.append(node)

                    for neighbor in graph[node]:
                        indegree[neighbor] -= 1
                        if indegree[neighbor] == 0:
                            queue.push_back(neighbor)

                if len(order) != n:
                    cycle exists
                else:
                    return order
              ```

        - Examples
            - Course Schedule
            - Course Schedule II
            - Alien Dictionary
            - Parallel Courses
            - Minimum Height Trees

    - Monotonic stack
        - Definition:
            - A monotonic stack maintains elements in increasing or decreasing order.
        - Purpose
            - Use monotonic stack to find next greater, next smaller, previous greater, previous smaller, and histogram-like problems.
        - Pseudo strategy
            - ```
                stack = []

                for i from 0 to n - 1:
                    while stack not empty and condition broken by nums[i]:
                        index = stack.pop()
                        answer[index] = use nums[i]

                    stack.push(i)
              ```

        - Examples
            - Daily Temperatures
            - Next Greater Element
            - Largest Rectangle in Histogram
            - Trapping Rain Water
            - Online Stock Span

    - Two heaps
        - Definition:
            - Two heaps usually means using one max-heap and one min-heap to maintain two partitions of data.
        - Purpose
            - Use two heaps for median maintenance, balancing, and dynamic order statistics.
        - Pseudo strategy
            - ```
                max_heap = lower half
                min_heap = upper half

                add_num(num):
                    if max_heap empty or num <= max_heap.top():
                        max_heap.push(num)
                    else:
                        min_heap.push(num)

                    rebalance so sizes differ by at most 1

                find_median():
                    if sizes equal:
                        return average of tops
                    else:
                        return top of larger heap
              ```

        - Examples
            - Median of data stream.
            - Sliding window median.
            - Dynamic Kth value.
            - Balancing partitions.
            - Task scheduler with heaps

- Problem patterns
    - There are only few unique patterns and most of the problems can be solved by identifying the best pattern
    - Divide and conquer patterns
        - Sort and merge
        - Split array in half
        - Binary search
        - Recursive tree divide
        - Closest pair
        - Count inversions
    - Greedy patterns
        - Sort by end time
        - Pick earliest finishing
        - Pick cheapest safe step
        - Jump as far as possible
        - Use interval overlap
        - Use priority queue for deadlines
    - Backtracking patterns
        - Take/skip
        - Choose unused element
        - Start-index combinations
        - Permutation with used array
        - Constraint placement
        - Palindrome partition
        - Path building
    - Branch and bound patterns
        - Optimization search tree
        - Priority queue of promising states
        - Upper/lower bound pruning
        - Best-first search
    - Dynamic programming patterns
        - DP is the most pattern-rich category. Learn to identify state first.
        - Linear DP (1D)
            - Pattern definition:
                - Incremental sequence building.
            - Pseudo code:
                - ```
                    dp[0] = base
                    dp[1] = base

                    for i from 2 to n:
                        dp[i] = best(dp[i - 1], dp[i - 2], ...)

                    return dp[n]
                  ```

        - 0/1 Knapsack:
            - Pattern definition:
                - Element selections used strictly once.
            - Pseudo code:
                - 2D
                    - ```
                        dp[i][w] = best value using first i items with capacity w

                        for i from 1 to n:
                            for w from 0 to capacity:
                                dp[i][w] = dp[i - 1][w]

                                if weight[i] <= w:
                                    dp[i][w] = max(
                                        dp[i][w],
                                        dp[i - 1][w - weight[i]] + value[i]
                                    )
                      ```

                - 1D
                    - Reverse capacity ensures each item is used once.

                    ```
                        dp[w] = best value for capacity w

                        for each item:
                            for w from capacity down to item.weight:
                                dp[w] = max(dp[w], dp[w - item.weight] + item.value)
                    ```

        - Unbounded Knapsack:
            - Pattern definition:
                - Infinite element reuse allowed.
            - Pseudo code:
                - ```
                    dp[w] = best value for capacity w

                    for each item:
                        for w from item.weight to capacity:
                            dp[w] = max(dp[w], dp[w - item.weight] + item.value)
                  ```

        - Grid/Matrix:
            - Pattern definition:
                - Path optimization or sizing across 2D constraints.
            - Pseudo code:
                - ```
                    dp[r][c] = best answer ending at or starting from cell (r, c)

                    for each cell in valid order:
                        dp[r][c] = value(r, c) + best(neighbor states)
                  ```

        - Longest Common Subsequence (LCS):
            - Pattern definition:
                - Multi-sequence alignments.
            - Pseudo code:
                - ```
                    dp[i][j] = LCS length of s1[:i] and s2[:j]

                    for i from 1 to len(s1):
                        for j from 1 to len(s2):
                            if s1[i - 1] == s2[j - 1]:
                                dp[i][j] = dp[i - 1][j - 1] + 1
                            else:
                                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1])
                  ```

        - Longest Increasing Subsequence (LIS):
            - Pattern definition:
                - Tracking relational growth within an array.
            - Pseudo code:
                - ```
                    dp[i] = length of LIS ending at i

                    for i from 0 to n - 1:
                        dp[i] = 1
                        for j from 0 to i - 1:
                            if nums[j] < nums[i]:
                                dp[i] = max(dp[i], dp[j] + 1)
                  ```

        - Interval DP:
            - Pattern definition:
                - Range manipulation and sub-interval merging.
            - Pseudo code:
                - ```
                    for length from 1 to n:
                        for l from 0 to n - length:
                            r = l + length - 1

                            dp[l][r] = base if l == r

                            for k from l to r - 1:
                                dp[l][r] = best(dp[l][r], combine(dp[l][k], dp[k + 1][r]))
                  ```

        - Palindromic Subsequence:
            - Pattern definition:
                - Range manipulation processing an absolute outer-to-inner loop.
            - Pseudo code:
                - ```
                    dp[l][r] = longest palindromic subsequence in s[l..r]

                    if l == r:
                        dp[l][r] = 1

                    if s[l] == s[r]:
                        dp[l][r] = dp[l + 1][r - 1] + 2
                    else:
                        dp[l][r] = max(dp[l + 1][r], dp[l][r - 1])
                  ```

        - State Machine DP:
            - Pattern definition:
                - Problems explicitly shifting between states based on strict contextual rules (e.g., Best Time to Buy and Sell Stock with Cooldown).
            - Pseudo code:
                - ```
                    state0 = initial state
                    state1 = initial state
                    ...

                    for each day/item:
                        new_state0 = best(old_state0, transition from another state)
                        new_state1 = best(old_state1, transition from another state)
                        ...

                    answer = best(final states)
                  ```

        - Tree DP:
            - Pattern definition:
                - Propagating subproblem solutions up or down a hierarchical graph structure.
            - Pseudo code:
                - ```
                    dfs(node):
                        if node is null:
                            return base

                        left = dfs(node.left)
                        right = dfs(node.right)

                        answer = combine(left, right, node.value)

                        return answer
                  ```

        - Bitmask DP (State Compression):
            - Pattern definition:
                - Representing small subset tracking states via integers to manage NP-hard boundaries efficiently.
            - Pseudo code:
                - ```
                    dp[mask] = best answer after selecting subset represented by mask

                    for mask from 0 to (1 << n) - 1:
                        for each unused item i:
                            next_mask = mask | (1 << i)
                            dp[next_mask] = best(dp[next_mask], dp[mask] + cost)
                  ```

        - Digit DP:
            - Pattern definition:
                - Generating integers satisfying algebraic constraints up to a given limit.
            - Pseudo code:
                - ```
                    dp(pos, tight, state):
                        if pos == len(digits):
                            return valid(state)

                        limit = digits[pos] if tight else 9
                        answer = 0

                        for d from 0 to limit:
                            answer += dp(
                                pos + 1,
                                tight and d == limit,
                                update(state, d)
                            )

                        return answer
                  ```

        - Probability/Game Theory DP:
            - Pattern definition:
                - Simulating sequential games played optimally by multiple players.
            - Pseudo code:
                - ```
                    dp[state] = best result current player can achieve

                    for move in possible_moves(state):
                        result = value(move) - dp[next_state]
                        dp[state] = max(dp[state], result)
                  ```

- Framework to quickly select the solving pattern
    - General
        - Need all solutions?
            - Yes -> Backtracking
        - Need optimal answer?
            - Yes -> Can local choice be proven safe?
                - Yes -> Greedy
                - No -> DP or Branch and Bound
        - Need shortest path?
            - Unweighted -> BFS
            - Weighted non-negative -> Dijkstra
            - Negative edges -> Bellman-Ford
        - Need ordering?
            - Dependencies -> Topological sort
        - Need connectivity?
            - Dynamic edges -> Union-Find
            - Static graph -> DFS/BFS
        - Need range queries with updates?
            - Point update prefix -> Fenwick
            - General range -> Segment tree
        - Need top K?
            - Heap
        - Need median?
            - Two heaps
        - Need next greater/smaller?
            - Monotonic stack
        - Need subarray/substring?
            - Sliding window or prefix sum
        - Need min/max/count over sequence?
            - DP

    - DP pattern selector
        - 1D sequence and local choices:
            - Linear DP
        - Capacity with items once:
            - 0/1 Knapsack
        - Capacity with reusable items:
            - Unbounded Knapsack
        - Grid movement:
            - Grid DP
        - Two sequences:
            - LCS / Edit Distance DP
        - Increasing subsequence:
            - LIS DP
        - Interval merging/removal:
            - Interval DP
        - Palindrome over range:
            - Palindromic DP
        - States like buy/sell/cooldown:
            - State Machine DP
        - Tree decisions:
            - Tree DP
        - Small subset selection:
            - Bitmask DP
        - Digit constraints:
            - Digit DP
        - Optimal two-player game:
            - Game Theory DP

- Learning strategy
    1. Master all data structures like arrays, trees, graphs, etc
    2. Master important algorithms like BFS, DFS, binary search, Quick sort, etc
    3. Learn all the techniques, understand different types of problems, and create a cheat sheet for future use
        - Do not start solving problems without fundamental knowledge or you will keep wasting your time
    4. Go through all the problems first via lectures

- Solve a problem
    1. Manually dry run and construct a solution for a sample case using brute force
    2. Write pseudo code for this dry run
    3. Find repeated work and categorize the problem into known patterns
    4. Choose data structure based on the requirement of the pattern
    5. Prove complexity
    6. Test edge cases
        - Empty input
        - Single element
        - Two elements
        - All duplicates
        - Already sorted
        - Reverse sorted
        - Negative numbers
        - Zero
        - Large input
        - Overflow
        - Null nodes
        - Disconnected graph
        - Cycle in graph
        - Boundary indices
        - Off-by-one
        - Unicode/special characters if strings
    7. Optimize based on known techniques like DP
