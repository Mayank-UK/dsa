#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Strassen's matrix multiplication — divide-and-conquer that multiplies two
// n×n matrices with 7 (not 8) recursive sub-multiplications. Divide = split each
// matrix into 4 n/2×n/2 blocks; Conquer = 7 cleverly-combined block products
// (M1..M7); Combine = stitch M1..M7 back into the 4 result blocks.
// The 8→7 saving is what drops the exponent below 3.

// ─── Block matrix arithmetic over n×n (power-of-two) matrices ───
static void add(const vector<vector<int>>& A, const vector<vector<int>>& B,
                vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
}

static void sub(const vector<vector<int>>& A, const vector<vector<int>>& B,
                vector<vector<int>>& C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
}

// Strassen: writes A·B into C (n must be a power of two).
void strassen(const vector<vector<int>>& A, const vector<vector<int>>& B,
              vector<vector<int>>& C, int n) {
    if (n == 1) { C[0][0] = A[0][0] * B[0][0]; return; }   // base case

    int k = n / 2;
    vector<vector<int>> A11(k, vector<int>(k)), A12(k, vector<int>(k)),
                        A21(k, vector<int>(k)), A22(k, vector<int>(k));
    vector<vector<int>> B11(k, vector<int>(k)), B12(k, vector<int>(k)),
                        B21(k, vector<int>(k)), B22(k, vector<int>(k));
    vector<vector<int>> M1(k, vector<int>(k)), M2(k, vector<int>(k)),
                        M3(k, vector<int>(k)), M4(k, vector<int>(k)),
                        M5(k, vector<int>(k)), M6(k, vector<int>(k)),
                        M7(k, vector<int>(k));
    vector<vector<int>> tA(k, vector<int>(k)), tB(k, vector<int>(k));
    vector<vector<int>> C11(k, vector<int>(k)), C12(k, vector<int>(k)),
                        C21(k, vector<int>(k)), C22(k, vector<int>(k));

    // Divide: copy the four blocks of each matrix.
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            A11[i][j] = A[i][j];       A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];   A22[i][j] = A[i + k][j + k];
            B11[i][j] = B[i][j];       B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];   B22[i][j] = B[i + k][j + k];
        }
    }

    // Conquer: the seven block products.
    add(A11, A22, tA, k);  add(B11, B22, tB, k);  strassen(tA, tB, M1, k); // M1=(A11+A22)(B11+B22)
    add(A21, A22, tA, k);                          strassen(tA, B11, M2, k); // M2=(A21+A22)B11
    sub(B12, B22, tB, k);                          strassen(A11, tB, M3, k); // M3=A11(B12-B22)
    sub(B21, B11, tB, k);                          strassen(A22, tB, M4, k); // M4=A22(B21-B11)
    add(A11, A12, tA, k);                          strassen(tA, B22, M5, k); // M5=(A11+A12)B22
    sub(A21, A11, tA, k);  add(B11, B12, tB, k);  strassen(tA, tB, M6, k); // M6=(A21-A11)(B11+B12)
    sub(A12, A22, tA, k);  add(B21, B22, tB, k);  strassen(tA, tB, M7, k); // M7=(A12-A22)(B21+B22)

    // Combine: rebuild the four result blocks.
    add(M1, M4, tA, k);  sub(tA, M5, tB, k);  add(tB, M7, C11, k);        // C11=M1+M4-M5+M7
    add(M3, M5, C12, k);                                                // C12=M3+M5
    add(M2, M4, C21, k);                                                // C21=M2+M4
    sub(M1, M2, tA, k);  add(tA, M3, tB, k);  add(tB, M6, C22, k);       // C22=M1-M2+M3+M6

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            C[i][j]       = C11[i][j];
            C[i][j + k]   = C12[i][j];
            C[i + k][j]   = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

// ─── Demo helpers ───
static void printMatrix(const string& label, const vector<vector<int>>& M, int n) {
    cout << "  " << label << ":\n";
    for (int i = 0; i < n; ++i) {
        cout << "    ";
        for (int j = 0; j < n; ++j) cout << M[i][j] << "\t";
        cout << "\n";
    }
}

// Naive O(n^3) multiply — reference to verify Strassen against in the demo.
static vector<vector<int>> naiveMultiply(const vector<vector<int>>& A,
                                         const vector<vector<int>>& B, int n) {
    vector<vector<int>> C(n, vector<int>(n, 0));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
    return C;
}

static bool matricesEqual(const vector<vector<int>>& A, const vector<vector<int>>& B, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            if (A[i][j] != B[i][j]) return false;
    return true;
}

// Multiplies A·B via Strassen and verifies against the naive result.
static void runCase(const string& name,
                    const vector<vector<int>>& A,
                    const vector<vector<int>>& B, int n) {
    cout << "  " << name << " (" << n << "x" << n << ")\n";
    vector<vector<int>> C(n, vector<int>(n, 0));
    strassen(A, B, C, n);
    printMatrix("A x B (Strassen)", C, n);
    vector<vector<int>> ref = naiveMultiply(A, B, n);
    cout << "    Matches naive O(n^3) : " << (matricesEqual(C, ref, n) ? "Yes" : "No") << "\n\n";
}

int main() {
    cout << "============== Strassen Matrix Multiplication (Divide & Conquer) ==============\n\n";

    cout << "[Complexity]\n";
    cout << "  Time   : O(n^log2(7)) ~= O(n^2.807)   vs naive O(n^3); 7 not 8 sub-products\n";
    cout << "  Space  : O(n^2)                        block copies at each recursion level\n";
    cout << "  Notes  : wins only for large dense matrices; the constant overhead is high.\n\n";

    cout << "[Limitation] this implementation requires n to be a power of two (it splits\n";
    cout << "  matrices into exact n/2 blocks). General matrices are padded up to the next\n";
    cout << "  power of two; that padding/trimming is omitted here for clarity.\n\n";

    cout << "[Demo]\n";
    int n = 2;
    vector<vector<int>> A = {{1, 2}, {3, 4}};
    vector<vector<int>> B = {{5, 6}, {7, 8}};
    printMatrix("A", A, n);
    printMatrix("B", B, n);
    cout << "\n";
    runCase("product", A, B, n);

    cout << "[Edge Cases]\n";
    runCase("1x1 base case   ", {{3}}, {{7}}, 1);                  // base case: single multiply
    runCase("identity matrix ", {{1, 0}, {0, 1}}, {{9, 8}, {7, 6}}, 2);   // A·I style
    runCase("4x4 recursion   ",
            {{1, 2, 3, 4}, {5, 6, 7, 8}, {1, 1, 1, 1}, {0, 0, 0, 1}},
            {{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}, 4); // one full divide level
    cout << "\n";

    return 0;
}
