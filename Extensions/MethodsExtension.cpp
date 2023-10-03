//
// Created by Wojtek on 03.10.2023.
//

#include "MethodsExtension.h"

std::array<std::array<std::vector<int>, 9>, 9> MethodsExtension::FindCandidates(std::array<std::array<int, 9>, 9> numbers)
{
    std::array<std::array<std::vector<int>, 9>, 9> candidates;

    for (int i = 0;i < 9;i++)
    {
        for (int j = 0;j < 9;j++)
        {
            if (numbers[i][j] != 0)
                candidates[i][j].push_back(10);
            else
            {
                for (int k = 1;k <= 9;k++)
                {
                    bool exist = false;
                    for (int x = 0;x < 9;x++)
                    {
                        if (k == numbers[i][x])
                        {
                            exist = true;
                            break;
                        }
                    }
                    for (int x = 0;x < 9;x++)
                    {
                        if (k == numbers[x][j])
                        {
                            exist = true;
                            break;
                        }
                    }
                    if (IsInSquare(numbers,i, j, k))
                        exist = true;

                    if (!exist)
                        candidates[i][j].push_back(k);
                }
            }
        }
    }
    return candidates;
}

bool MethodsExtension::IsInSquare(std::array<std::array<int,9>,9> numbers, int y, int x, int k) {
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
            if (numbers[i][j] == k)
                return true;
    return false;
}

bool MethodsExtension::IsContained(std::vector<int> vec, const int &elem) {
    bool result = false;
    for (auto& x : vec)
    {
        if (x == elem)
        {
            result = true;
            break;
        }
    }
    return result;
}
