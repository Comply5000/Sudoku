#include "Sudoku.h"
#include <windows.h>

int main()
{
    ::ShowWindow(GetConsoleWindow(), SW_HIDE);
    Sudoku sudoku;
    while (sudoku.IsRunning())
    {
        sudoku.Update();
        sudoku.Render();
    }
    return 0;
}
