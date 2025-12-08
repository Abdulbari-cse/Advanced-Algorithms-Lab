# 📦 Huffman Compression & Decompression (Greedy Algorithm)

This project implements **Huffman Coding**, a greedy algorithm for **lossless data compression**.  
It compresses a text file into a binary `.huf` file and then decompresses it back to its original form.

---

## 🎯 Objectives
- Understand and implement **Greedy Algorithms**.
- Generate **Huffman Codes** for characters based on frequency.
- Compare:
  - ASCII encoding
  - Fixed-length encoding
  - Huffman encoding
- Implement:
  - Compression to `.huf` binary file
  - Decompression back to readable text

---

## ⚙️ Features
- Builds Huffman Tree using **Priority Queue**
- Generates **Binary Prefix Codes**
- Stores:
  - Character frequencies
  - Encoded binary data
- Displays:
  - Huffman codes
  - Compression statistics
- Fully supports:
  - Compression
  - Decompression

---

## 📂 Files
| File | Description |
|------|-------------|
| `huffman.cpp` | Main C++ implementation |
| `input.txt` | Input text file |
| `output.huf` | Compressed binary file |
| `decoded.txt` | Decompressed output file |

---

## 🛠 Build & Run

### ✅ Compile
```bash
g++ huffman.cpp -o huffman
./huffman
[huffman.cpp](https://github.com/user-attachments/files/24021989/huffman.cpp)
