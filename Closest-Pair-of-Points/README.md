Closest Pair of Points using Divide and Conquer (C)

Project Overview  
This project implements the classic Closest Pair of Points problem using the Divide and Conquer approach.  
The program finds the minimum distance between any two points in a 2D plane efficiently.

Unlike standard implementations that rely on arrays, this project uses a custom linked list structure to manage spatial data dynamically.

The time complexity of the algorithm is O(n log n).

---

Algorithm Description  

The algorithm works in three main steps:

1. Sort all points based on x-coordinate.
2. Recursively divide the points into left and right halves.
3. Find the minimum distance in:
   - Left half
   - Right half
   - The strip formed around the midpoint

The final answer is the minimum of the three computed distances.

---

Input Format  

The program reads data from a file named:

test.txt

Each line in the file should contain a point in the following format:

x y

Example:
3 4  
5 1  
9 7  

---

Build and Run Instructions  

Requirements:
- GCC Compiler
- Math Library

Compile:
gcc ClosestPair.c -o closest_pair -lm

Run:
./closest_pair

---

File Structure  

Closest-Pair-of-Points/
|
|-- ClosestPair.c
|-- test.txt
|-- README.md

---

Academic Context  

This project was developed as part of the Advanced Algorithms coursework.  
It demonstrates practical implementation of divide and conquer techniques, geometric algorithms, and dynamic data structures in C.

---

Author  

AbdulBari Mohammed Alameer  
Master's Student – Computer Science and Engineering  
Tezpur University
