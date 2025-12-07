#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
using namespace std;

struct GroceryItem {
    int id;
    char name[50];
    char category[30];
    float price;
    char expiry[11]; // YYYY-MM-DD
};

// ================= Program A: LIST =================
class GroceryList {
    vector<GroceryItem> items;

public:
    void insert(GroceryItem g) { items.push_back(g); }

    void deleteItem(int pos) {
        if (pos < 0 || pos >= (int)items.size()) {
            cout << "Invalid position!" << endl;
            return;
        }
        items.erase(items.begin() + pos);
    }

    int search(int id) {
        for (int i = 0; i < (int)items.size(); i++) {
            if (items[i].id == id) return i;
        }
        return -1;
    }

    void print() {
        if (items.empty()) {
            cout << "List is empty!\n";
            return;
        }
        for (int i = 0; i < (int)items.size(); i++) {
            cout << i << ") "
                 << items[i].id << " " << items[i].name << " "
                 << items[i].category << " " << items[i].price
                 << " " << items[i].expiry << endl;
        }
    }

    void writeToFile(string filename) {
        ofstream fout(filename, ios::binary);
        for (auto &it : items) {
            fout.write((char*)&it, sizeof(GroceryItem));
        }
        fout.close();
        cout << "Data saved to " << filename << endl;
    }

    void readFromFile(string filename) {
        ifstream fin(filename, ios::binary);
        GroceryItem g;
        items.clear();
        while (fin.read((char*)&g, sizeof(GroceryItem))) {
            items.push_back(g);
        }
        fin.close();
    }

    vector<GroceryItem> getItems() { return items; }
    void makeNull() { items.clear(); }
    bool isEmpty() { return items.empty(); }
};

// ================= Program B: QUEUE =================
class GroceryQueue {
    vector<GroceryItem> q;

public:
    void enqueue(GroceryItem g) { q.push_back(g); }

    void dequeue() {
        if (q.empty()) cout << "Queue empty!\n";
        else q.erase(q.begin()); // remove first
    }

    void print() {
        if (q.empty()) { cout << "Queue empty!\n"; return; }
        for (int i = 0; i < (int)q.size(); i++) {
            cout << q[i].id << " " << q[i].name << " "
                 << q[i].category << " " << q[i].price << " "
                 << q[i].expiry << endl;
        }
    }

    int countByExpiry(string d) {
        int c = 0;
        for (auto &g : q) {
            if (string(g.expiry) <= d) c++;
        }
        return c;
    }

    void loadFromList(vector<GroceryItem> items) {
        q.clear();
        for (auto g : items) q.push_back(g);
    }

    void makeNull() { q.clear(); }
    bool isEmpty() { return q.empty(); }
};

// ================= Program C: STACK =================
class GroceryStack {
    vector<GroceryItem> s;

public:
    void push(GroceryItem g) { s.push_back(g); }

    void pop() {
        if (s.empty()) cout << "Stack empty!\n";
        else s.pop_back();
    }

    void print() {
        if (s.empty()) { cout << "Stack empty!\n"; return; }
        for (int i = (int)s.size()-1; i >= 0; i--) {
            cout << s[i].id << " " << s[i].name << " "
                 << s[i].category << " " << s[i].price << " "
                 << s[i].expiry << endl;
        }
    }

    void loadFromList(vector<GroceryItem> items) {
        s.clear();
        for (auto g : items) s.push_back(g);
    }

    void makeNull() { s.clear(); }
    bool isEmpty() { return s.empty(); }
};

// ================= MAIN PROGRAM =================
int main() {
    GroceryList gl;
    GroceryQueue gq;
    GroceryStack gs;

    string filename = "grocery.dat";
    int choice;

    do {
        cout << "\n===== MAIN MENU =====\n";
        cout << "1. Work with List (Program A)\n";
        cout << "2. Work with Queue (Program B)\n";
        cout << "3. Work with Stack (Program C)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int ch;
            do {
                cout << "\n--- LIST MENU ---\n";
                cout << "1. Insert Item\n2. Delete Item\n3. Search Item\n4. Print List\n5. Save to File\n6. Back\n";
                cout << "Enter choice: ";
                cin >> ch;

                if (ch == 1) {
                    GroceryItem g;
                    cout << "Enter id name category price expiry(YYYY-MM-DD): ";
                    cin >> g.id >> g.name >> g.category >> g.price >> g.expiry;
                    gl.insert(g);
                }
                else if (ch == 2) {
                    int pos; cout << "Enter position: "; cin >> pos;
                    gl.deleteItem(pos);
                }
                else if (ch == 3) {
                    int id; cout << "Enter id: "; cin >> id;
                    int pos = gl.search(id);
                    if (pos == -1) cout << "Not found!\n";
                    else cout << "Found at position " << pos << endl;
                }
                else if (ch == 4) {
                    gl.print();
                }
                else if (ch == 5) {
                    gl.writeToFile(filename);
                }
            } while (ch != 6);
        }

        else if (choice == 2) {
            gl.readFromFile(filename); // load from file
            gq.loadFromList(gl.getItems());
            cout << "\n--- QUEUE DATA ---\n";
            gq.print();

            string d;
            cout << "Enter expiry date (YYYY-MM-DD) to count: ";
            cin >> d;
            cout << "Items expiring before/equal to " << d << ": "
                 << gq.countByExpiry(d) << endl;
        }

        else if (choice == 3) {
            gl.readFromFile(filename); // load from file
            gs.loadFromList(gl.getItems());
            cout << "\n--- STACK DATA ---\n";
            gs.print();
        }

    } while (choice != 4);

    return 0;
}