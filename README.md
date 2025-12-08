# 🚀 Advanced Algorithms & Data Structures Lab

👨‍🎓 **Author:** Abdulbari Mohammed Alameer  
🎓 **Program:** M.Tech in Computer Science and Engineering  
🏫 **University:** Tezpur University, Assam, India  
📅 **Semester:** July 2025  
📌 **Course Codes:** CSMT503, CSMT533  

---

## 🧠 About This Repository

This repository contains **high-performance implementations of Advanced Data Structures and Algorithms (DSA)** developed as part of my Master's coursework.  
The projects focus on:

- Algorithm Optimization
- Time & Space Complexity Analysis
- Low-level Memory Management
- File Handling & Data Processing
- Divide & Conquer Techniques

All implementations are developed using **pure C and C++ without relying on STL**, to strengthen core algorithmic foundations.

---

## 🛠 Technical Skills Demonstrated

- ✅ C / C++
- ✅ Data Structures: Linked Lists, Stacks, Queues
- ✅ Divide & Conquer Algorithms
- ✅ Sorting Algorithms (Merge, Quick)
- ✅ Binary Search
- ✅ File Handling (Binary + CSV)
- ✅ Algorithm Complexity Analysis
- ✅ GCC / G++

---

## 📂 Project Index

### 1️⃣ 🛒 Grocery Inventory Management System (C++)
- **File:** `Grocery_Store_Management_System.cpp`
- **Description:** Inventory system built using custom implementations of Lists, Queues, and Stacks.
- **Key Features:**
  - Binary File Storage
  - Expiry Date Tracking
  - Category-Based Queues
  - LIFO Stock Management
- **Concepts Used:** OOP, File Handling, Data Structures

---

### 2️⃣ 💳 E-Commerce Transaction Analyzer (C)
- **File:** `ECommerce_Transaction_Analyzer.c`
- **Dataset:** `ecommerce_transactions.csv`
- **Description:** High-performance engine for processing large transaction datasets.
- **Algorithms Implemented:**
  - Merge Sort (Stable Sorting)
  - Quick Sort (Randomized Pivot)
  - Binary Search (O(log n))
- **Extra Feature:** Algorithm Performance Benchmarking

---

### 3️⃣ 📍 Closest Pair of Points – Divide & Conquer (C)
- **File:** `ClosetPair.c`
- **Description:** Solves the Closest Pair Problem using Divide & Conquer with **Custom Linked Lists instead of Arrays**.
- **Time Complexity:** O(n log n)
- **Input:** Coordinates read from file `test`

---

## ▶️ Build & Run Instructions

### 🔹 Project 1 (C++)

```bash
g++ Grocery_Store_Management_System.cpp -o grocery_sys
./grocery_sys

### 🔹 Project 2: E-Commerce Transaction Analyzer (C)

Requires GCC Compiler & CSV Dataset  
Ensure `ecommerce_transactions.csv` is in the same directory.

```bash
gcc ECommerce_Transaction_Analyzer.c -o ecommerce_app
./ecommerce_app

---

### 🔹 Project 3: Closest Pair of Points (C + Math Library)

Requires GCC Compiler & Math Library (`-lm`)  
Ensure the input file `test` exists in the same directory.

```bash
gcc ClosetPair.c -o closest_pair -lm
./closest_pair
