Student Record Management System using BST and AVL Tree

This project implements a student record management system using two different tree data structures:

1. Binary Search Tree (BST)
2. AVL Tree (Self-Balancing Binary Search Tree)

Each student record consists of:

* Roll Number (used as the key)
* Marks

The main objective of this project is to compare the performance of a normal BST with a self-balancing AVL tree in terms of height and number of comparisons during search operations.

---

Features

* Insert student records into BST
* Insert student records into AVL Tree
* Search for a student record in both trees
* Display the number of comparisons during search
* Delete records from both trees
* Display student records in sorted order using Inorder Traversal
* Compare the height of BST and AVL Tree
* Load student records directly from a text file

---

Input File Format

The program reads student records from a file named:

students.txt

Each line in the file should contain:

RollNumber   Marks

Example:

CS101 85.5
CS105 90.0
CS099 75.0
CS110 88.5

---

Program Output

After loading the file, the program:

* Builds both BST and AVL trees
* Displays their heights
* Allows the user to perform insert, search, delete, and display operations through a menu
* Shows the number of comparisons for every search operation
* Displays student records in sorted order from the AVL tree

---

How to Compile and Run

Use the following commands:

g++ student_bst_avl.cpp -o student_tree
./student_tree

Make sure that the file students.txt is present in the same directory before running the program.

---

Purpose of the Project

This project is designed to study and compare:

* The behavior of a normal Binary Search Tree
* The efficiency of a self-balancing AVL Tree
* The effect of tree height on search performance

It is implemented as part of an academic laboratory assignment for tree-based data structures.

---
Language Used

C++
---
Run :
Save it as student_bst_avl.cpp, compile with g++ -std=c++17 student_bst_avl.cpp -O2 -o student_tree and run ./student_tree.


Author

AbdulBari Mohammed Alameer

