//
// Created by Wojtek on 31.10.2023.
//

#include "SolverHelperExtension.h"

std::array<std::array<int, 9>, 9> SolverHelperExtension::_numbers = {};
std::vector<std::array<std::array<int, 9>, 9>> SolverHelperExtension::_solutions = {};

void SolverHelperExtension::Count()
{
    if(_solutions.size() < 2)
    {
        for (int i = 0;i < 9;i++)
        {
            for (int j = 0;j < 9;j++)
            {
                if (_numbers[i][j] == 0)
                {
                    for (int n = 1;n < 10;n++)
                    {
                        if (Possible(i, j, n))
                        {
                            _numbers[i][j] = n;
                            Count();
                            _numbers[i][j] = 0;
                        }
                    }
                    return;
                }
            }
        }
        _solutions.push_back(_numbers);
    }
}

bool SolverHelperExtension::Possible(int y, int x, int n)
{
    for (int i = 0;i < 9;i++)
        if (_numbers[y][i] == n)
            return false;

    for (int i = 0;i < 9;i++)
        if (_numbers[i][x] == n)
            return false;

    if (ExistInSquare(y, x, n))
        return false;

    return true;
}

bool SolverHelperExtension::ExistInSquare(int y, int x, int k) {
    int a, b;
    if (x < 3)
        b = 0;
    else if (x >= 3 && x < 6)
        b = 3;
    else if (x >= 6)
        b = 6;

    if (y < 3)
        a = 0;
    else if (y >= 3 && y < 6)
        a = 3;
    else if (y >= 6)
        a = 6;

    for (int i = a;i < a + 3;i++)
        for (int j = b;j < b + 3;j++)
            if (_numbers[i][j] == k)
                return true;
    return false;
}

bool SolverHelperExtension::SolutionCount(std::array<std::array<int, 9>, 9> numbers)
{
    _solutions.clear();
    _numbers = numbers;
    Count();

    return _solutions.size() == 1;
}
