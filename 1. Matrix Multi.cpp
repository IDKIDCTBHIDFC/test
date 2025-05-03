#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <omp.h>

using namespace std;

vector<int> matrix_vector_mult_seq(const vector<vector<int>>& matrix, const vector<int>& vec){
    long long rows = matrix.size();
    long long cols = vec.size();
    vector<int> result(rows, 0);

    for (long long i = 0; i < rows; i++) {
        for (long long j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

vector<int> matrix_vector_mult_par(const vector<vector<int>>& matrix, const vector<int>& vec){
    long long rows = matrix.size();
    long long cols = vec.size();
    vector<int> result(rows, 0);

    #pragma omp parallel for
    for (long long i = 0; i < rows; i++) {
        for (long long j = 0; j < cols; j++) {
            result[i] += matrix[i][j] * vec[j];
        }
    }
    return result;
}

vector<vector<int>> matrix_matrix_mult_seq(const vector<vector<int>>& A, const vector<vector<int>>& B){
    long long rows = A.size();
    long long cols = B[0].size();
    long long inner_dim = B.size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));

    for (long long i = 0; i < rows; i++) {
        for (long long j = 0; j < cols; j++) {
            for (long long k = 0; k < inner_dim; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

vector<vector<int>> matrix_matrix_mult_par(const vector<vector<int>>& A, const vector<vector<int>>& B){
    long long rows = A.size();
    long long cols = B[0].size();
    long long inner_dim = B.size();
    vector<vector<int>> result(rows, vector<int>(cols, 0));

    #pragma omp parallel for collapse(2)
    for (long long i = 0; i < rows; i++) {
        for (long long j = 0; j < cols; j++) {
            for (long long k = 0; k < inner_dim; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

int main() {
    srand(time(0));

    const long long rows = 500, cols = 500;
    vector<vector<int>> matrix(rows, vector<int>(cols));
    for (long long i = 0; i < rows; i++) {
        for (long long j = 0; j < cols; j++) {
            matrix[i][j] = rand() % 100 + 1;
        }
    }

    vector<int> vec(cols);
    for (long long i = 0; i < cols; i++) {
        vec[i] = rand() % 100 + 1;
    }

    vector<vector<int>> matrix2(cols, vector<int>(rows));
    for (long long i = 0; i < cols; i++) {
        for (long long j = 0; j < rows; j++) {
            matrix2[i][j] = rand() % 100 + 1;
        }
    }

    while (true) {
        int choice;
        cout << "\nChoose an operation (0 to exit)"<<endl;
        cout << "1 - mat x vec Multiplication (seq)"<<endl;
        cout << "2 - mat x vec Multiplication (par)"<<endl;
        cout << "3 - mat x mat Multiplication (seq)"<<endl;
        cout << "4 - mat x mat Multiplication (par)"<<endl;
        cout << "0 - exit"
        cin >> choice;

        if (choice == 0) {
            cout << "exit"<<endl;
            break;
        }

        if (choice == 1) {
            vector<int> result = matrix_vector_mult_seq(matrix, vec);
            cout << "mat x vec Multiplication Done"<<endl;
        } 
        else if (choice == 2) {
            vector<int> result = matrix_vector_mult_par(matrix, vec);
            cout << "mat x vec Multiplication Done"<<endl;
        } 
        else if (choice == 3) {
            vector<vector<int>> result = matrix_matrix_mult_seq(matrix, matrix2);
            cout << "mat x mat Multiplication Done"<<endl;
        } 
        else if (choice == 4) {
            vector<vector<int>> result = matrix_matrix_mult_par(matrix, matrix2);
            cout << "mat x mat Multiplication Done"<<endl;
        } 
        else {
            cout << "Invalid choice"<<endl;
        }
    }
}
