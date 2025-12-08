
#include <bits/stdc++.h>
using namespace std;

struct Node {
    string roll;
    double marks;
    Node *left, *right;
    int height;
    Node(const string &r, double m) : roll(r), marks(m), left(nullptr), right(nullptr), height(1) {}
};

//
void printSeparator(char c = '=', int width = 80) {
    cout << string(width, c) << "\n";
}

void printHeader(const string &title) {
    printSeparator('=');
    int padding = (80 - title.length()) / 2;
    cout << string(padding, ' ') << title << "\n";
    printSeparator('=');
}

void printTableHeader() {
    printSeparator('-');
    cout << left << setw(20) << "Roll Number" << " | "
         << right << setw(10) << "Marks" << "\n";
    printSeparator('-');
}

void printNodeRow(Node* n) {
    if (n) {
        cout << left << setw(20) << n->roll << " | "
             << right << setw(10) << fixed << setprecision(2) << n->marks << "\n";
    }
}


class BST {
public:
    Node *root;
    BST() : root(nullptr) {}
    ~BST() { free_tree(root); }

    void Insert(const string &roll, double marks) { root = insert_rec(root, roll, marks); }
    void Delete(const string &roll) { root = delete_rec(root, roll); }
    Node* Search(const string &roll, size_t &comparisons) {
        comparisons = 0;
        return search_rec(root, roll, comparisons);
    }
    int Height() { return height_rec(root); }
    int Count() { return count_nodes(root); }
    void InOrder(function<void(Node*)> visit) { inorder_rec(root, visit); }

    void DisplayTree() {
        printHeader("BST - IN-ORDER TRAVERSAL");
        if (!root) {
            cout << "  (Empty Tree)\n";
            printSeparator('=');
            return;
        }
        printTableHeader();
        InOrder(printNodeRow);
        printSeparator('-');
        cout << "Total Nodes: " << Count() << " | Tree Height: " << Height() << "\n";
        printSeparator('=');
    }

private:
    Node* insert_rec(Node* node, const string &roll, double marks) {
        if (!node) return new Node(roll, marks);
        if (roll < node->roll) node->left = insert_rec(node->left, roll, marks);
        else if (roll > node->roll) node->right = insert_rec(node->right, roll, marks);
        else node->marks = marks;
        return node;
    }
    Node* find_min(Node* node) { while (node && node->left) node = node->left; return node; }
    Node* delete_rec(Node* node, const string &roll) {
        if (!node) return nullptr;
        if (roll < node->roll) node->left = delete_rec(node->left, roll);
        else if (roll > node->roll) node->right = delete_rec(node->right, roll);
        else {
            if (!node->left) { Node* r = node->right; delete node; return r; }
            if (!node->right) { Node* l = node->left; delete node; return l; }
            Node* succ = find_min(node->right);
            node->roll = succ->roll; node->marks = succ->marks;
            node->right = delete_rec(node->right, succ->roll);
        }
        return node;
    }
    Node* search_rec(Node* node, const string &roll, size_t &comparisons) {
        if (!node) return nullptr;
        ++comparisons;
        if (roll == node->roll) return node;
        if (roll < node->roll) return search_rec(node->left, roll, comparisons);
        return search_rec(node->right, roll, comparisons);
    }
    int height_rec(Node* node) {
        if (!node) return 0;
        return 1 + max(height_rec(node->left), height_rec(node->right));
    }
    int count_nodes(Node* node) {
        if (!node) return 0;
        return 1 + count_nodes(node->left) + count_nodes(node->right);
    }
    void inorder_rec(Node* node, function<void(Node*)> visit) {
        if (!node) return;
        inorder_rec(node->left, visit);
        visit(node);
        inorder_rec(node->right, visit);
    }
    void free_tree(Node* node) {
        if (!node) return;
        free_tree(node->left);
        free_tree(node->right);
        delete node;
    }
};


class AVL {
public:
    Node *root;
    AVL() : root(nullptr) {}
    ~AVL() { free_tree(root); }

    void Insert(const string &roll, double marks) { root = insert_rec(root, roll, marks); }
    void Delete(const string &roll) { root = delete_rec(root, roll); }
    Node* Search(const string &roll, size_t &comparisons) {
        comparisons = 0;
        return search_rec(root, roll, comparisons);
    }
    int Height() { return height_rec(root); }
    int Count() { return count_nodes(root); }
    void InOrder(function<void(Node*)> visit) { inorder_rec(root, visit); }

    void DisplayTree() {
        printHeader("AVL TREE - IN-ORDER TRAVERSAL");
        if (!root) {
            cout << "  (Empty Tree)\n";
            printSeparator('=');
            return;
        }
        printTableHeader();
        InOrder(printNodeRow);
        printSeparator('-');
        cout << "Total Nodes: " << Count() << " | Tree Height: " << Height()
             << " | Balance Factor: Optimal\n";
        printSeparator('=');
    }

private:
    int node_height(Node *n) { return n ? n->height : 0; }
    void update_height(Node *n) { if (n) n->height = 1 + max(node_height(n->left), node_height(n->right)); }
    int balance_factor(Node *n) { return n ? node_height(n->left) - node_height(n->right) : 0; }
    Node* right_rotate(Node* y) {
        Node* x = y->left, *T2 = x->right;
        x->right = y; y->left = T2;
        update_height(y); update_height(x);
        return x;
    }
    Node* left_rotate(Node* y) {
        Node* x = y->right, *T2 = x->left;
        x->left = y; y->right = T2;
        update_height(y); update_height(x);
        return x;
    }
    Node* insert_rec(Node* node, const string &roll, double marks) {
        if (!node) return new Node(roll, marks);
        if (roll < node->roll) node->left = insert_rec(node->left, roll, marks);
        else if (roll > node->roll) node->right = insert_rec(node->right, roll, marks);
        else { node->marks = marks; return node; }
        update_height(node);
        int bf = balance_factor(node);
        if (bf > 1 && roll < node->left->roll) return right_rotate(node);       // LL
        if (bf < -1 && roll > node->right->roll) return left_rotate(node);      // RR
        if (bf > 1 && roll > node->left->roll) { node->left = left_rotate(node->left); return right_rotate(node); } // LR
        if (bf < -1 && roll < node->right->roll) { node->right = right_rotate(node->right); return left_rotate(node); } // RL
        return node;
    }
    Node* find_min(Node* node) { while (node && node->left) node = node->left; return node; }
    Node* delete_rec(Node* node, const string &roll) {
        if (!node) return nullptr;
        if (roll < node->roll) node->left = delete_rec(node->left, roll);
        else if (roll > node->roll) node->right = delete_rec(node->right, roll);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* succ = find_min(node->right);
                node->roll = succ->roll; node->marks = succ->marks;
                node->right = delete_rec(node->right, succ->roll);
            }
        }
        update_height(node);
        int bf = balance_factor(node);
        if (bf > 1 && balance_factor(node->left) >= 0) return right_rotate(node);      // LL
        if (bf > 1 && balance_factor(node->left) < 0) {                                // LR
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
        if (bf < -1 && balance_factor(node->right) <= 0) return left_rotate(node);     // RR
        if (bf < -1 && balance_factor(node->right) > 0) {                              // RL
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
        return node;
    }
    Node* search_rec(Node* node, const string &roll, size_t &comparisons) {
        if (!node) return nullptr;
        ++comparisons;
        if (roll == node->roll) return node;
        if (roll < node->roll) return search_rec(node->left, roll, comparisons);
        return search_rec(node->right, roll, comparisons);
    }
    int height_rec(Node* node) {
        if (!node) return 0;
        return 1 + max(height_rec(node->left), height_rec(node->right));
    }
    int count_nodes(Node* node) {
        if (!node) return 0;
        return 1 + count_nodes(node->left) + count_nodes(node->right);
    }
    void inorder_rec(Node* node, function<void(Node*)> visit) {
        if (!node) return;
        inorder_rec(node->left, visit);
        visit(node);
        inorder_rec(node->right, visit);
    }
    void free_tree(Node* node) {
        if (!node) return;
        free_tree(node->left);
        free_tree(node->right);
        delete node;
    }
};

bool try_read_file(const string &path, vector<pair<string,double>> &records) {
    ifstream fin(path);
    if (!fin.is_open()) return false;
    string line;
    while (getline(fin, line)) {
        if (line.empty()) continue;
        string roll; double marks;
        istringstream iss(line);
        iss >> roll >> marks;
        if (!roll.empty() && iss) records.emplace_back(roll, marks);
    }
    fin.close();
    return !records.empty();
}

// ----------- Comparison Display -----------
void displayComparison(BST &bst, AVL &avl) {
    printHeader("TREE COMPARISON");
    cout << left << setw(30) << "Metric" << " | "
         << setw(15) << "BST" << " | "
         << setw(15) << "AVL" << "\n";
    printSeparator('-');
    cout << left << setw(30) << "Total Nodes" << " | "
         << setw(15) << bst.Count() << " | "
         << setw(15) << avl.Count() << "\n";
    cout << left << setw(30) << "Tree Height" << " | "
         << setw(15) << bst.Height() << " | "
         << setw(15) << avl.Height() << "\n";
    printSeparator('=');
}

// ----------- Main Menu -----------
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    vector<pair<string,double>> records;

    printHeader("STUDENT RECORD MANAGEMENT SYSTEM");
    cout << "\nAttempting to read 'students.txt'...\n";

    if (!try_read_file("students.txt", records)) {
        cout << "students.txt not found. Trying '/mnt/data/asn4_2.txt'...\n";
        if (!try_read_file("/mnt/data/asn4_2.txt", records)) {
            cout << "\n[INFO] Using sample data for demonstration.\n";
            records = { {"CS101",85.5}, {"CS105",90.0}, {"CS099",75.0},
                       {"CS110",88.5}, {"CS103",92.0}, {"CS107",79.5},
                       {"CS112",95.0}, {"CS098",82.0} };
        }
    }

    cout << "\n✓ Successfully loaded " << records.size() << " records.\n\n";

    BST bst; AVL avl;
    for (auto &p : records) {
        bst.Insert(p.first, p.second);
        avl.Insert(p.first, p.second);
    }

    cout << "Initial trees built successfully!\n\n";
    displayComparison(bst, avl);
    cout << "\n";
    avl.DisplayTree();

    while (true) {
        cout << "\n";
        printHeader("MAIN MENU");
        cout << "  1.  Insert record into BST\n";
        cout << "  2.  Insert record into AVL\n";
        cout << "  3.  Search in BST\n";
        cout << "  4.  Search in AVL\n";
        cout << "  5.  Delete from BST\n";
        cout << "  6.  Delete from AVL\n";
        cout << "  7.  Display BST (In-Order)\n";
        cout << "  8.  Display AVL (In-Order)\n";
        cout << "  9.  Show Tree Comparison\n";
        cout << "  10. Display Both Trees\n";
        cout << "  11. Rebuild trees from file\n";
        cout << "  12. Exit\n";
        printSeparator('=');
        cout << "Enter your choice (1-12): ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            string dummy;
            getline(cin, dummy);
            cout << "\n[ERROR] Invalid input. Please enter a number.\n";
            continue;
        }

        string key; double marks; size_t comps=0;

        switch (choice) {
            case 1:
                cout << "\nRoll Number: "; cin >> key;
                cout << "Marks: "; cin >> marks;
                bst.Insert(key, marks);
                cout << "\n✓ Record inserted into BST successfully!\n\n";
                displayComparison(bst, avl);
                break;

            case 2:
                cout << "\nRoll Number: "; cin >> key;
                cout << "Marks: "; cin >> marks;
                avl.Insert(key, marks);
                cout << "\n✓ Record inserted into AVL successfully!\n\n";
                displayComparison(bst, avl);
                break;

            case 3:
                cout << "\nRoll Number to search: "; cin >> key;
                {
                    Node* res = bst.Search(key, comps);
                    cout << "\n";
                    printHeader("BST SEARCH RESULT");
                    if (res) {
                        cout << "✓ Record Found!\n";
                        cout << "  Roll Number: " << res->roll << "\n";
                        cout << "  Marks: " << fixed << setprecision(2) << res->marks << "\n";
                    } else {
                        cout << "✗ Record Not Found\n";
                    }
                    cout << "  Comparisons Made: " << comps << "\n";
                    printSeparator('=');
                }
                break;

            case 4:
                cout << "\nRoll Number to search: "; cin >> key;
                {
                    Node* res = avl.Search(key, comps);
                    cout << "\n";
                    printHeader("AVL SEARCH RESULT");
                    if (res) {
                        cout << "✓ Record Found!\n";
                        cout << "  Roll Number: " << res->roll << "\n";
                        cout << "  Marks: " << fixed << setprecision(2) << res->marks << "\n";
                    } else {
                        cout << "✗ Record Not Found\n";
                    }
                    cout << "  Comparisons Made: " << comps << "\n";
                    printSeparator('=');
                }
                break;

            case 5:
                cout << "\nRoll Number to delete: "; cin >> key;
                bst.Delete(key);
                cout << "\n✓ Record deleted from BST (if it existed).\n\n";
                displayComparison(bst, avl);
                break;

            case 6:
                cout << "\nRoll Number to delete: "; cin >> key;
                avl.Delete(key);
                cout << "\n✓ Record deleted from AVL (if it existed).\n\n";
                displayComparison(bst, avl);
                break;

            case 7:
                cout << "\n";
                bst.DisplayTree();
                break;

            case 8:
                cout << "\n";
                avl.DisplayTree();
                break;

            case 9:
                cout << "\n";
                displayComparison(bst, avl);
                break;

            case 10:
                cout << "\n";
                bst.DisplayTree();
                cout << "\n";
                avl.DisplayTree();
                break;

            case 11: {
                vector<pair<string,double>> newrec;
                if (!try_read_file("students.txt", newrec) &&
                    !try_read_file("/mnt/data/asn4_2.txt", newrec)) {
                    cout << "\n[ERROR] Could not reload files. No changes made.\n";
                    break;
                }
                bst.~BST(); new (&bst) BST();
                avl.~AVL(); new (&avl) AVL();
                for (auto &p : newrec) {
                    bst.Insert(p.first, p.second);
                    avl.Insert(p.first, p.second);
                }
                cout << "\n✓ Trees rebuilt from file successfully!\n\n";
                displayComparison(bst, avl);
            } break;

            case 12:
                cout << "\n";
                printHeader("THANK YOU");
                cout << "  Exiting Student Record Management System...\n";
                printSeparator('=');
                cout << "\n";
                return 0;

            default:
                cout << "\n[ERROR] Invalid choice. Please select 1-12.\n";
                break;
        }
    }
}
