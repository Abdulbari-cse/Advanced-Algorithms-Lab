#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cmath>

using namespace std;

typedef vector<vector<double>> Matrix;

Matrix readMatrix(const string &filename) {
    ifstream file(filename);
    Matrix matrix;
    string line;
    while (getline(file, line)) {
        vector<double> row;
        string num = "";
        for (char c : line) {
            if (isdigit(c) || c == '-' || c == '.') {
                num += c;
            } else if (!num.empty()) {
                row.push_back(stod(num));
                num = "";
            }
        }
        if (!num.empty()) row.push_back(stod(num));
        if (!row.empty()) matrix.push_back(row);
    }
    return matrix;
}


void printMatrix(const Matrix &A) {
    for (auto &row : A) {
        for (auto &val : row)
            cout << setw(10) << fixed << setprecision(2) << val << " ";
        cout << endl;
    }
}


Matrix transpose(const Matrix &A) {
    Matrix T(A[0].size(), vector<double>(A.size()));
    for (size_t i = 0; i < A.size(); ++i)
        for (size_t j = 0; j < A[0].size(); ++j)
            T[j][i] = A[i][j];
    return T;
}


double determinant(Matrix A) {
    int n = A.size();
    if (n == 1) return A[0][0];
    if (n == 2) return A[0][0]*A[1][1] - A[0][1]*A[1][0];

    double det = 0;
    for (int p = 0; p < n; p++) {
        Matrix subMat(n-1, vector<double>(n-1));
        for (int i = 1; i < n; i++) {
            int colIndex = 0;
            for (int j = 0; j < n; j++) {
                if (j == p) continue;
                subMat[i-1][colIndex++] = A[i][j];
            }
        }
        det += A[0][p] * pow(-1, p) * determinant(subMat);
    }
    return det;
}


Matrix cofactor(const Matrix &A) {
    int n = A.size();
    Matrix cof(n, vector<double>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            Matrix subMat(n-1, vector<double>(n-1));
            int r = 0;
            for (int x = 0; x < n; x++) {
                if (x == i) continue;
                int c = 0;
                for (int y = 0; y < n; y++) {
                    if (y == j) continue;
                    subMat[r][c++] = A[x][y];
                }
                r++;
            }
            cof[i][j] = pow(-1, i+j) * determinant(subMat);
        }
    }
    return cof;
}


Matrix inverse(const Matrix &A) {
    double det = determinant(A);
    int n = A.size();
    Matrix adj = transpose(cofactor(A));
    Matrix inv(n, vector<double>(n));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            inv[i][j] = adj[i][j] / det;
    return inv;
}


Matrix multiply(const Matrix &A, const Matrix &B) {
    int r1 = A.size(), c1 = A[0].size(), r2 = B.size(), c2 = B[0].size();
    Matrix C(r1, vector<double>(c2, 0));
    for (int i = 0; i < r1; i++)
        for (int j = 0; j < c2; j++)
            for (int k = 0; k < c1; k++)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}


void showOperations(const Matrix &A, const string &name) {
    cout << "\nMatrix " << name << ":" << endl;
    printMatrix(A);

    if (A.size() == A[0].size()) {
        double det = determinant(A);
        cout << "\nDeterminant |" << name << "| = " << det << endl;

        cout << "\nTranspose (" << name << "^T):" << endl;
        printMatrix(transpose(A));

        if (fabs(det) > 1e-9) {
            cout << "\nInverse (" << name << "^-1):" << endl;
            printMatrix(inverse(A));
        } else {
            cout << "\nMatrix " << name << " is NOT invertible (Determinant = 0)." << endl;
        }
    } else {
        cout << "\nMatrix " << name << " is not square — determinant/inverse not defined." << endl;
    }
}

int main() {
    Matrix A = readMatrix("Matrix_A.txt");
    Matrix B = readMatrix("Matrix_B.txt");

    cout << fixed << setprecision(2);


    showOperations(A, "A");
    showOperations(B, "B");


    if (A[0].size() == B.size()) {
        cout << "\nA × B result:" << endl;
        printMatrix(multiply(A, B));
    } else {
        cout << "\nA × B not possible (columns of A != rows of B)." << endl;
    }


    if (B[0].size() == A.size()) {
        cout << "\nB × A result:" << endl;
        printMatrix(multiply(B, A));
    } else {
        cout << "\nB × A not possible (columns of B != rows of A)." << endl;
    }

    return 0;
}
