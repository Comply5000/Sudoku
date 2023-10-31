//
// Created by wojci on 17.10.2023.
//

#ifndef SUDOKU_ENUMSTOSTRINGS_H
#define SUDOKU_ENUMSTOSTRINGS_H


#include <map>
#include <string>
#include "../Enums/StructureType.h"

///konwersja enum na string
class EnumsToStrings {
public:
    static std::map<StructureType, std::string> StructureTypes;
};


#endif //SUDOKU_ENUMSTOSTRINGS_H
