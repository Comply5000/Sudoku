//
// Created by wojci on 17.10.2023.
//

#include "EnumsToStrings.h"

std::map<StructureType, std::string> EnumsToStrings::StructureTypes = {
        {StructureType::Row, "row"},
        {StructureType::Column, "column"},
        {StructureType::Square, "square"}
};

std::map<SolutionResultType, std::string> EnumsToStrings::SolutionResultType = {
        {SolutionResultType::Correct, ""},
        {SolutionResultType::NoSolution, "Error: No solution"},
        {SolutionResultType::ToManySolutions, "Error: Many solutions"}
};