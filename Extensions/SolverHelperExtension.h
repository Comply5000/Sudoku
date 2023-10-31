//
// Created by Wojtek on 31.10.2023.
//

#ifndef SUDOKU_SOLVERHELPEREXTENSION_H
#define SUDOKU_SOLVERHELPEREXTENSION_H


#include <array>
#include <vector>

class SolverHelperExtension {
    static std::array<std::array<int, 9>, 9> _numbers;
    static std::vector<std::array<std::array<int, 9>, 9>> _solutions;

    static void Count();
    static bool Possible(int y, int x,int n);
    static bool ExistInSquare(int y, int x, int k);
public:
    static bool SolutionCount(std::array<std::array<int, 9>, 9> numbers);

};


#endif //SUDOKU_SOLVERHELPEREXTENSION_H
