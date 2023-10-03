//
// Created by Wojtek on 03.10.2023.
//

#ifndef SUDOKU_METHODSEXTENSION_H
#define SUDOKU_METHODSEXTENSION_H

#include <array>
#include <vector>

class MethodsExtension {
    static bool IsInSquare(std::array<std::array<int,9>,9> numbers, int y, int x, int k);
    static bool IsContained(std::vector<int> vec, const int& elem);

public:
    static std::array<std::array<std::vector<int>, 9>, 9> FindCandidates(std::array<std::array<int,9>,9> numbers);
};


#endif //SUDOKU_METHODSEXTENSION_H
