//
// Created by wojci on 05.10.2023.
//

#include "HelperFunctionsExtension.h"

bool HelperFunctionsExtension::IsInSquare(std::array<std::array<int,9>,9> numbers, int y, int x, int k) {
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

bool HelperFunctionsExtension::IsContained(std::vector<int> vec, const int &elem) {
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
