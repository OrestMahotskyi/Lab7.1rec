#include <iostream>
#include <iomanip>
#include <ctime>
using namespace std;

// Рекурсивна функція для генерації матриці випадкових чисел у заданому діапазоні
void CreateMatrixRecursive(int** matrix, int row, int col, const int rows, const int cols, const int low, const int high) {
    if (row >= rows) return;
    if (col < cols) {
        matrix[row][col] = low + rand() % (high - low + 1);
        CreateMatrixRecursive(matrix, row, col + 1, rows, cols, low, high);
    } else {
        CreateMatrixRecursive(matrix, row + 1, 0, rows, cols, low, high);
    }
}

// Рекурсивна функція для виведення матриці у вигляді таблиці
void PrintMatrixRecursive(int** matrix, int row, int col, const int rows, const int cols) {
    if (row >= rows) return;
    if (col < cols) {
        cout << setw(5) << matrix[row][col];
        PrintMatrixRecursive(matrix, row, col + 1, rows, cols);
    } else {
        cout << endl;
        PrintMatrixRecursive(matrix, row + 1, 0, rows, cols);
    }
}

// Рекурсивна функція для обчислення кількості та суми елементів за критерієм та заміни їх нулями
void CalculateAndReplaceRecursive(int** matrix, int row, int col, const int rows, const int cols, int& sum, int& count) {
    if (row >= rows) return;
    if (col < cols) {
        if ((matrix[row][col] % 2 != 0) || (matrix[row][col] >= 0)) {
            sum += matrix[row][col];
            count++;
            matrix[row][col] = 0;
        }
        CalculateAndReplaceRecursive(matrix, row, col + 1, rows, cols, sum, count);
    } else {
        CalculateAndReplaceRecursive(matrix, row + 1, 0, rows, cols, sum, count);
    }
}

// Рекурсивна функція для сортування рядків матриці за заданими ключами
void SortMatrixRecursive(int** matrix, int row, int cols, bool swapped) {
    if (row <= 0 || !swapped) return;

    bool newSwap = false;
    for (int j = 0; j < row; j++) {
        if ((matrix[j][0] > matrix[j + 1][0]) ||
            (matrix[j][0] == matrix[j + 1][0] && matrix[j][1] > matrix[j + 1][1]) ||
            (matrix[j][0] == matrix[j + 1][0] && matrix[j][1] == matrix[j + 1][1] && matrix[j][3] < matrix[j + 1][3])) {
            // Обмін рядків місцями
            for (int k = 0; k < cols; k++) {
                int temp = matrix[j][k];
                matrix[j][k] = matrix[j + 1][k];
                matrix[j + 1][k] = temp;
            }
            newSwap = true;
        }
    }
    SortMatrixRecursive(matrix, row - 1, cols, newSwap);
}

int main() {
    srand(time(0));

    const int rows = 7;
    const int cols = 6;
    const int low = -12;
    const int high = 23;

    // Створення матриці
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++)
        matrix[i] = new int[cols];

    CreateMatrixRecursive(matrix, 0, 0, rows, cols, low, high);

    cout << "Original Matrix:" << endl;
    PrintMatrixRecursive(matrix, 0, 0, rows, cols);

    // Виконання обчислень
    int sum = 0, count = 0;
    CalculateAndReplaceRecursive(matrix, 0, 0, rows, cols, sum, count);
    cout << "\nModified Matrix after Calculation:" << endl;
    PrintMatrixRecursive(matrix, 0, 0, rows, cols);
    cout << "\nSum of elements = " << sum << endl;
    cout << "Count of elements = " << count << endl;

    // Сортування матриці
    SortMatrixRecursive(matrix, rows - 1, cols, true);
    cout << "\nSorted Matrix:" << endl;
    PrintMatrixRecursive(matrix, 0, 0, rows, cols);

    // Видалення матриці з пам'яті
    for (int i = 0; i < rows; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
