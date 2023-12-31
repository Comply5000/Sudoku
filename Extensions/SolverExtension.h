#ifndef SUDOKU_SOLVEREXTENSION_H
#define SUDOKU_SOLVEREXTENSION_H

#include <array>
#include <vector>
#include "../DTOs/SolutionResultDto.h"

///statyczna klasa do rozwiązania planszy sudoku
class SolverExtension {
    static std::array<std::array<int, 9>, 9> _numbers;
    static std::vector<std::array<std::array<int, 9>, 9>> _solutions;

    static void Solve(); ///metoda rozwiązująca planszę metodą bruteforce (rekucencyjnie)
    static bool IsValid(std::array<std::array<int, 9>, 9>& numbers, int row, int column); ///sprawdzenie czy dana plansza jest poprawna
    static bool RowConstraint(std::array<std::array<int, 9>, 9>& numbers, int row); ///sprawdzanie poprawności dla wierszy
    static bool ColumnConstraint(std::array<std::array<int, 9>, 9>& numbers, int column);  ///sprawdzanie poprawności dla kolumn
    static bool SubsectionConstraint(std::array<std::array<int, 9>, 9>& numbers, int row, int column);  ///sprawdzanie poprawności dla kwadratów
    static bool CheckConstraint(std::array<std::array<int, 9>, 9>& numbers, int row, int column, std::array<bool, 9>& constraint); ///ogólne sprawdzenie poprawności

public:
    static SolutionResultDto SolveBoard(std::array<std::array<int, 9>, 9> numbers); ///wywołanie Solve i zwrócenie rozwiązanie planszy jeżeli dało się ją rozwiązać lub zwrócenie starej planszy
    static std::array<std::array<bool, 9>, 9> ValidateBoard(std::array<std::array<int, 9>, 9> numbers);
};

#endif //SUDOKU_SOLVEREXTENSION_H
