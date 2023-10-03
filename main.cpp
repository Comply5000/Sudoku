#include "Sudoku.h"

int main()
{
    Sudoku sudoku;
    while (sudoku.IsRunning())
    {
        sudoku.Update();
        sudoku.Render();
    }
    return 0;
}
