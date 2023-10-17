//
// Created by wojci on 05.10.2023.
//

#ifndef SUDOKU_HELPERFUNCTIONSEXTENSION_H
#define SUDOKU_HELPERFUNCTIONSEXTENSION_H


#include <array>
#include <vector>
#include <map>
#include <string>
#include "../Shared/Enums/MethodType.h"
#include "../Shared/Enums/StructureType.h"

class HelperFunctionsExtension {
public:
    static bool IsInSquare(std::array<std::array<int,9>,9> numbers, int y, int x, int k);
    static bool IsContained(std::vector<int> list, const int& elem);

    template <typename T>
    static std::string EnumToString(T value, const std::map<T, std::string>& enumToStringMap) {
        auto it = enumToStringMap.find(value);
        if (it != enumToStringMap.end()) {
            return it->second;
        }
        return "Unknown";
    }
};


#endif //SUDOKU_HELPERFUNCTIONSEXTENSION_H
