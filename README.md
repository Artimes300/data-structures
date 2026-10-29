# COMP 2233 — Data Structures

> A hands-on study repo covering all topics in COMP 2233 Data Structures.  
> Built to understand fundamentals deeply — implemented from scratch with complexity analysis.

[![Language](https://img.shields.io/badge/Language-C%20%2F%20C%2B%2B-blue)](https://isocpp.org/)
[![Topics](https://img.shields.io/badge/Topics-7-green)](#topics)
[![Labs](https://img.shields.io/badge/Labs-5-orange)](#lab-work)

---

## 🗺️ Topics

| # | Topic | Big-O Focus | Status |
|---|-------|-------------|--------|
| [01](./02-algorithm-analysis/) | Algorithm Analysis & Time Complexity | O(1) → O(n²) | ✅ |
| [02](./03-arrays/) | Arrays (1D & 2D) | Access O(1), Insert O(n) | ✅ |
| [03](./04-vectors/) | Vectors (C++ STL) | Dynamic sizing, push_back O(1) amortized | ✅ |
| [04](./05-pointers/) | Pointers & Dynamic Memory | malloc/free, double pointer | ✅ |
| [05](./06-linked-lists/) | Linked Lists | Insert O(1), Search O(n) | ✅ |

---

## 🧪 Lab Work

| Lab | Experiment | Concept | Solution |
|-----|-----------|---------|---------|
| LAB 2 | Exp 1 | Discrete Vars vs Array Search | [lab2-search](./labs/lab2-search/) |
| LAB 2 | Exp 2 | Linear vs Binary Search O(n) vs O(log n) | [lab2-search](./labs/lab2-search/) |
| LAB 3 | Exp 1 | Music Playlist — Array CRUD (C) | [lab3-exp1](./labs/lab3-exp1-array-playlist/) |
| LAB 3 | Exp 2 | Phone Book — Vector CRUD (C++) | [lab3-exp2](./labs/lab3-exp2-vector-phonebook/) |
| LAB 4 | Exp 1 | Cafe Sales — 2D Dynamic Array (C) | [lab4](./labs/lab4-cafe-sales/) |
| LAB 5 | Exp 1 | Student Linked List — CRUD + Reverse (C) | [lab5-exp1](./labs/lab5-exp1-student-list/) |
| LAB 5 | Exp 2 | Merge Two Sorted Linked Lists (C) | [lab5-exp2](./labs/lab5-exp2-merge-lists/) |

---

## 🧠 Key Concepts Cheatsheet

### Big-O Complexity Order
```
O(1) < O(log n) < O(n) < O(n log n) < O(n²) < O(2ⁿ)
```

### Data Structure Quick Compare
| Structure | Access | Insert (head) | Insert (tail) | Search | Memory |
|-----------|--------|---------------|---------------|--------|--------|
| Array | O(1) | O(n) | O(1) | O(n) | Contiguous |
| Linked List | O(n) | O(1) | O(n) | O(n) | Scattered |
| Vector | O(1) | O(n) | O(1)* | O(n) | Contiguous |

*amortized

---

## 🛠️ Build & Run

```bash
# C files
gcc solution.c -o solution && ./solution

# C++ files  
g++ solution.cpp -o solution && ./solution
```

---

*COMP 2233 Data Structures | Study repository*
