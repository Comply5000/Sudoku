//
// Created by wojci on 05.10.2023.
//

#ifndef SUDOKU_HELPERFUNCTIONSEXTENSION_H
#define SUDOKU_HELPERFUNCTIONSEXTENSION_H


#include <array>
#include <vector>

class HelperFunctionsExtension {
public:
    static bool IsInSquare(std::array<std::array<int,9>,9> numbers, int y, int x, int k);
    static bool IsContained(std::vector<int> vec, const int& elem);
};


#endif //SUDOKU_HELPERFUNCTIONSEXTENSION_H
