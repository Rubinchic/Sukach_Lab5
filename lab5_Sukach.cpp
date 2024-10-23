#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Matrix;

Matrix add(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] + B[i][j];
    return C;
}

Matrix subtract(const Matrix &A, const Matrix &B) {
    int n = A.size();
    Matrix C(n, vector<int>(n));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            C[i][j] = A[i][j] - B[i][j];
    return C;
}

Matrix strassen(const Matrix &A, const Matrix &B) {
    int n = A.size();

    if (n == 1) {
        Matrix C(1, vector<int>(1));
        C[0][0] = A[0][0] * B[0][0];
        return C;
    }

    int newSize = n / 2;
    Matrix a11(newSize, vector<int>(newSize)), a12(newSize, vector<int>(newSize)),
           a21(newSize, vector<int>(newSize)), a22(newSize, vector<int>(newSize)),
           b11(newSize, vector<int>(newSize)), b12(newSize, vector<int>(newSize)),
           b21(newSize, vector<int>(newSize)), b22(newSize, vector<int>(newSize));

    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            a11[i][j] = A[i][j];
            a12[i][j] = A[i][j + newSize];
            a21[i][j] = A[i + newSize][j];
            a22[i][j] = A[i + newSize][j + newSize];

            b11[i][j] = B[i][j];
            b12[i][j] = B[i][j + newSize];
            b21[i][j] = B[i + newSize][j];
            b22[i][j] = B[i + newSize][j + newSize];
        }
    }

    Matrix p1 = strassen(a11, subtract(b12, b22));
    Matrix p2 = strassen(add(a11, a12), b22);
    Matrix p3 = strassen(add(a21, a22), b11);
    Matrix p4 = strassen(a22, subtract(b21, b11));
    Matrix p5 = strassen(add(a11, a22), add(b11, b22));
    Matrix p6 = strassen(subtract(a12, a22), add(b21, b22));
    Matrix p7 = strassen(subtract(a11, a21), add(b11, b12));

    Matrix c11 = add(subtract(add(p5, p4), p2), p6);
    Matrix c12 = add(p1, p2);
    Matrix c21 = add(p3, p4);
    Matrix c22 = subtract(subtract(add(p5, p1), p3), p7);

    Matrix C(n, vector<int>(n));
    for (int i = 0; i < newSize; ++i) {
        for (int j = 0; j < newSize; ++j) {
            C[i][j] = c11[i][j];
            C[i][j + newSize] = c12[i][j];
            C[i + newSize][j] = c21[i][j];
            C[i + newSize][j + newSize] = c22[i][j];
        }
    }

    return C;
}

void printMatrix(const Matrix &matrix) {
    for (const auto &row : matrix) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Write size of matrix (power 2): ";
    cin >> n;

    Matrix A(n, vector<int>(n));
    cout << "Write first matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> A[i][j];

    Matrix B(n, vector<int>(n));
    cout << "Write second matrix:\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> B[i][j];

    Matrix C = strassen(A, B);

    cout << "Result:\n";
    printMatrix(C);

    return 0;
}