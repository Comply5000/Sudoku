#ifndef SUDOKU_SOLVEREXTENSION_H
#define SUDOKU_SOLVEREXTENSION_H

#include <array>

class SolverExtension {
    static std::array<std::array<int, 9>, 9> _numbers;

    static bool IsSolvable(std::array<std::array<int, 9>, 9>& numbers);
    static bool IsValid(std::array<std::array<int, 9>, 9>& numbers, int row, int column);
    static bool RowConstraint(std::array<std::array<int, 9>, 9>& numbers, int row);
    static bool ColumnConstraint(std::array<std::array<int, 9>, 9>& numbers, int column);
    static bool SubsectionConstraint(std::array<std::array<int, 9>, 9>& numbers, int row, int column);
    static bool CheckConstraint(std::array<std::array<int, 9>, 9>& numbers, int row, int column, std::array<bool, 9>& constraint);

public:
    static std::array<std::array<int, 9>, 9> SolveBoard(std::array<std::array<int, 9>, 9> numbers);
};

#endif //SUDOKU_SOLVEREXTENSION_H
