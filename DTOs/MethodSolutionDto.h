//
// Created by wojci on 10.10.2023.
//

#ifndef SUDOKU_METHODSOLUTIONDTO_H
#define SUDOKU_METHODSOLUTIONDTO_H


#include <array>
#include <vector>
#include "../Shared/Enums/StructureType.h"

///dto przechowujące informacje o metodzie rozwiązywania sudoku
struct MethodSolutionDto {
    std::array<std::array<std::vector<int>,9>,9> Candidates;
    std::array<std::array<std::vector<int>,9>,9> CandidatesToDelete;
    StructureType StructureType;

    bool operator==(const MethodSolutionDto& other) const {
        return Candidates == other.Candidates;
    }

    bool operator<(const MethodSolutionDto& other) const {
        return Candidates < other.Candidates;
    }
};


#endif //SUDOKU_METHODSOLUTIONDTO_H
