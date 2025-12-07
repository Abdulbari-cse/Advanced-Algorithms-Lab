# 🚀 Advanced Algorithms & Data Structures Lab

### Advanced Algorithms & Data Structure Implementation
This repository contains advanced implementations of Data Structures and Algorithms (DSA) developed for the *CSMT503* and *CSMT533* courses. The projects demonstrate proficiency in C/C++ optimization, custom memory management, and algorithm complexity analysis.

---

## 📂 Project Index

### 1️⃣ 🛒 Grocery Inventory Management System
* *File:* Grocery_Store_Management_System.cpp
* *Overview:* A comprehensive system to manage store inventory using custom implementations of *Lists, Queues, and Stacks*.
* *Key Tech:* Binary File Serialization, No STL (Standard Template Library), Expiry Date Tracking.
* *Core Logic:*
    * *Inventory List:* Manages CRUD operations and saves data to a binary file.
    * *Category Queues:* Processes items based on categories to track expiry dates.
    * *Stock Stacks:* Handles inventory using LIFO (Last-In-First-Out) logic.

### 2️⃣ 💳 E-Commerce Transaction Analyzer
* *File:* ECommerce_Transaction_Analyzer.c
* *Dataset:* ecommerce_transactions.csv
* *Overview:* A high-performance sorting and searching engine designed to process large e-commerce datasets.
* *Key Tech:* Divide & Conquer Algorithms, CSV Parsing, Performance Benchmarking.
* *Features:*
    * *Merge Sort:* Implements stable sorting for transaction records.
    * *Quick Sort:* Uses Randomized Pivot strategy to optimize speed and avoid O(n²) worst-case scenarios.
    * *Binary Search:* Enables O(log n) fast lookup for transactions via Invoice ID.
    * *Metrics:* Calculates swaps and comparisons to analyze algorithmic efficiency.

### 3️⃣ 📍 Closest Pair of Points (Divide & Conquer)
* *File:* ClosetPair.c
* *Overview:* Solves the geometric "Closest Pair of Points" problem using the Divide and Conquer strategy.
* *Key Innovation:* Unlike standard implementations that use Arrays, this project utilizes *Custom Linked Lists* (struct pnode) to manage spatial data dynamically.
* *Complexity:* O(n log n).
* *Input Data:* Reads 2D coordinates from a file named test.

---

## 🛠 Build & Usage Instructions

### 🔹 Project 1: Grocery System (C++)
Requires G++ Compiler
```bash
g++ Grocery_Store_Management_System.cpp -o grocery_sys
./grocery_sys

### 🔹Project 2: E-Commerce Analyzer (C)
​Requires GCC Compiler & CSV Dataset
Ensure ecommerce_transactions.csv is in the same directory.
gcc ECommerce_Transaction_Analyzer.c -o ecommerce_app
./ecommerce_app
### 🔹Project 3: Closest Pair of Points (C)
​Requires GCC Compiler & Math Library
Note: You must link the math library using -lm. Ensure the test file exists for input
cc ClosetPair.c -o closest_pair -lm
./closest_pair
