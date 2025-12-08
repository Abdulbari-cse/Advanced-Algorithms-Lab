# 💳 E-Commerce Transaction Analyzer (C)

## 📌 Project Overview
This project is a **high-performance E-Commerce Transaction Analyzer** built using the **C programming language**.  
It is designed to efficiently process **large transaction datasets** using advanced **sorting and searching algorithms**.

The system reads transaction data from a CSV file and applies optimized algorithms to analyze performance.

---

## 🎯 Key Features

- ✅ Reads real-world transaction data from CSV  
- ✅ Implements **Merge Sort** and **Quick Sort**  
- ✅ Uses **Binary Search** for fast transaction lookup  
- ✅ Performance benchmarking (swaps & comparisons)  
- ✅ Randomized pivot strategy to avoid worst-case Quick Sort  
- ✅ Efficient memory handling in pure C

---

## 🧠 Algorithms Used

| Algorithm | Purpose | Complexity |
|------------|----------|------------|
| Merge Sort | Stable high-performance sorting | O(n log n) |
| Quick Sort (Random Pivot) | Fast average-case sorting | O(n log n) |
| Binary Search | Fast lookup by Invoice ID | O(log n) |

---

## ⚙️ Build & Run Instructions

### 🔹 Requirements
- GCC Compiler  
- CSV Dataset File  

Ensure the following file exists in the same folder before running:

---

### 🔹 Compile
```bash
gcc ECommerce_Transaction_Analyzer.c -o ecommerce_app
./ecommerce_app

