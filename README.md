# Advanced-Algorithms-Lab
# 🚀 Advanced Algorithms & Data Structures Lab

### 🎓 Master's Coursework | Tezpur University
This repository contains advanced implementations of Data Structures and Algorithms (DSA) developed for the *CSMT503* and *CSMT533* courses. The projects demonstrate proficiency in C/C++ optimization, memory management, and algorithm complexity analysis.

## 📂 Project Index

### 1️⃣ 🛒 Grocery Inventory Management System
*File:* Grocery_Store_Management_System.cpp
* *Overview:* A comprehensive system to manage store inventory using custom implementation of *Lists, Queues, and Stacks*.
* *Key Tech:* Binary File Serialization, Data Structures (No STL), Expiry Date Tracking.
* *Core Logic:*
    * *Inventory List:* Manages CRUD operations and saves data to a binary file.
    * *Category Queues:* Processes items based on categories to track expiry dates.
    * *Stock Stacks:* Handles inventory using LIFO (Last-In-First-Out) logic.

### 2️⃣ 💳 E-Commerce Transaction Analyzer
*File:* ECommerce_Transaction_Analyzer.c
*Dataset:* ecommerce_transactions.csv
* *Overview:* A high-performance sorting and searching engine designed to process large e-commerce datasets.
* *Key Tech:* Divide & Conquer Algorithms, CSV Parsing, Performance Benchmarking.
* *Features:*
    * *Merge Sort:* Implements stable sorting for transaction records.
    * *Quick Sort:* Uses Randomized Pivot strategy to optimize sorting speed and avoid O(n²) worst-case scenarios.
    * *Binary Search:* Enables O(log n) fast lookup for transactions via Invoice ID.
    * *Performance Metrics:* Calculates and displays the number of swaps and comparisons for algorithmic efficiency analysis.

---

## 🛠 Build & Usage

### 🔹 Running the Grocery System (C++)
This system uses C++ features. Compile it using g++.
```bash
g++ Grocery_Store_Management_System.cpp -o grocery_sys
./grocery_sys

