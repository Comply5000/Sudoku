//
// Created by wojci on 10.10.2023.
//

#ifndef SUDOKU_METHODSOLUTIONDTO_H
#define SUDOKU_METHODSOLUTIONDTO_H


#include <array>
#include <vector>
#include "../Shared/Enums/BoardStructureType.h"

struct MethodSolutionDto {
    std::array<std::array<std::vector<int>,9>,9> Candidates;
    std::array<std::array<std::vector<int>,9>,9> CandidatesToDelete;
    BoardStructureType StructureType;
};


#endif //SUDOKU_METHODSOLUTIONDTO_H
