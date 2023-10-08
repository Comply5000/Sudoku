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

class FileExtension {
    static bool SaveFileDialog(wchar_t szFileName[]);
    static bool OpenFileDialog(wchar_t szFileName[]);

public:
    static void SaveBoard(std::array<std::array<int,9>,9> numbers);
    static std::array<std::array<int,9>,9> LoadBoard(std::array<std::array<int, 9>, 9> oldNumbers);
};


#endif //SUDOKU_FILEEXTENSION_H
