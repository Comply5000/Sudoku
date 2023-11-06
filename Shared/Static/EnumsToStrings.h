//
// Created by wojci on 17.10.2023.
//

#ifndef SUDOKU_ENUMSTOSTRINGS_H
#define SUDOKU_ENUMSTOSTRINGS_H


#include <map>
#include <string>
#include "../Enums/StructureType.h"
#include "../Enums/SolutionResultType.h"

///konwersja enum na string
class EnumsToStrings {
public:
    static std::map<StructureType, std::string> StructureTypes;
    static std::map<SolutionResultType, std::string> SolutionResultType;
};


#endif //SUDOKU_ENUMSTOSTRINGS_H
