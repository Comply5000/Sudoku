#ifndef SUDOKU_SOLVEREXTENSION_H
#define SUDOKU_SOLVEREXTENSION_H

#include <array>

//statyczna klasa do rozwiązania planszy sudoku
class SolverExtension {
    static std::array<std::array<int, 9>, 9> _numbers;

    static bool IsSolvable(std::array<std::array<int, 9>, 9>& numbers); //metoda rozwiązująca planszę metodą bruteforce (rekucencyjnie)
    static bool IsValid(std::array<std::array<int, 9>, 9>& numbers, int row, int column); //sprawdzenie czy dana plansza jest poprawna
    static bool RowConstraint(std::array<std::array<int, 9>, 9>& numbers, int row); //sprawdzanie poprawności dla wierszy
    static bool ColumnConstraint(std::array<std::array<int, 9>, 9>& numbers, int column);  //sprawdzanie poprawności dla kolumn
    static bool SubsectionConstraint(std::array<std::array<int, 9>, 9>& numbers, int row, int column);  //sprawdzanie poprawności dla kwadratów
    static bool CheckConstraint(std::array<std::array<int, 9>, 9>& numbers, int row, int column, std::array<bool, 9>& constraint); //ogólne sprawdzenie poprawności

public:
    static std::array<std::array<int, 9>, 9> SolveBoard(std::array<std::array<int, 9>, 9> numbers); //wywołanie IsSolvable i zwrócenie rozwiązanie planszy jeżeli dało się ją rozwiązać lub zwrócenie starej planszy
    static std::array<std::array<bool, 9>, 9> ValidateBoard(std::array<std::array<int, 9>, 9> numbers);
};

#endif //SUDOKU_SOLVEREXTENSION_H
