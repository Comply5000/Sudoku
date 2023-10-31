//
// Created by wojci on 05.10.2023.
//

#ifndef SUDOKU_FILEEXTENSION_H
#define SUDOKU_FILEEXTENSION_H


#include <array>
#include <vector>
#include <string>
#include <fstream>
#include <windows.h>
#include <regex>

///statuczna klasa do obsługi zapisu i odczytu planszy
class FileExtension {
    static bool SaveFileDialog(wchar_t szFileName[]); ///otwarcie okna explorer do zapisania pliku txt
    static bool OpenFileDialog(wchar_t szFileName[]); ///otwarcie okna explorer do otworzenia pliku txt

public:
    static void SaveBoard(std::array<std::array<int,9>,9> numbers); ///zapisanie planszy w pliku
    static std::array<std::array<int,9>,9> LoadBoard(std::array<std::array<int, 9>, 9> oldNumbers); ///odczytanie planszy z pliku
};


#endif //SUDOKU_FILEEXTENSION_H
