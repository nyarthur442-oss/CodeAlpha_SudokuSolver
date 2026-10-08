#include <iostream>
using namespace std;

const int N = 9;

// Function to print the Sudoku grid
void printGrid(int grid[N][N]) {
    cout << "\n-------------------------" << endl;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (col % 3 == 0) cout << "| ";
            cout << grid[row][col] << " ";
        }
        cout << "|" << endl;
        if ((row + 1) % 3 == 0) {
            cout << "-------------------------" << endl;
        }
    }
}

// Check if placing num at grid[row][col] is valid
// Sudoku rules: row, column, and 3x3 subgrid constraints
bool isValid(int grid[N][N], int row, int col, int num) {
    // Check row
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num)
            return false;
    }

    // Check column
    for (int x = 0; x < N; x++) {
        if (grid[x][col] == num)
            return false;
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }

    return true;
}

// Find empty cell (0 means empty)
bool findEmpty(int grid[N][N], int &row, int &col) {
    for (row = 0; row < N; row++) {
        for (col = 0; col < N; col++) {
            if (grid[row][col] == 0)
                return true;
        }
    }
    return false;
}

// Backtracking algorithm to solve Sudoku
bool solveSudoku(int grid[N][N]) {
    int row, col;

    // If no empty cell left, puzzle is solved
    if (!findEmpty(grid, row, col))
        return true;

    // Try numbers 1-9
    for (int num = 1; num <= 9; num++) {
        // Check if valid to place
        if (isValid(grid, row, col, num)) {
            grid[row][col] = num; // Place number

            // Recursively try to solve rest
            if (solveSudoku(grid))
                return true;

            // If placing num didn't lead to solution, backtrack
            grid[row][col] = 0;
        }
    }
    return false; // Trigger backtracking
}

int main() {
    // Represent Sudoku grid as 2D array (0 = empty cells)
    int grid[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    cout << "Original Sudoku Puzzle:" << endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        cout << "\nSolved Sudoku Puzzle:" << endl;
        printGrid(grid);
    } else {
        cout << "No solution exists!" << endl;
    }

    return 0;
}
