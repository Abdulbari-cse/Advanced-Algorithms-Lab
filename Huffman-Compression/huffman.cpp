#include <iostream>
#include <fstream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

// ------------------- Node Definition -------------------
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

struct compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;
    }
};

// ------------------- Global Variables -------------------
unordered_map<char, string> huffmanCode;
unordered_map<string, char> reverseCode;

// ------------------- Build Huffman Tree -------------------
void buildCodes(Node* root, string str) {
    if (!root) return;

    if (!root->left && !root->right) {
        huffmanCode[root->ch] = str;
        reverseCode[str] = root->ch;
        return;
    }
    buildCodes(root->left, str + "0");
    buildCodes(root->right, str + "1");
}

Node* buildHuffmanTree(unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, compare> pq;
    for (auto& pair : freq)
        pq.push(new Node(pair.first, pair.second));

    while (pq.size() != 1) {
        Node *left = pq.top(); pq.pop();
        Node *right = pq.top(); pq.pop();
        Node *sum = new Node('\0', left->freq + right->freq);
        sum->left = left;
        sum->right = right;
        pq.push(sum);
    }
    return pq.top();
}

// ------------------- Memory Cleanup -------------------
void freeTree(Node* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

// ------------------- Compression -------------------
void compress(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Error: Cannot open input file.\n";
        return;
    }

    string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());
    in.close();

    if (text.empty()) {
        cerr << "Error: Input file is empty.\n";
        return;
    }

    // Count frequencies
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;

    // Build Huffman tree
    Node* root = buildHuffmanTree(freq);
    buildCodes(root, "");

    cout << "\n--- Huffman Codes ---\n";
    for (auto& pair : huffmanCode) {
        string key = (pair.first == '\n') ? "\\n" :
                     (pair.first == ' ') ? "space" : string(1, pair.first);
        cout << "'" << key << "' : " << pair.second << "\n";
    }

    // Encode text
    string encoded = "";
    for (char ch : text) encoded += huffmanCode[ch];

    // Write to output.huf
    ofstream out(outputFile, ios::binary);
    int n = freq.size();
    out.write(reinterpret_cast<char*>(&n), sizeof(n));

    // Write header: char + freq
    for (auto& pair : freq) {
        out.write(reinterpret_cast<const char*>(&pair.first), sizeof(pair.first));
        out.write(reinterpret_cast<const char*>(&pair.second), sizeof(pair.second));
    }

    int validBits = encoded.size();
    out.write(reinterpret_cast<char*>(&validBits), sizeof(validBits));

    // ----------- Safe Bit Writing (Fixed Version) -----------
    unsigned char buffer = 0;
    int bitCount = 0;

    for (char bit : encoded) {
        buffer = (buffer << 1) | (bit - '0');
        bitCount++;

        if (bitCount == 8) {
            out.write(reinterpret_cast<char*>(&buffer), 1);
            bitCount = 0;
            buffer = 0;
        }
    }

    // Handle last partial byte
    if (bitCount > 0) {
        buffer <<= (8 - bitCount); // pad with zeros
        out.write(reinterpret_cast<char*>(&buffer), 1);
    }

    out.close();

    // Compression Statistics
    int originalBits = text.size() * 8;
    int fixedBits = text.size() * ceil(log2(freq.size()));
    int huffmanBits = encoded.size();

    cout << "\n--- Compression Report ---\n";
    cout << "Original (ASCII) bits: " << originalBits << endl;
    cout << "Fixed-length bits: " << fixedBits << endl;
    cout << "Huffman-coded bits: " << huffmanBits << endl;
    cout << "Compression Ratio: "
         << (double)huffmanBits / originalBits * 100 << "%\n";

    cout << "\nCompressed file saved as: " << outputFile << endl;

    freeTree(root);
}

// ------------------- Decompression -------------------
void decompress(const string& inputFile, const string& outputFile) {
    ifstream in(inputFile, ios::binary);
    if (!in.is_open()) {
        cerr << "Error: Cannot open compressed file.\n";
        return;
    }

    int n;
    in.read(reinterpret_cast<char*>(&n), sizeof(n));

    unordered_map<char, int> freq;
    for (int i = 0; i < n; i++) {
        char ch;
        int f;
        in.read(reinterpret_cast<char*>(&ch), sizeof(ch));
        in.read(reinterpret_cast<char*>(&f), sizeof(f));
        freq[ch] = f;
    }

    int validBits;
    in.read(reinterpret_cast<char*>(&validBits), sizeof(validBits));

    // Rebuild Huffman tree
    Node* root = buildHuffmanTree(freq);

    // Read compressed data safely
    string bits = "";
    unsigned char byte;
    while (in.read(reinterpret_cast<char*>(&byte), 1)) {
        for (int i = 7; i >= 0; i--) {
            bits += ((byte >> i) & 1) ? '1' : '0';
        }
    }
    in.close();

    bits = bits.substr(0, validBits); // trim padded zeros

    // Decode
    string decoded = "";
    Node* curr = root;
    for (char bit : bits) {
        curr = (bit == '0') ? curr->left : curr->right;
        if (!curr->left && !curr->right) {
            decoded += curr->ch;
            curr = root;
        }
    }

    ofstream out(outputFile, ios::binary);
    out << decoded;
    out.close();

    cout << "Decompressed file saved as: " << outputFile << endl;

    freeTree(root);
}

// ------------------- Main -------------------
int main() {
    string inputFile = "input.txt";
    string compressedFile = "output.huf";
    string decompressedFile = "decoded.txt";

    compress(inputFile, compressedFile);
    decompress(compressedFile, decompressedFile);

    return 0;
}
