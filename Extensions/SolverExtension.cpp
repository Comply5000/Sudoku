#include "SolverExtension.h"
#include <iostream>

std::array<std::array<int, 9>, 9> SolverExtension::_numbers = {};

std::array<std::array<int, 9>, 9> SolverExtension::SolveBoard(std::array<std::array<int, 9>, 9> numbers)
{
    _numbers = numbers;
    if (IsSolvable(_numbers))
    {
        return _numbers; // Zwróć rozwiązanie, jeśli istnieje.
    }
    else
    {
        return numbers; // Zwróć oryginalny stan planszy, jeśli sudoku jest nierozwiązywalne.
    }
}

bool SolverExtension::IsSolvable(std::array<std::array<int, 9>, 9> &numbers)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (numbers[i][j] == 0)
            {
                for (int k = 1; k <= 9; k++)
                {
                    numbers[i][j] = k;
                    if (IsValid(numbers, i, j) && IsSolvable(numbers))
                    {
                        return true;
                    }
                    numbers[i][j] = 0;
                }
                return false;
            }
        }
    }
    return true;
}

bool SolverExtension::IsValid(std::array<std::array<int, 9>, 9> &numbers, int row, int column)
{
    return (RowConstraint(numbers, row) && ColumnConstraint(numbers, column) && SubsectionConstraint(numbers, row, column));
}

bool SolverExtension::RowConstraint(std::array<std::array<int, 9>, 9> &numbers, int row)
{
    std::array<bool, 9> constraint{};

    for (int column = 0; column < 9; column++)
    {
        if (!CheckConstraint(numbers, row, column, constraint))
            return false;
    }

    return true;
}

bool SolverExtension::ColumnConstraint(std::array<std::array<int, 9>, 9> &numbers, int column)
{
    std::array<bool, 9> constraint{};

    for (int row = 0; row < 9; row++)
    {
        if (!CheckConstraint(numbers, row, column, constraint))
            return false;
    }

    return true;
}

bool SolverExtension::SubsectionConstraint(std::array<std::array<int, 9>, 9> &numbers, int row, int column)
{
    std::array<bool, 9> constraint{};
    int subsectionRowStart = (row / 3) * 3;
    int subsectionRowEnd = subsectionRowStart + 3;

    int subsectionColumnStart = (column / 3) * 3;
    int subsectionColumnEnd = subsectionColumnStart + 3;

    for (int r = subsectionRowStart; r < subsectionRowEnd; r++)
    {
        for (int c = subsectionColumnStart; c < subsectionColumnEnd; c++)
        {
            if (!CheckConstraint(numbers, r, c, constraint))
                return false;
        }
    }
    return true;
}

bool SolverExtension::CheckConstraint(std::array<std::array<int, 9>, 9> &numbers, int row, int column, std::array<bool, 9> &constraint)
{

    if (numbers[row][column] != 0)
    {
        if (!constraint[numbers[row][column] - 1])
        {
            constraint[numbers[row][column] - 1] = true;
        }
        else
        {
            return false;
        }
    }
    return true;
}
