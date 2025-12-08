# 🛒 Grocery Inventory Management System (C++)

## 📌 Project Overview
This project is a **Grocery Store Inventory Management System** implemented in **C++** without using the STL.  
It is designed to manage grocery items efficiently using **custom-built Data Structures** such as:

- Linked Lists
- Queues
- Stacks

The system supports **persistent storage using Binary Files**, allowing the inventory data to be saved and reloaded.

---

## 🎯 Key Features

- ✅ Add, Update, Delete inventory items  
- ✅ Track expiry dates of products  
- ✅ Category-wise Queue processing  
- ✅ Stock management using Stack (LIFO)  
- ✅ Binary file storage (No Database used)  
- ✅ No STL used — full manual memory management  

---

## 🧠 Core Data Structures Used

| Structure | Purpose |
|------------|----------|
| Linked List | Store inventory records dynamically |
| Queue | Handle expiry tracking per category |
| Stack | Manage stock movement (LIFO logic) |
| Binary Files | Persistent data storage |

---

## ⚙️ Build & Run Instructions

### 🔹 Requirements
- G++ Compiler  
- Linux / Windows (CLI support)

### 🔹 Compile
```bash
g++ Grocery_Store_Management_System.cpp -o grocery_sys
./grocery_sys
