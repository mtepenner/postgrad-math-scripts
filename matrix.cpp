#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Function to print the matrix (useful for debugging)
void printMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= n; ++j) {
            cout << setw(10) << setprecision(4) << matrix[i][j] << " ";
            if (j == n - 1) cout << "| "; // Separator for the augmented column
        }
        cout << endl;
    }
    cout << endl;
}

// Function to solve the matrix using Gaussian Elimination
vector<double> solveMatrix(vector<vector<double>> matrix) {
    int n = matrix.size();

    // Step 1: Forward Elimination with Partial Pivoting
    for (int i = 0; i < n; ++i) {
        // Find the pivot (the largest absolute value in the current column)
        // This prevents division by zero and reduces rounding errors
        int pivotRow = i;
        for (int k = i + 1; k < n; ++k) {
            if (abs(matrix[k][i]) > abs(matrix[pivotRow][i])) {
                pivotRow = k;
            }
        }

        // Swap the current row with the pivot row
        if (pivotRow != i) {
            swap(matrix[i], matrix[pivotRow]);
        }

        // If the pivot is 0, the matrix is singular (no unique solution exists)
        if (abs(matrix[i][i]) < 1e-10) {
            cout << "Error: The matrix is singular or nearly singular. No unique solution exists." << endl;
            return {}; 
        }

        // Eliminate the entries below the pivot
        for (int k = i + 1; k < n; ++k) {
            double factor = matrix[k][i] / matrix[i][i];
            for (int j = i; j <= n; ++j) {
                matrix[k][j] -= factor * matrix[i][j];
            }
        }
    }

    // Step 2: Back Substitution
    // Now that the matrix is in upper triangular form, we solve from bottom to top
    vector<double> solution(n);
    for (int i = n - 1; i >= 0; --i) {
        double sum = matrix[i][n]; // Start with the augmented value
        for (int j = i + 1; j < n; ++j) {
            sum -= matrix[i][j] * solution[j]; // Subtract the known variables
        }
        solution[i] = sum / matrix[i][i]; // Divide by the coefficient of the current variable
    }

    return solution;
}

int main() {
    int n;
    cout << "Enter the number of variables (n): ";
    cin >> n;

    if (n < 1) {
        cout << "The number of variables must be at least 1." << endl;
        return 1;
    }

    // Create an n by (n+1) matrix to hold the coefficients and the constants
    vector<vector<double>> matrix(n, vector<double>(n + 1));

    cout << "Enter the augmented matrix row by row (coefficients followed by the constant term):" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Row " << i + 1 << ": ";
        for (int j = 0; j <= n; ++j) {
            cin >> matrix[i][j];
        }
    }

    cout << "\nInitial Augmented Matrix:\n";
    printMatrix(matrix);

    // Solve the matrix
    vector<double> solution = solveMatrix(matrix);

    // Print the results if a solution was found
    if (!solution.empty()) {
        cout << "Solution:\n";
        for (int i = 0; i < n; ++i) {
            // Clean up tiny floating point errors
            if (abs(solution[i]) < 1e-9) solution[i] = 0.0;
            cout << "x" << i + 1 << " = " << solution[i] << endl;
        }
    }

    return 0;
}
