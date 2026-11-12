# Algorithm Battle – Which Data Structure Wins?

**Application:** Student Record Search (key = Register Number)
**Language:** C
**Student:** `<Your Name>` | **Reg. No:** `<Your Reg No>` | **Section:** `<Section>`
**Course:** SRM Institute of Science and Technology, Tiruchirappalli – CLA-2

---

## Part A – Problem Selection

**What is the problem?**
A college keeps thousands of student records (register number, name, department). The system must store new records and find a student quickly using the register number.

**Why is efficient searching required?**
Searching happens constantly (attendance, fee payment, results, ID verification). A linear scan takes O(n) time, which becomes slow as records grow, so a structure with faster lookup is needed.

**Why BST, AVL and Hashing?**
- **BST** gives O(log n) average search and keeps data sorted, but can become skewed.
- **AVL** is a self-balancing BST that guarantees O(log n) in the worst case.
- **Hashing** gives O(1) average search but stores data unordered and suffers from collisions.

They represent three different trade-offs (simple ordered, balanced ordered, fast unordered), which makes them a good comparison.

---

## Project Structure

| File | Description |
|---|---|
| `dataset.h` | Common dataset: 40 unique records, unsuccessful search keys, new insertion key |
| `bst_student.c` | Binary Search Tree implementation |
| `avl_student.c` | AVL Tree implementation (with rotations) |
| `hash_student.c` | Hashing with Linear Probing (`key % 53`) |

## How to Compile and Run

Keep all files in the same folder.

```bash
gcc bst_student.c  -o bst   && ./bst
gcc avl_student.c  -o avl   && ./avl
gcc hash_student.c -o hash  && ./hash
```

On Windows (MinGW) run `bst.exe`, `avl.exe`, `hash.exe`.
Each program ends with a **viva demo**: enter any register number to see how that structure searches for it (path / probed slots).

---

## Part B – Implementation

| Operation | BST | AVL | Hashing |
|---|---|---|---|
| Insertion | Iterative, counts comparisons | Recursive with LL, RR, LR, RL rotations | `key % 53`, linear probing |
| Searching | Iterative, prints path | Iterative, prints path | Probes slots until key or empty slot |
| Traversal | Inorder, Preorder, Postorder | Inorder, Preorder, Postorder | Table display |
| Collision handling | – | – | Linear probing: `(index + 1) % size` |

## Part C – Mini Experiment

- **Dataset:** 40 unique records (same for all three structures)
- **Successful search:** all 40 keys searched
- **Unsuccessful search:** keys `1000, 2000, 5000, 7000, 9500`
- **Insertion:** new record with key `4747`
- **Comparison counting:** one comparison per tree node visited (BST/AVL) or per hash slot examined (Hashing)
- **Hash table:** size 53 (prime), load factor 40/53 = 0.75

## Part D – Algorithm Battle

| Parameter | BST | AVL | Hashing |
|---|---|---|---|
| Avg search comparisons (successful) | 4.92 | 4.60 | **1.80** |
| Max search comparisons (successful) | 8 | **6** | 7 |
| Avg search comparisons (unsuccessful) | **5.20** | 5.80 | 6.20 |
| Total insertion comparisons (40 records) | 157 | 155 | – |
| Insertion of new key (4747) | 3 comparisons | 5 comparisons | 4 collisions |
| Tree height (levels) | 8 | **6** | – |
| Rotations performed | – | 18 | – |
| Collisions | – | – | 32 |
| Sorted output | Yes (inorder) | Yes (inorder) | No |

**Overall observation**
- **BST:** simple and sorted, but the insertion order produced a taller tree (height 8).
- **AVL:** 18 rotations kept the height at 6, so searches are shorter and the worst case is controlled.
- **Hashing:** fastest for successful search, but the 32 collisions form clusters, which makes unsuccessful search slower (for example, key 9500 needed 13 probes).

---

## Part E – Final Verdict

**Winner for Student Record Search: Hashing (with AVL as the runner-up when ordering is needed).**

**Justification from experiment**
1. Hashing needed only **1.80 comparisons** on average for successful search, against 4.92 (BST) and 4.60 (AVL). Looking up a student by register number is the most common operation, so this matters most.
2. AVL beat BST: height **6 vs 8**, and a worst-case search of **6 vs 8** comparisons, which shows why balancing helps.
3. Hashing is weaker on unsuccessful search (**6.20**) because of clustering from linear probing at 75% load. A larger table or lower load factor would reduce this.
4. Only BST and AVL support sorted listing and range queries (such as "all students from 2000 to 3000"). If the application needs those, **AVL** is the better choice.

**Recommendation:** use **Hashing** for direct register-number lookup. Use **AVL** if sorted reports or range search are also required.

---

## Time Complexity Summary

| Operation | BST (avg / worst) | AVL (worst) | Hashing (avg / worst) |
|---|---|---|---|
| Search | O(log n) / O(n) | O(log n) | O(1) / O(n) |
| Insert | O(log n) / O(n) | O(log n) | O(1) / O(n) |
| Sorted traversal | O(n) | O(n) | Not supported directly |

## Note

Results depend on the dataset and insertion order. Changing the keys in `dataset.h` will change the numbers, so update the tables above if you modify the data.
