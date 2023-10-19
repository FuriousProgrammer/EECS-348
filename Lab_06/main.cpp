#include <iostream>
using std::cout;
using std::endl;

#include <iomanip>
using std::setw;

#include <fstream>
using std::ifstream;

#include <string>
using std::to_string;

#define MAX_DIM 100

// 1. Read values from a file into a matrix
int matrix_ReadDataFromFile( int (&A)[MAX_DIM][MAX_DIM], int (&B)[MAX_DIM][MAX_DIM] );
// 2. Print a matrix
void matrix_Print( const int N, const int matrix[MAX_DIM][MAX_DIM] );
// 3. Add two matrices and place the result in a third matrix
void matrix_Add( int N, int A[MAX_DIM][MAX_DIM], int B[MAX_DIM][MAX_DIM], int (&result)[MAX_DIM][MAX_DIM] );
// 4. Multiply two matrices and place the result in a third matrix
void matrix_Mul( int N, int A[MAX_DIM][MAX_DIM], int B[MAX_DIM][MAX_DIM], int (&result)[MAX_DIM][MAX_DIM] );
// 5. Subtract the second matrix from the first matrix and place the result in a third matrix
void matrix_Sub( int N, int A[MAX_DIM][MAX_DIM], int B[MAX_DIM][MAX_DIM], int (&result)[MAX_DIM][MAX_DIM] );


int main() {
    int matrix_A[MAX_DIM][MAX_DIM];
    int matrix_B[MAX_DIM][MAX_DIM];
    int result[MAX_DIM][MAX_DIM];

    int N = matrix_ReadDataFromFile( matrix_A, matrix_B );

    cout << "Adam Albee\n"
         << "2888458\n"
         << "Lab #6: Matrix manipulation" << endl;

    cout << "\nMatrix A:" << endl;
    matrix_Print( N, matrix_A );

    cout << "\nMatrix B:" << endl;
    matrix_Print( N, matrix_B );

    cout << "\nMatrix Sum (A + B):" << endl;
    matrix_Add( N, matrix_A, matrix_B, result );
    matrix_Print( N, result );

    cout << "\nMatrix Product (A * B):" << endl;
    matrix_Mul( N, matrix_A, matrix_B, result );
    matrix_Print( N, result );

    cout << "\nMatrix Difference (A - B):" << endl;
    matrix_Sub( N, matrix_A, matrix_B, result );
    matrix_Print( N, result );

    return 0;
}

// reads from `matrix_input.txt`
// reads two subsequence NxN matrices into `matrix_A` and `matrix_B`
int // returns N
matrix_ReadDataFromFile(
    int (&matrix_A)[MAX_DIM][MAX_DIM],
    int (&matrix_B)[MAX_DIM][MAX_DIM]
) {
    ifstream file("matrix_input.txt");

    int N;
    file >> N;

    for ( int y = 0; y < N; ++y ) {
        for ( int x = 0; x < N; ++x ) {
            file >> matrix_A[y][x];
        }
    }

    for ( int y = 0; y < N; ++y ) {
        for ( int x = 0; x < N; ++x ) {
            file >> matrix_B[y][x];
        }
    }

    return N;
}

// print an NxN matrix
void // no return
matrix_Print(
    const int N,
    const int matrix[MAX_DIM][MAX_DIM]
) {
    // find the length of the "longest" number in each column
    int maxcols[N] = {0};
    for ( int x = 0; x < N; ++x ) {
        // TODO: find a better way to compute the length of numbers?
        for ( int y = 0; y < N; ++y ) {
            int len = to_string(matrix[y][x]).length();
            if ( len > maxcols[x] ) {
                maxcols[x] = len;
            }
        }
    }

    // TODO: cache `to_string` results to save time printing here?
    // print matrix!
    for ( int y = 0; y < N; ++y ) {
        for ( int x = 0; x < N; ++x ) {
            cout << setw(maxcols[x]) << matrix[y][x] << " ";
        }
        cout << endl;
    }
}

// add two NxN matrices
void // no return
matrix_Add(
    int N,
    int A[MAX_DIM][MAX_DIM], int B[MAX_DIM][MAX_DIM],
    int (&result)[MAX_DIM][MAX_DIM]
) {
    for ( int y = 0; y < N; ++y ) {
        for ( int x = 0; x < N; ++x ) {
            result[y][x] = A[y][x] + B[y][x];
        }
    }
}

// multiply two NxN matrices
void // no return
matrix_Mul(
    int N,
    int A[MAX_DIM][MAX_DIM], int B[MAX_DIM][MAX_DIM],
    int (&result)[MAX_DIM][MAX_DIM]
) {
    for ( int y = 0; y < N; ++y ) {
        for ( int x = 0; x < N; ++x ) {
            int sum = 0;
            for ( int k = 0; k < N; ++k ) {
                sum += A[y][k] * B[k][x];
            }
            result[y][x] = sum;
        }
    }
}

// subtract two NxN matrices
void // no return
matrix_Sub(
    int N,
    int A[MAX_DIM][MAX_DIM], int B[MAX_DIM][MAX_DIM],
    int (&result)[MAX_DIM][MAX_DIM]
) {
    for ( int y = 0; y < N; ++y ) {
        for ( int x = 0; x < N; ++x ) {
            result[y][x] = A[y][x] - B[y][x];
        }
    }
}

