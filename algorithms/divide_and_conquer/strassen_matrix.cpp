#include <iostream>
#include <vector>

using namespace std;

// Function to add two matrices
void add(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Function to subtract two matrices
void sub(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's algorithm for matrix multiplication
void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B, vector<vector<int>>& C, int n) {
    // Base case: 1x1 matrix
    if (n == 1) {
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)), A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)), B21(k, vector<int>(k)), B22(k, vector<int>(k));
    vector<vector<int>> M1(k, vector<int>(k)), M2(k, vector<int>(k)), M3(k, vector<int>(k)), M4(k, vector<int>(k));
    vector<vector<int>> M5(k, vector<int>(k)), M6(k, vector<int>(k)), M7(k, vector<int>(k));
    vector<vector<int>> tempA(k, vector<int>(k)), tempB(k, vector<int>(k));
    vector<vector<int>> C11(k, vector<int>(k)), C12(k, vector<int>(k)), C21(k, vector<int>(k)), C22(k, vector<int>(k));

    // Divide matrices into 4 sub-matrices
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22) * (B11 + B22)
    add(A11, A22, tempA, k);
    add(B11, B22, tempB, k);
    strassen(tempA, tempB, M1, k);

    // M2 = (A21 + A22) * B11
    add(A21, A22, tempA, k);
    strassen(tempA, B11, M2, k);

    // M3 = A11 * (B12 - B22)
    sub(B12, B22, tempB, k);
    strassen(A11, tempB, M3, k);

    // M4 = A22 * (B21 - B11)
    sub(B21, B11, tempB, k);
    strassen(A22, tempB, M4, k);

    // M5 = (A11 + A12) * B22
    add(A11, A12, tempA, k);
    strassen(tempA, B22, M5, k);

    // M6 = (A21 - A11) * (B11 + B12)
    sub(A21, A11, tempA, k);
    add(B11, B12, tempB, k);
    strassen(tempA, tempB, M6, k);

    // M7 = (A12 - A22) * (B21 + B22)
    sub(A12, A22, tempA, k);
    add(B21, B22, tempB, k);
    strassen(tempA, tempB, M7, k);

    // C11 = M1 + M4 - M5 + M7
    add(M1, M4, tempA, k);
    sub(tempA, M5, tempB, k);
    add(tempB, M7, C11, k);

    // C12 = M3 + M5
    add(M3, M5, C12, k);

    // C21 = M2 + M4
    add(M2, M4, C21, k);

    // C22 = M1 - M2 + M3 + M6
    sub(M1, M2, tempA, k);
    add(tempA, M3, tempB, k);
    add(tempB, M6, C22, k);

    // Combine sub-matrices into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j] = C11[i][j];
            C[i][j + k] = C12[i][j];
            C[i + k][j] = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

int main() {
    int n = 2;
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};
    vector<vector<int>> C(n, vector<int>(n, 0));

    strassen(A, B, C, n);

    cout << "Resultant Matrix:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}