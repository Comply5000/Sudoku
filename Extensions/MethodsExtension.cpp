//
// Created by Wojtek on 03.10.2023.
//

#include "MethodsExtension.h"
#include "HelperFunctionsExtension.h"

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
                    if (HelperFunctionsExtension::IsInSquare(numbers,i, j, k))
                        exist = true;

                    if (!exist)
                        candidates[i][j].push_back(k);
                }
            }
        }
    }
    return candidates;
}

