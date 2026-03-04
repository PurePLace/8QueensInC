#include <stdio.h>
#include <stdbool.h>

#define N 8 // Размер доски (8x8)

// Доска 8 на 8(печать)
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            printf("%2d ", board[i][j]);
        printf("\n");
    }
    printf("\n");
}

// проверка, безопасно ли ставить ферзя на клетку (row, col)
bool isSafe(int board[N][N], int row, int col) {
    int i, j;

    // проверка все клетки слева в этом же ряду (горизонталь)
    for (i = 0; i < col; i++)
        if (board[row][i])
            return false;

    // проверка верхняя диагональ слева
    for (i = row, j = col; i >= 0 && j >= 0; i--, j--)
        if (board[i][j])
            return false;

    // проверяю нижняя диагональ слева
    for (i = row, j = col; j >= 0 && i < N; i++, j--)
        if (board[i][j])
            return false;

    // если ни одно из условий не нарушено, клетка безопасна
    return true;
}

// главная рекурсивная функция для поиска решений
bool solveNQueens(int board[N][N], int col) {
    //  если все ферзи расставлены (прошли все колонки)
    if (col >= N) {
        return true;
    }

    // ставлю ферзя в текущую колонку (col) на каждую строку (row)
    for (int i = 0; i < N; i++) {
        // безопасно ли ставить ферзя на клетку (i, col)
        if (isSafe(board, i, col)) {
            // ставлю ферзя (1)
            board[i][col] = 1;

            // рекурсивно пытаюсь расставить остальных ферзей в следующие колонки
            if (solveNQueens(board, col + 1)) {
                return true; // Если успешно, единица на клетку(т.е ферзь)
            }

            /* если расставить ферзей не получилось, то убираю ферзя
             и пробую следующую строку */
            board[i][col] = 0;
        }
    }

    /* Если ни в одной строке текущей колонки нельзя поставить ферзя,
    значит, предыдущее решение было ошибочным, возвращаю false*/
    return false;
}

int main() {
    // Пустая доска (все клетки = 0)
    int board[N][N] = {0};

    // поиск решения, начиная с первой колонки (col = 0)
    if (solveNQueens(board, 0) == true) {
        printf("The solution for 8 queens has been found.:\n");
        printBoard(board);
    } else {
        printf("No solution found.\n");
    }

    return 0;
}
