#include "SolverExtension.h"
#include <iostream>

std::array<std::array<int, 9>, 9> SolverExtension::_numbers = {};
std::vector<std::array<std::array<int, 9>, 9>> SolverExtension::_solutions = {};

std::array<std::array<int, 9>, 9> SolverExtension::SolveBoard(std::array<std::array<int, 9>, 9> numbers)
{
    _solutions.clear();
    _numbers = numbers;
    IsSolvable();
    if (_solutions.size() == 1)
    {
        return _solutions[0];
    }
    else
    {
        return numbers; // Zwróć oryginalny stan planszy, jeśli sudoku jest nierozwiązywalne.
    }
}

void SolverExtension::IsSolvable()
{
    if(_solutions.size() < 2)
    {
        for (int i = 0; i < 9; i++)
        {
            for (int j = 0; j < 9; j++)
            {
                if (_numbers[i][j] == 0)
                {
                    for (int k = 1; k <= 9; k++)
                    {
                        _numbers[i][j] = k;
                        if (IsValid(_numbers, i, j) )
                        {
                            IsSolvable();
                        }
                        _numbers[i][j] = 0;
                    }
                    return;
                }
            }
        }
        _solutions.push_back(_numbers);
    }
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

std::array<std::array<bool, 9>, 9> SolverExtension::ValidateBoard(std::array<std::array<int, 9>, 9> numbers)
{
    std::array<std::array<bool, 9>, 9> invalidNumbers {};

    for(int row = 0;row < 9;row++)
    {
        for(int col = 0;col < 9;col++)
        {
            if(numbers[row][col] != 0)
            {
                for(int a = 0;a<9;a++)
                {
                    if(numbers[row][col] == numbers[row][a] && col != a)
                    {
                        invalidNumbers[row][col] = true;
                        invalidNumbers[row][a] = true;
                    }
                }
            }
        }
    }

    for(int row = 0;row < 9;row++)
    {
        for(int col = 0;col < 9;col++)
        {
            if(numbers[row][col] != 0)
            {
                for(int a = 0;a<9;a++)
                {
                    if(numbers[row][col] == numbers[a][col] && row != a)
                    {
                        invalidNumbers[row][col] = true;
                        invalidNumbers[a][col] = true;
                    }
                }
            }
        }
    }

    for(int y = 0; y <= 6; y+=3)
    {
        for(int x = 0;x <= 6; x+=3)
        {
            for(int row = y; row < y + 3; row++)
            {
                for(int col = x; col < x + 3; col++)
                {
                    if(numbers[row][col] != 0)
                    {
                        for(int a = y; a < y + 3; a++)
                        {
                            for(int b = x; b < x + 3; b++)
                            {
                                if(numbers[row][col] == numbers[a][b] && row != a && col != b)
                                {
                                    invalidNumbers[row][col] = true;
                                    invalidNumbers[a][b] = true;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return invalidNumbers;
}
