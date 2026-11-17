# Experiment Results – Student Record Search

**Dataset:** 40 unique records (key = Register Number)
**Hash table:** size 53, `key % 53`, linear probing (load factor 0.75)
**Unsuccessful search keys:** 1000, 2000, 5000, 7000, 9500
**New insertion key:** 4747

---

## Algorithm Battle Table

| Parameter | BST | AVL | Hashing |
|---|---|---|---|
| Avg comparisons (successful search) | 4.92 | 4.60 | **1.80** |
| Max comparisons (successful search) | 8 | **6** | 7 |
| Min comparisons (successful search) | 1 | 1 | 1 |
| Avg comparisons (unsuccessful search) | **5.20** | 5.80 | 6.20 |
| Total insertion comparisons (40 records) | 157 | 155 | - |
| Insertion of new key 4747 | 3 comparisons | 5 comparisons | 4 collisions |
| Tree height (levels) | 8 | **6** | - |
| Rotations | - | 18 | - |
| Collisions | - | - | 32 |

## Unsuccessful Search (comparisons per key)

| Key | BST | AVL | Hashing |
|---|---|---|---|
| 1000 | 4 | 6 | 1 |
| 2000 | 7 | 6 | 2 |
| 5000 | 3 | 5 | 8 |
| 7000 | 6 | 6 | 7 |
| 9500 | 6 | 6 | 13 |
| **Average** | **5.20** | **5.80** | **6.20** |

---

## Final Verdict

**Winner: Hashing**

- Fewest comparisons for successful search (1.80 average), the most common operation for student records.
- AVL is the best tree: height 6 against 8 for BST, and a worst-case search of 6 against 8.
- Hashing is slower on unsuccessful search (6.20) because of clustering from linear probing.
- Use AVL instead if sorted output or range queries are required.
