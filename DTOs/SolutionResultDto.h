//
// Created by Wojtek on 06.11.2023.
//

#ifndef SUDOKU_SOLUTIONRESULTDTO_H
#define SUDOKU_SOLUTIONRESULTDTO_H

#include <array>
#include "../Shared/Enums/SolutionResultType.h"

struct SolutionResultDto {
    std::array<std::array<int, 9>, 9> Numbers;
    SolutionResultType ResultType;
};

#endif //SUDOKU_SOLUTIONRESULTDTO_H
